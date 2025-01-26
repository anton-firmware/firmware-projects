/** \file
 *
 * Implementation for HAL Serial peripheral.
 * 
 * \warning The current implementation only works for SERCOM[0].
 */

#include <stdbool.h>

#include "hal_serial.h"
#include "sam.h"

#define F_REF 1000000 /* Reference frequency. Unused at the moment due to floating point library. */
#define S     16      /* Samples per bit. Unused at the moment due to floating point library. */

#define BAUD_REG_4800 60503u
#define BAUD_REG_9600 55469u
#define BAUD_REG_115200 0u /* Unused at current reference frequency.*/

static volatile bool sercom_usart_enabled;

static volatile uint8_t tx_len = 0;
static const volatile uint8_t *tx_pointer;

static hal_serial_read_cb_t read_callback;
static hal_serial_write_cb_t write_callback;

/** Wait for syncronisation after software reset of the SERCOM peripheral.
 *  
 * See page 451 - Atmel SAMD11 reference manual.
 * See page 472, 25.8.9, Synchronization Busy register - Atmel SAMD11 reference manual.
 * 
 * This is required due to the asynchronicity between CLK_SERCOMx_APB and GCLK_SERCOMx_CORE.
 */
static inline void wait_for_sercom_sync_swrst(void)
{
    while (SERCOM1->USART.SYNCBUSY.reg & SERCOM_USART_SYNCBUSY_SWRST);
}

/** Wait for syncronisation after enabling the SERCOM peripheral. */
static inline void wait_for_sercom_sync_enable(void)
{
    while (SERCOM1->USART.SYNCBUSY.reg & SERCOM_USART_SYNCBUSY_ENABLE);
}

/** Wait for syncronisation after modifying CTRLB register. */
static inline void wait_for_sercom_sync_ctrl_b(void)
{
    while (SERCOM1->USART.SYNCBUSY.reg & SERCOM_USART_SYNCBUSY_CTRLB);
}

/** Helper function to set up the clock source for the SERCOM1 peripheral.
 * 
 * In order to set a generic clock, we do a 16 bit write of the configurations 
 * and the ID, see page 99 of ATSAMD11 reference manual.
 */
static inline void setup_sercom_1_gclk(void)
{
    uint16_t clk_ctl_reg_value = 0;

    /* Set the SERCOM1 core clock to be Generic Clock Generator 0 (Internal 8MHz oscilator). 
     * Note: On reset, the OSC8M is fed through a divide by 8 step, so this clock is actually 1MHz. 
     */
    clk_ctl_reg_value |= (GCLK_CLKCTRL_ID_SERCOM1_CORE | GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0);

    GCLK->CLKCTRL.reg = clk_ctl_reg_value; 

    /* Wait for syncronisation. */
    while (GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY);
}

#if 0
/** Helper function to calculate the value of the SERCOM BAUD register.
 * 
 * See page 434 ATSAMD11 reference manual for baud rate calulcation.
 * BAUD = 65,536 * (1 - (S * F_BAUD)/F_REF)
 * 
 * S - Number of samples per bit (16, 8, or 3).
 * F_BAUD - Baud rate.
 * F_REF - Reference frequency.
 * 
 * \param[in] baud_rate The baud rate.
 * 
 * \return The 16-bit BAUD rate register value.
 */
static inline uint16_t calculate_baud_register(uint32_t baud_rate)
{
    return (uint16_t)(65536.0f * (1.0f - (float)(S) * ((float)baud_rate / (float)F_REF)));
}
#endif

/** ISR for the SERCOM1 peripheral. */
void SERCOM1_Handler(void)
{
	uint8_t interrupt_status = SERCOM1->USART.INTFLAG.reg;
	
    if (interrupt_status & (SERCOM_USART_INTFLAG_DRE | SERCOM_USART_INTFLAG_TXC))
    {
        if (tx_len > 0)
        {
            SERCOM1->USART.DATA.reg = *tx_pointer++;
            tx_len--;
			SERCOM1->USART.INTFLAG.reg = (SERCOM_USART_INTFLAG_TXC | SERCOM_USART_INTFLAG_DRE);
        }
        else 
        {
            /* We've transmitted all the data, turn off TX interrupts for now. */
            SERCOM1->USART.INTENCLR.reg = (SERCOM_USART_INTENCLR_TXC | SERCOM_USART_INTFLAG_DRE);
        }
    }

    if (interrupt_status & SERCOM_USART_INTFLAG_RXC)
    {
		const uint8_t byte = SERCOM1->USART.DATA.reg;
        read_callback(byte);
    }

}

hal_result_t hal_serial_init(hal_serial_init_t *init_struct)
{
    hal_result_t result = HAL_ERROR_PARAM_ERROR;

    if (!init_struct)
    {
        /* Do nothing, invalid init structure. */
    }
    else if (sercom_usart_enabled)
    {
        /* Trying to initialise already initialised USART. */
        result = HAL_ERROR_REJECTED;
    }
    else 
    {
        setup_sercom_1_gclk();

        /* RX on SERCOM pad 1. */
        SERCOM1->USART.CTRLA.reg |= SERCOM_USART_CTRLA_RXPO(0x1);

        /* TX on SERCOM pad 0. */
        SERCOM1->USART.CTRLA.reg |= SERCOM_USART_CTRLA_TXPO(0x0);

        /* USART with internal clock. */
        SERCOM1->USART.CTRLA.reg |= SERCOM_USART_CTRLA_MODE(0x1);

        /* Transmit LSB first. */
        SERCOM1->USART.CTRLA.reg |= SERCOM_USART_CTRLA_DORD;

        switch (init_struct->mode)
        {
            case HAL_SERIAL_MODE_RX:
                SERCOM1->USART.CTRLB.reg |= SERCOM_USART_CTRLB_RXEN;
                break;
            case HAL_SERIAL_MODE_TX:
                SERCOM1->USART.CTRLB.reg |= SERCOM_USART_CTRLB_TXEN;
                break;
            case HAL_SERIAL_MODE_RX_TX:
                SERCOM1->USART.CTRLB.reg |= (SERCOM_USART_CTRLB_TXEN | SERCOM_USART_CTRLB_RXEN);
                break;
            default:
                /* Cry, invalid USART mode. */
                break;
        }

        switch (init_struct->stop_bits)
        {
            case HAL_SERIAL_STOP_BITS_ONE:
                SERCOM1->USART.CTRLB.reg &= ~SERCOM_USART_CTRLB_SBMODE;
                break;
            case HAL_SERIAL_STOP_BITS_TWO:
                SERCOM1->USART.CTRLB.reg |= SERCOM_USART_CTRLB_SBMODE;
                break;
            default:
                /* Cry, invalid stop bits. */
                break;
        }

        /* This driver currently only supports even parity. */
        switch (init_struct->parity_bits)
        {
            case HAL_SERIAL_PARITY_BITS_NONE:
                SERCOM1->USART.CTRLA.reg &= ~SERCOM_USART_CTRLA_FORM(0x1);
                break;
            case HAL_SERIAL_PARITY_BITS_ONE:
                /* FORM 0x1 = USART frame with parity, see Table 25-6, ATSAMD11 reference manual.*/
                SERCOM1->USART.CTRLA.reg |= SERCOM_USART_CTRLA_FORM(0x1);
                break;
            default:
                /* Cry, invalid parity bits. */
                break;
        }

        switch (init_struct->baud_rate)
        {
            // TODO: Precalulcate these values because the floating point library is FUCKING MASSIVE

            case HAL_SERIAL_BAUD_RATE_4800:
                SERCOM1->USART.BAUD.reg = BAUD_REG_4800;
                break;
            case HAL_SERIAL_BAUD_RATE_9600:
                SERCOM1->USART.BAUD.reg = BAUD_REG_9600;
                break;
            /* TODO: Change reference freq to make 115200 usable. */
            case HAL_SERIAL_BAUD_RATE_115200:
            default:
                /* Cry, invalid baud rate. */
                break;
        }
        
        if (init_struct->read_event_cb)
        {
            read_callback = init_struct->read_event_cb;
            SERCOM1->USART.INTENSET.reg = SERCOM_USART_INTENSET_RXC;
        }

        if (init_struct->write_event_cb)
        {
            write_callback = init_struct->write_event_cb;
        }

        SERCOM1->USART.CTRLA.reg |= SERCOM_USART_CTRLA_ENABLE;

        wait_for_sercom_sync_enable();

        /* Enable interrupts. */
        NVIC_EnableIRQ(SERCOM1_IRQn);

        sercom_usart_enabled = true;
		
		result = HAL_SUCCESS;
    }

    return result;
}

hal_result_t hal_serial_teardown()
{
    hal_result_t result = HAL_ERROR_REJECTED;

    if (!sercom_usart_enabled)
    {
        /* Do nothing, USART not initialised. */
    }
    else
    {
        /* Reset the SERCOM back to normal state, disable USART. */
        SERCOM1->USART.CTRLA.reg |= SERCOM_USART_CTRLA_SWRST;
        
        wait_for_sercom_sync_swrst();
		
		result = HAL_SUCCESS;
    }
	
	return result;
}

hal_result_t hal_serial_clock_init()
{
    /* Enable APB clock for SERCOM1. */
    PM->APBCMASK.reg |= PM_APBCMASK_SERCOM1;

    return HAL_SUCCESS;
}

hal_result_t hal_serial_clock_teardown()
{
    /* Disable APB clock for SERCOM1. */
    PM->APBCMASK.reg &= ~PM_APBCMASK_SERCOM1;

    return HAL_SUCCESS;    
}

hal_result_t hal_serial_transmit_blocking(const uint8_t *tx, const uint8_t len)
{
    hal_result_t result = HAL_ERROR_REJECTED;

    if (!sercom_usart_enabled)
    {
        /* Do nothing, peripheral not enabled. */
    }
    else if (!tx)
    {
        /* Invalid tx pointer. */
        result = HAL_ERROR_PARAM_ERROR;
    }
    else if (len == 0)
    {
        /* Invalid transmit length. */
        result = HAL_ERROR_PARAM_ERROR;
    }
    else 
    {
        for (uint8_t i = 0; i < len; i++)
        {
            SERCOM1->USART.DATA.reg = *tx++;

            while (SERCOM1->USART.INTFLAG.bit.TXC == 0)
            {
                /* Do nothing, wait for transmit flag to be set. */
            }

            SERCOM1->USART.INTFLAG.reg |= (SERCOM_USART_INTFLAG_TXC | SERCOM_USART_INTFLAG_DRE);
        }
    }

    return result;
}

hal_result_t hal_serial_receive_blocking(uint8_t *rx, const uint8_t len)
{
    hal_result_t result = HAL_ERROR_REJECTED;

    if (!sercom_usart_enabled)
    {
        /* Do nothing, peripheral not enabled. */
    }
    else if (!rx)
    {
        /* Invalid tx pointer. */
        result = HAL_ERROR_PARAM_ERROR;
    }
    else if (len == 0)
    {
        /* Invalid transmit length. */
        result = HAL_ERROR_PARAM_ERROR;
    }
    else 
    {
        for (uint8_t i = 0; i < len; i++)
        {
            while (SERCOM1->USART.INTFLAG.bit.RXC == 0)
            {
                /* Do nothing, wait for receive flag to be set. */
            }

            *rx++ = SERCOM1->USART.DATA.reg;
        }
    }

    return result;
}

hal_result_t hal_serial_transmit_non_blocking(const uint8_t *tx, const uint8_t len)
{
    hal_result_t result = HAL_ERROR_REJECTED;

    if (!sercom_usart_enabled)
    {
        /* Do nothing, peripheral not enabled. */
    }
    else if (tx == 0)
    {
        /* Invalid tx pointer. */
        result = HAL_ERROR_PARAM_ERROR;
    }
    else if (len == 0)
    {
        /* Invalid transmit length. */
        result = HAL_ERROR_PARAM_ERROR;
    }
    else 
    {
        tx_len = len;
        tx_pointer = tx;

        SERCOM1->USART.INTENSET.reg = (SERCOM_USART_INTFLAG_TXC | SERCOM_USART_INTFLAG_DRE);
    }

    return result;
}

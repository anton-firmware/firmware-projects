# Define tools
ARM_GCC := arm-none-eabi-gcc.exe
ARM_LIB := arm-none-eabi-ar.exe

# Tempoary directory
TMP_DIR := tmp

# Paths
HAL_PATH                         := hal/inc
HAL_PATH_PERIPHERALS             := $(HAL_PATH)/peripherals/
HAL_PATH_CORE                    := $(HAL_PATH)/core/
ATSAMD11D14_PACK_INC             := packs/Atmel.SAMD11_DFP.1.1.81/include/
CMSIS_5_INC                      := packs/cmsis5/CMSIS/Core/Include

# Source Files
ATSAMD11D14_PERIPHERAL_SOURCES   := $(wildcard atsamd11d14/peripherals/*.c)
ATSAMD11D14_CORE_SOURCES         := $(wildcard atsamd11d14/core/*.c)

# Compiler Flags
CPU                              := cortex-m0plus
DEBUG_FLAGS 				     := -gdwarf-3 -g3
COMMON_FLAGS                     := -mcpu=$(CPU) $(DEBUG_FLAGS) -c
INCLUDES                         := -I$(HAL_PATH) -I$(HAL_PATH_PERIPHERALS) -I$(HAL_PATH_CORE) -I$(ATSAMD11D14_PACK_INC) -I$(CMSIS_5_INC)

ATSAMD11D14AS                    := __SAMD11D14AS__
ATSAMD11D14AM                    := __SAMD11D14AM__

OBJECTS_ATSAMD11D14AS_PERIPH     := $(patsubst %.c,%.atsamd11d14as.o,$(ATSAMD11D14_PERIPHERAL_SOURCES))
OBJECTS_ATSAMD11D14AS_CORE       := $(patsubst %.c,%.atsamd11d14as.o,$(ATSAMD11D14_CORE_SOURCES))
OBJECTS_ATSAMD11D14AM_PERIPH     := $(patsubst %.c,%.atsamd11d14am.o,$(ATSAMD11D14_PERIPHERAL_SOURCES))
OBJECTS_ATSAMD11D14AM_CORE       := $(patsubst %.c,%.atsamd11d14am.o,$(ATSAMD11D14_CORE_SOURCES))

LIB_NAME_ATSAMD11D14AS	         := libATSAMD11D14AS.a
LIB_NAME_ATSAMD11D14AM	         := libATSAMD11D14AM.a

clean:
	rm *.a

# Pattern rules for compiling .c to .o for each MCU
%.atsamd11d14as.o: %.c
	$(ARM_GCC) $(COMMON_FLAGS) $(INCLUDES) -D$(ATSAMD11D14AS) -o $@ $<
	mv $@ $(TMP_DIR)

%.atsamd11d14am.o: %.c
	$(ARM_GCC) $(COMMON_FLAGS) $(INCLUDES) -D$(ATSAMD11D14AM) -o $@ $<
	mv $@ $(TMP_DIR)

atsamd11d14as_lib: $(OBJECTS_ATSAMD11D14AS_PERIPH) $(OBJECTS_ATSAMD11D14AS_CORE)
	$(ARM_LIB) -rc $(TMP_DIR)/$(LIB_NAME_ATSAMD11D14AS) $(TMP_DIR)/*.o

atsamd11d14am_lib: $(OBJECTS_ATSAMD11D14AM_PERIPH) $(OBJECTS_ATSAMD11D14AM_CORE)
	$(ARM_LIB) -rc $(TMP_DIR)/$(LIB_NAME_ATSAMD11D14AM) $(TMP_DIR)/*.o

all: atsamd11d14am_lib atsamd11d14as_lib
	rm $(TMP_DIR)/hal_*

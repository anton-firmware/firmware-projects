#ifndef DISPLAY_EDITOR_H
#define DISPLAY_EDITOR_H

#include "display_control.h"

#define MAX_FRAME_COUNT   12u
#define DISPLAY_MAGIC     0xBEEFCAFE
#define DISPLAY_VERSION   0x00000001

typedef struct display_frames
{
    display_led_state_t frames[MAX_FRAME_COUNT][LED_NUMBER];
    uint16_t version;
    uint32_t reserved[10];
    uint32_t magic;
} display_frames_t;

_Static_assert(sizeof(display_frames_t) % 64 == 0, "frames struct must be a whole number of flash pages");

void display_editor_edit_mode(void);

void display_editor_load_from_flash(void);

uint32_t display_editor_get_frame_magic(void);

const display_led_state_t* display_editor_get_frame_array(uint8_t frame_index);

#endif /* DISPLAY_EDITOR_H */

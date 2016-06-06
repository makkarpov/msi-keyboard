#ifndef MSIKBD_KEYBOARD_H
#define MSIKBD_KEYBOARD_H

#include <hidapi/hidapi.h>
#include <utility>
#include "Color.h"

class Keyboard {
    hid_device *_dev;

    void write(uint8_t *data, size_t length);
    void write_color(uint8_t function, uint8_t index, Color color);
    void write_mode(uint8_t mode);
    void write_gradient(uint8_t region, Color first, Color second);

    enum {
        MODE_NORMAL     = 0x01,
        MODE_GAMING     = 0x02,
        MODE_BREATHING  = 0x03,
        MODE_AUDIO      = 0x04,
        MODE_WAVE       = 0x05,
        MODE_DUAL_COLOR = 0x06,

        REGION_LEFT     = 0x01,
        REGION_MIDDLE   = 0x02,
        REGION_RIGHT    = 0x03,

        FUNCTION_SET    = 0x40,
        FUNCTION_GRAD   = 0x44
    };

public:
    Keyboard();

    typedef std::pair<Color, Color> ColorPair;

    void normal(Color left, Color middle, Color right);
    void gaming(Color left);
    void breathing(Color left, Color middle, Color right);
    void breathing(ColorPair left, ColorPair middle, ColorPair right);
    void wave(Color left, Color middle, Color right);
    void wave(ColorPair left, ColorPair middle, ColorPair right);
};


#endif //MSIKBD_KEYBOARD_H
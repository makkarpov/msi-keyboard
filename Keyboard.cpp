
#include "Keyboard.h"

#include <stdexcept>

Keyboard::Keyboard() {
    _dev = hid_open(0x1770, 0xFF00, nullptr);

    if (_dev == nullptr) {
        throw std::runtime_error("device is not present");
    }
}

void Keyboard::write(uint8_t *data, size_t length) {
    if (hid_send_feature_report(_dev, data, length) != length) {
        throw std::runtime_error("feature report failed");
    }
}

void Keyboard::write_color(uint8_t function, uint8_t index, Color color) {
    uint8_t data[] = {
        0x01, 0x02, function, index,
        color.r(), color.g(), color.b(), 0x00
    };

    write(data, sizeof(data));
}

void Keyboard::write_mode(uint8_t mode) {
    uint8_t data[] = {
        0x01, 0x02, 0x41, mode,
        0x00, 0x00, 0x00, 0x00
    };

    write(data, sizeof(data));
}

void Keyboard::write_gradient(uint8_t region, Color first, Color second) {
    uint8_t index = (uint8_t) ((region - 1) * 3 + 1);
    write_color(FUNCTION_GRAD, index++, first);
    write_color(FUNCTION_GRAD, index++, second);
    write_color(FUNCTION_GRAD, index, Color(0, 0, 255));
}

void Keyboard::normal(Color left, Color middle, Color right) {
    write_mode(MODE_NORMAL);
    write_color(FUNCTION_SET, REGION_LEFT, left);
    write_color(FUNCTION_SET, REGION_MIDDLE, middle);
    write_color(FUNCTION_SET, REGION_RIGHT, right);
}

void Keyboard::gaming(Color left) {
    write_mode(MODE_GAMING);
    write_color(FUNCTION_SET, REGION_LEFT, left);
}

void Keyboard::breathing(Color left, Color middle, Color right) {
    write_gradient(REGION_LEFT, left, Color(0, 0, 0));
    write_mode(MODE_BREATHING);
    write_gradient(REGION_MIDDLE, middle, Color(0, 0, 0));
    write_mode(MODE_BREATHING);
    write_gradient(REGION_RIGHT, right, Color(0, 0, 0));
    write_mode(MODE_BREATHING);
}

void Keyboard::breathing(ColorPair left, ColorPair middle, ColorPair right) {
    write_gradient(REGION_LEFT, left.first, left.second);
    write_mode(MODE_BREATHING);
    write_gradient(REGION_MIDDLE, middle.first, middle.second);
    write_mode(MODE_BREATHING);
    write_gradient(REGION_RIGHT, right.first, right.second);
    write_mode(MODE_BREATHING);
}

void Keyboard::wave(Color left, Color middle, Color right) {
    write_gradient(REGION_LEFT, left, Color(0, 0, 0));
    write_mode(MODE_WAVE);
    write_gradient(REGION_MIDDLE, middle, Color(0, 0, 0));
    write_mode(MODE_WAVE);
    write_gradient(REGION_RIGHT, right, Color(0, 0, 0));
    write_mode(MODE_WAVE);
}

void Keyboard::wave(ColorPair left, ColorPair middle, ColorPair right) {
    write_gradient(REGION_LEFT, left.first, left.second);
    write_mode(MODE_WAVE);
    write_gradient(REGION_MIDDLE, middle.first, middle.second);
    write_mode(MODE_WAVE);
    write_gradient(REGION_RIGHT, right.first, right.second);
    write_mode(MODE_WAVE);
}

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

#ifdef WIN32
static Color get_saturated_color(int r, int g, int b) {
    const auto v = 1.45;
    const auto gray = 0.2989 * r + 0.5870 * g + 0.1140 * b;
    r = -gray * v + r * (1 + v);
    g = -gray * v + g * (1 + v);
    b = -gray * v + b * (1 + v);

    r = max(0, min(255, r));
    g = max(0, min(255, g));
    b = max(0, min(255, b));

    return { static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b) };
}

void Keyboard::automatic() {
    DWORD colorization;
    BOOL unused;
    if (FAILED(DwmGetColorizationColor(&colorization, &unused))) { return; }
    const auto color = get_saturated_color(colorization >> 16 & 0xFF, colorization >> 8 & 0xFF, colorization & 0xFF);
    this->normal(color, color, color);
}

#endif
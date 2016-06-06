#include "Color.h"

Color::Color(uint8_t r, uint8_t g, uint8_t b) noexcept
    : _r(r), _g(g), _b(b)
{
}

uint8_t Color::r() const noexcept {
    return _r;
}

uint8_t Color::g() const noexcept {
    return _g;
}

uint8_t Color::b() const noexcept {
    return _b;
}

bool Color::operator==(const Color &rhs) const noexcept {
    return (_r == rhs._r) && (_g == rhs._g) && (_b == rhs._b);
}

bool Color::operator!=(const Color &rhs) const noexcept {
    return (_r != rhs._r) || (_g != rhs._g) || (_b != rhs._b);
}

Color Color::rgb(int rgb) noexcept {
    return Color((uint8_t)((rgb >> 16) & 0xFF), (uint8_t) ((rgb >> 8) & 0xFF), (uint8_t) (rgb & 0xFF));
}

Color Color::hue(unsigned int hue) noexcept {
    if (hue >= 360) {
        hue %= 360;
    }

    uint8_t cu = (uint8_t) ((hue % 60) * 255 / 60);
    uint8_t cd = (uint8_t) (255 - cu);

    uint8_t r, g, b;

    switch (hue / 60) {
    case 0: r = 255; g = cu; b = 0; break;
    case 1: r = cd; g = 255; b = 0; break;
    case 2: r = 0; g = 255; b = cu; break;
    case 3: r = 0; g = cd; b = 255; break;
    case 4: r = cu; g = 0; b = 255; break;
    case 5: r = 255; g = 0; b = cd; break;
    default: r = 0; g = 0; b = 0; break; // to avoid compiler warning
    }

    return Color(r, g, b);
}
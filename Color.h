#ifndef MSIKBD_COLOR_H
#define MSIKBD_COLOR_H

#include <cstdint>

class Color {
    uint8_t _r, _g, _b;

public:
    Color(uint8_t r, uint8_t g, uint8_t b) noexcept;

    uint8_t r() const noexcept;
    uint8_t g() const noexcept;
    uint8_t b() const noexcept;

    bool operator==(const Color &rhs) const noexcept;
    bool operator!=(const Color &rhs) const noexcept;

    static Color hue(unsigned int hue) noexcept;
    static Color rgb(int rgb) noexcept;
};

#endif //MSIKBD_COLOR_H

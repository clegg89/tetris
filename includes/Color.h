/**
 * @file Color.h
 * 
 * @author C. Smith
 * @date Jan 9, 2016
 */

#ifndef _COLOR_H_
#define _COLOR_H_

#include <cstdint>

class Color
{
    public:
        uint8_t r, g, b, a;

        Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 0) : r(r), g(g), b(b), a(a){}
        Color(uint32_t full_color)
        {
            r = (full_color & 0xFF000000) >> 24;
            g = (full_color & 0x00FF0000) >> 16;
            b = (full_color & 0x0000FF00) >> 8;
            a = (full_color & 0x000000FF);
        }

        void operator = (const Color& param)
        {
            this->r = param.r;
            this->g = param.g;
            this->b = param.b;
            this->a = param.a;
        }
};

#endif /* _COLOR_H_ */

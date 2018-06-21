//
//  Buffer.cpp
//  SpaceInvaders
//
//  Created by Hilton Pintor Bezerra Leite on 21/06/2018.
//

#include "Buffer.hpp"

// MARK: - Tint Buffer
void Buffer::tint(uint32_t color) {
    for (size_t i = 0; i < width * height; ++i) {
        pixels[i] = color;
    }
}

void Buffer::drawSprite(const Sprite &sprite, size_t x, size_t y, uint32_t color) {
    for(size_t xi = 0; xi < sprite.width; ++xi)
    {
        for(size_t yi = 0; yi < sprite.height; ++yi)
        {
            size_t sy = sprite.height - 1 + y - yi;
            size_t sx = x + xi;
            if(sprite.data[yi * sprite.width + xi] &&
               sy < height && sx < width)
            {
                pixels[sy * width + sx] = color;
            }
        }
    }
}

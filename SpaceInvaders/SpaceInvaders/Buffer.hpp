//
//  Buffer.hpp
//  SpaceInvaders
//
//  Created by Hilton Pintor Bezerra Leite on 21/06/2018.
//

#ifndef Buffer_hpp
#define Buffer_hpp

#include <stdio.h>
#include <cstdint>
#include "Sprite.hpp"

// MARK: - Buffer (screen representation)
struct Buffer {
    size_t width, height;
    uint32_t* pixels;
    
    
public:
    void tint(uint32_t color);
    void drawSprite(const Sprite& sprite, size_t x, size_t y, uint32_t color);
};

#endif /* Buffer_hpp */

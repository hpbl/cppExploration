//
//  Sprite.hpp
//  SpaceInvaders
//
//  Created by Hilton Pintor Bezerra Leite on 21/06/2018.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include <stdio.h>
#include <cstdint>

struct Sprite {
    size_t width, height;
    uint8_t* data;
};

#endif /* Sprite_hpp */

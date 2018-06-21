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

struct SpriteAnimation {
    bool loop;
    size_t numFrames;
    size_t frameDuration;
    size_t time;
    Sprite** frames;
};

#endif /* Sprite_hpp */

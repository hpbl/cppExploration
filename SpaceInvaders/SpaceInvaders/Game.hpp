//
//  Game.hpp
//  SpaceInvaders
//
//  Created by Hilton Pintor Bezerra Leite on 21/06/2018.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <cstdint>

struct Alien {
    size_t x, y;
    uint8_t type;
};

struct Player {
    size_t x, y;
    size_t life;
};

struct Game {
    size_t width, height;
    size_t numAliens;
    Alien* aliens;
    Player player;
};

#endif /* Game_hpp */

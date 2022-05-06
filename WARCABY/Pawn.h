//
// Created by podgo on 25.03.2022.
//

#ifndef WARCABY_PAWN_H
#define WARCABY_PAWN_H
#include <string>
#include <SFML/Graphics.hpp>
class Pawn{
protected:
    sf::Texture pawnW,pawnB,queenW,queenB;
public:
    std::string color;
    std::string kind;
    sf::Sprite sprite;
    bool isCaptured=false;
    Pawn();
};


#endif //WARCABY_PAWN_H

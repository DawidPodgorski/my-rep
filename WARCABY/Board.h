//
// Created by podgo on 16.03.2022.
//

#ifndef WARCABY_BOARD_H
#define WARCABY_BOARD_H
#include <string>
#include "Pawn.h"
#include <SFML/Graphics.hpp>
struct Field
{
    sf::Sprite sprite;
    std::string color;
    sf::Sprite activeSprite;
    bool isFree;
    bool isActive;
};
class Board: public Pawn{
private:
    sf::Texture textureW, textureB, textureWood;//wczytanie tekstur pol
    sf::Font font;
protected:
    sf::Texture textureBlackNow, textureWhiteNow;
    sf::Sprite spriteWhoseNow;
    sf::Texture textureActiveField;
    sf::Sprite background;
    Field field[8][8];
    int width;
    int height;
    Pawn black[12];
    Pawn white[12];
public:
    explicit Board(int width = 8, int height = 8);//konstruktor
    void initialStateBoard(sf::RenderWindow &window);
};


#endif //WARCABY_BOARD_H

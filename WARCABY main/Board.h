//
// Created by podgo on 16.03.2022.
//

#ifndef WARCABY_BOARD_H
#define WARCABY_BOARD_H
#include <string>
#include "Pawn.h"
#include <SFML/Graphics.hpp>


class Board: public Pawn{
private:
    sf::Texture textureW, textureB, textureWood;//wczytanie tekstur pol
    sf::Font font;
protected:
    virtual void initialStateBoard(sf::RenderWindow &window);

    //textures
    sf::Texture textureBlackNow, textureWhiteNow;
    sf::Texture textureActiveField;
    sf::Texture textureCapturing;
    sf::Texture textureToQueen;

    //sprites
    sf::Sprite spriteWhoseNow;
    sf::Sprite background;
    Field field[8][8];
    int width;
    int height;
    Pawn black[12];
    Pawn white[12];
public:
    explicit Board(int width = 8, int height = 8);//konstruktor
    int queenMovementCounter=0;




};


#endif //WARCABY_BOARD_H

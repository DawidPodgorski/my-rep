//
// Created by podgo on 16.03.2022.
//

#include "Board.h"
#include <iostream>

void Board::initialStateBoard(sf::RenderWindow &window) {
    Pawn*w=&white[0];
    Pawn*b=&black[0];

    background.setTexture(textureWood);
    background.setScale(0.65, 0.65);

    spriteWhoseNow.setTexture(textureWhiteNow);
    spriteWhoseNow.setPosition(680,370);
    spriteWhoseNow.setScale(0.75, 0.75);

    float xPos=0.0;
    float yPos=630.0;
    const float fieldScale=0.7;
    const float pawnScale=0.45;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (i % 2)
            {
                if (j % 2) {
                    field[i][j].color = "white";
                    field[i][j].sprite.setTexture(textureW);
                    field[i][j].sprite.setPosition(xPos,yPos);
                    field[i][j].sprite.setScale(fieldScale,fieldScale);
                }
                else
                {
                    field[i][j].isFree=true;
                    field[i][j].isActive=false;
                    field[i][j].color = "black";
                    field[i][j].sprite.setTexture(textureB);
                    field[i][j].sprite.setPosition(xPos,yPos);
                    field[i][j].sprite.setScale(fieldScale,fieldScale);
                    if(i>=5)
                    {
                        field[i][j].isFree=false;
                        w->sprite.setTexture(pawnW);
                        w->sprite.setPosition(field[i][j].sprite.getPosition());
                        w->sprite.setScale(pawnScale,pawnScale);
                        w++;
                        //tutaj okresl polozenie pionka
                    }
                    else if(i<3)
                    {
                        field[i][j].isFree=false;
                        b->color="black";
                        b->sprite.setTexture(pawnB);
                        b->sprite.setPosition(field[i][j].sprite.getPosition());
                        b->sprite.setScale(pawnScale,pawnScale);
                        b++;
                    }
                }
            }
            else {
                if (j % 2)
                {
                    field[i][j].isFree=true;
                    field[i][j].isActive=false;
                    field[i][j].color = "black";
                    field[i][j].sprite.setTexture(textureB);
                    field[i][j].sprite.setPosition(xPos,yPos);
                    field[i][j].sprite.setScale(fieldScale,fieldScale);
                    if(i>=5)
                    {
                        field[i][j].isFree=false;
                        w->sprite.setTexture(pawnW);
                        w->sprite.setPosition(field[i][j].sprite.getPosition());
                        w->sprite.setScale(pawnScale,pawnScale);
                        w++;
                    }
                    else if(i<3)
                    {
                        field[i][j].isFree=false;
                        b->color="black";
                        b->sprite.setTexture(pawnB);
                        b->sprite.setPosition(field[i][j].sprite.getPosition());
                        b->sprite.setScale(pawnScale,pawnScale);
                        b++;
                    }
                }
                else
                {
                    field[i][j].color = "white";
                    field[i][j].sprite.setTexture(textureW);
                    field[i][j].sprite.setPosition(xPos,yPos);
                    field[i][j].sprite.setScale(fieldScale,fieldScale);
                }

            }
            if(xPos<440)
                xPos+=70;
            else
            {
                xPos=0;
                yPos-=70;
            }
        }
    }
}
Board::Board(int w, int h)
:width(w), height(h)
{
    //wczytanie tekstur
    if (!textureW.loadFromFile("Textures/whiteField.png") or
    (!textureB.loadFromFile("Textures/blackField.png")) or
    (!textureWood.loadFromFile("Textures/woodTexture.jpg")) or
    (!textureActiveField.loadFromFile("Textures/activeField.png")) or
    (!font.loadFromFile("Fonts/font.ttf")) or
    (!textureBlackNow.loadFromFile("Textures/BLACKnow.png")) or
    (!textureWhiteNow.loadFromFile("Textures/WHITEnow.png")))
    {
        std::cout<<"Failed to load texture"<<std::endl;
    }
}


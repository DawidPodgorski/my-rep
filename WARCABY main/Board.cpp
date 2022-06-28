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
                    field[i][j].name=std::to_string(i+1)+' '+std::to_string(j+1);
                    field[i][j].sprite.setTexture(textureW);
                    field[i][j].sprite.setPosition(xPos,yPos);
                    field[i][j].sprite.setScale(fieldScale,fieldScale);
                }
                else
                {
                    field[i][j].name=std::to_string(i+1)+' '+std::to_string(j+1);
                    field[i][j].isFree=true;
                    field[i][j].isActive=false;
                    field[i][j].isCapturing=false;
                    field[i][j].color = "black";

                    //ladowanie tesktur dla kazdego pola
                    field[i][j].sprite.setTexture(textureB);
                    field[i][j].sprite.setPosition(xPos,yPos);
                    field[i][j].sprite.setScale(fieldScale,fieldScale);
                    field[i][j].captureSprite.setTexture(textureCapturing);
                    field[i][j].captureSprite.setPosition(xPos,yPos);
                    field[i][j].captureSprite.setScale(fieldScale,fieldScale);
                    field[i][j].activeSprite.setTexture(textureActiveField);
                    field[i][j].activeSprite.setPosition(xPos,yPos);
                    field[i][j].activeSprite.setScale(fieldScale,fieldScale);
                    if(i>=5)
                    {
                        field[i][j].isFree=false;
                        w->isCaptured=false;
                        w->sprite.setTexture(pawnW);
                        w->sprite.setPosition(field[i][j].sprite.getPosition());
                        w->sprite.setScale(pawnScale,pawnScale);
                        w->position=&field[i][j];
                        w->name="W "+std::to_string(i+1)+' '+std::to_string(j+1);
                        w->kind="normal";
                        w++;
                        //tutaj okresl polozenie pionka
                    }
                    else if(i<3)
                    {
                        field[i][j].isFree=false;
                        b->isCaptured=false;
                        b->color="black";
                        b->sprite.setTexture(pawnB);
                        b->sprite.setPosition(field[i][j].sprite.getPosition());
                        b->sprite.setScale(pawnScale,pawnScale);
                        b->position=&field[i][j];
                        b->name="B "+std::to_string(i+1)+' '+std::to_string(j+1);
                        b->kind="normal";
                        b++;
                    }
                }
            }
            else {
                if (j % 2)
                {
                    field[i][j].name=std::to_string(i+1)+' '+std::to_string(j+1);
                    field[i][j].isFree=true;
                    field[i][j].isActive=false;
                    field[i][j].isCapturing=false;
                    field[i][j].color = "black";
                    field[i][j].sprite.setTexture(textureB);
                    field[i][j].sprite.setPosition(xPos,yPos);
                    field[i][j].sprite.setScale(fieldScale,fieldScale);
                    field[i][j].captureSprite.setTexture(textureCapturing);
                    field[i][j].captureSprite.setPosition(xPos,yPos);
                    field[i][j].captureSprite.setScale(fieldScale,fieldScale);
                    field[i][j].activeSprite.setTexture(textureActiveField);
                    field[i][j].activeSprite.setPosition(xPos,yPos);
                    field[i][j].activeSprite.setScale(fieldScale,fieldScale);

                    if(i>=5)
                    {
                        field[i][j].isFree=false;
                        w->isCaptured=false;
                        w->sprite.setTexture(pawnW);
                        w->sprite.setPosition(field[i][j].sprite.getPosition());
                        w->sprite.setScale(pawnScale,pawnScale);
                        w->position=&field[i][j];
                        w->name="W "+std::to_string(i+1)+' '+std::to_string(j+1);
                        w->kind="normal";
                        w++;
                    }
                    else if(i<3)
                    {
                        b->isCaptured=false;
                        field[i][j].isFree=false;
                        b->color="black";
                        b->sprite.setTexture(pawnB);
                        b->sprite.setPosition(field[i][j].sprite.getPosition());
                        b->sprite.setScale(pawnScale,pawnScale);
                        b->position=&field[i][j];
                        b->name="B "+std::to_string(i+1)+' '+std::to_string(j+1);
                        b->kind="normal";
                        b++;
                    }
                }
                else
                {
                    field[i][j].name=std::to_string(i+1)+' '+std::to_string(j+1);
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
    //(!textureB.loadFromFile("Textures/blackField.png")) or
    (!textureWood.loadFromFile("Textures/woodTexture.png")) or
    (!textureActiveField.loadFromFile("Textures/activeField.png")) or
    //(!font.loadFromFile("Fonts/font.ttf")) or
    (!textureBlackNow.loadFromFile("Textures/BLACKnow.png")) or
    (!textureWhiteNow.loadFromFile("Textures/WHITEnow.png"))or
    (!textureCapturing.loadFromFile("Textures/capturing.png"))or
    (!textureToQueen.loadFromFile("Textures/toQueen.png")))
    {
        std::cout<<"Failed to load texture"<<std::endl;
    }
}


//
// Created by podgo on 28.04.2022.
//

#ifndef MAIN_CPP_GAME_H
#define MAIN_CPP_GAME_H

#include "Board.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Game: public Board{
    void newPositionActiveField(sf::RenderWindow &window, sf::Event&event);
    void determinePossibleFields(sf::RenderWindow &window);
    void currentlyPositionActiveField(sf::RenderWindow & window);
    Pawn*isMouseOverPawn(sf::RenderWindow &window, sf::Event&event);
protected:
    std::string whoseMove="white";
    std::vector<Field> possibleFieldsToMove;
    Pawn*activePawn= nullptr;
    bool startMove=false;
    Field*lastFieldActivePawn= nullptr;
public:
    virtual void move(sf::RenderWindow &window, sf::Event&event);
    void displayBoard(sf::RenderWindow &window)const ;//sa one tutaj poniewaz jest potrzebny atrybut whoseMove ktory jest zmieniany podczas ruchu
    void displayPawns(sf::RenderWindow &window)const;


};


#endif //MAIN_CPP_GAME_H

//
// Created by podgo on 28.04.2022.
//

#include "Game.h"
#include <iostream>
void Game::displayPawns(sf::RenderWindow &window)const
{
    if(whoseMove=="black") {
        for (const auto &i: white) {
            if (!i.isCaptured)//jezeli pole nie ma przypisanego zadnego pionka
                window.draw(i.sprite);
        }
        for (const auto &i: black) {
            if (!i.isCaptured)//jezeli pole nie ma przypisanego zadnego pionka
                window.draw(i.sprite);
        }
        if(activePawn!= nullptr)
        window.draw(activePawn->sprite);
    }
    else
    {
        for (const auto &i: black) {
            if (!i.isCaptured)//jezeli pole nie ma przypisanego zadnego pionka
                window.draw(i.sprite);
        }
        for (const auto &i: white) {
            if (!i.isCaptured)//jezeli pole nie ma przypisanego zadnego pionka
                window.draw(i.sprite);
        }
        if(activePawn!= nullptr)
            window.draw(activePawn->sprite);
    }

}
void Game::displayBoard(sf::RenderWindow &window)const  {//przeniesc do klasy game
    window.draw(background);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            window.draw(field[i][j].sprite);
            if(activePawn!= nullptr and field[i][j].isActive)
                    window.draw(field[i][j].activeSprite);
            window.draw(spriteWhoseNow);
            displayPawns(window);
        }
    }

}


Pawn*Game::isMouseOverPawn(sf::RenderWindow &window, sf::Event &event)
{
    for (int i = 0; i < 12; ++i) {
        if (black[i].isCaptured and white[i].isCaptured) {
            continue;
        }
        if(whoseMove=="black") {
            if (event.mouseButton.x >= (int) black[i].sprite.getPosition().x and
                event.mouseButton.x <= (int) black[i].sprite.getPosition().x + 70)
                if (event.mouseButton.y >= (int) black[i].sprite.getPosition().y and
                    event.mouseButton.y <= (int) black[i].sprite.getPosition().y + 70) {
                    return &black[i];
                }
        }
        else {
            if (event.mouseButton.x >= (int) white[i].sprite.getPosition().x and
                event.mouseButton.x <= (int) white[i].sprite.getPosition().x + 70)
                if (event.mouseButton.y >= (int) white[i].sprite.getPosition().y and
                    event.mouseButton.y <= (int) white[i].sprite.getPosition().y + 70) {
                    return &white[i];
                }
        }
    }

    return nullptr;


}

void Game::determinePossibleFields(sf::RenderWindow &window)//ustalenie mozliwych pol ruchu
{
    possibleFieldsToMove.clear();
    Field*pnt=&field[0][0];
    //for black
    if(whoseMove=="black")
    for(;pnt<=&field[7][7]; pnt++ )
    {
        if(pnt->color=="black" and pnt->isFree and (pnt-lastFieldActivePawn==7 or pnt-lastFieldActivePawn==9) ) {
            possibleFieldsToMove.push_back(*pnt);
            pnt->activeSprite.setTexture(textureActiveField);
            pnt->activeSprite.setPosition(pnt->sprite.getPosition());
            pnt->activeSprite.setScale(pnt->sprite.getScale());
            pnt->isActive=true;
        }
    }
    //for white
    else
    for(;pnt<=&field[7][7]; pnt++ )
    {
        if(pnt->color=="black" and pnt->isFree and (lastFieldActivePawn-pnt==7 or lastFieldActivePawn-pnt==9) ) {
            possibleFieldsToMove.push_back(*pnt);
            pnt->activeSprite.setTexture(textureActiveField);
            pnt->activeSprite.setPosition(pnt->sprite.getPosition());
            pnt->activeSprite.setScale(pnt->sprite.getScale());
            pnt->isActive=true;
        }
    }
}

void Game::newPositionActiveField(sf::RenderWindow &window, sf::Event & event)
{
    for( auto& i:possibleFieldsToMove)
    {
        if (activePawn->sprite.getPosition().x+35 >=  i.sprite.getPosition().x and
                activePawn->sprite.getPosition().x+35 <= i.sprite.getPosition().x+70)
            if (activePawn->sprite.getPosition().y+35 >= i.sprite.getPosition().y and
                    activePawn->sprite.getPosition().y+35 <= i.sprite.getPosition().y + 70)
            {
                lastFieldActivePawn=&i;
                //setting the next move
                if(whoseMove=="black") {
                    whoseMove = "white";
                    spriteWhoseNow.setTexture(textureWhiteNow);
                }
                else {
                    whoseMove = "black";
                    spriteWhoseNow.setTexture(textureBlackNow);
                }
            }
    }

}

void Game::currentlyPositionActiveField(sf::RenderWindow &window)
{
    Field*pnt=&field[0][0];
    for(;pnt<=&field[7][7]; pnt++ )
    {
        pnt->isActive=false;
        if (activePawn->sprite.getPosition().x+35 >=  pnt->sprite.getPosition().x and
            activePawn->sprite.getPosition().x+35 <= pnt->sprite.getPosition().x+70)
            if (activePawn->sprite.getPosition().y+35 >= pnt->sprite.getPosition().y and
                activePawn->sprite.getPosition().y+35 <= pnt->sprite.getPosition().y + 70)
            {
                lastFieldActivePawn=pnt;
            }
    }
}
void Game::move(sf::RenderWindow &window, sf::Event&event) {


    if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)//when i click
    {
        activePawn = isMouseOverPawn(window, event);
        if(activePawn!= nullptr)//and whose pawn is active
        {
            currentlyPositionActiveField(window);
            lastFieldActivePawn->isFree=true;
            determinePossibleFields(window);//when I take pawn, determine possible fields
            activePawn->sprite.setScale(0.6, 0.6);
            startMove=true;
        }

        // pomocniczna petla
        for(auto i:possibleFieldsToMove)
            std::cout<<i.isFree<<i.color<<std::endl;
        std::cout<<"---------"<<std::endl;
        //
    }
    else if (event.type == sf::Event::MouseButtonReleased and event.mouseButton.button == sf::Mouse::Left)//co zrobic na zakonczenie ruchu
    {
        if(activePawn!= nullptr) {

            newPositionActiveField(window, event);//only here change player
            activePawn->sprite.move(lastFieldActivePawn->sprite.getPosition()-activePawn->sprite.getPosition());
            activePawn->sprite.setScale(0.45, 0.45);
            currentlyPositionActiveField(window);//poniewaz po ruchu przechwyc aktualna pozycje

            lastFieldActivePawn->isFree=false;
        }
        activePawn= nullptr;
        startMove=false;
        //zakonczenie ruchu

    }
    //
    else if( startMove and event.type == sf::Event::MouseMoved and activePawn!= nullptr)//jesli jest start ruch oraz myszka sie porusza i jest aktywny pionek
    {

        activePawn->sprite.move((float)event.mouseMove.x- activePawn->sprite.getPosition().x
                                ,(float)event.mouseMove.y - activePawn->sprite.getPosition().y);
    }
}





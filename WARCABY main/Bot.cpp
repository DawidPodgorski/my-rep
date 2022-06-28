//
// Created by podgo on 31.05.2022.
//
#include "Game.h"
#include <iostream>


void Game::changePlayerSimulation(){
    //zmiana gracza
    player1.kind="bot";//change kind human player to bot
    if (whoseMove.color == "black") {
        if (whoseMove.name == "player1")
            whoseMove = player2;
        else
            whoseMove = player1;
    } else {
        if (whoseMove.color == "white") {
            if (whoseMove.name == "player1")
                whoseMove = player2;
            else
                whoseMove = player1;
        }
        //capturePriority = false;
    }
}
void Game::botMoveSimulation(Moves*move, sf::RenderWindow &window) {
    //robienie kopi pozycji wszystkich niezbitych pionkow
    std::vector<Field*>copyPosition;
    for(int j=0; j<12; ++j)
    {
        if(!black[j].isCaptured)
            copyPosition.push_back(black[j].position);
        if(!white[j].isCaptured)
            copyPosition.push_back(white[j].position);
    }
    //
    std::vector<bool>copyIsFree;
    Game copy=*this;
    for(int x=0; x<8; ++x)
        for(int y=0; y<8; ++y)

    for(int i=1; i<=1; i++)
    {
        move->pawn->position->isFree=true;
        move->pawn->position=move->where;
        move->where->isFree=false;

        capturePriority=false;
        changePlayerSimulation();
        thereIsCapturing(window);
        if(capturePriority and i%2!=0)//when opponent hitting
            move->profitability-=5;
        else if(capturePriority and i%2==0)//when bot will hit in his next move
            move->profitability+=5;

        move->where->isFree=true;
        move->pawn->position->isFree=false;
        changePlayerSimulation();//zmiana po zakonczeniu sprawdzania
    }

    //przywrocenie pozycji wszytkim pionkom
    int j=0;
    for(int i=0; i<12; ++i)
    {
        if(!black[i].isCaptured) {
            black[i].position = copyPosition[j];
            j++;
        }
        if(!white[i].isCaptured) {
            white[i].position = copyPosition[j];
            j++;
        }
    }

    for(int x=0; x<8; ++x)
        for(int y=0; y<8; ++y)
            ;//przywracanie fieldow



    player1.kind="human";
}
void Game::botHitSimulation(Capture*capture, sf::RenderWindow &window)
{

}
void Game::checkMoves(sf::RenderWindow &window) {
    if(whoseMove.color=="white")
    {
        for(auto&w:white)
        {
            for(auto &f:w.moves) {
                botMoveSimulation(&f, window);
                if(f.profitability>=bestBotMove.profitability) {
                    bestBotMove = f;
                    bestBotMove.pawn=&w;
                }
            }
        }
    }
    else
    {
        for(auto&b:black)
        {
            for(auto &f:b.moves) {
                botMoveSimulation(&f, window);
                if (f.profitability >= bestBotMove.profitability)
                {
                    bestBotMove = f;
                    bestBotMove.pawn=&b;
                }
            }
        }
    }
}
void Game::checkBeatings(sf::RenderWindow &window) {
    if(whoseMove.color=="white")
    {
        for(auto&w:white)
        {
            for(auto &c:w.possibleFieldsToCapture)
                botHitSimulation(&c, window);

        }

    }
    else
    {
        for(auto&b:black)
        {
            for(auto &c:b.possibleFieldsToCapture)
                botHitSimulation(&c, window);
        }
    }
}
void Game::bot(sf::RenderWindow &window, sf::Event&event) {
    //pisz algorytm
    thereIsCapturing(window);//generates a hit list as for a normal player
    if(!capturePriority)//if there is not hitting
    {
        std::cout<<"Ther is not hitting"<<std::endl;
        //if bot is white
        if(whoseMove.color=="white")
        {
            for(auto&w:white)
                thereIsMove(window, &w);

        }
        //if bot is black
        if(whoseMove.color=="black")
        {
            for(auto&b:black)
                thereIsMove(window, &b);

        }


        //choice of moves
        checkMoves(window);

        //


    }
    else//if there is hitting
    {
        //choice of hit
        checkBeatings(window);
        //
    }
    std::cout<<bestBotMove.where->name<<" "<<bestBotMove.profitability<<std::endl;
    bestBotMove.pawn->position->isFree=true;
    bestBotMove.pawn->sprite.move(bestBotMove.where->sprite.getPosition()-bestBotMove.pawn->position->sprite.getPosition());
    bestBotMove.pawn->position=bestBotMove.where;
    bestBotMove.pawn->position->isFree=false;
    bestBotMove={nullptr,0};

    changePlayer();



}


/*pomocnicza paetla sprawdzajaca czy nie ma bicia
if(whoseMove.color=="black")
for(const auto&j:black) {
for (auto i: j.possibleFieldsToCapture)
std::cout << i.FieldToMoveAfterCapture->name << std::endl;
for(auto x:j.moves)
std::cout<<x->name<<" for "<<j.name<<std::endl;
}
else
for(const auto&j:white) {
for (auto i: j.possibleFieldsToCapture)
std::cout << i.FieldToMoveAfterCapture->name << std::endl;
for(auto x:j.moves)
std::cout<<x->name<<" for "<<j.name<<std::endl;
}
std::cout<<"---------"<<std::endl;
//*/
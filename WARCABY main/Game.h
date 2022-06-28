//
// Created by podgo on 28.04.2022.
//

#ifndef MAIN_CPP_GAME_H
#define MAIN_CPP_GAME_H

#include "Board.h"
#include <SFML/Graphics.hpp>
#include <vector>

struct Player
{
    std::string color;
    std::string kind;
    std::string name;
};

class Game: public Board{
    Pawn*isMouseOverPawn(sf::RenderWindow &window, sf::Event&event);
    void thereIsCapturingPart2(sf::RenderWindow &window, Pawn* player, Pawn*opponent);
    void thereIsCapturing(sf::RenderWindow&window);
    void thereIsSecondCapture(sf::RenderWindow&window);
    bool thereIsCapturingPart3(sf::RenderWindow &window);
    bool pawnIsPossibleSpace(sf::RenderWindow &window, sf::Event&event);
    void thereIsMove(sf::RenderWindow &window, Pawn* pawn);
    void changePlayer();
    void turnIntoQueen();
    //for Queen
    void moveQuenn(sf::RenderWindow &window, Pawn * pawn);
    void captureQueen(sf::RenderWindow &window, Pawn* player, Pawn*opponent);

    //ending and beginning Game
    bool isItOver(sf::RenderWindow &window);

        //Textures
        sf::Texture backgroundWinTexture;
        sf::Texture backgroundDrawTexture;
        sf::Texture mainMenuTexture;
        sf::Texture choosingColorTexture;
        //

        //Sprites
        sf::Sprite backgroundWinSprite;
        sf::Sprite backgroundDrawSprite;
        sf::Sprite mainMenuSprite;
        sf::Sprite choosingColorSprite;
        //
    //

    //Bot
    void changePlayerSimulation();
    void checkMoves(sf::RenderWindow &window);
    void checkBeatings(sf::RenderWindow &window);
    void botHitSimulation(Capture*capture, sf::RenderWindow &window);
    void botMoveSimulation(Moves*move, sf::RenderWindow &window);
    //


protected:
    //Mouse move
    int lastX=0;
    int lastY=0;
    int moveX=0;
    int moveY=0;
    //

    //for pvp pvs
    Player player1={"white", "human", "player1"};
    Player player2={"black", "human", "player2"};
    //


    Field* endBoard=&field[7][7];
    Field* beginningBoard=&field[0][0];
    std::vector<Field*> possibleFieldsToMove;
    Pawn*activePawn= nullptr;
    bool startMove=false;
    bool capturePriority=false;
    Pawn*pawnWhoseCaptured= nullptr;

    //Bot
    Moves bestBotMove={nullptr, 0};
    //

public:
    //window to display
    bool whoseWon=false;
    bool draw=false;
    bool isItMainMenu=true;
    bool isItChoosingColor=false;
    //
    Player whoseMove;

    Game();
    void initialStateBoard(sf::RenderWindow &window) final;
    void move(sf::RenderWindow &window, sf::Event&event);
    void displayBoard(sf::RenderWindow &window)const ;//sa one tutaj poniewaz jest potrzebny atrybut whoseMove ktory jest zmieniany podczas ruchu
    void displayPawns(sf::RenderWindow &window)const;
    void displayWin(sf::RenderWindow &window);
    void displayDraw(sf::RenderWindow &window);
    void displayMenu(sf::RenderWindow &window);
    void displayColorMenu(sf::RenderWindow&window);
    void choiceWin(sf::RenderWindow &window, sf::Event&event);
    void choiceDraw(sf::RenderWindow &window, sf::Event&event);
    void choiceMenu(sf::RenderWindow &window, sf::Event&event);
    void choiceColorMenu(sf::RenderWindow &window, sf::Event&event);
    void lastMousePosition(sf::RenderWindow &window, sf::Event &event);

    //Bot
    void bot(sf::RenderWindow &window, sf::Event&event);
    //

};


#endif //MAIN_CPP_GAME_H

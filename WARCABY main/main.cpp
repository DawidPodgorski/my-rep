#include <SFML/Graphics.hpp>
#include "Game.h"




int main() {
    Game game;
    sf::RenderWindow win(sf::VideoMode(1000, 700), "CHECKERS author:Dawid Podgorski");
    win.setVerticalSyncEnabled(true);//właczenie synchrinizacji pionowej z odswiezaniem monitora



    while (win.isOpen())
    {


        sf::Event event;

        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();
            if(game.whoseWon)
                game.choiceWin(win, event);//wyswietla obsługe interfejsu wygranej
            else if (game.isItMainMenu) { game.choiceMenu(win, event); }
            else if (game.isItChoosingColor) {game.choiceColorMenu(win, event); }
            else if (game.draw) {game.choiceDraw(win, event); }//wyswietla obsługe interfejsu remisu
            else if(game.whoseMove.kind=="human") {game.move(win, event); }//interakacja z graczem


        }
        if(game.whoseMove.kind=="bot")
            game.bot(win, event);//wczytanie ruchu bota

        win.clear(sf::Color::Black);
        win.setActive();
        if(game.whoseWon) {
            game.displayWin(win);//wyswietla menu wygranej jesli ktos wygral
        }
        else if(game.draw) {
            game.displayDraw(win);//wyswietla menu remisu
        }
        else if(game.isItMainMenu) {game.displayMenu(win); }
        else if(game.isItChoosingColor) {game.displayColorMenu(win);}
        else
            game.displayBoard(win);
        win.display();
    }
    return 0;
}

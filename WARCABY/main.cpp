#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"




int main() {
    Game game;
    sf::RenderWindow win(sf::VideoMode(1000, 700), "CHECKERS author:Dawid Podgorski");
    win.setVerticalSyncEnabled(true);//właczenie synchrinizacji pionowej z odswiezaniem monitora

    game.initialStateBoard(win);//tutaj poniewaz initial musi dostac adres do win



    while (win.isOpen())
    {

        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();

            game.move(win,event);
        }

        win.clear(sf::Color::Black);
        win.setActive();
        game.displayBoard(win);
        win.display();
    }
    return 0;
}

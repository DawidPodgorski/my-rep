//
// Created by podgo on 28.04.2022.
//

#include "Game.h"
#include <iostream>
void Game::displayPawns(sf::RenderWindow &window)const//correct
{
    if(whoseMove.color=="black") {
        for (const auto &i: white) {
            if (!i.isCaptured)//jezeli pionek nie jest zbity
                window.draw(i.sprite);
        }
        for (const auto &i: black) {
            if (!i.isCaptured)//jezeli pionek nie jest zbity
                window.draw(i.sprite);
        }
        if(activePawn!= nullptr)
        window.draw(activePawn->sprite);
    }
    else
    {
        for (const auto &i: black) {
            if (!i.isCaptured)//jezeli pionek nie jest zbity
                window.draw(i.sprite);
        }
        for (const auto &i: white) {
            if (!i.isCaptured)//jezeli pionek nie jest zbity
                window.draw(i.sprite);
        }
        if(activePawn!= nullptr)
            window.draw(activePawn->sprite);
    }

}
void Game::displayBoard(sf::RenderWindow &window)const  {
    window.draw(background);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            window.draw(field[i][j].sprite);
            //active's fields
            if(activePawn!= nullptr and field[i][j].isActive)
                    window.draw(field[i][j].activeSprite);
            //capture's fields
            if(field[i][j].isCapturing)
                window.draw(field[i][j].captureSprite);

            window.draw(spriteWhoseNow);
            displayPawns(window);
        }
    }

}

void Game::displayWin(sf::RenderWindow &window) {
    window.draw(backgroundWinSprite);
    spriteWhoseNow.setPosition(400,240);
    spriteWhoseNow.setScale(0.75, 0.75);
    window.draw(spriteWhoseNow);
}

void Game::displayDraw(sf::RenderWindow &window)
{
    window.draw(backgroundDrawSprite);
}

void Game::displayMenu(sf::RenderWindow &window)
{
    window.draw(mainMenuSprite);
}

void Game::displayColorMenu(sf::RenderWindow&window)
{
    window.draw(choosingColorSprite);
}

void Game::choiceWin(sf::RenderWindow &window, sf::Event&event){
    if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
    {
        //oprogramowanie przycisku exit
        if(event.mouseButton.x>=151 and event.mouseButton.x<=385 )
            if(event.mouseButton.y>=592 and event.mouseButton.y<=669)
                window.close();
        //
        //oprogramowanie przycisku play again
        if(event.mouseButton.x>=632 and event.mouseButton.x<=852 )
            if(event.mouseButton.y>=587 and event.mouseButton.y<=688)
            {
                //Robienie porzadzkow
                capturePriority=false;
                //usuniecie tekstur z pol bicia
                for(Field *c=beginningBoard; c<=endBoard; ++c)
                    c->isCapturing=false;//natomiast tekstury bylyby widoczne wiec trzeba wyczyscic
                //wyczysc wektor molziwych bic
                for(auto &b:black)
                    b.possibleFieldsToCapture.clear();//dla czarnych

                for(auto &w:white)
                    w.possibleFieldsToCapture.clear();//i bialych
                //
                possibleFieldsToMove.clear();
                //

                initialStateBoard(window);//odnowienie planszy
            }
        //

    }
}

void Game::choiceDraw(sf::RenderWindow &window, sf::Event&event)
{
    if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
    {
        //oprogramowanie przycisku exit
        if(event.mouseButton.x>=172 and event.mouseButton.x<=441 )
            if(event.mouseButton.y>=543 and event.mouseButton.y<=641)
                window.close();
        //
        //oprogramowanie przycisku play again
        if(event.mouseButton.x>=551 and event.mouseButton.x<=823 )
            if(event.mouseButton.y>=544 and event.mouseButton.y<=642)
            {
                //Robienie porzadzkow
                capturePriority=false;
                //usuniecie tekstur z pol bicia
                for(Field *c=beginningBoard; c<=endBoard; ++c)
                    c->isCapturing=false;//natomiast tekstury bylyby widoczne wiec trzeba wyczyscic
                //wyczysc wektor molziwych bic
                for(auto &b:black)
                    b.possibleFieldsToCapture.clear();//dla czarnych

                for(auto &w:white)
                    w.possibleFieldsToCapture.clear();//i bialych
                //
                possibleFieldsToMove.clear();
                //

                initialStateBoard(window);//odnowienie planszy
            }
        //

    }
}

void Game::choiceMenu(sf::RenderWindow &window, sf::Event&event)
{
    if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left) {
        std::cout << event.mouseButton.x << " " << event.mouseButton.y << std::endl;

        //oprogramowanie przycisku exit
        if (event.mouseButton.x >= 769 and event.mouseButton.x <= 932)
            if (event.mouseButton.y >= 505 and event.mouseButton.y <= 619)
                window.close();

        //oporgramowanie player vs player
        if (event.mouseButton.x >= 265 and event.mouseButton.x <= 440)
            if (event.mouseButton.y >= 210 and event.mouseButton.y <= 540) {
                isItMainMenu = false;
                whoseMove=player1;
                initialStateBoard(window);
            }

        //oporgramowanie player vs computer
        if (event.mouseButton.x >= 554 and event.mouseButton.x <= 731)
            if (event.mouseButton.y >= 210 and event.mouseButton.y <= 540) {
                //go to choosing color menu
                isItMainMenu = false;
                isItChoosingColor=true;
            }
    }


}

void Game::choiceColorMenu(sf::RenderWindow &window, sf::Event&event)
{

    if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)
    {
        std::cout<<event.mouseButton.x<<" "<<event.mouseButton.y<<std::endl;
        //oprogramowanie przycisku back
        if(event.mouseButton.x>=769 and event.mouseButton.x<=930 )
            if(event.mouseButton.y>=504 and event.mouseButton.y<=620)
            {
                //back to the main menu
                isItChoosingColor=false;
                isItMainMenu=true;
            }
        //for white choose
        if(event.mouseButton.x>=223 and event.mouseButton.x<=481 )
            if(event.mouseButton.y>=263 and event.mouseButton.y<=488)
            {
                //play with computer
                isItChoosingColor=false;
                //ustalenie funkcji bota oraz gracza
                player1={"white", "human", "player1"};
                player2={"black", "bot", "player2"};
                whoseMove=player1;
                //
                initialStateBoard(window);//write bot
            }
        //for black choose
        if(event.mouseButton.x>=514 and event.mouseButton.x<=772 )
            if(event.mouseButton.y>=263 and event.mouseButton.y<=488)
            {
                //play with computer
                isItChoosingColor=false;
                player1={"black", "human", "player1"};
                player2={"white", "bot", "player2"};
                whoseMove=player2;
                initialStateBoard(window);//write bot
            }
    }


}

void Game::initialStateBoard(sf::RenderWindow &window)
{
    Board::initialStateBoard(window);

    //ustawienie domyslnych wartosci dla play again
    whoseWon=false;
    draw=false;
    queenMovementCounter=0;
    //
}
Game::Game()
{

    //dla displayWin
    if (!backgroundWinTexture.loadFromFile("Textures/backgroundWin.jpg"))
        std::cout<<"Failed to load texture"<<std::endl;
    backgroundWinSprite.setTexture(backgroundWinTexture);
    backgroundWinSprite.setScale(0.4, 0.37);
    //

    //dla displayDraw
    if (!backgroundDrawTexture.loadFromFile("Textures/draw.jpg"))
        std::cout<<"Failed to load texture"<<std::endl;
    backgroundDrawSprite.setTexture(backgroundDrawTexture);
    backgroundDrawSprite.setScale(1, 1);
    //

    //for main menu and choosing color
    if (!mainMenuTexture.loadFromFile("Textures/menu.png")
        or !choosingColorTexture.loadFromFile("Textures/color.png"))
        std::cout<<"Failed to load texture"<<std::endl;
    mainMenuSprite.setTexture(mainMenuTexture);
    mainMenuSprite.setScale(0.52, 0.66);
    choosingColorSprite.setTexture(choosingColorTexture);
    choosingColorSprite.setScale(0.52,0.66);
    //
}


Pawn*Game::isMouseOverPawn(sf::RenderWindow &window, sf::Event &event)//correct
{
    for (int i = 0; i < 12; ++i) {
        if(whoseMove.color=="black" and !(black[i].isCaptured)) {
            if (event.mouseButton.x >= (int) black[i].sprite.getPosition().x and
                event.mouseButton.x <= (int) black[i].sprite.getPosition().x + 70)
                if (event.mouseButton.y >= (int) black[i].sprite.getPosition().y and
                    event.mouseButton.y <= (int) black[i].sprite.getPosition().y + 70) {
                    lastX=event.mouseButton.x;
                    lastY=event.mouseButton.y;
                    return &black[i];
                }
        }
        else if(whoseMove.color=="white" and !(white[i].isCaptured)){
            if (event.mouseButton.x >= (int) white[i].sprite.getPosition().x and
                event.mouseButton.x <= (int) white[i].sprite.getPosition().x + 70)
                if (event.mouseButton.y >= (int) white[i].sprite.getPosition().y and
                    event.mouseButton.y <= (int) white[i].sprite.getPosition().y + 70) {
                    lastX=event.mouseButton.x;
                    lastY=event.mouseButton.y;
                    return &white[i];
                }
        }
    }

    return nullptr;


}

void Game::thereIsCapturing(sf::RenderWindow&window)
{
    if(whoseMove.color=="black")
        for(auto &b: black)//sprawdz czy dla jakiegos pionka z czarnych
        {
            if(!(b.isCaptured))
            for(auto &w:white)//znajduje sie jakis z bialych
            {
                if (!(w.isCaptured)) {
                    if(b.kind=="normal")
                        thereIsCapturingPart2(window, &b, &w);
                    else {
                        captureQueen(window, &b, &w);
                    }
                }
            }
        }
    else if(whoseMove.color=="white")
        for(auto &w:white )//sprawdz czy dla jakiegos pionka z bialych
        {
            if(!(w.isCaptured))
            for(auto &b:black)//znajduje sie jakis z czarncyh
            {
                if (!(b.isCaptured)) {
                    if(w.kind=="normal")
                        thereIsCapturingPart2(window, &w, &b);
                    else {
                        captureQueen(window, &w, &b);
                    }
                }
            }
        }
}
void Game::thereIsSecondCapture(sf::RenderWindow &window) {
    if(whoseMove.color=="black")

                for(auto &w:white)//znajduje sie jakis z bialych
                {
                    if (!(w.isCaptured)) {
                        if(pawnWhoseCaptured->kind=="normal")
                            thereIsCapturingPart2(window, pawnWhoseCaptured, &w);
                        else {
                            captureQueen(window, pawnWhoseCaptured, &w);
                        }
                    }
                }
    else if(whoseMove.color=="white")

                for(auto &b:black)//znajduje sie jakis z czarncyh
                {
                    if (!(b.isCaptured)) {
                        if(pawnWhoseCaptured->kind=="normal")
                            thereIsCapturingPart2(window, pawnWhoseCaptured, &b);
                        else {
                            captureQueen(window, pawnWhoseCaptured, &b);
                        }
                    }
                }
}
void Game::thereIsCapturingPart2(sf::RenderWindow &window, Pawn*player, Pawn*opponent )
{
    Capture structCapture{};

    if(endBoard-player->position>=14) {
        if (opponent->position == player->position + 7 and (player->position + 14)->isFree) {
            if(whoseMove.kind=="human")//set the frame only for human
                (player->position + 14)->isCapturing = true;//ustawienie czerwonej ramki na pozycji do bicia

            structCapture.FieldToMoveAfterCapture=player->position + 14;
            structCapture.FieldBrokenPawn=player->position + 7;
            player->possibleFieldsToCapture.push_back(structCapture);//dodanie mozliwego bicia gracza
        }
    }
    if(endBoard-player->position>=18) {
        if (opponent->position == player->position + 9 and (player->position + 18)->isFree) {
            if(whoseMove.kind=="human")//set the frame only for human
                (player->position + 18)->isCapturing = true;

            structCapture.FieldToMoveAfterCapture=player->position + 18;
            structCapture.FieldBrokenPawn=player->position + 9;
            player->possibleFieldsToCapture.push_back(structCapture);//dodanie mozliwego bicia gracza
        }
    }
    if(player->position-beginningBoard>=14) {
        if (opponent->position == player->position - 7 and (player->position - 14)->isFree) {
            if(whoseMove.kind=="human")//set the frame only for human
                (player->position - 14)->isCapturing = true;

            structCapture.FieldToMoveAfterCapture=player->position - 14;
            structCapture.FieldBrokenPawn=player->position -7;
            player->possibleFieldsToCapture.push_back(structCapture);//dodanie mozliwego bicia gracza
        }
    }
    if(player->position-beginningBoard>=18) {//kolejna pozycja sprawdzana jest blizej beggining board
        if (opponent->position == player->position - 9 and (player->position - 18)->isFree) {
            if(whoseMove.kind=="human")//set the frame only for human
                (player->position - 18)->isCapturing = true;

            structCapture.FieldToMoveAfterCapture=player->position - 18;
            structCapture.FieldBrokenPawn=player->position -9;
            player->possibleFieldsToCapture.push_back(structCapture);//dodanie mozliwego bicia gracza
        }
    }

    if(!(player->possibleFieldsToCapture.empty()))
    {
        capturePriority=true;

    }

}


bool Game::thereIsCapturingPart3(sf::RenderWindow &window)
{


    if(!(activePawn->possibleFieldsToCapture.empty()))
        return true;
    else
        return false;
}
void Game::thereIsMove(sf::RenderWindow &window, Pawn * pawn)//ustalenie mozliwych pol ruchu
{

    if(pawn->kind=="queen") {//jesli aktywny pion jest dama wygeneruj dla niego odpowiednie dostepne pola
        moveQuenn(window, activePawn);
        return;
    }

    //for black
    if(whoseMove.color=="black")
    {
        for(int i=7; i<=9; i+=2)
        {
            if(endBoard - pawn->position >=i)
                if((pawn->position+ i)->isFree and (pawn->position+ i)->color=="black" )
                {
                    if(whoseMove.kind=="human") {
                        possibleFieldsToMove.push_back((pawn->position + i));//add field to possibleFields
                        (pawn->position+ i)->isActive = true;
                    }
                    else {
                        Moves move;
                        move.profitability=0;
                        move.where=(pawn->position + i);
                        move.pawn=pawn;
                        pawn->moves.push_back(move);//add field to possibleFields
                    }

                }
        }


    }
    //for white
    else if (whoseMove.color=="white")
    {
        for(int i=7; i<=9; i+=2)
        {
            if(pawn->position - beginningBoard >= i)
                if ((pawn->position - i)->isFree and (pawn->position- i)->color=="black")
                {
                    if(whoseMove.kind=="human") {
                        possibleFieldsToMove.push_back((pawn->position - i));//add field to possibleFields
                        (pawn->position - i)->isActive = true;
                    }
                    else {
                        Moves move;
                        move.profitability=0;
                        move.where=(pawn->position - i);
                        move.pawn=pawn;
                        pawn->moves.push_back(move);//add field to possibleFields
                    }

                }

        }
    }

}

bool Game::pawnIsPossibleSpace(sf::RenderWindow &window, sf::Event &event)
{

    //kiedy bicie
    if(capturePriority)
    {
        if (thereIsCapturingPart3(window))//keidy aktywny pionek ma dostepne bicie
        {
            std::cout<<"to jest pion ktory moze bic"<<std::endl;
            for (Capture&x: activePawn->possibleFieldsToCapture)//sprawdz czy pionek jest nad ktoryms ze swoich mozliwych bic
            {
                if (activePawn->sprite.getPosition().x + 35 >= x.FieldToMoveAfterCapture->sprite.getPosition().x and
                    activePawn->sprite.getPosition().x + 35 <= x.FieldToMoveAfterCapture->sprite.getPosition().x + 70)
                    if (activePawn->sprite.getPosition().y + 35 >= x.FieldToMoveAfterCapture->sprite.getPosition().y and
                        activePawn->sprite.getPosition().y + 35 <= x.FieldToMoveAfterCapture->sprite.getPosition().y + 70) {

                        activePawn->position->isFree = true;//ustawienie starej poozycji na wolna;
                        activePawn->position = x.FieldToMoveAfterCapture;//ustawienie nowej pozycji pionka
                        x.FieldToMoveAfterCapture->isFree = false;//ustawienie nowej pozycji jako zajeta
                        //
                        ////// USTAWIENIE PIONKA ZBITEGO JAKO IS CAPTURED TRUE po uzyskaniu nowej pozycji
                        if(whoseMove.color=="white") {
                            for (Pawn &b: black)
                                if (b.position == (x.FieldBrokenPawn)) {
                                    b.isCaptured = true;
                                    b.position->isFree=true;
                                }
                        }
                        else {
                            for (Pawn &w: white)
                                if (w.position == (x.FieldBrokenPawn)){
                                    w.isCaptured = true;
                                    w.position->isFree=true;
                                }
                        }
                        //po biciu ustawiam capture priority na false bo bicie zakonczone
                        pawnWhoseCaptured=activePawn;//ustawiam piona ktory zbil na ostniego ktory bil dla bicia wielokrotnego
                        capturePriority=false;
                        queenMovementCounter=0;
                        //

                        return true;
                    }
            }
        }
    }
    else//dla zwykłego ruchu
    {
        for( auto i:possibleFieldsToMove  )
        {
            const int srodek =35;
            if (activePawn->sprite.getPosition().x+srodek >=  i->sprite.getPosition().x and
                    activePawn->sprite.getPosition().x+srodek <= i->sprite.getPosition().x+70)
                if (activePawn->sprite.getPosition().y+srodek >= i->sprite.getPosition().y and
                        activePawn->sprite.getPosition().y+srodek <= i->sprite.getPosition().y + 70)//jeśli pionek podczas ruchu jest obecnie nad obszarem dostepnym
                {

                    //tutaj obszar gdy pionek zmieni miejsce
                    activePawn->position->isFree= true;//ustawienie starej poozycji na wolna
                    activePawn->position=i;//ustawienie nowej pozycji pionka
                    i->isFree=false;//ustawienie nwoej pozycji jako zajeta
                    if(activePawn->kind=="queen")//jesli pionek ktory zmienia pozycje jest dama
                        queenMovementCounter++;//dodaj ruch dla damy
                    //sprawdzam czy nie ma konca gry
                    if(isItOver(window))
                        return false;
                    else
                        std::cout<<"gramy dalej\n";
                    turnIntoQueen();//sprawdzam czy zmiana w dame po ruchu
                    //zmiana gracza
                    changePlayer();//udany ruch zmiana gracza

                    thereIsCapturing(window);//po zmianie sprawdzi czy nie ma kolejnego bicia
                    //
                    possibleFieldsToMove.clear();//wyczysc wektor mozliwych ruchow
                    return false;
                }
        }
    }
    return false;//omijam przy powrocie kwestie bicia
}
void Game::changePlayer() {
    //zmiana gracza
    if (whoseMove.color == "black") {
        if (whoseMove.name == "player1")
            whoseMove = player2;
        else
            whoseMove = player1;
        spriteWhoseNow.setTexture(textureWhiteNow);
    } else {
        if (whoseMove.color == "white") {
            if (whoseMove.name == "player1")
                whoseMove = player2;
            else
                whoseMove = player1;
            spriteWhoseNow.setTexture(textureBlackNow);
        }
        capturePriority = false;
    }
}
void Game::turnIntoQueen() {
    if(whoseMove.color== "black") {
        if (endBoard - activePawn->position >= 0 and endBoard - activePawn->position <= 7) {//jeśli na ostatnim polu zmien teksture pionka
            std::cout<<"zamiana w dame\n";
            activePawn->kind = "queen";
            activePawn->sprite.setTexture(queenB);
            activePawn->sprite.setPosition(activePawn->position->sprite.getPosition());//pozycja z pozycji na ktorej stoi
            activePawn->sprite.setScale(0.45, 0.45);
        }
    }
    else
        if(activePawn->position-beginningBoard>=0 and activePawn->position-beginningBoard<=7) {
            std::cout<<"zamiana w dame\n";
            activePawn->kind = "queen";
            activePawn->sprite.setTexture(queenW);
            activePawn->sprite.setPosition(activePawn->position->sprite.getPosition());//pozycja z pozycji na ktorej stoi
            activePawn->sprite.setScale(0.45, 0.45);
        }
}

//QUEEN
void Game::moveQuenn(sf::RenderWindow &window, Pawn * pawn) {
    //w gore w lewo
    for(int i=7; i<=49; i+=7)//najdlusza przekatna
        {
            if(endBoard - pawn->position >= i) {
                if ((pawn->position + i)->isFree and (pawn->position + i)->color == "black") {
                    if(whoseMove.kind=="human") {
                        possibleFieldsToMove.push_back((pawn->position + i));//add field to possibleFields
                        (pawn->position + i)->isActive = true;
                    }
                    else {
                        Moves move;
                        move.profitability=0;
                        move.where=(pawn->position + i);
                        move.pawn=pawn;
                        pawn->moves.push_back(move);
                    }
                }
                else//służy do tego aby zakonczyc szukanie miejsc w tej przekatnej jesli kolejny jest zajety
                    break;
            }

        }
    // w gore w prawo
    for(int i=9; i<=54; i+=9)
    {
        if(endBoard - pawn->position >= i) {
            if ((pawn->position + i)->isFree and (pawn->position + i)->color == "black") {
                if(whoseMove.kind=="human") {
                    possibleFieldsToMove.push_back((pawn->position + i));//add field to possibleFields
                    (pawn->position + i)->isActive = true;
                }
                else{
                    Moves move;
                    move.profitability=0;
                    move.where=(pawn->position + i);
                    move.pawn=pawn;
                    pawn->moves.push_back(move);
                }
            }
            else
                break;
        }

    }

    //w dol w lewo
        for(int i=7; i<=42; i+=7)
        {
            if(pawn->position - beginningBoard >= i) {
                if ((pawn->position - i)->isFree and (pawn->position - i)->color == "black") {
                    if(whoseMove.kind=="human")
                    {
                        possibleFieldsToMove.push_back((pawn->position - i));//add field to possibleFields
                        (pawn->position - i)->isActive = true;
                    }
                    else
                    {
                        Moves move;
                        move.profitability=0;
                        move.where=(pawn->position - i);
                        move.pawn=pawn;
                        pawn->moves.push_back(move);
                    }
                }
                else
                    break;//konczy dalsze poszukiwania w tym kierunku kiedy pole jest zajete
            }


        }
    //w dol w prawo
    for(int i=9; i<=63; i+=9)//najdluzsza przekatna
    {
        if(pawn->position - beginningBoard >= i) {
            if ((pawn->position - i)->isFree and (pawn->position - i)->color == "black") {
                if(whoseMove.kind=="human")
                {
                    possibleFieldsToMove.push_back((pawn->position - i));//add field to possibleFields
                    (pawn->position - i)->isActive = true;
                }
                else
                {
                    Moves move;
                    move.profitability=0;
                    move.where=(pawn->position - i);
                    move.pawn=pawn;
                    pawn->moves.push_back(move);
                }
            }
            else
                break;
        }

    }

}

void Game::captureQueen(sf::RenderWindow &window, Pawn* player, Pawn*opponent) {
    Capture structCapture{};
    //gora lewo
        for(int j=7; j<49; j+=7)
        {
            if (endBoard - player->position >= j + 7)//zapobieganie wyjsciu poza tablice
            {
                std::cout<<"sprawdzam bicie gora lewo dla damy\n";
                if (opponent->position == player->position + j and(player->position + j + 7)->isFree) {//warunek konieczny do bicia
                    structCapture.FieldToMoveAfterCapture=player->position +j + 7;
                    structCapture.FieldBrokenPawn=player->position +j;
                    player->possibleFieldsToCapture.push_back(structCapture);//dodanie mozliwego bicia gracza
                    if(whoseMove.kind=="human")
                        (player->position + j+ 7)->isCapturing = true;//ustawienie czerwonej ramki na pozycji damy po biciu
                    std::cout<<"jest bicie gora lewo dama\n";

                    //ustalenie miejsc po biciu
                    for (int i = j+7; i <= 49; i += 7)//najdlusza przekatna
                    {
                        if (endBoard - player->position >= i) {
                            if ((player->position + i)->isFree and (player->position + i)->color == "black") {
                                structCapture.FieldToMoveAfterCapture=player->position +i;
                                player->possibleFieldsToCapture.push_back(structCapture);//dodanie mozliwego bicia gracza
                                if(whoseMove.kind=="human")
                                    (player->position +i)->isCapturing = true;//ustawienie czerwonej ramki na pozycji damy po biciu
                            } else//służy do tego aby zakonczyc szukanie miejsc w tej przekatnej jesli kolejny jest zajety
                                break;
                        }

                    }
                }
                else if(!((player->position+j)->isFree))//jesli na tej pozycji jest pion z twojej druzyny to nie szukaj dalej bicia
                    break;

            }
        }
    //gora prawo
    for(int j=9; j<54; j+=9)
    {
        if (endBoard - player->position >= j + 9)//zapobieganie wyjsciu poza tablice
        {
            std::cout<<"sprawdzam bicie gora prawo dla damy\n";
            if (opponent->position == player->position + j and(player->position + j + 9)->isFree) {//warunek konieczny do bicia
                structCapture.FieldToMoveAfterCapture=player->position +j + 9;
                structCapture.FieldBrokenPawn=player->position +j;
                player->possibleFieldsToCapture.push_back(structCapture);//dodanie mozliwego bicia gracza
                if(whoseMove.kind=="human")
                    (player->position + j+9)->isCapturing = true;//ustawienie czerwonej ramki na pozycji damy po biciu
                std::cout<<"jest bicie gora prawo dama\n";

                //ustalenie miejsc po biciu
                for (int i = j+9; i <= 54; i += 9)//najdlusza przekatna
                {
                    if (endBoard - player->position >= i) {
                        if ((player->position + i)->isFree and (player->position + i)->color == "black") {
                            structCapture.FieldToMoveAfterCapture=player->position +i;
                            player->possibleFieldsToCapture.push_back(structCapture);//dodanie mozliwego bicia gracza
                            if(whoseMove.kind=="human")
                                (player->position +i)->isCapturing = true;//ustawienie czerwonej ramki na pozycji damy po biciu
                        } else//służy do tego aby zakonczyc szukanie miejsc w tej przekatnej jesli kolejny jest zajety
                            break;
                    }

                }
            }
            else if(!((player->position+j)->isFree))//jesli na tej pozycji jest pion z twojej druzyny to nie szukaj dalej bicia
                break;
        }
    }
    //dol lewo

    for(int j=7; j<42; j+=7)
    {
        if (player->position-beginningBoard>=j+7)//zapobieganie wyjsciu poza tablice
        {
            std::cout<<"sprawdzam bicie dol lewo dla damy\n";
            if (opponent->position == player->position - j and(player->position - j - 7)->isFree) {//warunek konieczny do bicia
                structCapture.FieldToMoveAfterCapture=player->position -j - 7;
                structCapture.FieldBrokenPawn=player->position -j;
                player->possibleFieldsToCapture.push_back(structCapture);//dodanie mozliwego bicia gracza
                if(whoseMove.kind=="human")
                    (player->position - j - 7)->isCapturing = true;//ustawienie czerwonej ramki na pozycji damy po biciu
                std::cout<<"jest bicie dol prawo dama\n";

                //ustalenie miejsc po biciu
                for(int i=j+7; i<=42; i+=7)
                {
                    if(player->position - beginningBoard >= i) {
                        if ((player->position - i)->isFree and (player->position - i)->color == "black") {
                            structCapture.FieldToMoveAfterCapture=player->position -i;
                            //field broken pawn zostaje ten sam
                            player->possibleFieldsToCapture.push_back(structCapture);//dodanie mozliwego bicia gracza
                            if(whoseMove.kind=="human")
                                (player->position - i)->isCapturing = true;//ustawienie czerwonej ramki na pozycji damy po biciu
                        }
                        else//służy do tego aby zakonczyc szukanie miejsc w tej przekatnej jesli kolejny jest zajety
                            break;
                    }

                }
            }
            else if(!((player->position-j)->isFree))//jesli na tej pozycji jest pion z twojej druzyny to nie szukaj dalej bicia
                break;

        }
    }

    //dol prawo
    for(int j=9; j<63; j+=9)
    {
        if (player->position-beginningBoard>=j+9)//zapobieganie wyjsciu poza tablice
        {
            std::cout<<"sprawdzam bicie dol prawo dla damy\n";
            if (opponent->position == player->position - j and(player->position - j - 9)->isFree) {//warunek konieczny do bicia
                structCapture.FieldToMoveAfterCapture=player->position -j - 9;
                structCapture.FieldBrokenPawn=player->position -j;
                player->possibleFieldsToCapture.push_back(structCapture);//dodanie mozliwego bicia gracza
                if(whoseMove.kind=="human")
                    (player->position - j - 9)->isCapturing = true;//ustawienie czerwonej ramki na pozycji damy po biciu
                std::cout<<"jest bicie dol lewo dama\n";
                //ustalenie miejsc po biciu
                for(int i=j+9; i<=63; i+=9)
                {
                    if(player->position - beginningBoard >= i) {
                        if ((player->position - i)->isFree and (player->position - i)->color == "black") {
                            structCapture.FieldToMoveAfterCapture=player->position -i;
                            player->possibleFieldsToCapture.push_back(structCapture);//dodanie mozliwego bicia gracza
                            (player->position - i)->isCapturing = true;//ustawienie czerwonej ramki na pozycji damy po biciu
                        }
                        else//służy do tego aby zakonczyc szukanie miejsc w tej przekatnej jesli kolejny jest zajety
                            break;
                    }

                }
            }
            else if(!((player->position-j)->isFree))//jesli na tej pozycji jest pion z twojej druzyny to nie szukaj dalej bicia
                break;
        }
    }


    if(!(player->possibleFieldsToCapture.empty()))
    {
        capturePriority=true;
        queenMovementCounter=0;
        std::cout<<"mam bicie dla piona "<<player->name<<std::endl;

    }
}

//ENDING

bool Game::isItOver(sf::RenderWindow &window)
{
    //CZY WYGRANA
    //dla zbicia wszystkich pionow
    if(whoseMove.color=="black")//jesli czarny
    {
        for(auto&w:white)//jesli wszystkie biale sa zbite
        {


            if (!(w.isCaptured))
                break;
            if(&w==&white[11]) {
                std::cout << "black won\n";
                whoseWon=true;
                return true;
            }
        }


    }
    else
    {
        for(auto&b:black)//jesli wszystkie biale sa zbite
        {
            if (!(b.isCaptured))
                break;
            if(&b==&black[11]) {
                std::cout << "black won\n";
                whoseWon=true;
                return true;
            }

        }
    }
    //
    //dla unieruchomienia wszystkich pionów
    if(whoseMove.color=="black")//jesli czarny
    {
        changePlayer();//sprawdza czy po zmianie nie bylo by bicia
        thereIsCapturing(window);//i sprawdzam czy nie ma bicia po zmianie gracza
        if(capturePriority)//sprawdz
        {
            changePlayer();
            return false;
        }

        for(auto&w:white)//jesli wszystkie biale sa zablokowane
        {
            if(w.kind=="queen" and !w.isCaptured)
                moveQuenn(window,&w);
            else if(!w.isCaptured)
                thereIsMove(window, &w);

            if(!(possibleFieldsToMove.empty()) and !w.isCaptured)
            {
                break;
            }
            if(&w==&white[11]) {
                std::cout << "black won unieruchomienie\n";
                whoseWon=true;
                changePlayer();
                return true;
            }
        }
        possibleFieldsToMove.clear();
        changePlayer();//zmienia gracza zpowrotem na tego ktory sprawdzal

    }
    else
    {
        changePlayer();
        thereIsCapturing(window);//i sprawdzam czy nie ma bicia po zmianie gracza
        if(capturePriority)//sprawdz
        {
            changePlayer();
            std::cout<<"jest jakies bicie przy sprawdzeniu\n";
            return false;
        }

        for(auto&b:black)//jesli wszystkie czarne sa zablokowane
        {

            if(b.kind=="queen" and !b.isCaptured)//nie sprawdza kiedy ktos zbity
                moveQuenn(window,&b);
            else if(!b.isCaptured)
                thereIsMove(window, &b);

            if(!(possibleFieldsToMove.empty()) and !b.isCaptured)//if pawn has something movement and isn't captured
            {
                break;
            }

            if(&b==&black[11]) {
                std::cout << "white won unieruchomienie\n";
                whoseWon=true;
                changePlayer();
                return true;
            }
        }
        possibleFieldsToMove.clear();
        changePlayer();
    }
    //CZY REMIS
    if(queenMovementCounter==30)
    {
        draw=true;
        std::cout<<"remis"<<std::endl;
        return true;
    }
    return false;
}
void Game::move(sf::RenderWindow &window, sf::Event&event) {//obsługa zdarzen

    if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.button == sf::Mouse::Left)//when i click
    {
        //pomocnicze dla okreslenia wspolrzednych punktu
        std::cout<<event.mouseButton.x<<" "<<event.mouseButton.y<<std::endl;
        //

        activePawn = isMouseOverPawn(window, event);
        if(activePawn!= nullptr)//and whose pawn is active
        {

            if(!capturePriority)//jesli nie ma bicia
                thereIsMove(window, activePawn);//to wtedy ustal miejsca dla ruchu

            //zacznij poruszanie pionkiem mysza
            activePawn->sprite.setScale(0.6, 0.6);
            startMove=true;
            //
        }

        // pomocniczna petla pokazujaca  jakie ruchy sa mozliwe
        for(const auto& z:possibleFieldsToMove)
            std::cout<<z->name<<std::endl;

        //pomocnicza paetla sprawdzajaca czy nie ma bicia
        if(whoseMove.color=="black")
            for(const auto&j:black)
                for(auto i:j.possibleFieldsToCapture)
                std::cout<<i.FieldToMoveAfterCapture->name<<std::endl;
        else
            for(const auto&j:white)
                for(auto i:j.possibleFieldsToCapture)
                    std::cout<<i.FieldToMoveAfterCapture->name<<std::endl;
        std::cout<<"---------"<<std::endl;
        //
    }
    else if (event.type == sf::Event::MouseButtonReleased and event.mouseButton.button == sf::Mouse::Left)//co zrobic kiedy puszcze myszke
    {

        if(activePawn!= nullptr) {//i trzymalem jakiegos pionka

            if(pawnIsPossibleSpace(window, event)){//sprawdzenie czy pionek jest nad dostepna pozycja dla bicia jesli nie ma bicia to tez zwroci false

                //usuniecie tekstur z pol bicia
                for(Field *c=beginningBoard; c<=endBoard; ++c)
                    c->isCapturing=false;

                //wyczysc wektor molziwych bic
                for(auto &b:black)
                    b.possibleFieldsToCapture.clear();//dla czarnych

                for(auto &w:white)
                    w.possibleFieldsToCapture.clear();//i bialych
                //
                thereIsSecondCapture(window);//sprawdzam czy kolejne bicie poriorytet wyczyszczony tylko dla ostatniego piona
                if(pawnWhoseCaptured->possibleFieldsToCapture.empty()) {//jeśli nie ma loejnego bicia  tzn ostatni pion ktory bil nie ma juz bicia

                    //sprawdzam czy nie ma konca gry
                    if(isItOver(window)) {
                        return;
                    }
                    else
                        std::cout<<"gramy dalej\n";
                    turnIntoQueen();//sprawdzam czy zmiana w dame poniewaz w tym miejsu nie ma juz kolejnego bicia przed zmiana gracza

                    changePlayer();//zmiana gracza
                    //usuniecie tekstur z pol bicia
                    for(Field *c=beginningBoard; c<=endBoard; ++c)
                        c->isCapturing=false;//natomiast tekstury bylyby widoczne wiec trzeba wyczyscic
                    //wyczysc wektor molziwych bic
                    for(auto &b:black)
                        b.possibleFieldsToCapture.clear();//dla czarnych

                    for(auto &w:white)
                        w.possibleFieldsToCapture.clear();//i bialych
                    //

                    thereIsCapturing(window);//i sprawdzam czy nie ma bicia po zmianie gracza
                }


            }
            activePawn->sprite.move(activePawn->position->sprite.getPosition()-activePawn->sprite.getPosition());//wykonaj ruch do ostatniej lub nowej
            activePawn->sprite.setScale(0.45, 0.45);
            possibleFieldsToMove.clear();


            //zawsze po upuszczniu pionka usun tekstury z pol mozliwych dla ruchu
            for(Field *m=beginningBoard; m<=endBoard; ++m)
                m->isActive=false;

        }
        activePawn= nullptr;//zwolnienie aktywnego pionjka po jego upuszczeniu
        startMove=false;//zatrzymanie ruchu pionka za myszka po jego upuszczniu
        //zakonczenie ruchu

    }
    // ruch za myszką NIE zmiana pozycji
    else if( startMove and event.type == sf::Event::MouseMoved and activePawn!= nullptr)//jesli jest start ruch oraz myszka sie porusza i jest aktywny pionek
    {
        lastMousePosition(window, event);
        activePawn->sprite.move((float)moveX, (float)moveY);//zmienia pozycje sprita o ruch myszka

    }
}

void Game::lastMousePosition(sf::RenderWindow &window, sf::Event &event) {
    moveX=event.mouseMove.x-lastX;
    moveY=event.mouseMove.y-lastY;

    lastX=event.mouseMove.x;
    lastY=event.mouseMove.y;

}





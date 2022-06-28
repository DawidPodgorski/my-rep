//
// Created by podgo on 22.04.2022.
//

#include "Pawn.h"
#include <iostream>
Pawn::Pawn()
{
    color="white";
    kind ="normal";
    if (!pawnW.loadFromFile("Textures/whitePawn.png") or
    (!pawnB.loadFromFile("Textures/blackPawn.png")) or
    (!queenW.loadFromFile("Textures/whiteQueen.png")) or
    (!queenB.loadFromFile("Textures/blackQueen.png")))
    {
        std::cout<<"Failed to load texture"<<std::endl;
    }
}

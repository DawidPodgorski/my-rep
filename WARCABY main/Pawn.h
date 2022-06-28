//
// Created by podgo on 25.03.2022.
//

#ifndef WARCABY_PAWN_H
#define WARCABY_PAWN_H
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
struct Field
{
    //sprites
    sf::Sprite sprite;
    sf::Sprite activeSprite;
    sf::Sprite captureSprite;
    sf::Sprite toQueenSprite;
    std::string name;

    std::string color;
    bool isFree;
    bool isActive;
    bool isCapturing;
};
class Pawn;
struct Moves
{
    Field*where= nullptr;
    int profitability=0;
    Pawn*pawn= nullptr;
};

struct Capture
{
    Field* FieldToMoveAfterCapture;
    Field* FieldBrokenPawn;
};

class Pawn{
protected:
    sf::Texture pawnW,pawnB,queenW,queenB;
public:

    std::string name;
    Field*position= nullptr;
    std::vector<Moves>moves;
    std::string color;
    std::string kind="normal";
    sf::Sprite sprite;
    bool isCaptured=false;
    std::vector<Capture> possibleFieldsToCapture;

    //constructors
    Pawn();
};


#endif //WARCABY_PAWN_H

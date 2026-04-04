#include "OracleCard.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
#include <string>
#include "OracleCard.h"

OracleCard::OracleCard(int value) : Card(CardType::Oracle, value) {
}

std::string OracleCard::str() const {
    return "Oracle(" + std::to_string(_value) + ")";
}

void OracleCard::play(Game& game, Player& player) {
    Card* top = game.peekTopDeck();

    if (top == nullptr) {
        std::cout << "Oracle: no card to peek at." << std::endl;
    }
    else {
        std::cout << "Oracle peek: " << top->str() << std::endl;
    }
}
#include "KeyCard.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
#include <string>

KeyCard::KeyCard(int value) : Card(CardType::Key, value) {
}

std::string KeyCard::str() const {
    return "Key(" + std::to_string(_value) + ")";
}

void KeyCard::play(Game& game, Player& player) {
    std::cout << "Key: no immediate effect." << std::endl;
}

void KeyCard::willAddToBank(Game& game, Player& player) {
   // empty as chest currntly handles both itself and key 
}
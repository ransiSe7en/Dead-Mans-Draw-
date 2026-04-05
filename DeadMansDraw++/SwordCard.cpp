#include "SwordCard.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
#include <string>

SwordCard::SwordCard(int value) : Card(CardType::Sword, value) {
}

std::string SwordCard::str() const {
    return "Sword(" + std::to_string(_value) + ")";
}

void SwordCard::play(Game& game, Player& player) {
    Player* other = game.getOtherPlayer();
    Card* chosen = nullptr;

    for (int i = 0; i < 10; i++) {
        CardType type = static_cast<CardType>(i);
        Card* current = other->getHighestBankCardOfSuit(type);

        if (current != nullptr) {
            if (chosen == nullptr || current->value() > chosen->value()) {
                chosen = current;
            }
        }
    }

    if (chosen == nullptr) {
        std::cout << "Sword: no card to take from the other player's bank." << std::endl;
        return;
    }

    other->removeBankCard(chosen);
    player.addToPlayArea(chosen);

    std::cout << "Sword took " << chosen->str() << " from the other player's bank into play area." << std::endl;
}
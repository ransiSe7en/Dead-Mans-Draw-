#include "CannonCard.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
#include <string>

CannonCard::CannonCard(int value) : Card(CardType::Cannon, value) {
}

std::string CannonCard::str() const {
    return "Cannon(" + std::to_string(_value) + ")";
}

void CannonCard::play(Game& game, Player& player) {
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
        std::cout << "Cannon: no card to discard from the other player's bank." << std::endl;
        return;
    }

    other->removeBankCard(chosen);
    game.addToDiscard(chosen);

    std::cout << "Cannon discarded " << chosen->str() << " from the other player's bank." << std::endl;
}
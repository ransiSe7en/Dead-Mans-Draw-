#include "HookCard.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
#include <string>

HookCard::HookCard(int value) : Card(CardType::Hook, value) {
}

std::string HookCard::str() const {
    return "Hook(" + std::to_string(_value) + ")";
}

void HookCard::play(Game& game, Player& player) {
    Card* chosen = nullptr;

    for (int i = 0; i < 10; i++) {
        CardType type = static_cast<CardType>(i);
        Card* current = player.getHighestBankCardOfSuit(type);

        if (current != nullptr) {
            if (chosen == nullptr || current->value() > chosen->value()) {
                chosen = current;
            }
        }
    }

    if (chosen == nullptr) {
        std::cout << "Hook: no card to bring from bank to play area." << std::endl;
        return;
    }

    player.removeBankCard(chosen);
    player.addToPlayArea(chosen);

    std::cout << "Hook moved " << chosen->str() << " from bank to play area." << std::endl;
}
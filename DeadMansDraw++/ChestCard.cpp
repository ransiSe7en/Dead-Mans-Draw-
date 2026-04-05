#include "ChestCard.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
#include <string>

ChestCard::ChestCard(int value) : Card(CardType::Chest, value) {
}

std::string ChestCard::str() const {
    return "Chest(" + std::to_string(_value) + ")";
}

void ChestCard::play(Game& game, Player& player) {
    std::cout << "Chest: no immediate effect." << std::endl;
}

void ChestCard::willAddToBank(Game& game, Player& player) {
    if (!player.hasTypeInPlayArea(CardType::Key)) {
        return;
    }

    int bonusCount = player.playAreaSize();

    std::cout << "Chest + Key: drawing " << bonusCount
        << " bonus card(s) from discard pile into bank." << std::endl;

    for (int i = 0; i < bonusCount; i++) {
        Card* bonus = game.drawOneFromDiscard();
        if (bonus == nullptr) {
            std::cout << "No more cards in discard pile." << std::endl;
            return;
        }

        player.addBankCard(bonus);
        std::cout << "  Bonus banked: " << bonus->str() << std::endl;
    }
}
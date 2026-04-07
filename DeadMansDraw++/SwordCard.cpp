#include "SwordCard.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <vector>

SwordCard::SwordCard(int value) : Card(CardType::Sword, value) {
}

std::string SwordCard::str() const {
    return "Sword(" + std::to_string(_value) + ")";
}

void SwordCard::play(Game& game, Player& player) {
    Player* other = game.getOtherPlayer();
    std::vector<Card*> bankCards = other->getBankCards();

    if (bankCards.empty()) {
        std::cout << "Sword: no card available in opponent's bank." << std::endl;
        return;
    }

    std::cout << "Select a card from " << other->getName() << "'s bank:" << std::endl;

    for (int i = 0; i < static_cast<int>(bankCards.size()); i++) {
        std::cout << "  " << (i + 1) << ". " << bankCards[i]->str() << std::endl;
    }

    int choice;
    std::cin >> choice;

    if (choice < 1 || choice > static_cast<int>(bankCards.size())) {
        std::cout << "Sword: invalid choice." << std::endl;
        return;
    }

    Card* chosen = bankCards[choice - 1];

    other->removeBankCard(chosen);
    bool bust = player.playMovedCard(chosen, game);

    if (bust) {
        std::cout << "Bust!" << std::endl;
        player.resolveBustWithAnchor(game);
        player.setBustedThisTurn(true);
        return;
    }

    std::cout << "Sword took " << chosen->str() << " from " << other->getName() << "'s bank into play area." << std::endl;
}
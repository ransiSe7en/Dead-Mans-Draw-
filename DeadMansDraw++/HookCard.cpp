#include "HookCard.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <vector>

HookCard::HookCard(int value) : Card(CardType::Hook, value) {
}

std::string HookCard::str() const {
    return "Hook(" + std::to_string(_value) + ")";
}

void HookCard::play(Game& game, Player& player) {
    std::vector<Card*> bankCards = player.getBankCards();

    if (bankCards.empty()) {
        std::cout << "Hook: no card available in bank." << std::endl;
        return;
    }

    std::cout << "Select a card from your bank to play:" << std::endl;
    for (int i = 0; i < static_cast<int>(bankCards.size()); i++) {
        std::cout << "  " << (i + 1) << ". " << bankCards[i]->str() << std::endl;
    }

    int choice;
    std::cin >> choice;

    if (choice < 1 || choice > static_cast<int>(bankCards.size())) {
        std::cout << "Hook: invalid choice." << std::endl;
        return;
    }

    Card* chosen = bankCards[choice - 1];

    player.removeBankCard(chosen);

    bool bust = player.playMovedCard(chosen, game);

    if (bust) {
        std::cout << "Bust!" << std::endl;
        player.resolveBustWithAnchor(game);
        return;
    }

    std::cout << "Hook moved " << chosen->str() << " from bank to play area." << std::endl;
}
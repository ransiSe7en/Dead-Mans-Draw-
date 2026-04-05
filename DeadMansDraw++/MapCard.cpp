#include "MapCard.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <vector>

MapCard::MapCard(int value) : Card(CardType::Map, value) {
}

std::string MapCard::str() const {
    return "Map(" + std::to_string(_value) + ")";
}

void MapCard::play(Game& game, Player& player) {
    std::vector<Card*> drawn = game.drawFromDiscard(3);

    if (drawn.empty()) {
        std::cout << "Map: no cards available in discard pile." << std::endl;
        return;
    }

    std::cout << "Select a card from discard pile to play:" << std::endl;
    for (int i = 0; i < static_cast<int>(drawn.size()); i++) {
        std::cout << "  " << (i + 1) << ". " << drawn[i]->str() << std::endl;
    }

    int choice;
    std::cin >> choice;

    if (choice < 1 || choice > static_cast<int>(drawn.size())) {
        std::cout << "Map: invalid choice." << std::endl;

        for (auto c : drawn) {
            game.addToDiscard(c);
        }
        return;
    }

    Card* chosen = drawn[0];
    player.addToPlayArea(chosen);

    std::cout << "Map: played " << chosen->str()
        << " from discard pile into play area." << std::endl;

    for (auto c : drawn) {
        if (c != chosen) {
            game.addToDiscard(c);
        }
    }
}
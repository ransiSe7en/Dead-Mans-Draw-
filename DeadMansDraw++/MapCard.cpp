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

    Card* chosen = drawn[0];

    for (auto c : drawn) {
        if (c->value() > chosen->value()) {
            chosen = c;
        }
    }

    player.addToPlayArea(chosen);

    std::cout << "Map: played " << chosen->str()
        << " from discard pile into play area." << std::endl;

    for (auto c : drawn) {
        if (c != chosen) {
            game.addToDiscard(c);
        }
    }
}
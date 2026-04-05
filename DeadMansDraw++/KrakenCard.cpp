#include "KrakenCard.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
#include <string>

KrakenCard::KrakenCard(int value) : Card(CardType::Kraken, value) {
}

std::string KrakenCard::str() const {
    return "Kraken(" + std::to_string(_value) + ")";
}

void KrakenCard::play(Game& game, Player& player) {
    std::cout << "Kraken: must draw and play 3 more cards." << std::endl;
    game.forceKrakenDraws(player, 3);
}
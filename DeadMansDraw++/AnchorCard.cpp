#include "AnchorCard.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
#include <string>

AnchorCard::AnchorCard(int value) : Card(CardType::Anchor, value) {
}

std::string AnchorCard::str() const {
    return "Anchor(" + std::to_string(_value) + ")";
}

void AnchorCard::play(Game& game, Player& player) {
    player.setAnchorActive(true);
    std::cout << "Anchor: cards drawn before Anchor are now safe." << std::endl;
}
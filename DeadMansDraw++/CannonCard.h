#pragma once
#include "Card.h"

class CannonCard : public Card {
public:
    CannonCard(int value);
    std::string str() const override;
    void play(Game& game, Player& player) override;
};
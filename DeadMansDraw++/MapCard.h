#pragma once
#include "Card.h"

class MapCard : public Card {
public:
    MapCard(int value);
    std::string str() const override;
    void play(Game& game, Player& player) override;
};
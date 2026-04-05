#pragma once
#include "Card.h"

class AnchorCard : public Card {
public:
    AnchorCard(int value);
    std::string str() const override;
    void play(Game& game, Player& player) override;
};
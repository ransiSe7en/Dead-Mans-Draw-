#pragma once
#include "Card.h"

class HookCard : public Card {
public:
    HookCard(int value);
    std::string str() const override;
    void play(Game& game, Player& player) override;
};
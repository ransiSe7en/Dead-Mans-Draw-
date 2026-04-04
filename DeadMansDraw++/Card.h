
#pragma once
#include <string>

class Game;
class Player;

enum class CardType {
    Cannon, Chest, Key, Anchor, Sword, Hook, Oracle, Map, Mermaid, Kraken
};

class Card {
protected:
    CardType _type;
    int _value;

public:
    Card(CardType type, int value);
    virtual ~Card();

    CardType type() const;
    int value() const;

    virtual std::string str() const = 0;
    virtual void play(Game& game, Player& player) = 0;
    virtual void willAddToBank(Game& game, Player& player);
};
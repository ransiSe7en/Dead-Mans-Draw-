#pragma once
#include <vector>
#include <string>

class Card;
class Game;

class Player {
private:
    std::string _name;
    std::vector<Card*> _bank;
    std::vector<Card*> _playArea;

public:
    Player();

    bool playCard(Card* card, Game& game);

    void addToPlayArea(Card* card);
    bool hasSuitInPlayArea(Card* card) const;
    bool isBust() const;

    void bankPlayArea(Game& game);
    void discardPlayArea(Game& game);

    int calculateScore() const;

    void printBank() const;
    void printPlayArea() const;

    std::string getName() const;
};
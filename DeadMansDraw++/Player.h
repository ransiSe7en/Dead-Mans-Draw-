#pragma once
#include <vector>
#include <string>
#include "Card.h"

class Game;

class Player {
private:
    std::string _name;
    std::vector<Card*> _bank;
    std::vector<Card*> _playArea;
    bool _anchorActive;

public:
    Player();

    bool playCard(Card* card, Game& game);
    bool playMovedCard(Card* card, Game& game);

    void addToPlayArea(Card* card);
    bool hasSuitInPlayArea(Card* card) const;
    bool isBust() const;

    void bankPlayArea(Game& game);
    void discardPlayArea(Game& game);

    int calculateScore() const;

    void printBank() const;
    void printPlayArea() const;

    std::string getName() const;

    Card* getHighestBankCardOfSuit(CardType type) const;
    void removeBankCard(Card* card);

    void addBankCard(Card* card);

    std::vector<Card*> getBankCards() const;

    bool hasTypeInPlayArea(CardType type) const;
    int playAreaSize() const;

    bool hasAnchorActive() const;
    void setAnchorActive(bool active);
    void resolveBustWithAnchor(Game& game);
};
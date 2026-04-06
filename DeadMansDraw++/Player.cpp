#include <algorithm>
#include <map>
#include "Player.h"
#include "Card.h"
#include "Game.h"
#include <iostream>
#include <cstdlib>

Player::Player(): _anchorActive(false) {
    std::string names[] = { "Sam", "Billy", "Jen", "Bob", "Sally", "Joe", "Sue", "Sasha", "Tina", "Marge" };
    _name = names[rand() % 10];
}

bool Player::playCard(Card* card, Game& game) {
    addToPlayArea(card);

    if (isBust()) {
        return true;
    }

    card->play(game, *this);
    return false;
}

bool Player::playMovedCard(Card* card, Game& game) {
    addToPlayArea(card);

    if (isBust()) {
        return true;
    }

    card->play(game, *this);
    return false;
}

void Player::addToPlayArea(Card* card) {
    _playArea.push_back(card);
}

bool Player::hasSuitInPlayArea(Card* card) const {
    for (auto c : _playArea) {
        if (c->type() == card->type()) {
            return true;
        }
    }
    return false;
}

bool Player::isBust() const {
    for (size_t i = 0; i < _playArea.size(); i++) {
        for (size_t j = i + 1; j < _playArea.size(); j++) {
            if (_playArea[i]->type() == _playArea[j]->type()) {
                return true;
            }
        }
    }
    return false;
}

void Player::bankPlayArea(Game& game) {
    for (auto c : _playArea) {
        c->willAddToBank(game, *this);
        _bank.push_back(c);
    }
    _playArea.clear();
    _anchorActive = false;
}

void Player::discardPlayArea(Game& game) {
    for (auto c : _playArea) {
        game.addToDiscard(c);
    }
    _playArea.clear();
}

int Player::calculateScore() const {
    int highest[10] = {0};

    for (auto c : _bank) {
        int index = static_cast<int>(c->type());
        if (c->value() > highest[index]) {
            highest[index] = c->value();
        }
    }

    int total = 0;
    for (int i = 0; i < 10; i++) {
        total += highest[i];
    }
    return total; 
}

void Player::printCollection(const std::vector<Card*>& collection, const std::string& title) const {
    std::cout << title << ":" << std::endl;

    if (collection.empty()) {
        std::cout << "  Empty" << std::endl;
        return;
    }

    std::map<CardType, std::vector<Card*>> grouped;

    for (auto c : collection) {
        grouped[c->type()].push_back(c);
    }

    for (auto& pair : grouped) {
        std::vector<Card*>& cards = pair.second;

        std::sort(cards.begin(), cards.end(), [](Card* a, Card* b) {
            return a->value() > b->value();
            });

        std::cout << "  ";
        for (int i = 0; i < static_cast<int>(cards.size()); i++) {
            if (i > 0) {
                std::cout << ", ";
            }
            std::cout << cards[i]->str();
        }
        std::cout << std::endl;
    }
}


void Player::printBank() const {
    printCollection(_bank, "Bank");
}

void Player::printPlayArea() const {
    printCollection(_playArea, "Play Area");
}

std::string Player::getName() const {
    return _name;
}

Card* Player::getHighestBankCardOfSuit(CardType type) const {
    Card* highest = nullptr;

    for (auto c : _bank) {
        if (c->type() == type) {
            if (highest == nullptr || c->value() > highest->value()) {
                highest = c;
            }
        }
    }
    return highest;
}

void Player::removeBankCard(Card* card) {
    for (auto it = _bank.begin(); it != _bank.end(); ++it) {
        if (*it == card) {
            _bank.erase(it);
            return;
        }
    }
}

void Player::addBankCard(Card* card) {
    _bank.push_back(card);
}

std::vector<Card*> Player::getBankCards() const {
    return _bank;
}

bool Player::hasTypeInPlayArea(CardType type) const {
    for (auto c : _playArea) {
        if (c->type() == type) {
            return true;
        }
    }
    return false;
}

int Player::playAreaSize() const {
    return static_cast<int>(_playArea.size());
}

bool Player::hasAnchorActive() const {
    return _anchorActive;
}

void Player::setAnchorActive(bool active) {
    _anchorActive = active;
}

void Player::resolveBustWithAnchor(Game& game) {
    if (!_anchorActive) {
        discardPlayArea(game);
        return;
    }

    int anchorIndex = -1;

    for (int i = 0; i < static_cast<int>(_playArea.size()); i++) {
        if (_playArea[i]->type() == CardType::Anchor) {
            anchorIndex = i;
            break;
        }
    }

    if (anchorIndex == -1) {
        discardPlayArea(game);
        _anchorActive = false;
        return;
    }

    for (int i = 0; i < anchorIndex; i++) {
        _bank.push_back(_playArea[i]);
    }

    for (int i = anchorIndex; i < static_cast<int>(_playArea.size()); i++) {
        game.addToDiscard(_playArea[i]);
    }

    _playArea.clear();
    _anchorActive = false;
}
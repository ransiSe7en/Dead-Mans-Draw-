#include "Player.h"
#include "Card.h"
#include "Game.h"
#include <iostream>

Player::Player() {
    static int count = 1;
    _name = "Player " + std::to_string(count++);
}

bool Player::playCard(Card* card, Game& game) {
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
}

void Player::discardPlayArea(Game& game) {
    for (auto c : _playArea) {
        game.addToDiscard(c);
    }
    _playArea.clear();
}

int Player::calculateScore() const {
    return 0; 
}

void Player::printBank() const {
    std::cout << "Bank: " << std::endl;
    if (_bank.empty()) {
        std::cout << "  Empty" << std::endl;
        return;
    }

    for (auto c : _bank) {
        std::cout << "  " << c->str() << std::endl;
    }
}

void Player::printPlayArea() const {
    std::cout << "Play Area: " << std::endl;
    if (_playArea.empty()) {
        std::cout << "  Empty" << std::endl;
        return;
    }

    for (auto c : _playArea) {
        std::cout << "  " << c->str() << std::endl;
    }
}

std::string Player::getName() const {
    return _name;
}
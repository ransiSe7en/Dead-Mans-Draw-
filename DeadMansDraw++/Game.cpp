#include "Game.h"
#include "Player.h"
#include "Card.h"
#include <iostream>

Game::Game() {
    _currentPlayerIndex = 0;
    _round = 1;
    _turn = 1;
}

Game::~Game() {
    for (auto p : _players) delete p;
    for (auto c : _deck) delete c;
    for (auto c : _discardPile) delete c;
}

void Game::initialiseGame() {
    _players.push_back(new Player());
    _players.push_back(new Player());
}

void Game::createDeck() {
}

void Game::shuffleDeck() {
}

void Game::start() {
    initialiseGame();
    std::cout << "Game started" << std::endl;
}

void Game::playTurn() {
    std::cout << "Playing turn..." << std::endl;
}

Card* Game::drawCard() {
    if (_deck.empty()) return nullptr;

    Card* c = _deck.back();
    _deck.pop_back();
    return c;
}

void Game::addToDiscard(Card* card) {
    _discardPile.push_back(card);
}

Player* Game::getCurrentPlayer() {
    return _players[_currentPlayerIndex];
}

Player* Game::getOtherPlayer() {
    return _players[1 - _currentPlayerIndex];
}

void Game::nextPlayer() {
    _currentPlayerIndex = 1 - _currentPlayerIndex;
}
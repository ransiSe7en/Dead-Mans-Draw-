#include "Game.h"
#include "Player.h"
#include "Card.h"
#include <iostream>
#include "MermaidCard.h"
#include "OracleCard.h"
#include "CannonCard.h"
#include "HookCard.h"
#include "SwordCard.h"
#include "MapCard.h"
#include "KrakenCard.h"
#include "ChestCard.h"
#include "KeyCard.h"
#include "AnchorCard.h"

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
    _deck.push_back(new MermaidCard(4));
    _deck.push_back(new MermaidCard(5));
    _deck.push_back(new MermaidCard(6));
    _deck.push_back(new MermaidCard(7));
}

void Game::shuffleDeck() {
}

void Game::start() {
    initialiseGame();
    createDeck();
    shuffleDeck();

    while (!isGameOver()) {
        playTurn();

        if (isGameOver()) {
            break;
        }

        nextPlayer();
        _turn++;
        _round = getRound();
    }

    printFinalScores();
}

int Game::getRound() const {
    return ((_turn - 1) / 2) + 1;
}

bool Game::isGameOver() const {
    return _deck.empty() || _turn > 20;
}

void Game::playTurn() {
    Player* player = getCurrentPlayer();

    std::cout << std::endl;
    std::cout << "Round " << getRound() << ", Turn " << _turn << std::endl;
    std::cout << player->getName() << "'s turn" << std::endl;
    player->printBank();

    bool continueDrawing = true;

    while (continueDrawing) {
        Card* drawn = drawCard();

        if (drawn == nullptr) {
            std::cout << "Deck is empty." << std::endl;
            return;
        }

        std::cout << "Drew: " << drawn->str() << std::endl;

        bool bust = player->playCard(drawn, *this);

        if (bust) {
            std::cout << "Bust!" << std::endl;
            player->resolveBustWithAnchor(*this);
            player->printBank();
            break;
        }

        player->printPlayArea();

        if (_deck.empty()) {
            std::cout << "Deck is empty." << std::endl;
            player->bankPlayArea(*this);
            std::cout << "Cards banked." << std::endl;
            player->printBank();
            std::cout << "Score: " << player->calculateScore() << std::endl;
            return;
        }

        std::string choice;
        std::cout << "Draw again? (y/n): ";
        std::cin >> choice;

        if (choice != "y") {
            player->bankPlayArea(*this);
            std::cout << "Cards banked." << std::endl;
            player->printBank();
            std::cout << "Score: " << player->calculateScore() << std::endl;
            continueDrawing = false;
        }
    }
}

Card* Game::drawCard() {
    if (_deck.empty()) {
        return nullptr;
    }

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

Card* Game::peekTopDeck() const {
    if (_deck.empty()) {
        return nullptr;
    }
    return _deck.back();
}

std::vector<Card*> Game::drawFromDiscard(int count) {
    std::vector<Card*> drawn;

    for (int i = 0; i < count; i++) {
        if (_discardPile.empty()) {
            break;
        }

        drawn.push_back(_discardPile.back());
        _discardPile.pop_back();
    }

    return drawn;
}

void Game::forceKrakenDraws(Player& player, int count) {
    for (int i = 0; i < count; i++) {
        Card* drawn = drawCard();

        if (drawn == nullptr) {
            std::cout << "Kraken: deck is empty." << std::endl;
            return;
        }

        std::cout << "Kraken forced draw: " << drawn->str() << std::endl;

        bool bust = player.playCard(drawn, *this);

        if (bust) {
            std::cout << "Bust!" << std::endl;
            player.resolveBustWithAnchor(*this);
            return;
        }

        player.printPlayArea();
    }
}

Card* Game::drawOneFromDiscard() {
    if (_discardPile.empty()) {
        return nullptr;
    }

    Card* card = _discardPile.back();
    _discardPile.pop_back();
    return card;
}

void Game::printFinalScores() const {
    std::cout << std::endl;
    std::cout << "===== Final Scores =====" << std::endl;

    int score1 = _players[0]->calculateScore();
    int score2 = _players[1]->calculateScore();

    std::cout << _players[0]->getName() << ": " << score1 << std::endl;
    std::cout << _players[1]->getName() << ": " << score2 << std::endl;

    if (score1 > score2) {
        std::cout << _players[0]->getName() << " wins!" << std::endl;
    }
    else if (score2 > score1) {
        std::cout << _players[1]->getName() << " wins!" << std::endl;
    }
    else {
        std::cout << "It's a tie!" << std::endl;
    }
}
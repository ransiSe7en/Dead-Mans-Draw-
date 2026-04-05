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
    _deck.push_back(new MermaidCard(6));
    _deck.push_back(new AnchorCard(5));
    _deck.push_back(new OracleCard(3));
}

void Game::shuffleDeck() {
}

void Game::start() {
    initialiseGame();
    createDeck();

    std::cout << "Game started" << std::endl;

    for (int i = 0; i < 2; i++) {
        playTurn();
        nextPlayer();
    }

    Card* drawn = drawCard();
    if (drawn != nullptr) {
        bool bust = getCurrentPlayer()->playCard(drawn, *this);
        std::cout << "Drew: " << drawn->str() << std::endl;
        
        if (bust) {
            std::cout << "Player busted!" << std::endl;
        }
        else {
            getCurrentPlayer()->printPlayArea();
        }
    
    }
}

void Game::playTurn() {
    Player* player = getCurrentPlayer();

    std::cout << std::endl;
    std::cout << "----- Turn " << _turn << " -----" << std::endl;
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

    _turn++;
}

Card* Game::drawCard() {
    if (_deck.empty()) {
        std::cout << "Deck is empty" << std::endl;
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
            player.discardPlayArea(*this);
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
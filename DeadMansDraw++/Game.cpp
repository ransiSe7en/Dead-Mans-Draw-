#include "Game.h"
#include "Player.h"
#include "Card.h"
#include <iostream>
#include "MermaidCard.h"
#include "OracleCard.h"
#include "CannonCard.h"

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
    _deck.push_back(new CannonCard(5));
    _deck.push_back(new MermaidCard(6));
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
            player->discardPlayArea(*this);
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
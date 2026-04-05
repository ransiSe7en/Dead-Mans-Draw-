#pragma once
#include <vector>

class Player;
class Card;

class Game {
private:
    std::vector<Player*> _players;
    std::vector<Card*> _deck;
    std::vector<Card*> _discardPile;

    int _currentPlayerIndex;
    int _round;
    int _turn;

public:
    Game();
    ~Game();

    void initialiseGame();
    void createDeck();
    void shuffleDeck();

    void start();
    void playTurn();

    Card* drawCard();
    void addToDiscard(Card* card);

    Player* getCurrentPlayer();
    Player* getOtherPlayer();

    void nextPlayer();

    Card* peekTopDeck() const;

    std::vector<Card*> drawFromDiscard(int count);
};
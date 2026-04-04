#include "Card.h"

Card::Card(CardType type, int value) : _type(type), _value(value) {}

Card::~Card() {}

CardType Card::type() const {
    return _type;
}

int Card::value() const {
    return _value;
}

void Card::willAddToBank(Game&, Player&) {
    // default does nothing
}
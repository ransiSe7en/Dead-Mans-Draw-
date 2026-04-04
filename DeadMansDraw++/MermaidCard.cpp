#include "MermaidCard.h"
#include "Game.h"
#include "Player.h"
#include <string>

MermaidCard::MermaidCard(int value) : Card(CardType::Mermaid, value) {
}

std::string MermaidCard::str() const {
    return "Mermaid(" + std::to_string(_value) + ")";
}

void MermaidCard::play(Game& game, Player& player) {

}
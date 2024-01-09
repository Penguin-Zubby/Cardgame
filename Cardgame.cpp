#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <memory>

using namespace std;

// Class representing a playing card
class Card {
public:
  string suit;
  string rank;
  int value;
// Attributes are set in the constructor and not modified afterward.
  Card(string suit, string rank, int value) : suit(suit), rank(rank), value(value) {}
};

// Class representing a player
class Player {
public:
  string name;
  int skill_level;
  int total_points;
// Attributes are set in the constructor and not modified afterward.
  Player(string name, int skill_level) : name(name), skill_level(skill_level), total_points(0) {}
};
// Using std::unique_ptr for Card and Player
using CardPtr = std::unique_ptr<Card>;
using PlayerPtr = std::unique_ptr<Player>;

// Function to generate a deck of cards
vector<CardPtr> generateDeck() {
  vector<CardPtr> deck;
  vector<string> suits = {"Hearts", "Diamonds", "Clubs", "Spades"};
  vector<string> ranks = {"Ace",  "Two",   "Three", "Four", "Five",
                          "Six",  "Seven", "Eight", "Nine", "Ten",
                          "Jack", "Queen", "King"};
  vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 13};

  // Nested loops to create each card and add it to the deck
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 13; j++) {
      deck.push_back(std::make_unique<Card>(suits[i], ranks[j], values[j]));// Creating instances with unique pointers
    }
  }

  return deck;
}

// Function to generate players
vector<PlayerPtr> generatePlayers() {
  vector<PlayerPtr> players;
  vector<string> names = {"Tom Cruise", "Jason Statham", "John Cena"};

  // Loop to create each player and add them to the vector
  for (int i = 0; i < 3; i++) {
    players.push_back(std::make_unique<Player>(names[i], rand() % 10 + 1));
  }

  return players;
}

// Function to draw a specified number of cards from the deck
vector<CardPtr> drawCards(vector<CardPtr> &deck, int number_of_cards) {
  vector<CardPtr> drawn_cards;

  // Loop to randomly draw cards from the deck
  for (int i = 0; i < number_of_cards; i++) {
    int random_index = rand() % deck.size();
    drawn_cards.push_back(std::move(deck[random_index]));
    deck.erase(deck.begin() + random_index);
  }

  return drawn_cards;
}

// Function to calculate the total points of a set of cards
int calculatePoints(vector<CardPtr> &cards) {
  int points = 0;
  for (CardPtr &card : cards) {
    points += card->value;
  }

  return points;
}

// Function to determine the winner among players
PlayerPtr getWinner(vector<PlayerPtr> &players) {
  PlayerPtr winner = std::move(players[0]);

  // Loop to find the player with the highest total points
  for (int i = 1; i < players.size(); i++) {
    if (players[i]->total_points > winner->total_points) {
      winner = std::move(players[i]);
    }
  }

  return winner;
}

int main() {
  srand(static_cast<unsigned>(time(0)));

  // Generate the initial deck of cards and players
  vector<CardPtr> deck = generateDeck();
  vector<PlayerPtr> players = generatePlayers();

  // Simulate 5 rounds of the game
  for (int i = 0; i < 5; i++) {
    cout << "\nGame " << i + 1 << ":\n";

    // Each player draws 3 cards and accumulates points
    for (int j = 0; j < players.size(); j++) {
      vector<CardPtr> drawn_cards = drawCards(deck, 3);
      int points = calculatePoints(drawn_cards) * players[j]->skill_level;
      players[j]->total_points += points;
      cout << "Player " << players[j]->name << " has drawn cards worth "
           << points << " points.\n";
    }
  }

  // Determine and display the winner of the game
  PlayerPtr winner = getWinner(players);
  cout << "\nThe winner is: " << winner->name << " with " << winner->total_points
       << " points.\n";

  return 0;
}

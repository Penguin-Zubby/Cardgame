#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Card {
public:
    virtual void display() const = 0;  // Pure virtual function for polymorphism
    virtual int getSkillLevel() const = 0;  // Another pure virtual function

    virtual ~Card() {}  // Virtual destructor for polymorphic behavior
};

class NumberCard : public Card {
private:
  string card_name;
  string suit;
  int skill_level;		

public:
    NumberCard(const string& name, const string& s, int level) : cardName(name), suit(s), skillLevel(level) {}

    void display() const override {
        cout << "Number Card: " << cardName << " of " << suit;
    }

    int getSkillLevel() const override {
        return skillLevel;
    }
};

class PictureCard : public Card {
private:
    string cardName;
    string suit;
    int skillLevel;

public:
    PictureCard(const string& name, const string& s, int level) : cardName(name), suit(s), skillLevel(level) {}

    void display() const override {
        cout << "Picture Card: " << cardName << " of " << suit;
    }

    int getSkillLevel() const override {
        return skillLevel;
    }
};

// Additional classes and interfaces can be added for more complex designs
void initializeDeck(Card* deck, int size);
void shuffleDeck(Card* deck, int size);
void dealCards(Card* deck, int size, int numCards);

int main() {
  srand(static_cast<unsigned int>(time(0)));

  const int deckSize = 52;
  Card* deck = new Card[deckSize];

  initializeDeck(deck, deckSize);
  shuffleDeck(deck, deckSize);

  int numGuesses = 0;
  int score = 0;

  const int numCardsToDeal = 5;
  dealCards(deck, deckSize, numCardsToDeal);

  for (int i = 0; i < numCardsToDeal; ++i) {
    cout << "Guess the card: ";
    deck[i].display();
    cout << "\n";
    
    numGuesses++;
    }

    cout << "Game Over! Your Score: " << score << " out of " << numGuesses << "\n";

    delete[] deck;

    return 0;
}
void initializeDeck(Card* deck, int size) {
    // Similar initialization logic with the use of classes
}

void shuffleDeck(Card* deck, int size) {
    // Similar shuffling logic
}

void dealCards(Card* deck, int size, int numCards) {
    cout << "Dealing " << numCards << " cards:\n";

    for (int i = 0; i < numCards; ++i) {
        deck[i].display();
        cout << "\n";
    }

    cout << "\n";
}

/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA5
 * Shuffle.cpp
 * Top level client
***/

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

// Function to perform a perfect shuffle on a deck
std::vector<int> perfectShuffle(const std::vector<int>& deck) {
    int n = deck.size();
    int mid = n / 2;
    std::vector<int> shuffledDeck(n);

    // Splitting the deck into two halves
    std::vector<int> leftHalf(deck.begin(), deck.begin() + mid);
    std::vector<int> rightHalf(deck.begin() + mid, deck.end());

    // Merging the two halves alternately
    int leftIndex = 0, rightIndex = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0)
            shuffledDeck[i] = rightHalf[rightIndex++];
        else
            shuffledDeck[i] = leftHalf[leftIndex++];
    }

    return shuffledDeck;
}

// Function to find the order of a perfect shuffle
int findOrder(int n) {
    int order = 1;
    std::vector<int> deck(n);
    for (int i = 0; i < n; i++) {
        deck[i] = i;
    }

    std::vector<int> originalDeck = deck;
    deck = perfectShuffle(deck);

    while (deck != originalDeck) {
        deck = perfectShuffle(deck);
        order++;
    }

    return order;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <deck_size>" << std::endl;
        return 1;
    }

    int deckSize = std::stoi(argv[1]);
    std::cout << "deck size       shuffle count" << std::endl;
    std::cout << "------------------------------" << std::endl;
    for (int i = 1; i <= deckSize; i++) {
        int order = findOrder(i);
        std::cout << " " << i;
        std::cout << "               ";
        if (order < 10)
            std::cout << " ";
        std::cout << order << std::endl;
    }

    return 0;
}

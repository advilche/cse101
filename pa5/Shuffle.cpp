#include <iostream>
#include <iomanip>
#include "List.h" // Assuming List.h defines the List ADT and is provided

// Function to perform a perfect shuffle on a List
void shuffle(List& D) {
    int n = D.length();
    int mid = n / 2;

    // Create two temporary lists to represent the two halves
    List leftHalf, rightHalf;

    // Split the original list into two halves
    D.moveFront();
    for (int i = 0; i < mid; ++i) {
        leftHalf.insertAfter(D.peekNext());
        D.moveNext();
    }
    while (D.position() < n) {
        rightHalf.insertAfter(D.peekNext());
        D.moveNext();
    }

    // Merge the two halves back into the original list
    D.clear();
    leftHalf.moveFront();
    rightHalf.moveFront();
    while (leftHalf.position() < leftHalf.length() || rightHalf.position() < rightHalf.length()) {
        if (rightHalf.position() < rightHalf.length()) {
            D.insertAfter(rightHalf.peekNext());
            rightHalf.moveNext();
        }
        if (leftHalf.position() < leftHalf.length()) {
            D.insertAfter(leftHalf.peekNext());
            leftHalf.moveNext();
        }
    }
}

int main(int argc, char* argv[]) {
    // Ensure a valid command-line argument
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <max_deck_size>" << std::endl;
        return EXIT_FAILURE;
    }

    int maxDeckSize = std::stoi(argv[1]);

    if (maxDeckSize <= 0) {
        std::cerr << "Error: max_deck_size must be a positive integer." << std::endl;
        return EXIT_FAILURE;
    }

    // Print table header
    std::cout << "deck size       shuffle count\n";
    std::cout << "------------------------------\n";

    // Perform shuffle operations for deck sizes from 1 to maxDeckSize
    for (int n = 1; n <= maxDeckSize; ++n) {
        List deck;

        // Initialize the deck with integers 0 through n-1
        for (int i = 0; i < n + 1; ++i) {
            deck.insertAfter(i);
        }

        int shuffleCount = 0;

        // Shuffle until the deck returns to its original order
        List originalDeck = deck; // Copy the original deck
        do {
            shuffle(deck);
            ++shuffleCount;
        } while (!(deck == originalDeck));

        // Print the result for this deck size
        std::cout << std::setw(5) << n << std::setw(18) << shuffleCount << '\n';
    }

    return EXIT_SUCCESS;
}
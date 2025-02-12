
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int getCardValue(int card, int currentScore) {
    if (card >= 11 && card <= 13) return 10;  // Face cards
    if (card == 1) {  // Ace
        return (currentScore + 11 <= 21) ? 11 : 1;
    }
    return card;
}

void displayCard(int card) {
    if (card == 1) cout << "Ace";
    else if (card == 11) cout << "Jack";
    else if (card == 12) cout << "Queen";
    else if (card == 13) cout << "King";
    else cout << card;
}

int main() {
    double money = 1000.00;
    double bet = 0;
    char playAgain = 'y';

    srand(time(0));

    while (playAgain == 'y' || playAgain == 'Y') {
        cout << "\nYou have $" << money << endl;
        cout << "Place your bet ($5 minimum, $500 maximum): $";
        cin >> bet;

        while (bet < 5 || bet > 500 || bet > money) {
            cout << "Please enter a valid bet between $5 and $" << min(500.0, money) << ": $";
            cin >> bet;
        }

        // Deal initial cards
        int playerCards[10] = {0};
        int dealerCards[10] = {0};
        int playerCardCount = 2;
        int dealerCardCount = 2;
        
        playerCards[0] = rand() % 13 + 1;
        playerCards[1] = rand() % 13 + 1;
        dealerCards[0] = rand() % 13 + 1;
        dealerCards[1] = rand() % 13 + 1;

        int playerScore = getCardValue(playerCards[0], 0) + getCardValue(playerCards[1], getCardValue(playerCards[0], 0));
        int dealerScore = getCardValue(dealerCards[0], 0);

        // Show cards
        cout << "\nDealer's up card: ";
        displayCard(dealerCards[0]);
        cout << "\nYour cards: ";
        displayCard(playerCards[0]);
        cout << ", ";
        displayCard(playerCards[1]);
        cout << " (Total: " << playerScore << ")" << endl;

        // Player's turn
        bool canDoubleDown = (money >= bet * 2);
        char action = 'x';
        
        while (playerScore < 21 && (action != 's' && action != 'S' && action != 'd' && action != 'D')) {
            if (canDoubleDown) {
                cout << "Hit (H), Stand (S), or Double Down (D)? ";
            } else {
                cout << "Hit (H) or Stand (S)? ";
            }
            cin >> action;

            if ((action == 'd' || action == 'D') && canDoubleDown) {
                bet *= 2;
                playerCards[playerCardCount] = rand() % 13 + 1;
                playerScore += getCardValue(playerCards[playerCardCount], playerScore);
                cout << "New card: ";
                displayCard(playerCards[playerCardCount]);
                cout << " (Total: " << playerScore << ")" << endl;
                break;
            } else if (action == 'h' || action == 'H') {
                playerCards[playerCardCount] = rand() % 13 + 1;
                playerScore += getCardValue(playerCards[playerCardCount], playerScore);
                cout << "New card: ";
                displayCard(playerCards[playerCardCount]);
                cout << " (Total: " << playerScore << ")" << endl;
                playerCardCount++;
            }
        }

        // Dealer's turn if player hasn't busted
        if (playerScore <= 21) {
            cout << "\nDealer's hole card: ";
            displayCard(dealerCards[1]);
            dealerScore += getCardValue(dealerCards[1], dealerScore);
            cout << " (Total: " << dealerScore << ")" << endl;

            while (dealerScore < 17) {
                dealerCards[dealerCardCount] = rand() % 13 + 1;
                int newValue = getCardValue(dealerCards[dealerCardCount], dealerScore);
                dealerScore += newValue;
                cout << "Dealer draws: ";
                displayCard(dealerCards[dealerCardCount]);
                cout << " (Total: " << dealerScore << ")" << endl;
                dealerCardCount++;
            }
        }

        // Determine winner
        if (playerScore > 21) {
            cout << "Bust! You lose $" << bet << endl;
            money -= bet;
        } else if (dealerScore > 21) {
            cout << "Dealer busts! You win $" << bet << endl;
            money += bet;
        } else if (dealerScore > playerScore) {
            cout << "Dealer wins! You lose $" << bet << endl;
            money -= bet;
        } else if (playerScore > dealerScore) {
            if (playerScore == 21 && playerCardCount == 2) {
                cout << "Blackjack! You win $" << (bet * 1.5) << endl;
                money += bet * 1.5;
            } else {
                cout << "You win $" << bet << endl;
                money += bet;
            }
        } else {
            cout << "Push! Bet returned." << endl;
        }

        if (money <= 0) {
            cout << "You're out of money! Game over!" << endl;
            break;
        }

        cout << "Play again? (y/n): ";
        cin >> playAgain;
    }

    cout << "Thanks for playing! You left with $" << money << endl;
    return 0;
}

#include <iostream>
#include <array>
#include <ctime>
#include <algorithm>
#include <random>

enum class CardRank
{
    RANK_2,
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_9,
    RANK_10,
    RANK_JACK,
    RANK_QUEEN,
    RANK_KING,
    RANK_ACE,

    maxRANK,
};

enum class CardSuit
{
    SUIT_DIAMONDS,
    SUIT_HEARTS,
    SUIT_CLUBS,
    SUIT_SPADES,

    maxSUIT,
};

struct Card
{
    CardRank rank{};
    CardSuit suit{};
};

void printCard(const Card& myCard)
{
    switch (myCard.rank)
    {
    case CardRank::RANK_2:
        std::cout << '2';
        break;
    case CardRank::RANK_3:
        std::cout << '3';
        break;
    case CardRank::RANK_4:
        std::cout << '4';
        break;
    case CardRank::RANK_5:
        std::cout << '5';
        break;
    case CardRank::RANK_6:
        std::cout << '6';
        break;
    case CardRank::RANK_7:
        std::cout << '7';
        break;
    case CardRank::RANK_8:
        std::cout << '8';
        break;
    case CardRank::RANK_9:
        std::cout << '9';
        break;
    case CardRank::RANK_10:
        std::cout << '1'<< '0';
        break;
    case CardRank::RANK_JACK:
        std::cout << 'J';
        break;
    case CardRank::RANK_QUEEN:
        std::cout << 'Q';
        break;
    case CardRank::RANK_KING:
        std::cout << 'K';
        break;
    case CardRank::RANK_ACE:
        std::cout << 'A';
        break;
    }
    switch (myCard.suit)
    {
    case CardSuit::SUIT_CLUBS:
        std::cout << 'C';
        break;
    case CardSuit::SUIT_DIAMONDS:
        std::cout << 'D';
        break;
    case CardSuit::SUIT_HEARTS:
        std::cout << 'H';
        break;
    case CardSuit::SUIT_SPADES:
        std::cout << 'S';
        break;
    }
}

using deck_type = std::array<Card, 52>;
using index_type = deck_type::size_type;

deck_type createDeck() {
    deck_type deck{};
    index_type card{ 0 };

    auto suits{ static_cast<int>(CardSuit::maxSUIT) };
    auto ranks{ static_cast<int>(CardRank::maxRANK) };

    for (int suit{ 0 }; suit < suits; ++suit)
    {
        for (int rank{ 0 }; rank < ranks; ++rank)
        {
            deck[card].suit = static_cast<CardSuit>(suit);
            deck[card].rank = static_cast<CardRank>(rank);
            ++card;
        }
    }

    return deck;
}

void printDeck(const deck_type& deck)
{
    for (const auto& card : deck)
    {
        printCard(card);
        std::cout << ' ';
    }
    std::cout << '\n';
}

deck_type shuffleDeck(deck_type& deck)
{
    std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    std::shuffle(deck.begin(), deck.end(), mt);

    return deck;
}

int getCardValue(Card card)
{
    if (card.rank <= CardRank::RANK_10)
    {
        return (static_cast<int>(card.rank) + 2);
    }

    switch (card.rank)
    {
    case CardRank::RANK_JACK:
        return 10;
        break;
    case CardRank::RANK_QUEEN:
        return 10;
        break;
    case CardRank::RANK_KING:
        return 10;
        break;
    case CardRank::RANK_ACE:
        return 11;
        break;
    default:
        return 0;
    }
}

bool playAgain()
{
    char yesNo{};
    std::cout << "Would you like to play again? Type 'y' or 'n': \n";
    std::cin >> yesNo;
    if (yesNo == 'y')
        return true;
    else if (yesNo == 'n')
        return false;
    else
        std::cout << "Error, please enter 'y' or 'n': \n";

}

bool hitOrStay() 
{
    char input{};
    std::cout << "Would you like to hit or stay? To hit type 'h'. To stay type 's'.\n";
    std::cin >> input;
    if (input == 'h')
        return true;
    else if (input == 's')
        return false;
    else
        std::cout << "Error, please either enter 'h' or 's'.\n";
}

int dealCard(deck_type deck, int turnNum)
{
    int playScore = getCardValue(deck[turnNum]);
    return playScore;
}

bool playBlackjack(deck_type deck) 
{
    int playerScore{};
    int dealerScore{};
    int turnNum{ 0 };

    dealerScore += dealCard(deck, turnNum);
    std::cout << "Dealer's score is: " << dealerScore << '\n';
    ++turnNum;

    playerScore += dealCard(deck, turnNum);
    ++turnNum;
    playerScore += dealCard(deck, turnNum);
    ++turnNum;
    std::cout << "Your score is: " << playerScore << '\n';
    if (playerScore == 21)
    {
        std::cout << "Blackjack!\n";
        return true;
    }

    bool hit{};
    hit = hitOrStay();

    while (hit == true)
    {
        playerScore += dealCard(deck, turnNum);
        ++turnNum;
        std::cout << "Your score is : " << playerScore << '\n';
        if (playerScore < 21)
        {
            hit = hitOrStay();
        }
        else if (playerScore > 21)
        {
            std::cout << "Sorry, you bust!\n";
            return false;
        }
       
    }

    while (dealerScore < 17)
    {
        dealerScore += dealCard(deck, turnNum);
        std::cout << "The dealer's score is: " << dealerScore << '\n';
        if (dealerScore > 21)
        {
            std::cout << "Dealer busts!\n";
            return true;
        }
        ++turnNum;
    }

    if (playerScore > dealerScore)
        return true;
    else
        return false;
}

int main()
{
    bool playGame{ true };
    while (playGame == true)
    {
        std::array<Card, 52> myDeck{ createDeck() };
        shuffleDeck(myDeck);

        bool winner{};
        winner = playBlackjack(myDeck);

        if (winner == true)
            std::cout << "Congratulations, you win!\n";
        else
            std::cout << "Dealer wins. Sorry, try again.\n";
        playGame = playAgain();
        std::cout << '\n';
    }

    return 0;
}

#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::map;

static map<char, int> cardValue;
static std::ifstream file;


enum HAND_TYPE{
    HIGH_CARD = 1,
    ONE_PAIR,
    TWO_PAIRS,
    THREE_OK,
    FULL_HOUSE,
    FOUR_OK,
    FIVE_OK
};

struct Hand {
    int bet;
    HAND_TYPE type;
    string cards;
};

static vector<Hand> bidHands;

void readInput(bool joker);
void setCardValue(string deck);
map<char, int> countCards( string cards);
HAND_TYPE categorizeHand(string cards ,bool joker);
int solve(string deck, bool joker);
bool lessThan(string a, string b);
HAND_TYPE selectBestAlter(HAND_TYPE cat, int JCount); 

int main() {
    //std::cout << solve("23456789TJQKA", false)<< "\n";
    std::cout << solve("J23456789TQKA", true)<< "\n";

}

bool lessThan(string a, string b) {
    for (size_t i = 0; i < a.size(); ++i) {
        if (cardValue[a[i]] > cardValue[b[i]]) return false;
        if (cardValue[a[i]] < cardValue[b[i]]) return true;
    }
    return false;
}

int solve(string deck, bool joker) {
    readInput(joker);
    setCardValue(deck);
    vector<Hand> orderedHands;

    for (Hand &h: bidHands) {
         std::cout << h.cards << " " << h.bet << " " << h.type << "\n";
    }

    for (int i = HIGH_CARD; i < FIVE_OK+1; i++){
        vector<Hand> placeHolder;
        for (Hand h : bidHands) {
            if (h.type == i) {
                placeHolder.push_back(h);
            }        
        }
        
        for (size_t i = 0; i < placeHolder.size(); ++i) {
            for (size_t j = i; j < placeHolder.size(); ++j) {
                if (lessThan(placeHolder[j].cards, placeHolder[i].cards)) {
                    Hand aux;
                    aux = placeHolder[i];
                    placeHolder[i] = placeHolder[j];
                    placeHolder[j] = aux;
                }
            }
        }
        orderedHands.insert(
            orderedHands.end(),
            std::make_move_iterator(placeHolder.begin()),
            std::make_move_iterator(placeHolder.end())
        );
    }

    
    // for (Hand h: orderedHands) {
    //      std::cout << h.cards << " " << h.bet << " " << h.type << "\n";
    // }

    bidHands = orderedHands;
    std::cout << "Tamano final: " << bidHands.size() << "\n";

    int acum = 0;
    for (size_t i = 0; i < orderedHands.size(); ++i) {
        acum += orderedHands[i].bet * (i+1);
    }
    return acum;
}

map<char, int> countCards(string cards) {
    map<char,int> cardCount;
    for (char &c: cards) {
        cardCount[c]++;
    }


    return cardCount;
}

HAND_TYPE categorizeHand(string cards, bool joker) {
    map<char, int> cardCount = countCards(cards);
    
    int jokerCount = cardCount.find('J') != cardCount.end() ? cardCount.find('J')->second: 0;
    HAND_TYPE cat = static_cast<HAND_TYPE>(0);

    switch (cardCount.size()) {
        case 5: {
            cat = HIGH_CARD;
        } break;
        case 4: {
            cat = ONE_PAIR;
        } break;
        case 3: {
            for (char c: cards) {
                int count = cardCount[c]; 
                if (count == 3) {
                    cat = THREE_OK;
                } // poner un break
            }
            cat = cat != 0 ? THREE_OK : TWO_PAIRS;
        } break;
        case 2: {
            for (char c: cards) {
                int count = cardCount[c];
                if (count == 4) {
                    cat = FOUR_OK;
                    break;
                }
            }
            cat = cat == FOUR_OK ? FOUR_OK : FULL_HOUSE;
        } break;
        case 1:
            cat = FIVE_OK;
        break;
    }

    if (joker) {
        cat = selectBestAlter(cat, jokerCount);
    }
    
    if (cat == 0) std::cerr << "Error bad category: " << cards << "\n" ;
        
    return cat;
}

HAND_TYPE selectBestAlter(HAND_TYPE cat, int JCount) {
    if (JCount == 0) return cat; 
    switch (cat) {
        case HIGH_CARD:
            return ONE_PAIR;
            break;
        case ONE_PAIR:
            return THREE_OK;
            break;
        case TWO_PAIRS: {
                if (JCount == 1) return FULL_HOUSE;
                return FOUR_OK;
            } break;
        case THREE_OK:
            return FOUR_OK;
            break;
        case FOUR_OK:
            return FIVE_OK;
            break;
        case FULL_HOUSE:
            return FIVE_OK;
            break;
        case FIVE_OK:
            return FIVE_OK;
            break;
    }
    return FIVE_OK;
}

void readInput(bool joker) {
    file.open("input.txt");
    string cards;
    int bets;  
    bidHands.clear();
    while (file >> cards >> bets) {
        bidHands.push_back(Hand{bets, categorizeHand(cards, joker) ,cards});
    }
    
    file.close();
}

void setCardValue (string deck) {
    cardValue.clear();
    for (size_t i = 0; i < deck.size(); ++i) {
        cardValue[deck[i]] = i+1;
    }
}

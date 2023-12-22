#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include <utility>
#include <vector>

int getWiningCards(std::array<int, 10> winNums, std::array<int, 25> ourNums);
int getTotalcards(int* array, int size, int index);

int main() {
  std::ifstream file;
  std::string line;
  std::vector<std::pair<std::array<int, 10>, std::array<int, 25>>> card_list; 
  std::array<int, 10> wining_numbers;
  std::array<int, 25> card_numbers;
  int sumofcards = 0;


  file.open(("input.txt"));
  while(std::getline(file, line, '\n')) {
    std::stringstream s_card(line);
    std::string card;
    while(std::getline(s_card, card, ':')) {
      std::getline(s_card, card, ':');
      std::stringstream numbers(card);
      std::string win_nums;
      std::string card_nums;
      while(std::getline(numbers, win_nums, '|')) {
        std::getline(numbers, card_nums, '|');
        
        std::stringstream s_win_nums(win_nums);
        std::stringstream s_card_nums(card_nums);
        
        std::string temp;
        for (int i = 0 ; i < wining_numbers.size(); i++) {
          std::getline(s_win_nums, temp, ' ');
          if (temp == "") {
            i--;
            continue;
          }
          wining_numbers[i] = std::stoi(temp);
        }

        for (int i = 0 ; i < card_numbers.size(); i++) {
          std::getline(s_card_nums, temp, ' ');
          if (temp == "") {
            i--;
            continue;
          }
          card_numbers[i] = std::stoi(temp);
        }
        std::pair<std::array<int, 10>, std::array<int, 25>> array_pair = std::make_pair(wining_numbers, card_numbers);
        card_list.push_back(array_pair);
      }
    }
  }
  
  int wining_cards_arr[card_list.size()];

  for (int i = 0; i < card_list.size() ; i++) {
    wining_cards_arr[i] = getWiningCards(card_list[i].first, card_list[i].second); 
  }

  for (int i = 0; i < card_list.size(); i++) {
    sumofcards += getTotalcards(wining_cards_arr, card_list.size(), i);
  }

  std::cout << sumofcards + card_list.size();
}

int getWiningCards(std::array<int, 10> winNums, std::array<int, 25> ourNums) {
    int sum  = 0;
    for (int i = 0; i < ourNums.size(); i++) {
      for (int j = 0; j < winNums.size(); j++) {
        if (ourNums[i] == winNums[j]) {
          sum ++;
        }
      }
    }  
    return sum;
}

int getTotalcards(int* array, int size, int index) {
  int sum = 0;
  sum += array[index];
  for (int i = index+1; i < index + array[index]+1; i++) {
    sum += getTotalcards(array, size, i);
  }

  return sum;
}

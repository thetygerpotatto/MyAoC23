#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

int calculate_points(int *, int *, int, int);

int main() {
  std::ifstream file;
  std::string line;
  int *wining_numbers = new int[10];
  int *card_numbers = new int[25];
  int wnSize = 10;
  int cnSize = 25;
  int sum = 0;


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
        for (int i = 0 ; i < wnSize; i++) {
          std::getline(s_win_nums, temp, ' ');
          if (temp == "") {
            i--;
            continue;
          }
          wining_numbers[i] = std::stoi(temp);
        }

        for (int i = 0 ; i < cnSize; i++) {
          std::getline(s_card_nums, temp, ' ');
          if (temp == "") {
            i--;
            continue;
          }
          card_numbers[i] = std::stoi(temp);
        }
        sum += calculate_points(wining_numbers, card_numbers, wnSize, cnSize);
      }
    }
  }

  std::cout << sum;
}


int calculate_points(int *WinNums, int *CardNums, int Wsize, int Csize) {
  int exp = 0;
  int points = 0;

  for (int i = 0; i < Csize; i++) {
    for (int j = 0; j < Wsize; j++) {
      if (CardNums[i] == WinNums[j]) {
        exp++;
      }
    }
  }
  
  if (exp == 0) {
    return 0;
  } 
  else {
    points = pow(2, exp-1);
  }
  return points;
}

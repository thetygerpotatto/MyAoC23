#include <iostream>
#include <ostream>
#include <queue>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <map>

int main (int argc, char *argv[]) {

  std::ifstream file;
  file.open("input.txt");

  int sum = 0;
  int index = 0;

  // 12 red 13 green 14 blue
  std::string line;

  while(std::getline(file, line, '\n')) {
    std::stringstream s_line(line);
    std::getline(s_line, line, ':');
    std::getline(s_line, line, ':');

    std::vector<std::map<std::string, int>> game; 
    std::string swop;
    std::stringstream s_swops(line);
    while(std::getline(s_swops, swop, ';')){
      std::map<std::string, int> cubeQuantity;
      std::string pair;
      std::stringstream s_pair(swop);

      while (std::getline(s_pair, pair, ',')) {
        std::stringstream member(pair);
        std::string color;
        std::string tempQantity;
        int quantity = 0;

        std::getline(member, tempQantity, ' ');
        std::getline(member, tempQantity, ' ');
        std::getline(member, color, ' ');
        
        quantity = std::stoi(tempQantity);
        
        cubeQuantity.insert(std::make_pair(color, quantity));
      }

      game.push_back(cubeQuantity);
    }
    bool r = true;
    bool g = true;
    bool b = true;
    for (int i = 0; i < game.size(); i++) {
      if (game[i]["red"] > 12) r = false;
      if (game[i]["green"] > 13) g = false;
      if (game[i]["blue"] > 14) b = false;
    }

    if ( r && g && b) {
      sum += index+1;
    }

    std::cout << index++ << "\n";
  }
  std::cout << sum;
}





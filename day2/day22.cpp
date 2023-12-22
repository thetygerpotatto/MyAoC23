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
    int r = game[0]["red"];
    int  g = game[0]["green"];
    int b = game[0]["blue"];

    for (int i = 0; i < game.size(); i++) {
      if (game[i]["red"] > r) r = game[i]["red"];
      if (game[i]["green"] > g) g = game[i]["green"];
      if (game[i]["blue"] > b) b = game[i]["blue"];
    }

    sum += r*g*b;

    std::cout << r << " " << g << " " << b << "\n";
  }
  std::cout << sum;
}





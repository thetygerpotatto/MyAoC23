#include <iostream>
#include <fstream>
#include <cctype>

bool inRange(char);
int lookForNum(int, int, char**);

int main() {
  std::ifstream file;
  char **array = new char*[140];
  for (int i = 0; i < 140; i++) array[i] = new char[140];

  int sum = 0;

  file.open("input.txt");
  if(!file) {
    std::cout << "failed to open file" << "\n";
  }
  // entre  33 y 48. y entre 57 65
  
  char p = 0;
  int line = 0;
  int car  = 0;
  while (line < 140) {
    p = file.get();
    array[line][car] = p;
    car++;
    if (p == '\n') {
      line++;
      car = 0;
    }
  }

  for (int i = 0; i < 140; i++) {
    for (int j = 0; j < 140; j++) {
      if (inRange(array[i][j])) {
        std::cout << "[" << i << "]" << "[" << j << "]:" ;
        int num = lookForNum(i, j, array);
        sum += num; 
      } 
    }
  }
  
 /* for (short i = 0;  i < 255; i++) {
    std::cout << i << " "<< (char)i << " " <<  std::isalnum(i) << " " << std::isalpha(i) << "\n";
  }/*/
  std::cout << sum;
}

bool inRange(char value) {
  if (value == '.') return false;
  if (value == '*') return true;
  return false;
}

int lookForNum(int i, int j, char** array) {
  std::string gears[2];
  int g = 0;

  for (int k = i-1; k < i+2; k++) {
    for (int m = j-1; m < j+2; m++){

      if (std::isdigit(array[k][m])) {
        int x = m;
        int y = k;
        std::string num;

        std::cout << " [" << y << "]" << "[" << x << "]:" << "\n";

        while(std::isdigit(array[y][x - 1])) {
          x--;
        }

        while(std::isdigit(array[y][x])) {
          num.push_back(array[y][x]);
          array[y][x] = '.';
          x++;
        }

        if (g == 2) continue;
        gears[g++].assign(num);
      }
    }
  }
  //std::cout << "  " << gears[0] << ":" << gears[1] << "\n";
  if (gears[1] == "") gears[1].assign("0");// this makes stoi not to trow an error when the seccon number gear is empty :P
  return std::stoi(gears[0]) * std::stoi(gears[1]); 
}

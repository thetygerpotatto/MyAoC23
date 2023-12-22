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
        std::cout << "[" << i << "]" << "[" << j << "]:" << "\n";
        int num = lookForNum(i, j, array);
        sum += num; 
        if (num != 0) j--;
      } 
    }
    //std::cout << "\n";
  }
  
 /* for (short i = 0;  i < 255; i++) {
    std::cout << i << " "<< (char)i << " " <<  std::isalnum(i) << " " << std::isalpha(i) << "\n";
  }/*/
  std::cout << sum;
}

bool inRange(char value) {
  if (value == '.') return false;
  if ((value > '!' && value < '0') || (value >  '9' && value < 'A')) return true;
  return false;
}

int lookForNum(int i, int j, char** array) {
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
        std::cout << "  " << num << "\n";
        return std::stoi(num); 
      }
    }
  }
  return 0; 
}

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

int calculateValues(std::string);
int calculate(std::vector<std::string>);
char asignValue(std::string);


int main(int argc, char *args[]) {
  std::ifstream file;
  std::string line;
  std::vector<std::string> lines;

  file.open(args[1]);
  if (!file) {
    std::cout << "failed to open";
  }
  else {
    while (file >> line) { 
      lines.push_back(line);
    }
  }

  int sum = calculate(lines);
  std::cout << sum;
  system("pause");
}

int calculate(std::vector<std::string> lines) {
  int sum;
  for (int i = 0; i < lines.size(); i++) {
    sum += calculateValues(lines[i]);
  }
  return sum;
}

int calculateValues(std::string str) {
  std::string nums[19] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
  std::string firstest = "NOT";
  std::string lastest = "NOT";
  int foundIndex = -1;
  bool diferent = false;

  for (int i = 0 ; i < str.size(); i++) {
    for(int j = 0; j < 19 ; j++) {
      if (foundIndex != -1) break;
      diferent = false;
      for (int k = 0; k < nums[j].size(); k++) {
        if (str[i+k] != nums[j][k] || k+i >= str.size()) {
          diferent = true;
        }
      }
      if (!diferent) {
        foundIndex = j;
        firstest = nums[j];
        break;
      }
    }
  }
  
  foundIndex = -1;

  for (int i = str.size()-1 ; i >= 0; i--) {
    for(int j = 0; j < 19 ; j++) {
      if (foundIndex != -1) break;
      diferent = false;
      for (int k = nums[j].size()-1; k >= 0; k--) {
        if (str[i+k] != nums[j][k] || i+k >= str.size()) {
          diferent = true;
        }
      }
      if (!diferent) {
        foundIndex = j;
        lastest = nums[j];
        break;
      }
    }
  }
  

  unsigned int n1 =(unsigned int)asignValue(firstest);
  unsigned int n2 =(unsigned int)asignValue(lastest);
  int result = (n1-48)*10 + (n2-48);
  return result;
}

char asignValue(std::string num) {
  std::string nums[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  bool itsName = false;
  int index = 0;

  for (int i = 0; i < 9; i++) {
    if (num == nums[i]) {
      itsName = true;
      index = i;
    }
  }

  if (itsName) {
    switch (index) {
      case 0:
        return '1'; 
        break;
      case 1:
        return '2';
        break;
      case 2:
        return '3';
        break;
      case 3:
        return '4';
        break;
      case 4:
        return '5';
        break;
      case 5:
        return '6';
        break;
      case 6:
        return '7';
        break;
      case 7:
        return '8';
        break;
      case 8:
        return '9';
        break;
    }
  }
  else {
    return num[0];
  }
  return NULL;
}

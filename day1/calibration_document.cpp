#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int calibration_value(std::vector<std::string>);
unsigned int decifer_value(std::string);

int main(int argc, char *args[]) {
  std::vector<std::string> calibrations;
  std::ifstream FILE;
  FILE.open(args[1]);
  if (!FILE) {
    std::cout << "No such file";
	}
  else {
    std::string word;
    while(FILE >> word) {
      //std::cout << word << "\n";
      calibrations.push_back(word);
    }
    FILE.close();
  }
  std::cout << calibration_value(calibrations);
}

int calibration_value(std::vector<std::string> values) {
  int sum = 0;
  for (int i = 0; i < values.size(); i++) {
    sum += decifer_value(values[i]);
  }
  
  return sum;
}

unsigned int decifer_value(std::string str) {
  int lenght = str.size();
  unsigned int firtNum;
  unsigned int lastnum;
  for (int i=0; i < lenght; i++) {
      if (str.at(i) >= '0' && str.at(i) <= '9') {
        firtNum = (unsigned int)str.at(i) - 48;
        break;
    }
  }
  for (int i=lenght-1; i >= 0; i--) {
      if (str.at(i) >= '0' && str.at(i) <= '9') {
        lastnum = (unsigned int)str.at(i) - 48;
        break;
    }
  }

std::cout << firtNum << "=" << lastnum << "\n";
  unsigned int decifered_value = firtNum*10+ lastnum;
  return decifered_value;
}



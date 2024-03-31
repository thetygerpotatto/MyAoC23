#include <array>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
int main() {
    std::ifstream file;
    file.open("input.txt");
    std::array<int,4> times;
    std::array<int,4> records;

    std::string str;
    std::getline(file, str);
    std::stringstream ss(str);

    for (int& t : times) {
        std::string s;
        ss >> s;
        t = std::stoi(s);
    }

    std::getline(file, str);
    ss = std::stringstream(str);
    
    for (int& t : records) {
        std::string s;
        ss >> s;
        t = std::stoi(s);
    }

    file.close();
    int result = 1;
    for (size_t i = 0 ; i < times.size(); ++i) {
        int acum = 0;
        for (int waitTime = times[i]; waitTime > 0; --waitTime) {
            int distance = waitTime*(times[i]-waitTime);
            if (distance > records[i]) acum++;
        }
        result*=acum;
    }

    std::cout << result << "\n";
}

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

    std::string s;
    ss >> s;
    long long time = std::stoll(s);
    

    std::getline(file, str);
    ss = std::stringstream(str);
    
    ss >> s;
    long long record = std::stoll(s);

    std::cout << time << " " << record << "\n";

    file.close();
    int result = 1;
    int acum = 0;
    for (long long waitTime = time; waitTime > 0; --waitTime) {
        long long distance = waitTime*(time-waitTime);
        if (distance > record) acum++;
    }

    std::cout << acum << "\n";
}

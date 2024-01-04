#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<long long> process_seeds(std::string &seeds); 
std::vector<std::array<long long, 3>> process_map(std::ifstream &file);
std::vector<long long> seeds_to_locations(std::vector<long long> &seeds, std::array<std::vector<std::array<long long, 3>>,7> &maps);

int main() {

  std::string seeds_string;
  std::array<std::vector<std::array<long long, 3>>,7> maps;
  std::vector<long long> seeds;
  std::vector<long long> locations;

  std::ifstream file;
  file.open("input.txt");

  if (!file) {
    std::cout << "failed to open input.txt\n";
    return 0;
  }

  std::getline(file, seeds_string);
  seeds = process_seeds(seeds_string);
  
  for (int i = 0; i < 7 ; i++) {
    maps[i] = process_map(file);
  }

  file.close();

  for (int seed_index= 0; seed_index < seeds.size(); seed_index++) {
    long long dest_in = seeds[seed_index];

    for (int map_index = 0; map_index < maps.size(); map_index++) {
      bool notMapped = true;
      long long dest_out = 0;
      for (int mapping = 0; mapping < maps[map_index].size(); mapping++) {
        long long range = maps[map_index][mapping][2];
        long long source = maps[map_index][mapping][1];
        long long dest = maps[map_index][mapping][0];

        if (dest_in >= source && dest_in <= source + range) {
          dest_out = dest_in - source + dest;
          notMapped = false;
          break;
        }
      }
      if (notMapped) dest_out = dest_in;
      dest_in = dest_out;
    }
    
    locations.push_back(dest_in);
  }

  std::vector<long long>::iterator min = std::min_element(locations.begin(), locations.end());
  std::cout << *min;
}

std::vector<long long> process_seeds(std::string &seeds) {
  std::stringstream seeds_ss(seeds);
  std::vector<long long> seeds_vec;
  std::string s;
  while (seeds_ss >> s){
    seeds_vec.push_back(std::stoll(s));
  }
  return seeds_vec;
}

std::vector<std::array<long long, 3>> process_map(std::ifstream &file) {
  std::vector<std::array<long long, 3>> map;
  std::string num;
  std::string triad = "-";

  while(true){
    std::array<long long, 3> values;
    std::getline(file, triad);

    if ( triad == "") break;

    std::stringstream triad_ss(triad);
    std::string temp;

    for (int i = 0; i < values.size(); i++) {
      triad_ss >> temp;
      values[i] = std::stoll(temp);
    }
    map.push_back(values);
  }
  return map;
}

std::vector<long long> seeds_to_locations(std::vector<long long> &seeds, std::array<std::vector<std::array<long long, 3>>,7> &maps) {
  std::vector<long long> locations;

  return locations;
}


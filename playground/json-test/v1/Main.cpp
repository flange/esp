#include <fstream>
#include <iostream>
#include <unordered_map>
#include <map>

#include "json.hpp"


using json = nlohmann::json;


int main() {

  json j;
  std::ifstream json_file("test.json", std::ifstream::binary);

  json_file >> j;
  std::cout << "complete json file:" << std::endl;
  std::cout << j << std::endl << std::endl;

  std::cout << "json query:" << std::endl;
  std::cout << j["object"] << std::endl << std::endl;

  std::cout << "json query on result of earlier query:" << std::endl;
  json j2 = j["object"];

  std::cout << j2 << std::endl;
  std::cout << j2["currency"] << std::endl << std::endl;

  std::cout << "json query as string from stringstream:" << std::endl;
  std::stringstream j2str;
  j2str << j2;

  std::cout << j2str.str() << std::endl << std::endl;

  std::cout << "json as unordered map: " << std::endl;
  auto j_umap = j.get<std::unordered_map<std::string, json>>();

  for (auto i : j_umap)
    std::cout << i.first << " : " << i.second << std::endl;




  return 0;
}



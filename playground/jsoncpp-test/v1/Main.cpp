#include <fstream>
#include <iostream>
#include <string>

#include "json.h"


int main() {

  Json::Value root;
  std::ifstream json_doc("test.json", std::ifstream::binary);

  json_doc >> root;
  //std::cout << root << std::endl;





  return 0;
}

/*

ifstream in(filename);
  Json::Value book_json;
  in >> book_json;
  for (Json::Value::iterator it = book_json["contacts"].begin(); it != book_json["contacts"].end(); ++it) {
    AddPerson((*it)["name"].asString(), (*it)["phone_number"].asString());
  }
  in.close();




#include <fstream>

std::ifstream config_doc("config_doc.json", std::ifstream::binary);
config_doc >> root;
#include <json/value.h>

Json::Value root;   // starts as "null"; will contain the root value after parsing
std::cin >> root;

// Get the value of the member of root named 'my-encoding', return 'UTF-32' if there is no
// such member.
std::string my_encoding = root.get("my-encoding", "UTF-32" ).asString();

// Get the value of the member of root named 'my-plug-ins'; return a 'null' value if
// there is no such member.
const Json::Value my_plugins = root["my-plug-ins"];
for ( int index = 0; index < my_plugins.size(); ++index )  // Iterates over the sequence elements.
   yourlib::loadPlugIn( my_plugins[index].asString() );

yourlib::setIndentLength( root["my-indent"].get("length", 3).asInt() );
yourlib::setIndentUseSpace( root["my-indent"].get("use_space", true).asBool() );

// ...
// At application shutdown to make the new configuration document:
// Since Json::Value has implicit constructor for all value types, it is not
// necessary to explicitly construct the Json::Value object:
root["encoding"] = yourlib::getCurrentEncoding();
root["indent"]["length"] = yourlib::getCurrentIndentLength();
root["indent"]["use_space"] = yourlib::getCurrentIndentUseSpace();

// Make a new JSON document with the new configuration. Preserve original comments.
std::cout << root << "\n";

*/

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include <boost/graph/graphml.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/iteration_macros.hpp>

using namespace boost;

struct EdgeProps {
  double weight;
};


typedef adjacency_list <vecS, vecS, directedS, EdgeProps> Graph;

int main() {

  Graph g(0);
  dynamic_properties dp;

  std::ifstream gmlFile;
  gmlFile.open("g.gml", std::ifstream::in);

  read_graphml(gmlFile, g, dp);
  //boost::write_graphml(std::cout, g,dp);

  Graph::edge_descriptor e;

  BGL_FORALL_EDGES(e, g, Graph)  //e is declared as Graph::edge_descriptor
  {
  }


  return 0;
}

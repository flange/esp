#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_list.hpp>

using namespace std;
using namespace boost;

struct VerticeProps {
  std::string name;
  std::string label;
};

struct EdgeProps {
  std::string label;
  double weight;
};

struct GraphProps {
  std::string name;
};

typedef adjacency_list< vecS, vecS, directedS, VerticeProps, EdgeProps, GraphProps> Graph;

int main(int,char*[])
{
    Graph g(0);

    dynamic_properties dp(ignore_other_properties);

    dp.property("node_id", get(&VerticeProps::name, g));
    dp.property("weight", get(&EdgeProps::weight, g));


    ifstream fin("g.gviz");
    read_graphviz(fin, g, dp);


    g[graph_bundle].name = "Test";


    write_graphviz(std::cout, g);


/*
  boost::property_map<graph_t, boost::vertex_name_t>::type vName = boost::get(boost::vertex_name, graph);
  dp.property("node_id", vName);

  boost::property_map<graph_t, boost::edge_weight_t>::type eWeight = boost::get(boost::edge_weight, graph);
  dp.property("label", eWeight);


  std::ifstream file;
  file.open("g.gviz", std::ifstream::in);

  bool status = boost::read_graphviz(file, graph, dp);

  std::cout << "status: " << status << std::endl;
*/
  return 0;
}

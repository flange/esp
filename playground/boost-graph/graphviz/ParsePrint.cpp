#include <algorithm>
#include <fstream>
#include <iostream>

#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_list.hpp>


struct VerticeProps {
  std::string name;
};

struct EdgeProps {
  std::string name;
};

using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                                    VerticeProps, EdgeProps>;

using vDesc = Graph::vertex_descriptor;
using eDesc = Graph::edge_descriptor;

using vIter = Graph::vertex_iterator;
using vIterPair = std::pair<vIter, vIter>;

using oeIter = Graph::out_edge_iterator;
using oeIterPair = std::pair<oeIter, oeIter>;



void printOutEdge(Graph g, eDesc e)
{
  vDesc src = boost::source(e, g);
  vDesc dst = boost::target(e, g);

  std::cout << g[src].name << " -> " << g[dst].name;
  std::cout << " [trans=\"" << g[e].name << "\"]" << std::endl;
}

void printOutEdges(Graph g, vDesc vd) {

  oeIterPair oeip = boost::out_edges(vd, g);

  if (oeip.first == oeip.second) // no out edge
    return;

  using eDesc = Graph::edge_descriptor;

  std::for_each(oeip.first, oeip.second, [&](eDesc e) {
    printOutEdge(g, e);
  });

}

void printGraph(Graph g)
{
  vIterPair vip = boost::vertices(g);

  std::for_each(vip.first, vip.second, [&](vDesc vd) {
    printOutEdges(g, vd);
  });
}

int main()
{
  Graph g;

  boost::dynamic_properties dp(boost::ignore_other_properties);

  dp.property("node_id", boost::get(&VerticeProps::name, g));
  dp.property("trans", boost::get(&EdgeProps::name, g));

  std::ifstream file("ex.gviz");
  boost::read_graphviz(file, g, dp);

  printGraph(g);

  return 0;
}




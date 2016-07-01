#include <algorithm>
#include <fstream>
#include <iostream>

#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/range/iterator_range.hpp>


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

template <typename T>
using Range = boost::iterator_range<T>;


template <typename T>
Range<T> makeRange(const std::pair<T, T> &p)
{
  return boost::make_iterator_range(p);
}

void printOutEdge(const Graph &g, const eDesc &e)
{
  const vDesc src = boost::source(e, g);
  const vDesc dst = boost::target(e, g);

  std::cout << g[src].name << " -> " << g[dst].name;
  std::cout << " [trans=\"" << g[e].name << "\"]" << std::endl;
}

void printOutEdges(const Graph &g, const vDesc &vd) {

  const Range<oeIter> outEdges = makeRange(boost::out_edges(vd, g));

  if (outEdges.empty())
    return;

  for (const eDesc &e : outEdges)
    printOutEdge(g, e);

}

void printGraph(const Graph &g)
{
  Range<vIter> vertices = makeRange(boost::vertices(g));

  for (const vDesc &v : vertices)
    printOutEdges(g, v);
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




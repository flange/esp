#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_list.hpp>


struct VerticeProps {
  std::string name;
};

struct EdgeProps {
  std::string name;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
                              VerticeProps, EdgeProps> Graph;


void printVertexName(Graph::vertex_iterator vit, Graph g)
{
  Graph::vertex_descriptor vd = *vit;
  std::cout << g[vd].name << std::endl;
}

void printEdgeName(Graph::edge_iterator eit, Graph g)
{
  Graph::edge_descriptor ed = *eit;
  std::cout << g[ed].name << std::endl;
}

void printVertexOutEdges(Graph::vertex_iterator vit, Graph g)
{
  typedef Graph::out_edge_iterator oeIter;
  typedef std::pair<oeIter, oeIter> oeIterPair;

  Graph::vertex_descriptor vd = *vit;

  oeIterPair oeip = out_edges(vd, g);

  if (oeip.first == oeip.second)
    return;

  Graph::vertex_descriptor targetV;

  for (oeIter oeiter = oeip.first; oeiter != oeip.second; ++oeiter) {
    std::cout << g[*oeiter].name << std::endl;

    targetV = target(*oeiter, g);
    std::cout << g[targetV].name << std::endl;
  }

}

void printVertexNames(Graph g)
{
  typedef Graph::vertex_iterator vIter;
  typedef std::pair<vIter, vIter> vIterPair;

  vIterPair vip = boost::vertices(g);

  for (vIter vit = vip.first; vit != vip.second; ++vit) {
    printVertexName(vit, g);
    printVertexOutEdges(vit, g);
  }

  return;
}

void printEdgeNames(Graph g)
{
  typedef Graph::edge_iterator eIter;
  typedef std::pair<eIter, eIter> eIterPair;

  eIterPair eip = boost::edges(g);

  for (eIter eit = eip.first; eit != eip.second; ++eit) {
    printEdgeName(eit, g);
  }

  return;
}


void printVertexName(Graph g, Graph::vertex_iterator vi)
{
  std::cout << g[*vi].name << std::endl;
}

void printGraph(Graph g)
{
  using vIter = Graph::vertex_iterator;
  using vIterPair = std::pair<vIter, vIter>;

  using oeIter = Graph::out_edge_iterator;
  using oeIterPair = std::pair<oeIter, oeIter>;

  Graph::vertex_descriptor vd;
  Graph::vertex_descriptor target;

  vIterPair vip = boost::vertices(g);

  std::cout << "digraph {" << std::endl;

  for (vIter vit = vip.first; vit != vip.second; ++vit) {
    vd = *vit;
    oeIterPair oeip = boost::out_edges(vd, g);

    if (oeip.first == oeip.second)
      continue;

    for (oeIter oeiter = oeip.first; oeiter != oeip.second; ++oeiter) {
      //std::cout << g[*oeiter].name << std::endl;

      target = boost::target(*oeiter, g);
      std::cout << "  " << g[vd].name << " -> " << g[target].name;
      std::cout << " [\"trans\"=" << g[*oeiter].name << "]" << std::endl;
    }

  }

  std::cout << "}" << std::endl;

  return;
}


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

void printGraphNew(Graph g)
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

  std::ifstream fin("ex.gviz");
  boost::read_graphviz(fin, g, dp);


//  printGraph(g);

  printGraphNew(g);






  return 0;
}

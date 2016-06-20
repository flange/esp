#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include <boost/graph/graphviz.hpp>
#include <boost/graph/adjacency_list.hpp>



struct DotVertex {
    std::string name;
    std::string label;
};

struct DotEdge {
    std::string label;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
        DotVertex, DotEdge> graph_t;

int main() {
    graph_t graphviz;
    boost::dynamic_properties dp(boost::ignore_other_properties);

    dp.property("node_id",     boost::get(&DotVertex::name,        graphviz));
    dp.property("label",       boost::get(&DotVertex::label,       graphviz));
    dp.property("label",       boost::get(&DotEdge::label,         graphviz));

    std::ifstream file;
    file.open("g.gviz", std::ifstream::in);

    bool status = boost::read_graphviz(file, graphviz, dp);


    boost::write_graphviz(std::cout, graphviz);



    return status;
}



#include <gtest/gtest.h>

#include "../src/dijkstras.h"
#include "../src/ladder.h"


void printGraph(ostream& out, const Graph& g)
{
  out << "CURRENT GRAPH: ";
  for (auto i: g)
    for (auto e: i)
      out << e << " ";
  out << std::endl;
}

void printVec(ostream& out, const vector<int> v)
{
  out << "Current Vec: ";
  for (auto i: v)
    out << i << " ";
  out << endl;
}

class Dijkstras: public testing::Test {};

TEST_F(Dijkstras, SmallTxt) {
  Graph g;
  file_to_graph("src/small.txt", g);
  printGraph(std::cout, g);

  vector<int> previous(g.size());

  vector<int> tree = dijkstra_shortest_path(g, 0, previous);
  printVec(cout, tree);

  auto path = extract_shortest_path(tree, previous, 2);
  printVec(cout, path);

}

TEST_F(Dijkstras, MedTxt) {
  Graph g;
  file_to_graph("src/medium.txt", g);
  printGraph(std::cout, g);

  vector<int> previous(g.size());

  vector<int> tree = dijkstra_shortest_path(g, 0, previous);
  printVec(cout, tree);

  auto path = extract_shortest_path(tree, previous, 2);
  printVec(cout, path);

}

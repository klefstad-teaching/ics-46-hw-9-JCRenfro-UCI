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

  for (size_t i=0; i < tree.size(); ++i){
    auto path = extract_shortest_path(tree, previous, i);
    print_path(path, tree[i]);
  }

}

TEST_F(Dijkstras, MedTxt) {
  Graph g;
  file_to_graph("src/medium.txt", g);
  printGraph(std::cout, g);

  vector<int> previous(g.size());

  vector<int> tree = dijkstra_shortest_path(g, 0, previous);
  printVec(cout, tree);
  printVec(cout, previous);

  for (size_t i=0; i < tree.size(); ++i){
    auto path = extract_shortest_path(tree, previous, i);
    print_path(path, tree[i]);
  }

}

TEST_F(Dijkstras, large) {
  Graph g;
  file_to_graph("src/large.txt", g);
  printGraph(std::cout, g);

  vector<int> previous(g.size());

  vector<int> tree = dijkstra_shortest_path(g, 0, previous);
  printVec(cout, tree);
  printVec(cout, previous);

  for (size_t i=0; i < tree.size(); ++i){
    auto path = extract_shortest_path(tree, previous, i);
    print_path(path, tree[i]);
  }

}


/*
class LadderTest: public testing::Test {};

void test_adjacency(const string& word1, const string& word2, bool expected = true){

  bool val = is_adjacent(word1, word2);
  string adjacent = (val) ? "SUCCESS": "FAIL";
  std::cout << "(" << word1 << ") AND (" << word2 << ") TEST: " << adjacent << std::endl;
  ASSERT_EQ(val, expected);
}

TEST_F(LadderTest, adjacent)
{
  test_adjacency("YES", "ES");
  test_adjacency("YES", "ESA", false);
  test_adjacency("YES", "YAS");
  test_adjacency("YES", "YE");
  test_adjacency("YES", "YA", false);
  test_adjacency("APP", "W", false);
  test_adjacency("WAPP", "WPPPP", false);
  test_adjacency("Petaler", "Petale", true);
  test_adjacency("ese", "Yese", true);
  test_adjacency("chat", "cheat", true);
  test_adjacency("for", "four", true);
  test_adjacency("whaet", "whaetee", false);
  test_adjacency("see", "base", false);
  test_adjacency("app", "apple", false);
}


TEST_F(LadderTest, WordLadder)
{
  set<string> wordList;
  //load_words(wordList, "src/largeword.txt");
  load_words(wordList, "src/words.txt");
  //for (auto i: wordList) std::cout << i << std::endl;
    //vector<string> ladder = generate_word_ladder("pee", "polar", wordList);
    //vector<string> ladder = generate_word_ladder("ice", "spice", wordList);
    vector<string> ladder = generate_word_ladder("villag", "village", wordList);
  std::cout << "Ladder Is: ";
  for (auto i: ladder) std::cout << i << "->";
  std::cout << std::endl;


}

TEST_F(LadderTest, Predefined){
  //verify_word_ladder();


}*/
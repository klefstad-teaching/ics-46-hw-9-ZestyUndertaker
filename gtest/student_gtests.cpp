#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

TEST(Dijkstra, find_shortest_path) {
  Graph G;
  vector<int> previous;
  vector<int> test_distance_values = {0, 3, 6, 1};
  file_to_graph("src/small.txt", G);
  vector<int> distances = dijkstra_shortest_path(G, 0, previous);

  vector<int> path = extract_shortest_path(distances, previous, 0);
  print_path(path, distances[0]);
  path = extract_shortest_path(distances, previous, 1);
  print_path(path, distances[1]);
  path = extract_shortest_path(distances, previous, 2);
  print_path(path, distances[2]);
  path = extract_shortest_path(distances, previous, 3);
  print_path(path, distances[3]);

  EXPECT_TRUE(distances == test_distance_values);
}

TEST(Word_Ladder, find_ladder) {
  verify_word_ladder();
}
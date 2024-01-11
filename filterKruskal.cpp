#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <execution>
#include <iostream>
#include <iterator>
#include <random>
#include <thread>

struct Edge {
  uint64_t source;
  uint64_t target;
  uint64_t weight;

  Edge(uint64_t from = -1, uint64_t to = -1, uint64_t weight = -1)
      : source(from), target(to), weight(weight){};
};

template <typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
  std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
  std::advance(start, dis(g));
  return start;
}

template <typename Iter>
Iter select_randomly(Iter start, Iter end) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  return select_randomly(start, end, gen);
}

inline uint64_t pickPivot(std::vector<Edge>& edges, size_t left, size_t right) {
  // median of three
  auto a = *select_randomly(edges.begin() + left, edges.begin() + right);
  auto b = *select_randomly(edges.begin() + left, edges.begin() + right);
  auto c = *select_randomly(edges.begin() + left, edges.begin() + right);

  return std::max(std::min(a.weight, b.weight),
                  std::min(std::max(a.weight, b.weight), c.weight));
}

class UnionFind {
 public:
  std::vector<uint64_t> parent;
  std::vector<uint64_t> rank;

 public:
  UnionFind(size_t n) : parent(n, 0), rank(n, 1) {
    std::iota(parent.begin(), parent.end(), 0);
  }

  size_t find(size_t i) {
    if (parent[i] != i) parent[i] = find(parent[i]);
    return parent[i];
  }

  void link(size_t i, size_t j) {
    if (rank[i] < rank[j]) {
      parent[i] = j;
    } else {
      parent[j] = i;
      rank[i] += (rank[i] == rank[j]);
    }
  }

  void union_sets(size_t i, size_t j) {
    if (find(i) != find(j)) {
      link(find(i), find(j));
    }
  }

  void pointerJumping() {
    for (size_t i = 0; i < parent.size(); ++i) {
      while (parent[i] != parent[parent[i]]) parent[i] = parent[parent[i]];
    }
  }
};

class Algorithm {
 private:
  size_t result;
  size_t mstEdges;
  size_t numNodes;
  UnionFind unionFind;
  std::vector<Edge> edges;

 public:
  Algorithm(size_t numNodes, size_t numEdges)
      : result(0),
        mstEdges(0),
        numNodes(numNodes),
        unionFind(numNodes),
        edges(numEdges) {}

  size_t run(std::vector<Edge>& edge_list) {
    result = 0;
    mstEdges = 0;
    edges = edge_list;

    filterKruskal(0, edges.size());
    return result;
  }

  inline void filterKruskal(size_t left, size_t right) {
    // some threshold linear in n
    // right - left == number of edges we need to process
    if ((right - left) * 5 <= 4 * numNodes) {
      kruskal(left, right);
      return;
    }

    auto pivot = pickPivot(edges, left, right);

    auto partitionIter = std::partition(
        std::execution::par, edges.begin() + left, edges.begin() + right,
        [pivot](const auto& a) { return a.weight < pivot; });

    size_t i = std::distance(edges.begin() + left, partitionIter);

    // try to find the mst edges on the left / smaller side
    filterKruskal(left, left + i);

    // did we find all the mst edges?
    if (mstEdges == numNodes - 1) return;

    // shift the left position
    left += i;

    // discard edges we do not need
    filter(left, right);

    // run recursive on the larger edges
    filterKruskal(left, right);
  }

  // Filter: 'removes' unnecessary edges
  // in parallel
  inline void filter(size_t& left, size_t& right) {
    // if this edge is 'inside' one component, remove it
    auto condition = [&](Edge& edge) {
      return unionFind.parent[edge.source] == unionFind.parent[edge.target];
    };

    auto newEnd = std::remove_if(std::execution::par, edges.begin() + left,
                                 edges.begin() + right, condition);
    right = std::distance(edges.begin(), newEnd);
  }

  // Base Kruskal: operates on the edges[left:right)
  inline void kruskal(size_t left, size_t right) {
    // maybe use ips4o?
    std::sort(std::execution::par, edges.begin() + left, edges.begin() + right,
              [](const Edge& a, const Edge& b) { return a.weight < b.weight; });

    // loop over all edges up until we have n-1 edges or we have no more edges
    for (size_t i(left); i < right && mstEdges < numNodes - 1; ++i) {
      auto fromVertex = unionFind.find(edges[i].source);
      auto toVertex = unionFind.find(edges[i].target);

      if (fromVertex != toVertex) {
        unionFind.link(fromVertex, toVertex);

        result += edges[i].weight;
        ++mstEdges;
      }
    }
  }
};

// this main method has been written by chatgpt to evaluate the algorithm (first
// simple 'benchmark', but it shows how to use it)
int main() {
  const int numRuns = 5;
  double totalTime = 0.0;

  for (size_t i = 1; i <= 10; ++i) {
    for (int run = 0; run < numRuns; ++run) {
      size_t numNodes = 1000 * std::pow(2, i);
      size_t numEdges = 10 * numNodes;
      Algorithm algorithm(numNodes, numEdges);

      // Example: Generating a vector of random edges
      std::vector<Edge> exampleEdges;
      for (size_t i = 0; i < numEdges; ++i) {
        uint64_t source = rand() % numNodes;
        uint64_t target = rand() % numNodes;
        uint64_t weight =
            rand() % 2000;  // Replace 100 with your desired maximum weight
        exampleEdges.emplace_back(source, target, weight);
      }

      // Measure execution time
      auto start = std::chrono::high_resolution_clock::now();

      // Example: Running the algorithm
      size_t result = algorithm.run(exampleEdges);

      auto end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> duration = end - start;

      totalTime += duration.count();

      // Example: Printing the result
      std::cout << "Run " << run + 1
                << ": Minimum Spanning Tree Weight: " << result << std::endl;
    }

    // Calculate average time
    double averageTime = totalTime / numRuns;
    std::cout << "Average Execution Time with i = " << i << " : " << averageTime
              << " seconds" << std::endl;
  }
  return 0;
}

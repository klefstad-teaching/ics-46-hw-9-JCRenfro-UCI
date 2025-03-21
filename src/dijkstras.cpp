#include "dijkstras.h"

// Dijkstras

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    /*
        Uses a MinHeap
        1. Takes all edges for minheap
        2. While heap not empty,
            a. extract minimum weight from miniheap
            b. set to visited
            c. get all edges from current node
            d. Check distance to currdistance + weight < currentMin for that node, if it is, update it by chaning distance & previous
                Also push to minHeap
        3. Repeat until minheap empty
        4. return distances
    */
    // Inialize Parts
    int size = G.size();
    vector<int> distances(size, INF);
    vector<bool> visited(size, false);
    //priority_queue<pair<int, int>> minHeap; // Minheap pair (vertex, weight)
    MinHeap minHeap;
    // Set distance of start position to 0
    distances[source] = 0;
    previous[source] = -1;
    // Push current minimum (source)
    minHeap.push({source, 0});
    // Start Iteration
    while (!minHeap.empty()){
        // Get current minimum node
        int currMinNode = minHeap.top().first;
            //std::cout << "IN: " << currMinNode << " WITH WEIGHT: " << minHeap.top().second << std::endl;
        minHeap.pop();
        // Check if visited, if visited go to next part
        if (visited[currMinNode]) continue;
        // If not visited set to visited
        visited[currMinNode] = true;
        // Process Edges of current node
        for (Edge edge: G[currMinNode]){
                //std::cout << "\tIN EDGE: " << edge; std::cout << " Distances are: "; for (auto i: distances) std::cout << i << " "; std::cout << std::endl;
            int disToDestNode = distances[currMinNode] + edge.weight;
            int currDisToDestNode = distances[edge.dst];
                //std::cout << "\tdisToDestNode: " << disToDestNode << " current Distance to that node: " << currDisToDestNode << std::endl;
                //std::cout << "\tVisited: "; for (auto i: visited) std::cout << i << " "; std::cout << std::endl;
            if (!visited[edge.dst] && disToDestNode < currDisToDestNode){
                // Update distance to new minimum
                distances[edge.dst] = disToDestNode;
                // Set previous node
                previous[edge.dst] = currMinNode;
                // Add to heap
                    //std::cout << "\t\tPUSHING NODE: " << edge.dst << std::endl;
                    //minHeap.push({edge.dst, disToDestNode});
                minHeap.push({edge.dst, edge.weight});
            }
        }
            //std::cout << "MINHEAP TOP IS: " << minHeap.top().first << std::endl;
    }
    return distances;
}
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination)
{
    /*Path is reversed since backtracking so use stack to pop into vector to fix*/
    vector<int> path;
    stack<int> rpath;
    rpath.push(destination);
    for (int currPrev=previous[destination]; currPrev != -1; currPrev=previous[currPrev])
        rpath.push(currPrev);
    while (!rpath.empty()){
        int val = rpath.top(); rpath.pop();
        path.push_back(val);
    }
    return path;
}
void print_path(const vector<int>& v, int total)
{
    size_t size = v.size();
    for (size_t i=0; i < size; ++i)
        std::cout << v[i] << " ";
    std::cout << std::endl;
    std::cout << "Total cost is " << total << std::endl;
}
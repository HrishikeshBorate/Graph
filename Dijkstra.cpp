// Given:
//  1. Weighted, Undirected Graph, with non-negative weights. 
//  2. Source node
//
// Compute: 
//  1. Shortest distance to all nodes from the source node

class Solution {
  private:
    std::vector<std::vector<int>>* createAdjList(int V, std::vector<std::vector<int>>& edges) {
        // IMPORTANT NOTE: Create a pointer of std::vector<std::vector<int>>* 
        std::vector<std::vector<int>>* adjList = new std::vector<std::vector<int>>[V];
        
        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];
        
            adjList[u].push_back({v, w});
            adjList[v].push_back({u, w});           
        }
        
        return adjList;
    }
    
  public:
    std::vector<int> dijkstra(int V, std::vector<std::vector<int>> &edges, int src) {
        std::vector<std::vector<int>>* adjList = createAdjList(V, edges);
        
        // I want to return the shortest distance from source to all the nodes.
        // Implies, I need a way to store the distance from source to all the nodes.
        // Create a distance vector, initialize it with INT_MAX
        std::vector<int> dist(V, INT_MAX);
        
        // Which node should I expand next, based on the smallest known distance from src 
        // Create a priority queue consisting of {Distance from source to current node, CurrentNode}
        std::priority_queue<
            std::pair<int, int>,
            std::vector<std::pair<int, int>>,
            std::greater<std::pair<int, int>>
        > pq;
            
        dist[src] = 0;
        pq.push({0, src});
        
        while (!pq.empty()) {
            int curDist = pq.top().first;
            int curNode = pq.top().second;
            pq.pop();
            
            for (auto &it : adjList[curNode]) {
                int adjNode = it[0];
                int edgeDist = it[1];
                
                // If going from source → current node → adjacent node <
                // current shortest dist from source → adjacent node,
                // then update it.
                if (curDist + edgeDist < dist[adjNode]) {
                    dist[adjNode] = curDist + edgeDist;
                    pq.push({dist[adjNode], adjNode});
                }
            }
        }
        
        // IMPORTANT NOTE: Free the memory
        delete[] adjList;
        return dist;
    }
};

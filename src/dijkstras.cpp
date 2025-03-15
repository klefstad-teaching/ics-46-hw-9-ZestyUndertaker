#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.size();

    vector<int> distance(n, INF);
    previous.resize(n, -1);
    vector<bool> visited(n, false);

    priority_queue<int, vector<int>, greater<int>> pq;
    pq.push(source);
    distance[source] = 0;
    
    while (!pq.empty()) {
        int v = pq.top();
        pq.pop();

        if (visited[v] == true) {
            continue;
        }

        visited[v] = true;
        for (Edge e : G[v]) {
            int u = e.dst;
            int weight = e.weight;

            if (!visited[u] && distance[v] + weight < distance[u]) {
                distance[u] = distance[v] + weight;
                previous[u] = v;
                pq.push(u);
            }
        }
    }

    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int> & previous, int destination) {
    vector<int> path;
    for (int current = destination; current != -1; current = previous[current]) {
        path.push_back(current);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    for (int vector : v) {
        cout << vector << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}
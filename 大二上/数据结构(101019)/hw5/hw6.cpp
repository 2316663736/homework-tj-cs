#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 使用邻接表存储图
class Edge {
public:
    int to, weight;
    Edge(int t, int w) : to(t), weight(w)
    {
    }
};

class Solution {
public:
    vector<vector<Edge>> graph;
    vector<int> grass_points;
    int n;

    // Dijkstra算法计算从start到所有其他点的最短距离
    vector<long long> dijkstra(int start) 
    {
        vector<long long> dist(n + 1, LLONG_MAX);
        dist[start] = 0;

        queue<int> pq;
        pq.push( start);

        while (!pq.empty()) 
        {
            int curr = pq.front();
            pq.pop();


            for (int i = 0; i < graph[curr].size(); i++) 
            {
                const Edge& edge = graph[curr][i];
                if (dist[edge.to] > dist[curr] + edge.weight) 
                {
                    dist[edge.to] = dist[curr] + edge.weight;
                    pq.push(edge.to);
                }
            }
        }
        return dist;
    }

    void solve()
    {
        int m;
        cin >> n >> m;

        graph.resize(n + 1);

        // 读取边
        for (int i = 0; i < m; i++) {
            int x, y, w;
            cin >> x >> y >> w;
            graph[x].push_back(Edge(y, w));
            graph[y].push_back(Edge(x, w));
        }

        // 读取草地点和马的数量
        int h, r;
        cin >> h >> r;

        // 读取草地点
        grass_points.resize(h);
        for (int i = 0; i < h; i++) {
            cin >> grass_points[i];
        }

        // 处理每匹马
        for (int i = 0; i < r; i++) {
            int start, end;
            cin >> start >> end;

           
            vector<long long> from_start = dijkstra(start);    // 计算从起点到所有点的最短距离
            vector<long long> from_end = dijkstra(end);   // 计算从终点到所有点的最短距离

            // 找到经过任意草地点的最短路径
            long long min_dist = LLONG_MAX;
            for (int i = 0; i < grass_points.size(); i++) {
                int grass = grass_points[i];
                if (from_start[grass] != LLONG_MAX && from_end[grass] != LLONG_MAX) {
                    min_dist = min(min_dist, from_start[grass] + from_end[grass]);
                }
            }

            cout << min_dist << endl;
        }
    }
};

int main() {


    Solution solution;
    solution.solve();

    return 0;
}
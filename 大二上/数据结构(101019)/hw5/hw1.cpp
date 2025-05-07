
//Paste your code here
//NOTE: If you use java, your Main class must be named solution
#include<iostream>

using namespace std;

typedef int ELEM;

struct grmap {
    bool exit = 0;//是否相连（邻接矩阵有没有这个边)
    int visit_time = 0;//遍历次数，由于要两次输出，所以加上了这个标记
};
static void input(grmap** gra, int* num_, int* min_, const int the_hu)
{
    int start = 0, end = 0;
    for (int tem_input = 0; tem_input < the_hu; tem_input++)
    {
        cin >> start >> end;
        gra[start][end].exit = gra[end][start].exit = true;
        num_[start]++;
        num_[end]++;
        min_[start] = (min_[start] < end) ? min_[start] : end;
        min_[end] = (min_[end] < start) ? min_[end] : start;
    }

}
static void  dfs_help(int now_v, grmap** gra, const int* num_, const int* min_, const int the_num_v, int* stack, int& top_stack, bool* out)
{
    if (out[now_v])
        return;
    if (num_[now_v] > 1)
        stack[top_stack++] = now_v;
    if (num_[now_v] == 0)
    {
        if (top_stack == 0)
            return;
        now_v = stack[--top_stack];
    }
    out[now_v] = true;
    for (int tem_v = min_[now_v]; tem_v < the_num_v; tem_v++)
    {
        if (out[tem_v])
            continue;
        if (gra[tem_v][now_v].exit && gra[tem_v][now_v].visit_time == 0)
        {
            gra[tem_v][now_v].visit_time = gra[now_v][tem_v].visit_time = 1;
            cout << ' ' << tem_v;
            dfs_help(tem_v, gra, num_, min_, the_num_v, stack, top_stack, out);
        }
    }
    if (top_stack == 0)
        return;
    now_v = stack[--top_stack];
    dfs_help(now_v, gra, num_, min_, the_num_v, stack, top_stack, out);
}

static void output_dfs(grmap** gra, const int* num_, const int* min_, const int the_num_v)
{

    bool* out = new(nothrow)  bool[the_num_v] {false};
    if (out == NULL)
    {
        cout << "空间申请失败" << endl;
        return;
    }
    for (int tem_v = 0; tem_v < the_num_v; tem_v++)
    {
        if (out[tem_v])
            continue;

        putchar('{');
        cout << tem_v;

        int* stack = new (nothrow) int[the_num_v];
        if (stack == NULL)
        {
            cout << "空间申请失败" << endl;
            return;
        }
        int top_stack = 0;
        dfs_help(tem_v, gra, num_, min_, the_num_v, stack, top_stack, out);
        delete[]stack;

        putchar('}');

    }
    delete out;
    cout << endl;
}
static void output_bfs(grmap** gra, const int* num_, const int* min_, const int the_num_v)
{
    int num_have_out = 0;
    bool* out = new(nothrow)  bool[the_num_v] {false};
    int* queue = new(nothrow)  int[the_num_v];
    int start = 0, end = 0;
    if (out == NULL || queue == NULL)
    {
        cout << "空间申请失败" << endl;
        return;
    }
    for (int tem_v = 0; tem_v < the_num_v; tem_v++)
    {
        if (out[tem_v])
            continue;
        putchar('{');
        cout << tem_v;
        out[tem_v] = true;
        queue[end++] = tem_v;
        while (end != start)
        {
            int now_v = queue[start++];
            for (int tem_num = 0, v = min_[now_v]; tem_num < num_[now_v] && v < the_num_v; v++)
            {
                if (out[v])
                    continue;
                if (gra[v][now_v].exit && gra[v][now_v].visit_time != 2)
                {
                    cout << ' ' << v;
                    if (num_[v] > 1)
                        queue[end++] = v;
                    out[v] = true;
                    num_have_out++;
                    gra[tem_v][now_v].visit_time = gra[now_v][tem_v].visit_time = 2;
                    tem_num++;
                }
            }
        }
        putchar('}');
        if (num_have_out == the_num_v)
            break;
    }

    delete[]queue;
    delete[]out;
    cout << endl;
}

int main()
{
    int the_num_v = 0, the_hu = 0;;
    cin >> the_num_v >> the_hu;
    grmap** gra;//邻接矩阵
    gra = new(nothrow) grmap * [the_num_v + 1];
    if (gra == NULL)
    {
        cout << "空间申请失败" << endl;
        return -1;
    }
    for (int tem__ = 0; tem__ < the_num_v; tem__++)
    {
        gra[tem__] = new(nothrow) grmap[the_num_v + 1];
        if (gra[tem__] == NULL)
        {
            cout << "空间申请失败" << endl;
            return -1;
        }
    }
    int* num_ = new(nothrow) int[the_num_v + 1];//第一个一维数组，记录这里有多少的元素相邻
    int* min_ = new(nothrow)int[the_num_v + 1];//记录这里标号最小的邻接点
    if (num_ == NULL || min_ == NULL)
    {
        cout << "空间申请失败" << endl;
        return -1;
    }
    for (int tem = 0; tem <= the_num_v; tem++)
    {
        min_[tem] = 0x7fffffff;
        num_[tem] = 0;
    }

    input(gra, num_, min_, the_hu);

    output_dfs(gra, num_, min_, the_num_v);
    output_bfs(gra, num_, min_, the_num_v);

    delete[]min_;
    delete[]num_;
    for (int tem__ = 0; tem__ < the_num_v; tem__++)
        delete[]gra[tem__];
    delete[]gra;
}











/*
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>

using namespace std;

// Implementing a simple find function
template<typename Iterator, typename T>
Iterator simple_find(Iterator begin, Iterator end, const T& val) {
    while (begin != end) {
        if (*begin == val) return begin;
        ++begin;
    }
    return end;
}

// Implementing a simple insertion sort
template<typename Iterator>
void insertion_sort(Iterator begin, Iterator end) {
    for (Iterator i = begin + 1; i != end; ++i) {
        auto key = *i;
        Iterator j = i - 1;
        while (j >= begin && *j > key) {
            *(j + 1) = *j;
            j--;
        }
        *(j + 1) = key;
    }
}

void dfs(int v, vector<bool>& visited, const vector<vector<int>>& adj_list, vector<int>& component) {
    stack<int> stk;
    stk.push(v);
    while (!stk.empty()) {
        int node = stk.top();
        stk.pop();
        if (!visited[node]) {
            visited[node] = true;
            component.push_back(node);
            for (int i = adj_list[node].size() - 1; i >= 0; --i) {
                int neighbor = adj_list[node][i];
                if (!visited[neighbor]) {
                    stk.push(neighbor);
                }
            }
        }
    }
}

void bfs(int v, vector<bool>& visited, const vector<vector<int>>& adj_list, vector<int>& component) {
    queue<int> q;
    q.push(v);
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        if (!visited[node]) {
            visited[node] = true;
            component.push_back(node);
            for (size_t i = 0; i < adj_list[node].size(); ++i) {
                int neighbor = adj_list[node][i];
                if (!visited[neighbor]) {
                    q.push(neighbor);
                }
            }
        }
    }
}

string format_components(const vector<vector<int>>& components) {
    string result;
    for (size_t i = 0; i < components.size(); ++i) {
        result += "{";
        for (size_t j = 0; j < components[i].size(); ++j) {
            result += to_string(components[i][j]);
            if (j < components[i].size() - 1) {
                result += " ";
            }
        }
        result += "}";
    }
    return result;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj_list(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        if (simple_find(adj_list[u].begin(), adj_list[u].end(), v) == adj_list[u].end()) {
            adj_list[u].push_back(v);
            adj_list[v].push_back(u);
            insertion_sort(adj_list[u].begin(), adj_list[u].end());
            insertion_sort(adj_list[v].begin(), adj_list[v].end());
        }
    }

    vector<bool> visited(n, false);
    vector<vector<int>> components_dfs;
    vector<vector<int>> components_bfs;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            vector<int> component;
            dfs(i, visited, adj_list, component);
            components_dfs.push_back(component);
        }
    }

    fill(visited.begin(), visited.end(), false);

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            vector<int> component;
            bfs(i, visited, adj_list, component);
            components_bfs.push_back(component);
        }
    }

    cout << format_components(components_dfs) << endl;
    cout << format_components(components_bfs) << endl;

    return 0;
}

*/
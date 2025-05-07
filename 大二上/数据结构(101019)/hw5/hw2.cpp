#include <iostream>
#include<queue>
#include<vector>
#include <iomanip> 

using namespace std;

static int bfs(const vector<vector<int>>& input_gramap, const int num_point, const int start_point)
{
	queue<int> que;
	bool* visit = new(nothrow) bool[num_point] {false};
	if (visit == NULL)
		return -1;
	int num_return = 0;
	que.push(start_point);
	for (int times = 0; times < 6&&!que.empty(); times++)
	{
		int num = que.size();
		for (int i = 0; i < num; i++)
		{ 
			vector<int> now = input_gramap[que.front()];
			que.pop();
			for (unsigned int tem = 0; tem < now.size(); tem++)
			{
				if (!visit[now[tem]])
				{
					que.push(now[tem]);
					visit[now[tem]] = true;
					num_return++;
				}
			}
		}
	}
	delete[] visit;

	return num_return;
}

int main()
{
	int num_point, num_line;
	cin >> num_point >> num_line;

	vector<vector<int>> input_gramap(num_point+1);
	for (int tem_line = 0; tem_line < num_line; tem_line++)
	{
		int m, n;
		cin >> m >> n;
		input_gramap[m-1].push_back(n-1);
		input_gramap[n-1].push_back(m-1);
	}
	cout <<fixed << setprecision(2);
	for (int tem_point = 0; tem_point < num_point; tem_point++)
	{
		int ret = bfs(input_gramap, num_point, tem_point);
		cout << tem_point + 1 << ": " << (float)(ret*100.0f/ num_point) << '%' << endl;
	}


}
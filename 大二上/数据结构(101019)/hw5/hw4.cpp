#include <iostream>
#include <vector>
using namespace std;

//int give_no(vector<vector<int>> & child)

void input(const int in_num, vector<int> &no,const int n)
{
	vector<int> child(n,0);
	vector<vector<int>>  father(n); vector<vector<int>>ch(n);
	vector<vector<bool>> appear(n, vector<bool>(n, false));
	

	int first, last;
	for (int i = 0; i < in_num; i++)
	{
		cin >> first >> last;
		if (!appear[first-1][last-1])
		{
			appear[first-1][last-1] = true;
			father[last -1].push_back(first-1);
			ch[first - 1].push_back(last - 1);
			child[first-1]++;
		}
	}

	int start = 0;
	for (start = 0; start < n; start++)
		if (!child[start])
			break;

	if (start == n)
		return;

	no[start] = n - 1;

	for (int i = 0; i < n; i++)
	{
 
		int tem_start = start;
 		for (int j = 0; j < father[start].size(); j++)
		{
 
			if (child[father[start][j]] == 1)
			{
				no[father[start][j]] = no[start]-1;
				tem_start = father[start][j];
			}
			else
				child[father[start][j]]--;
			 
 		}
		start = tem_start;
	}
 

}




int main()
{
	int n, up_down, left_right;
	cin >> n >> up_down >> left_right;


	 vector< vector<int>> res(n,  vector<int>(n,0));
	vector<int> up_down_id(n,-1);
	vector<int> left_right_id(n);
	vector<bool> row(n, false);
	vector<bool> col(n, false);

	input(up_down, up_down_id, n);
	input(left_right, left_right_id, n);

	for (int i = 0; i < n; i++)
	{
		if (up_down_id[i] == -1 || left_right_id[i] == -1|| row[up_down_id[i]]||col[left_right_id[i]])
		{
			cout << "-1" << endl;;
			exit(0);
		}
		res[up_down_id[i]][left_right_id[i]] = i + 1;
		row[up_down_id[i]] = true;
		col[left_right_id[i]] = true;
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << res[i][j] << ' ';
		putchar('\n');
	}

}




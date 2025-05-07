



/**
 * @file    solution.cpp
 * @name    换座位问题解决方案
 * @date    2024-12-16
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
using namespace std;

/********************************/
/*     以下是需要提交的代码     */
/********************************/
class Solution {
public:
    int solve(vector<vector<string>>& old_chart, vector<vector<string>>& new_chart) {
        // 获取座位表的尺寸
        int n = old_chart.size();
        int m = old_chart[0].size();

        // 创建学生名字到位置的映射
        map<string, pair<int, int>> student_pos;
        // 用于标记已访问的位置
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        // 记录总的交换次数
        int total_swaps = 0;

        // 构建学生到位置的映射关系
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                student_pos[old_chart[i][j]] = make_pair(i, j);
            }
        }

        // 遍历每个位置，寻找置换环
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // 如果该位置未访问且需要移动（当前学生不在正确位置）
                if (!visited[i][j] && old_chart[i][j] != new_chart[i][j]) {
                    int cycle_length = 0;  // 记录当前置换环的长度
                    int curr_i = i, curr_j = j;  // 当前处理的位置

                    // 追踪置换环
                    while (!visited[curr_i][curr_j]) {
                        // 标记当前位置已访问
                        visited[curr_i][curr_j] = true;
                        cycle_length++;

                        // 找到应该坐在当前位置的学生
                        string target_student = new_chart[curr_i][curr_j];
                        // 获取该学生在原座位表中的位置
                        pair<int, int> next_pos = student_pos[target_student];
                        int next_i = next_pos.first;
                        int next_j = next_pos.second;

                        // 如果回到起点，说明找到了一个完整的置换环
                        if (next_i == i && next_j == j) {
                            break;
                        }

                        // 移动到下一个位置
                        curr_i = next_i;
                        curr_j = next_j;
                    }

                    // 对于长度为k的置换环，需要k-1次交换
                    if (cycle_length > 0) {
                        total_swaps += (cycle_length - 1);
                    }
                }
            }
        }

        return total_swaps;
    }
};
/********************************/
/*     以上是需要提交的代码     */
/********************************/

int main() {
    // 读取输入的行数和列数
    int n, m;
    cin >> n >> m;

    // 创建并读取原始座位表
    vector<vector<string>> old_chart(n, vector<string>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> old_chart[i][j];
        }
    }

    // 创建并读取目标座位表
    vector<vector<string>> new_chart(n, vector<string>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> new_chart[i][j];
        }
    }

    // 创建Solution对象并解决问题
    Solution s;
    cout << s.solve(old_chart, new_chart) << endl;

    return 0;
}





































// 
// 
// 
// 
// 
// 
// 
// 
// #include<iostream>
//#include<string>
//using namespace std;
//
//
//
//class all_num {
//private:
//	struct BST_node {
//		string key;
//		BST_node* left;
//		BST_node* right;
//		BST_node(string k) :key(k), left(nullptr), right(nullptr)
//		{
//
//		}
//	};
//	int all_f;//总共有多少人坐错位置
//	int arroud;//那些人总共可以构成多少环（绕一圈，最后错位置回到了第一个人）
//	BST_node* root;
//public:
//	void insert(const string k);
//};
//
//struct Node {
//	string key;
//	string father ;
//};
//
//void all_num::insert(const string k)
//{
//	BST_node* now=root;
//	while (1)
//	{
//
//	}
//}
//int main()
//{
//	int all_different = 0, all_exchange = 0;
//	int n, m;
//	cin >> n >> m;
//	Node* old_chart = new(nothrow) Node[n * m];
//	Node* new_chart = new(nothrow) Node[n * m];
//	if (!old_chart || !new_chart)
//		exit(-999);
//	for (int i = 0; i < n * m; i++)
//	{
//		cin >> old_chart[i].key;
//		old_chart[i].father = old_chart[i].key;
//	}
//	for (int i = 0; i < n * m; i++)
//	{
//		cin >> new_chart[i].key;
//		new_chart[i].father = new_chart[i].key;
//	}
//
//	for (int tem_n = 0; tem_n < n; tem_n++)
//	{
//		for (int tem_m = 0; tem_m < m; tem_m++)
//		{
//			if (old_chart[tem_n * m + tem_m].key == new_chart[tem_n * m + tem_m].key)
//				continue;
//		}
//	}
//}
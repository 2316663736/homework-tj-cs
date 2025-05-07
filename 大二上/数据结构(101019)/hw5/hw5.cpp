#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
private:
    int n;
    vector<vector<int>> graph;//第i个数组中储存了所有以i课程为前置课程的课程
    vector<int> times;

    vector<int> cal_times(const vector<int>& times)
    {
        vector<int> inDegree(n, 0);
        vector<int> earliest(n, 0);

        // 计算入度，或者说前置课程数目
        for (int i = 0; i < n; i++) 
            for (int next : graph[i])
                inDegree[next]++;
            
        queue<int> q;
        for (int i = 0; i < n; i++) 
            if (inDegree[i] == 0) {
                q.push(i);
                earliest[i] = times[i];
            }
        

        while (!q.empty()) 
        {
            int curr = q.front();
            q.pop();

            for (int next : graph[curr])
            {   
                earliest[next] = max(earliest[next],earliest[curr] + times[next]);
                --inDegree[next];
                if (inDegree[next] == 0) 
                    q.push(next);
                
            }
        }

        return earliest;
    }
    int findMax(const vector<int>& nums) 
    {
        int maxVal = nums[0];  
        for (int i = 1; i < nums.size(); i++)     
            if (nums[i] > maxVal) 
                maxVal = nums[i];
    
        return maxVal;
    }
public:
    void solve() {
        // 读取输入
        cin >> n;
        graph.resize(n);
        times.resize(n);

        for (int i = 0; i < n; i++)
        {
            int  c;
            cin >> times[i] >> c;

            for (int j = 0; j < c; j++) 
            {
                int prereq;
                cin >> prereq;
                graph[prereq - 1].push_back(i);  
            }
        }


        vector<int> ori_times = cal_times(times);
        int ori_max_time = findMax(ori_times);


        for (int i = 0; i < n; i++)
        {
            times[i]++;

            vector<int> new_time = cal_times(times);
            int new_max_time = findMax(new_time);

            cout << ori_times[i] << " "
                << (new_max_time > ori_max_time ? 1 : 0) << endl;

            times[i]--;
        }
    }
};

int main() {


    Solution solution;
    solution.solve();

    return 0;
}
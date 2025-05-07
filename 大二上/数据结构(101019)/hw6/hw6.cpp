#include <unordered_map>
#include <vector>

class FreqStack {
private:
    // 记录每个元素的频率
    std::unordered_map<int, int> freq;
    // 按频率分组的栈，group[i]存储频率为i的元素
    std::unordered_map<int, std::vector<int>> group;
    // 当前最大频率
    int maxFreq;

public:
    FreqStack() {
        maxFreq = 0;
    }

    void push(int val) {
        // 更新频率
        freq[val]++;
        // 更新最大频率
        maxFreq = max(maxFreq, freq[val]);
        // 将元素加入对应频率的组
        group[freq[val]].push_back(val);
    }

    int pop() {
        // 获取最大频率组的最后一个元素
        int val = group[maxFreq].back();
        // 从组中移除该元素
        group[maxFreq].pop_back();
        // 更新频率
        freq[val]--;

        // 如果当前最大频率组为空，减小maxFreq
        if (group[maxFreq].empty()) {
            maxFreq--;
        }

        return val;
    }
};
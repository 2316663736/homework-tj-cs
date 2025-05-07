#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 判断是否为素数
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// 获取大于等于n的最小素数
int getNextPrime(int n) {
    if (n <= 2) return 2;
    if (n % 2 == 0) n++; // 如果是偶数，先加1变成奇数
    while (!isPrime(n)) n += 2; // 只检查奇数
    return n;
}

unsigned long long int getHash(const string& key) {
    unsigned long long int hash = 0;
    for (char c : key) {
        hash = hash * 37ULL + (unsigned long long int)c;
    }
    return hash;
}

// 平方探测
int findPosition(vector<bool>& used, unsigned long long int hash, int tableSize) {
    int base = hash % tableSize;

    // i从1开始，因为i=0的情况就是base位置
    // 先检查base位置
    if (!used[base]) return base;

    // 然后使用平方探测: base ± i^2
    for (int i = 1; i <= tableSize; i++) {
        // 正向探测: base + i^2
        long long offset = ((long long)i * i) % tableSize;
        int pos = (base + offset) % tableSize;
        if (!used[pos]) return pos;

        // 负向探测: base - i^2
        pos = ((base - offset) % tableSize + tableSize) % tableSize;
        if (!used[pos]) return pos;
    }
    return -1;
}

int main() {
    int N, P;
    cin >> N >> P;

    // 获取表长
    int tableSize = P;
    if (!isPrime(P)) {
        tableSize = getNextPrime(P);
    }

    vector<bool> used(tableSize, false);

    for (int i = 0; i < N; i++) {
        string key;
        cin >> key;

        if (i > 0) cout << " ";

        unsigned long long int hash = getHash(key);
        int pos = findPosition(used, hash, tableSize);

        if (pos == -1) {
            cout << "-";
        }
        else {
            cout << pos;
            used[pos] = true;
        }
    }
    cout << endl;

    return 0;
}
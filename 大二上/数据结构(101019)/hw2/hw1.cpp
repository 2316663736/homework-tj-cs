#include<iostream>
using namespace std;

int main()
{
	int input[100001] = { 0 }, output[100001] = { 0 }, len, k;
	cin >> len >> k;                  //读入结果数组长度和旋转位置数
	for (int i = 0; i < len; i++)
		cin >> input[i];             //读入输入元素
	for (int i = 0; i < len; i++)
		output[(i + k) % len] = input[i];
	for (int i = 0; i < len; i++)
		cout << output[i] << endl;;
	return 0;
}
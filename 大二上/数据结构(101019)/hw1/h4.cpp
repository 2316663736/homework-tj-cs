#include<iostream>
using namespace std;

int main()
{
	int n, m, output = 0;

	cin >> n >> m;
	for (int i = 2; i <= n; i++)
		output = (output + m) % i;
	cout << output;
}
//NOTE: If you use java, your Main class must be named solution
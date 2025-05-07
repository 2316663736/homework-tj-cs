#include<iostream>
#include <iomanip>
using namespace std;

int main()
{

	double all=0,tem;
	for (int i = 1; i <= 12; i++)
	{
		cin >> tem;
		all += tem;
	}
	cout << "¥";
	cout << setiosflags(ios::fixed) << setprecision(2) << all / 12<<'\n';
	return 0;

}
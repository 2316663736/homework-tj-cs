#include<iostream>
#include <vector> 
#include<map>
using namespace std;

//map中，前面的int代表几次方，后面代表系数
map<int, int>map_m;
map<int, int>map_n;
//a代表前面系数，b代表几次方(这个用数组存，记录下来）
int tem_m_a, tem_n_a, tem_m_b[2100], tem_n_b[2100];
int m, n;

void add_()
{

	int i_m,i_n;
	for (i_m=i_n = 0; i_m < m && i_n < n; )
	{
		if (tem_m_b[i_m] < tem_n_b[i_n])
		{
			cout << map_m[tem_m_b[i_m]] << " " << tem_m_b[i_m] << " ";
			i_m++;
		}
		else if (tem_m_b[i_m] > tem_n_b[i_n])
		{
			cout << map_n[tem_n_b[i_n]] << " " << tem_n_b[i_n] << " ";
			i_n++;
		}
		else 
		{
			if (map_n[tem_n_b[i_n]] + map_m[tem_m_b[i_m]] != 0)
				cout << map_n[tem_n_b[i_n]] + map_m[tem_m_b[i_m]] << " " << tem_n_b[i_n] << " ";
			i_m++;
			i_n++;
		}
	}
	for(;i_m<m;i_m++)
		cout << map_m[tem_m_b[i_m]] << " " << tem_m_b[i_m] << " ";
	for (; i_n < n; i_n++)
		cout << map_n[tem_n_b[i_n]] << " " << tem_n_b[i_n] << " ";
	cout << endl;
}
void multi()
{
	map<int, int > map_result;
	int i_m, i_n;
	int bb;
	for(i_m=0;i_m<m;i_m++)
		for (i_n = 0; i_n < n; i_n++)
		{
			bb = tem_m_b[i_m] + tem_n_b[i_n];
			if (map_result.count(bb) > 0)
				map_result[bb] +=map_m[tem_m_b[i_m]]*map_n[tem_n_b[i_n]] ;
			else
				map_result[bb] =map_m[tem_m_b[i_m]]*map_n[tem_n_b[i_n]];
		}
	map<int, int>::iterator it = map_result.begin();
	for (; it != map_result.end(); it++)
		if (it->second != 0)
			cout << it->second << " " << it->first << " ";
	cout << endl;
}

int main()
{

	cin >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> tem_m_a>>tem_m_b[i];
		map_m[tem_m_b[i]] = tem_m_a;	
	}
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> tem_n_a >> tem_n_b[i];
		map_n[tem_n_b[i] ]= tem_n_a;
	}

	int decide;
	cin >> decide;
	if (decide == 0)
		add_();
	else if (decide == 1)
		multi();
	else if (decide == 2)
	{
		add_();
		multi();

	}
	return 0;
}
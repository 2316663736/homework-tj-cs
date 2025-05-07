#include<iostream>
#include<vector>
using namespace std;

static void mysort(vector<int>& a, int start, int end)
{
	if (end - start <= 1)
		return;
	int mid = (start + end) / 2;
	mysort(a, start, mid);
	mysort(a, mid , end);


	int count_r = start, count_l = mid ,cou_a=start;
	vector<int>right(mid  - start);
	for (int i = start; i < mid; i++)
		right[i - start] = a[i];
	vector<int>left(end - mid );
	for (int i = mid ; i < end; i++)
		left[i - mid] = a[i];
	
	while (count_r < mid  && count_l < end)
	{
		if (right[count_r - start] < left[count_l - mid ])
		{
			a[cou_a] = right[count_r - start];
			count_r++;
		}
		else
		{
			a[cou_a] = left[count_l - mid ];
			count_l++;
		}
		cou_a++;
	}
	while(count_r < mid )
		a[cou_a++] = right[count_r++ - start];
	while (count_l < end)
		a[cou_a++] = left[count_l++ - mid ];
}

int main()
{
	int n, m;
	cin >> n >> m;
	vector<int> nums(n);
	vector<int> queries(m);
	for (int i = 0; i < n; i++)
		cin >> nums[i];
	for (int i = 0; i < m; i++)
		cin >> queries[i];

	mysort(nums, 0, n);

	vector<int> ad(n);
	ad[0] = nums[0];
	for (int i = 1; i < n; i++)
		ad[i] = ad[i-1] + nums[i];

	for(int i=0;i<m;i++)
	{
		int t;
		for ( t= 0; t < n; t++)
		{
			if (queries[i] >= ad[t] && (t + 1 == n || queries[i] < ad[t + 1]))
			{
				cout << t + 1 << " ";
				break;
			}
		}
		if (t == n)
			cout << "0 ";
	}
}
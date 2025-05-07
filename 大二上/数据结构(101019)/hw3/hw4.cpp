#include<iostream>
using namespace std;

void search_near(bool(&the_input)[1002][1002], int row, int col, bool& add_or_not,int row_num,int col_num)
{
	if (the_input[row][col])
	{
		the_input[row][col] = false;
		if (row != 1 && row != row_num && col != 1 && col != col_num)
			add_or_not = true;
		search_near(the_input, row + 1, col, add_or_not, row_num,  col_num);
		search_near(the_input, row - 1, col, add_or_not, row_num, col_num);
		search_near(the_input, row, col - 1, add_or_not, row_num, col_num);
		search_near(the_input, row, col + 1, add_or_not, row_num, col_num);
	}

}

int main()
{
	int row, col;
	//第0行与最后一行（列）不存放输入，只是单纯为了方便防止越界
	bool the_input[1002][1002] = { false };
	int num = 0;
	bool add_the_num_or_not = false;
	cin >> row >> col;
	for (int tem_row = 1; tem_row <= row; tem_row++)
		for (int tem_col = 1; tem_col <= col; tem_col++)
			cin >> the_input[tem_row][tem_col];
	for (int tem_row = 1; tem_row <= row; tem_row++)
		for (int tem_col = 1; tem_col <= col; tem_col++)
		{
			if (the_input[tem_row][tem_col])
				search_near(the_input, tem_row, tem_col, add_the_num_or_not, row, col);
			if (add_the_num_or_not)
			{
				num++;
				add_the_num_or_not = false;
			}
		}
	cout << num;
}
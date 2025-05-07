#include<iostream>
using namespace std;

int main()
{
	char input_stack[100005] = { 0 };
	int top_input_stack = 0;

	int the_start = 0;// 2147483647;//起始位置
	int max_len = 0;  //子串长度
	int left_no[10000] = { 0 }, top_left = 0;
	int right_no[10000] = { 0 }, top_right=0;


	while (cin >> input_stack[top_input_stack++])
	{
		//这个方便在程序测试时进行退出循环，实际情况不会使用
		if (input_stack[top_input_stack-1] == '1')
			break;
		if (input_stack[top_input_stack - 1] == ')')
		{
			if (top_left > 0 && (top_right==0||left_no[top_left - 1] > right_no[top_right - 1]))
			{
				input_stack[top_input_stack - 1] = '\0';
				input_stack[left_no[top_left - 1] - 1] = '\0';
				left_no[--top_left] = 0;
			}
			else
				right_no[top_right++] = top_input_stack;
		}
		else if (input_stack[top_input_stack - 1] != '(')
			top_input_stack--;
		else 
			left_no[top_left++] = top_input_stack;

	}
	int last_not_0[50000] = { 0 };
	int top_last=1;
	int tem_left = 0, tem_right=0;
	for (tem_left = 0, tem_right = 0; tem_left < top_left && tem_right < top_right;)
	{

		if (left_no[tem_left] < right_no[tem_right])
			last_not_0[top_last++] = left_no[tem_left++];
		else if (left_no[tem_left] > right_no[tem_right])
			last_not_0[top_last++] = right_no[tem_right++];	
		else
			cout << "错误";
	}
	while(tem_left<top_left)
		last_not_0[top_last++] = left_no[tem_left++];
	while (tem_right < top_right)
		last_not_0[top_last++] = right_no[tem_right++];
	last_not_0[top_last++] = top_input_stack;
	for (int tem = 0; tem < top_last-1; tem++)
	{
		if ((last_not_0[tem + 1] - last_not_0[tem]-1) > max_len)
		{
			max_len = last_not_0[tem + 1] - last_not_0[tem]-1;
			the_start = last_not_0[tem] ;
		}
	}
	if (left_no[0] == 0 && right_no[0] == 0 && top_input_stack > 0)
	{
		max_len = top_input_stack - 1;
		the_start = 0;
	}
	if (top_input_stack == 1||top_input_stack==2)
		max_len =the_start= 0;
	if (max_len == 0)
		the_start = 0;
	cout << max_len << " " << the_start << endl;
	return 0;
}



/*
#include<iostream>
using namespace std;

int main()
{
	char input_stack[100005] = { 0 };
	int top_input_stack = 0;

	int the_start = 0;// 2147483647;//起始位置
	int max_len = 0;  //子串长度
	int now_escape = 0;



	while (cin >> input_stack[top_input_stack++])
	{
		//这个方便在程序测试时进行退出循环，实际情况不会使用

		if (input_stack[top_input_stack - 1] == ')')
		{
			bool continue_or_not = false;
			for (int tem_top = top_input_stack - 1-now_escape; tem_top > 0; tem_top--)
			{
				if (input_stack[tem_top - 1] == ')')
					break;
				else if (input_stack[tem_top - 1] == '(')
				{
					input_stack[top_input_stack - 1] = '\0';
					input_stack[tem_top - 1] = '\0';
					now_escape++;
					continue_or_not = true;
					break;
				}
				if (continue_or_not)
					continue;
			}
		}
		else if (input_stack[top_input_stack - 1] != '(')
			top_input_stack--;
		now_escape = 0;
	}
	int tem_len=0, tem_start = 0;
	for (int i = 0; i < top_input_stack; i++)
		if (input_stack[i] == '\0')
		{
			for (tem_len = 0; (tem_len + i) < top_input_stack; tem_len++)
				if (input_stack[i + tem_len] != '\0')
					break;
			if(tem_len>max_len)
			{
				if ((tem_len + i) == top_input_stack )
					tem_len--;
				max_len = tem_len;
				the_start = i;
			}
		}
	if (top_input_stack == 1||top_input_stack==2)
		max_len =the_start= 0;
	cout << max_len << " " << the_start << endl;
	return 0;
}


*/

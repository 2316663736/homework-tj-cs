#include<iostream>
#include<string>
using namespace std;

struct num_next {
	int the_num;
	num_next* next=NULL;
};
 
class my_queue {
public:
	int enqueue();
	void dequeue();
	void max();
	void display();
	my_queue();

private:
	//队列的最大长度
	int max_num = 0;
	//队列现在长度
	int now_num = 0;
	//队列的开始位置
	num_next* start = 0;
	//队列结束位置
	num_next* end = 0;
	//记录最大值，并记录有多少个（0为那个最大值，1为个数）
	int max_and_num[2] = { -2147483647,0 };
	void search_the_max_and_num();

};
my_queue::my_queue()
{
	cin >> max_num;
}

void my_queue::search_the_max_and_num()
{
	num_next* i;
	max_and_num[0] = -2147483647;
	for (i= start; i != end;i=i->next)
	{
		if (i == NULL)
			return;
		if (i->the_num > max_and_num[0])
		{
			max_and_num[0] = i->the_num;
			max_and_num[1] = 1;
		}
		else if (i->the_num == max_and_num[0])
			max_and_num[1]++;
	}
	/*此时栈尾部还有一个元素*/
	if (i->the_num > max_and_num[0])
	{
		max_and_num[0] = i->the_num;
		max_and_num[1] = 1;
	}
	else if (i->the_num == max_and_num[0])
		max_and_num[1]++;
}

int  my_queue::enqueue()
{
	num_next* p = new num_next;
	if (p == NULL)
		return -1;
	cin >> p->the_num;
	if (now_num == max_num)
	{
		cout << "Queue is Full" << endl;
		delete p;
	}
	else
	{
		if (now_num == 0)
			start = p;
		else
			end->next = p;
		end = p;
		now_num++;
		if (p->the_num > max_and_num[0])
		{
			max_and_num[0] = p->the_num;
			max_and_num[1] = 1;
		}
		else if (p->the_num == max_and_num[0])
		{
			max_and_num[1]++;
		}
	}
	return 0;
}
void my_queue::dequeue()
{
	if(now_num==0)
		cout << "Queue is Empty" << endl;
	else
	{
		int tem_num = start->the_num;
		num_next* p = new num_next;
		p = start;
		start = start->next;
		delete p;
		now_num--;
		cout << tem_num << endl;


		if (tem_num == max_and_num[0])
			max_and_num[1]--;
		if (max_and_num[1] == 0)
			search_the_max_and_num();
	}
}
void my_queue::max()
{
	if (now_num==0)
		cout << "Queue is Empty" << endl;
	else
		cout << max_and_num[0] << endl;
}
void my_queue::display()
{
	num_next* i = new num_next;
	for (i = start; i != end; )
	{
		num_next* p = new num_next;
		p = i;
		i = i->next;
		cout << p->the_num << " ";
		delete p;
	}
	cout << i->the_num << endl;
	delete i;
}

int main()
{
	my_queue  the_que;
	string input;
	while (1)
	{
		cin >> input;
		if (input == "enqueue")
			the_que.enqueue();	
		else if (input == "dequeue")
			the_que.dequeue();
		else if (input == "max")
			the_que.max();
		else if (input == "quit")
			break;
	}
	the_que.display();
	return 0;
}

/*数组模拟队列*/
/*
#include<iostream>
#include<string>
using namespace std;

class queue_use_array {
public:
	void enqueue(int i);
	void dequeue();
	void max();
	void display();
	queue_use_array();

private:
	//队列的最大长度
	int max_num=0;
	//用数组模拟队列
	int queue[60000] = { 0 };
	//队列的开始位置
	int start =0;
	//队列结束位置的下一位
	int end =0;
	//记录最大值，并记录有多少个（0为那个最大值，1为个数）
	int max_and_num[2] = { -2147483647,0 };
	void search_the_max_and_num();

};
queue_use_array::queue_use_array()
{
	cin >> max_num;
}
void queue_use_array::search_the_max_and_num()
{
	max_and_num[0] = -2147483647;
	for (int i = start; i < end; i++)
	{
		if (queue[i] > max_and_num[0])
		{
			max_and_num[0] = queue[i];
			max_and_num[1] = 1;
		}
		else if (queue[i] == max_and_num[0])
			max_and_num[1]++;
	}
}
void  queue_use_array::enqueue(int i)
{
	if (end - start == max_num)
		cout << "Queue is Full" << endl;
	else
	{
		queue[end++] = i;

		if (i > max_and_num[0])
		{
			max_and_num[0] = i;
			max_and_num[1] = 1;
		}
		else if (i == max_and_num[0])
		{
			max_and_num[1]++;
		}
	}
}

void queue_use_array::dequeue()
{
	int the_out = 0;
	if (end == start)
		cout << "Queue is Empty" << endl;
	else
	{
		the_out = queue[start++];
		if (the_out == max_and_num[0])
			max_and_num[1]--;
		if (max_and_num[1] == 0)
			search_the_max_and_num();
		cout << the_out << endl;
	}
}

void queue_use_array::max()
{
	if(start==end)
		cout << "Queue is Empty" << endl;
	else
		cout << max_and_num[0] << endl;
}
void queue_use_array::display()
{
	for (int i = start; i < end; i++)
	{
		cout << queue[i] ;
		if (i != end - 1)
			putchar(' ');
	}
	cout << endl;
}
int main()
{
	queue_use_array  the_que;
	string input;
	while (1)
	{
		cin >> input;
		if (input == "enqueue")
		{
			int i = 0;
			cin >> i;
			if (i == 872828398)
				i = 872828398;
			the_que.enqueue(i);
		}
		else if (input == "dequeue")
			the_que.dequeue();
		else if (input == "max")
			the_que.max();
		else if (input == "quit")
			break;
	}
	the_que.display();
}
*/
#include<iostream>
#include<string>
using namespace std;

struct Student_no
{
	string name; //姓名
	string id; //学号
	Student_no* next; //指向下一位的指针
};
void insert(Student_no* &head,int& len)
{
	/*
     head ：链表的头节点
     len  ：当前链表长度
     都是跳过引用的方式返回值
	 */

	
	/*
	 输入：读入需要输入的位置、学号、姓名，并判断需要插入的位置是否合法（1到len+1），不合法则跳过实现部分
     实现：遍历到相应插入位置，申请内存（申请失败输出-1，退出函数），进行指针变换插入相应的节点，链表长度加一
     输出：插入成功输出0，否则输出-1
     */
	int place;
	string no, name;
	//输入和相关判断省略
	Student_no* new_stu = new Student_no{ no, name, NULL };
	if (place == 1) {
		new_stu->next = head;
		head = new_stu;
	}
	else {
		Student_no* prev = head;
		for (int i = 1; i < place - 1; i++) {
			prev = prev->next;
		}
		new_stu->next = prev->next;
		prev->next = new_stu;
	}
	len++;
	//输出省略
}
void remove(Student_no* &head, int & len)
{
	/*
	 head ：链表的头节点
	 len  ：当前链表长度
	 都是通过引用的方式返回值
	 */

	/*
	输入：读入需要删除的位置，并判断是否合法
	实现：遍历到待删除节点前驱进行指针变换删除链表中编号为i的节点，同时释放内存，链表长度减
	一
	输出：删除成功输出0，否则输出-1（没有查询到有这位学生）
	*/
	int place;
	Student_no* toDelete ;
	//输入和相关判断省略
	if (place == 1) {
		toDelete = head;
		head = head->next;
	}
	else {
		Student_no* prev = head;
		for (int i = 1; i < place - 1; ++i) {
			prev = prev->next;
		}
		toDelete = prev->next;
		prev->next = toDelete->next;
	}
	delete toDelete;
	len--;
	//输出省略
}
void checkName(Student_no* head, string name)
{
	/*
	head 链表的头节点
	name 要查询的学生姓名
	*/
	/*
	实现：遍历列表，检查链表每一个节点中存储的姓名是否与所给姓名相同
	输出：查找到此位学生输出相关信息，否则输出-1
	*/
	Student_no* current = head;
	int place = 1;
	while (current) {
		if (current->name == name) {
			cout << place<< " " << current->id << " " << current->name << endl;
			return;
		}
		current = current->next;
		place++;
	}
	cout << -1 << endl; // 找不到的情况下  
}




void _insert(string* name, string* no_id,int &now_num)
{
	int place;
	string tem_name, tem_no;
	cin >> place >>  tem_no>>tem_name;
	if (place >= 1 && place <= (now_num + 1))
	{
		int tem_place;
		for (tem_place = now_num ; tem_place != (place-1); tem_place--)
		{
			*(name + tem_place) = *(name + tem_place - 1);
			*(no_id + tem_place) = *(no_id + tem_place - 1);
		}
		*(name + place - 1) = tem_name;
		*(no_id + place - 1) = tem_no;
		cout << "0" << endl;
		now_num++;
	}
	else
		cout << "-1" << endl;

}

void _remove(string* name, string* no_id, int &now_num)
{
	int place;
	cin >> place;
	if (place >= 1 && place <= now_num)
	{
		int tem_place;
		for (tem_place = place - 1; tem_place != (now_num ); tem_place++)
		{
			*(name + tem_place) = *(name + tem_place + 1);
			*(no_id + tem_place) = *(no_id + tem_place + 1);
		}
		cout << "0" << endl;
		now_num--;
	}
	else
		cout << "-1" << endl;
}
void _check(string* name, string* no_id, int now_num)
{
	string chose, name_no;
	cin >> chose >> name_no;
	if (chose == "name")
	{
		int i;
		for (i = 0; i < now_num; i++)
			if (name_no == *(name + i))
			{
				cout << i + 1 << " " << no_id[i] << " " << name[i] << endl;
				return;
			}

	}
	else if (chose == "no")
	{
		int i;
		for (i = 0; i < now_num; i++)
			if (name_no == *(no_id + i))
			{
				cout << i + 1 << " " << no_id[i] << " " << name[i] << endl;
				return;
			}
	}
	cout << "-1" << endl;
}

int main()
{
	int now_num;
	string name[100000], no_id[100000];
	cin >> now_num;
	for (int i = 0; i < now_num; i++)
		cin >> no_id[i] >> name[i];

	string choice;
	while (1)
	{
		cin >> choice;
		if (choice == "insert")
			_insert(name, no_id, now_num);
		else if (choice == "remove")
			_remove(name, no_id, now_num);
		else if (choice == "check")
			_check(name,no_id,now_num);
		else if (choice == "end")
			break;
	}
	cout << now_num << endl;
	return 0;

}
/*#include<iostream>
#include<string>
#include <vector> 
using namespace std;   

vector<string> vec[2];
string no_name[1000][2];
int max_n=0;
void _insert()
{
	int place;
	string n_n[2];
	cin >> place>>n_n[0]>>n_n[1];
	if (place >= 1 && place <= int(vec[0].size()))
	{
		vec[0].insert(vec[0].begin() + place - 1, n_n[0]);
		vec[1].insert(vec[1].begin() + place - 1, n_n[1]);
		cout << "0" << endl;
		return;
	}
	else if (place == int(vec[0].size() + 1))
	{
		vec[0].push_back(n_n[0]);
		vec[1].push_back(n_n[1]);
		cout << "0" << endl;
		return;
	}
	cout << "-1" << endl;
}

void _remove()
{

	int place;
	cin >> place;
	if (place >= 1 && place <= int(vec[0].size()))
	{
		vec[0].erase(vec[0].begin() + place - 1);
		vec[1].erase(vec[1].begin() + place - 1);
		cout << "0" << endl;
		return;
	}
	cout << "-1" << endl;
}

void _check()
{
	string ss,n_n;
	cin >> ss>>n_n;
	int which = 0;
	if (ss == "name")
		which = 1;
	for (int i = 0; i < int(vec[0].size()); i++)
	{
		if (n_n == vec[which][i ])
		{
			cout <<i+1 << " " << vec[0][i ] << " " << vec[1] [i ]<< endl;
			return;
		}
	}
	cout << "-1" << endl;
}

int main()
{
	string n_n[2];
	cin >> max_n;
	vec[0].resize(max_n);
	vec[1].resize(max_n);
	for (int i = 0; i < max_n;i++)
		cin >> vec[0][i ] >> vec[1][i ];

	string choice ;
	while (1)
	{
		cin >> choice;
		if (choice == "insert")
			_insert();
		else if (choice == "remove")
			_remove();
		else if (choice == "check")
			_check();
		else if (choice == "end")
			break;
	}
	cout << vec[0].size() << endl;
	return 0;
}*/
#include<iostream>

using namespace std;

struct  tree {
	bool visit = false;//表示是否被感染
	int  father = -1;
	int  lchild = -1;
	int  rchild = -1;
};

void cin_tree(tree* the_tree,int num)
{
	int tem_left, tem_right;

	for (int i = 0; i < num; i++)
	{
		the_tree[i].visit = false;
		cin >> tem_left >> tem_right;
		if (tem_left == -1){
			the_tree[i].lchild = -1;
		}
		else {
			the_tree[i].lchild = tem_left;
			the_tree[tem_left].father = i;
		}

		if (tem_right == -1) {
			the_tree[i].rchild = -1;
		}
		else {
			the_tree[i].rchild = tem_right;
			the_tree[tem_right].father =i;
		}
	}
}
int infect(tree* infect_tree, int start_infect,int num)
{
	int* queue = new int[num];
	int end = 0,start=0;
	infect_tree[start_infect].visit = true;
	int time = -1;
	queue[end++] = start_infect;
	while (end!=start) {
		time++;
		int tem_num_queue =end-start;

		for (int i = 0; i < tem_num_queue;i++) {
			int current = queue[start++];
			if (infect_tree[current].father!=-1&&infect_tree[infect_tree[current].father].visit == false) {
				queue[end++] = infect_tree[current].father;
				infect_tree[infect_tree[current].father].visit = true;
			}
			if (infect_tree[current].lchild != -1 && infect_tree[infect_tree[current].lchild].visit == false) {
				queue[end++] = infect_tree[current].lchild;
				infect_tree[infect_tree[current].lchild].visit = true;
			}
			if (infect_tree[current].rchild != -1 && infect_tree[infect_tree[current].rchild].visit == false) {
				queue[end++] = infect_tree[current].rchild;
				infect_tree[infect_tree[current].rchild].visit = true;
			}
		}
	}
	return time;
}


int main()
{
	int num = 0,start_infect=0,time=0;
	cin >> num>>start_infect;

	tree* all = new(nothrow) tree[num + 1];
	if (all == NULL)
		return OVERFLOW;
	if (start_infect > num)
		return 0;
	cin_tree(all, num);
	time=infect(all, start_infect,num);
	cout << time;
	delete[]all;
}
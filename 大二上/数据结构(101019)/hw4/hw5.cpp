#include<iostream>

using namespace std;

struct  tree {
	int high = 0;//表示此节点所处的深度
	tree* first_child = NULL;//第一个孩子节点
	tree* first_brother = NULL;//右边第一个兄弟节点
	tree* father = NULL;//第一个父节点
	//这些节点没有则为空
};



tree* cin_tree(tree* start_tree, int num)
{
	for (int i_cycle = 1; i_cycle < num; i_cycle++)
	{
		int fa, child;
		cin >> fa >> child;
		start_tree[child].father = &start_tree[fa];
		if (start_tree[fa].first_child) {
			tree* now_tree = start_tree[fa].first_child;
			while (now_tree->first_brother)
				now_tree = now_tree->first_brother;
			now_tree->first_brother = &start_tree[child];
		}
		else
			start_tree[fa].first_child = &start_tree[child];
	}
	//找到第一个节点
	tree* root = &start_tree[1];
	while (root->father)
		root = root->father;
	//给所有节点深度赋值
	tree** queue = new(nothrow)tree * [num];
	if (queue == NULL)
		return NULL;
	int start = 0, end = 0;
	queue[end++] = root;
	while (end != start)
	{
		int tem_num_queue = end - start;
		for (int tem_cycle_1 = 0; tem_cycle_1 < tem_num_queue; tem_cycle_1++)
		{
			tree* now_tree = queue[start++];
			if (now_tree->first_brother) {
				queue[end++] = now_tree->first_brother;
				now_tree->first_brother->high = now_tree->high;
			}
			if (now_tree->first_child) {
				queue[end++] = now_tree->first_child;
				now_tree->first_child->high = now_tree->high + 1;
			}
		}
	}
	return root;
}

int search(tree* start_tree, int the_first, int the_second)
{
	tree* first = &start_tree[the_first];
	tree* second = &start_tree[the_second];
	const	int gap = first->high - second->high;
	for (int i = 0; i < gap; i++)
		first = first->father;
	for (int i = 0; i > gap; i--)
		second = second->father;
	while (first != second)
	{
		first = first->father;
		second = second->father;
	}
	return first - start_tree;
}
int main()
{
	int T;
	cin >> T;
	for (int tem_1 = 0; tem_1 < T; tem_1++)
	{
		int N, M;
		cin >> N >> M;
		tree* start = new(nothrow) tree[N + 1];
		if (start == NULL)
			return -1;
		cin_tree(start, N);
		for (int tem_2 = 0; tem_2 < M; tem_2++)
		{
			int first, second;
			cin >> first >> second;
			cout << search(start, first, second) << endl;
		}
	}
	return 0;
}




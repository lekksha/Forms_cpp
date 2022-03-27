#include "stdafx.h"



Node* BinTree::Tree(int n, Node* p)
{

	if (n == 0) return 0;
	Node* temp = new Node(std::rand() % 100);
	int left_child, right_child;
	left_child = (n - 1) / 2; right_child = n - 1 - left_child;
	temp->left = Tree(left_child, temp);
	temp->right = Tree(right_child, temp);
	temp->parent = p;
	return temp;

}

void BinTree::Copy(Node* q, Node* p, int f)
{
	if (q == NULL) return;
	Node* t = new Node(q->key);
	t->parent = p;
	if (f == 0) p->left = t;
	else p->right = t;
	Copy(q->left, t, 0);
	Copy(q->right, t, 1);
}

int BinTree::cycle(Node* root, int* a, int count, int n)
{
	if (root == 0)return count;
	root->key = a[count];
	count++;
	count = cycle(root->left, a, count, n - 1);
	count = cycle(root->right, a, count, n - 1);
	return count;
}

BinTree::BinTree(int n)
{
	root = Tree(n, 0);
}

BinTree::BinTree(int* a, int n) :BinTree(n)
{
	cycle(root, a, 0, n);
}

BinTree::BinTree(const BinTree& T)
{
	if (T.root == NULL) root = NULL;
	else
	{
		root = new Node(T.root->key);
		Copy(T.root->left, root, 0);
		Copy(T.root->right, root, 1);
	}
}

BinTree& BinTree::operator=(const BinTree& T)
{
	Clear();
	if (T.root == NULL) root = NULL;
	else
	{
		root = new Node(T.root->key);
		Copy(T.root->left, root, 0);
		Copy(T.root->right, root, 1);
	}
	return *this;
}

BinTree::~BinTree()
{
	this->Clear();
	delete root;
}

void BinTree::Add(int k, Node* p)
{
	if (p->left == NULL)
	{
		Node* q = new Node(k);
		p->left = q;  q->parent = p;
		return;
	}
	if (p->right == NULL)
	{
		Node* q = new Node(k);
		p->right = q;  q->parent = p;
		return;
	}
	if (rand() % 2) Add(k, p->left);
	else Add(k, p->right);

}

void BinTree::Del(Node* p)
{
	if (p == root) {
		DelRoot(); return;
	}
	Node* q = p->parent;
	//�������� �����
	if (p->left == 0 && p->right == 0)
	{
		if (q->left == p)q->left = 0;
		else q->right = 0;
		delete p;
		return;
	}
	//� p ��� ����� �����
	if (p->left == NULL && p->right != NULL)
	{
		if (q->left == p) q->left = p->right;
		else q->right = p->right;
		p->right->parent = q;
		delete p;
		return;
	}
	//� p ��� ������ �����
	if (p->left != NULL && p->right == NULL)
	{
		if (q->left == p) q->left = p->left;
		else q->right = p->left;
		p->left->parent = q;
		delete p;
		return;
	}

	//� p ���� ��� ���������
	Node* t = p;
	while (t->left != 0) t = t->left;

	//�������� t �� ������
	if (t->right == NULL)
		t->parent->left = NULL;
	else {
		t->parent->left = t->right;
		t->right->parent = t->parent;
	}
	//�������� p ����� t
	t->left = p->left;
	t->right = p->right;
	t->parent = q;

	if (q->left == p) q->left = t;
	else q->right = t;

	if (p->left != NULL)
		p->left->parent = t;

	p->right->parent = t;
	delete p;
	return;

}

void BinTree::DelRoot()
{
	if (root == 0 || root->left == 0 && root->right == 0)
	{
		delete root;
		root = 0;
		return;
	}
	if (root->left != 0 && root->right == 0)
	{
		Node* temp = root;
		root = root->left;
		delete temp;
		return;
	}
	if (root->left == 0 && root->right != 0)
	{
		Node* temp = root;
		root = root->right;
		delete temp;
		return;
	}
	if (root->left != 0 && root->right != 0)
	{
		Node* t = root;
		while (t->left != 0) t = t->left;


		if (t->right == NULL)
			t->parent->left = NULL;
		else {
			t->parent->left = t->right;
			t->right->parent = t->parent;
		}

		root->key = t->key;
		delete t;
		return;
	}
}
void BinTree::TreeTraversal_LCR(Node* p)
{
	if (p == NULL) return;
	TreeTraversal_LCR(p->left);
	std::cout << p->key << ' ';
	TreeTraversal_LCR(p->right);
}

void BinTree::TreeTraversal_LRC(Node* p)
{
	if (p->left)TreeTraversal_LRC(p->left);
	if (p->right)TreeTraversal_LRC(p->right);
	std::cout << p->key << ' ';
}

void BinTree::TreeTraversal_RLC(Node* p)
{
	if (p->right)TreeTraversal_LRC(p->right);
	if (p->left)TreeTraversal_LRC(p->left);
	std::cout << p->key << ' ';
}

void BinTree::WidthTraversal(Node* p)
{
	std::queue <Node*> q;
	int current_element = 0;
	q.push(p);
	while (q.size() != 0)
	{
		Node* tmp = q.front();
		q.pop();
		std::cout << tmp->key << ' ';
		if (tmp->left)q.push(tmp->left);
		if (tmp->right)q.push(tmp->right);
	}
}

Node* BinTree::FindKey(int k, Node* p)
{
	Node* temp(0);
	if (p == 0)return 0;
	if (p->key == k)return p;
	temp = FindKey(k, p->left);
	if (temp == 0)temp = FindKey(k, p->right);
	return temp;
}

Node* BinTree::FindMax(Node* p)
{
	if (p->left == 0)return p;
	Node* max_left = FindMax(p->left);
	Node* max_right = FindMax(p->right);
	Node* max = p;
	if (max->key < max_left->key)max = max_left;
	if (max->key < max_right->key)max = max_right;
	return max;
}
Node* BinTree::FindMin(Node* p)
{
	if (p == 0)return 0;
	if (p->left == 0)return p;
	Node* min_left = FindMin(p->left);
	Node* min_right = FindMin(p->right);
	Node* min = p;
	if (min->key > min_left->key)min = min_left;
	if (min->key > min_right->key)min = min_right;
	return min;
}

int BinTree::FindHight(Node* p)//���������� ������������ �������� ���� ����� (������???)
{

	int answer1 = 1;
	int answer2 = 1;
	if (p == 0)return 0;
	answer1 += FindHight(p->left);
	answer2 += FindHight(p->right);
	if (answer1 > answer2)return answer1;
	return answer2;
}

int BinTree::Count(Node* p)
{
	int count = 1;
	if (p->left != 0)	count += Count(p->left);
	if (p->right != 0)	count += Count(p->right);
	return count;
}

void BinTree::Clear()
{
	if (root == 0)return;
	while (root->right != 0)
	{
		Del(root->right);
	}
	while (root->left != 0)
	{
		Del(root->left);

	}
}

void BinTree::PrintTree(Node* p, int k)
{
	if (p == NULL) return;
	PrintTree(p->right, k + 5);
	for (int i = 0; i < k; i++) std::cout << ' ';
	std::cout << p->key << std::endl;
	PrintTree(p->left, k + 5);
}
#pragma once
#include <queue>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace System;
using namespace System::Drawing;
class Node
{
	int key;
	Node* left, * right, * parent;
public:
	Node(int k = 0, Node* L = 0, Node* R = 0, Node* P = 0)
	{
		key = k; left = L; right = R; parent = P;
	}
	friend class BinTree;
	friend void Print(Graphics^ gr, Node* q, int L, int R, int y);
};
class BinTree
{
	Node* root;// ������ ������
	Node* Tree(int n, Node* p);//���������� �������� ����������������� ������ � n ���������, p - ������ ������� �������
	void Copy(Node* q, Node* p, int f);//����������� ������ � ������ q, p - ����, � �������� �������������� �����
	//f=0 - ���������� ������ ����� ����� �������� ��� p;
	//f=1 - ���������� ������ ����� ������ �������� ��� p.
	int cycle(Node* root, int* a, int count, int n);

public:
	BinTree() { root = 0; }//����������� �� ���������
	BinTree(int n);// ����������� � n ���������� �������
	BinTree(int* a, int n);//����������� �������� �� ���� ������ ������ � �� ����������
	BinTree(const BinTree&);//����������� �����������
	BinTree& operator=(const BinTree&);//���������� ��������� ������������
	~BinTree();//����������
	void Add(int k, Node* p);//�������� � ������ � ������ p ���� � ������ k
	void Del(Node* p);//�������� ���� p
	void DelRoot();//�������� �����



	void TreeTraversal_LCR(Node* p);
	//����� ������ � ������ p, � ������� �� ��������
	//����-������-�����, ����� ��������� �� �������

//�������� ������ ������� ���� �������:
//void TreeTraversal_LCR (Node *p, int *a, int *n);	
	   //����� ������ � ������ p, � ������� �� ��������
	   //����-������-�����, ����� ����������� � ������� a, 
	   //n - ������ ������� a 
	void TreeTraversal_LRC(Node* p);
	//����� ������ � ������ p, � ������� �� ��������
	//����-�����-������, ����� ��������� �� �������
	void TreeTraversal_RLC(Node* p);
	//����� ������ � ������ p, � ������� �� ��������
	//�����-����-������, ����� ��������� �� �������
	void WidthTraversal(Node* p);
	//����� ������ � ������ p, � ������


	Node* FindKey(int k, Node* p);//����� ���� � ������ k � ������ � ������ p
	Node* FindMax(Node* p);//����� ���� � ������������ ������ � ����� � ������ p
	Node* FindMin(Node* p);//����� ���� � min ������ � ������ � ������ p
	int FindHight(Node* p);//����� ������ ������ � ������ p
	int Count(Node* p);//���������� ���������� ����� � ������ � ������ p
	Node* GetRoot() { return root; }//������ ������
	void Clear();//���������� ��� ������, ����� �����
	void PrintTree(Node* p, int k);
	//����� ������ �� �������, 
	//k - ������ �� ����� ������� �������
};
#pragma once

#include "MyForm.h"
#include <Windows.h>
#include "stdafx.h"

using namespace TreeForm; // Название проекта
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MyForm);
	return 0;
}

void Print(Graphics^ gr, Node* q, int L, int R, int y) 
{
	if (q == 0)return;
	int x0 = (R + L) / 2;
	int d = 30;
	int x = x0 - d / 2;
	Pen^ p = gcnew Pen(Color::Black, 2);
	Brush^ br1 = gcnew SolidBrush(Color::Yellow);
	gr->DrawEllipse(p, x, y, d, d);
	gr->FillEllipse(br1, x, y, d, d);
	String^ str = System::Convert::ToString(q->key);
	Brush^ br2 = gcnew SolidBrush(Color::Black);
	Font^ f = gcnew Font("Arial", 12);
	gr->DrawString(str, f, br2, x + 5, y + 7);
	if (q->left!=0) 
	{
		gr->DrawLine(p, x0, y + d, (L + x0) / 2, y + 50);
		Print(gr, q->left, L, x0, y + 50);

	}
	if (q->right != 0)
	{
		gr->DrawLine(p, x0, y + d, (R + x0) / 2, y + 50);
		Print(gr, q->right, x0, R, y + 50);
	}
}



System::Void TreeForm::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	Application::Exit();
}
BinTree GlobalTree;
System::Void TreeForm::MyForm::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	MyForm^ form = gcnew MyForm;
	if (textBox1->Text == "")return;
	int n = System::Convert::ToInt32(textBox1->Text);
	textBox1->Clear();
	textBox2->Clear();
	srand(time(0));
	int* a = new int[n];
	for (int i = 0; i < n; i++) 
	{
		a[i] = rand() % 100;
		textBox2->Text = textBox2->Text + System::Convert::ToString(a[i]) + " ";
	}
	BinTree temp(a, n);
	GlobalTree = temp;
	
}

System::Void TreeForm::MyForm::button4_Click(System::Object^ sender, System::EventArgs^ e)
{
	pictureBox1->Refresh();
	Graphics^ gr = pictureBox1->CreateGraphics();
	Print(gr, GlobalTree.GetRoot(), 20, this->pictureBox1->Width - 20,5);
}

System::Void TreeForm::MyForm::button3_Click(System::Object^ sender, System::EventArgs^ e)
{
	pictureBox1->Refresh();
}

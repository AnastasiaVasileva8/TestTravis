#pragma once
#include <iostream>
#include <vector>
#include <stack> 
#define _CRT_SECURE_NO_WARNINGS
#ifndef LIBAPP_CALC_HPP
#define LIBAPP_CALC_HPP
using namespace std;
#define TRUE 1
#define FALSE 0
typedef int Boolean;
typedef struct L *Lref; // ���: ��������� �� ������������ ����.
typedef struct T *Tref; // ���: ��������� �� ������� ����.

//�������� ���� ������������� ����.
typedef struct L
{
	int Key; //��� ������������� ����.
	int Count; //���������� ����������������.
	Boolean Flag; //���� ��������� ���� ��� ������.
	Tref Trail; //��������� �� ������ ���������.
	Lref Next; //��������� �� ��������� ���� � ������ ������������ �����.
} Leader;

//�������� ���� �������� ����.
typedef struct T
{
	Lref Id;
	Tref Next;
} Trailer;

//�������� ���� ���� �����.
typedef Tref TipElement;
typedef struct Zveno *svqz;
typedef struct Zveno
{
	TipElement Element; //��������� �� ������ ���������.
	svqz Sled;
} St;

class Spisok
{
private:
	Lref Head; //��������� �� ������ ������ ������������ �����.
	Lref Tail; //��������� �� ��������� ������� 
	// � ����� ������ ������������ �����.
	void SearchGraph(int, Lref *);
	void W_S(svqz *, TipElement);
	void DeleteEl(svqz *, TipElement *);
public:
	Spisok() {//������������� ������ ������������ �����.
		Head = Tail = new (Leader);
	}
	Lref GetHead() { return Head; }
	Lref GetTail() { return Tail; }
	//void MakeGraph();
	bool MakeGraph(std::vector<int>);
	void PrintGraph();
	std::vector<int>  Path_Depth_First_Search(int, int);
	};

//void main()
//{
//	setlocale(LC_ALL, "Rus");
//	Spisok A;
//	int B, E;
//	Lref t; //������� ��������� ��� ����������� 
//	// �� ������ ������������ �������.
//	//���������� ����� � ����� ��� ��������� �����.
//	A.MakeGraph();
//	A.PrintGraph(); cout << endl;
//	//����������� ���� ����� ����� ��������� ��������� �����.
//	t = A.GetHead();
//	while (t != A.GetTail())
//	{
//		(*t).Flag = TRUE; t = (*t).Next;
//	}
//	cout << "������� ��������� ������� ����: "; cin >> B;
//	cout << "������� �������� ������� ���� : "; cin >> E;
//	cout << "������� ����: ";
//	A.Path_Depth_First_Search(B, E); cout << endl;
//	system("pause");
//}

void Spisok::SearchGraph(int w, Lref *h)
//������� ���������� ��������� �� ������������ ���� 
//� ������ w � �����, �������� ���������� ����� � ���������� Head. 
{
	*h = Head; (*Tail).Key = w;
	while ((**h).Key != w) *h = (**h).Next;
	if (*h == Tail)
		//� ������ ������������ ����� ��� ���� � ������ w.
		//�������� ��� � ����� ������ Head.
	{
		Tail = new (Leader); (**h).Count = 0;
		(**h).Trail = NULL; (**h).Next = Tail;
	}
}

//void Spisok::MakeGraph()
bool Spisok::MakeGraph(std::vector<int> myvect)
//������� ���������� ��������� Head �� ���������
//�����, ��������������� ���������������� �����.
{
	if (!myvect.empty())
	{
		int x, y;
		Lref p, q; //������� ���������.
		Tref t, r; //������� ���������.
		Boolean Res; //���� ������� ����.
		int i = 0;
		x = myvect[i];
		i++;
		while (x != 0)
		{
			y = myvect[i];
			i++;
			//���������, ���������� �� � ����� ���� (x,y)?
			SearchGraph(x, &p); SearchGraph(y, &q);
			r = (*p).Trail; Res = FALSE;
			while ((r != NULL) && (!Res))
				if ((*r).Id == q) Res = TRUE;
				else r = (*r).Next;
				if (!Res) //���� ���� �����������, �� �������� � � ����.
				{
					t = new (Trailer); (*t).Id = q;
					(*t).Next = (*p).Trail; (*p).Trail = t; (*q).Count++;
				}
				x = myvect[i];
				i++;
		}
		return true;
	}
	else
	{

		std::cout << "���� �� �����������.";
		return false;
	}
}
//������� ���������� ��������� Head �� ��������� 
//�����, ��������������� ���������������� �����.
//{
//	int x, y;
//	Lref p, q; //������� ���������.
//	Tref t, r; //������� ���������.
//	Boolean Res; //���� ������� ����.
//	cout << "������� ��������� ������� ����: ";
//	cin >> x;
//	while (x != 0)
//	{
//		cout << "������� �������� ������� ����: "; cin >> y;
//		//���������, ���������� �� � ����� ���� (x,y)?
//		SearchGraph(x, &p); SearchGraph(y, &q);
//		r = (*p).Trail; Res = FALSE;
//		while ((r != NULL) && (!Res))
//			if ((*r).Id == q) Res = TRUE;
//			else r = (*r).Next;
//			if (!Res) //���� ���� �����������, �� �������� � � ����.
//			{
//				t = new (Trailer); (*t).Id = q;
//				(*t).Next = (*p).Trail; (*p).Trail = t; (*q).Count++;
//			}
//			cout << "������� ��������� ������� ����: "; cin >> x;
//	}
//}

void Spisok::PrintGraph()
//����� ��������� �����, �������� ���������� 
//Head � ��������������� ���������������� �����.
{
	Lref p; //������� ���������.
	Tref q; //������� ���������.

	p = Head;
	while (p != Tail)
	{
		cout << "(" << (*p).Key; q = (*p).Trail;
		while (q != NULL)
		{
			cout << (*(*q).Id).Key; q = (*q).Next;
		}
		cout << ")"; p = (*p).Next; cout << " ";
	}
}

void Spisok::W_S(svqz *stk, TipElement el)
//��������� �������� el � ���� stk.
{
	svqz q = new (St);
	(*q).Element = el; (*q).Sled = *stk; *stk = q;
}

void Spisok::DeleteEl(svqz *stk, TipElement *klad)
//�������� ����� �� �����, ��������� ���������� *stk. 
//�������� ��������������� ���� ���������� ����� �������- 
//���� � ��������� klad.
{
	svqz q;

	if (*stk == NULL) cout << "������� ������ �� ������� �����!\n";
	else
	{
		*klad = (**stk).Element; q = *stk; *stk = (**stk).Sled; delete q;
	}
}

std::vector<int> Spisok::Path_Depth_First_Search(int B, int E)
//���� ����� ��������� B � E � �����, �������� ���������� Head.
{
	Lref s, r = 0; //
	Tref t;
	svqz TempU; //������� ��������� ��� ����������� �� �����.                
	std::vector<int>ResVec;
	int i;
	svqz Stack = NULL; //���� ����.
	//��������� ��������� �� ������� B
	s = Head;
	
	while (s != Tail)//1
	{
		if (s->Key == B)  r = s;
		s = s->Next;
	}
	//������� ������ ������������ ������� ����� � 
	//�������� �� � ������������� ������ ����.
	if (r->Key == E)//2 ==................................................
	{
		TempU = Stack;
		while (TempU != NULL)//3
		{
			cout << TempU->Element->Id->Key << " ";
			ResVec.push_back(TempU->Element->Id->Key);
			TempU = TempU->Sled;
		}

		cout << B << endl;
		ResVec.push_back(B);
	}
	r->Flag = FALSE; W_S(&Stack, r->Trail);
	
	while (Stack != NULL)//4
	{
		//���������� "��������" �����.
		t = Stack->Element;
		if (t->Id->Trail != NULL)//5
			//� ��������������� ������� ���� ������� �������.
		{
			if (t->Id->Flag)//6
				//� ��������������� ������� ����
				//������������ ������� �������.
			{
				//������� ��������������� �������
				//� �������� ��������� �� �� ������ ��������� � ����.
				if (t->Id->Key == E)//7 ==,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
				{
					TempU = Stack;
					while (TempU != NULL)//8
					{
						cout << TempU->Element->Id->Key << " ";
						ResVec.push_back(TempU->Element->Id->Key);
						TempU = TempU->Sled;
					}

					cout << B << endl;
					ResVec.push_back(B);
				}
				t->Id->Flag = FALSE;
				W_S(&Stack, t->Id->Trail);
			
			}
			//� ��������������� ������� ���
			//������������ ������� ������.
			else//9
			{
				t = Stack->Element;
				if (t->Next != NULL)//10
					//�������� �������� ����� ���������� 
					//�� ��������� ������� ������ ���������...
				{
					DeleteEl(&Stack, &t);
					W_S(&Stack, t->Next);
					
				}
				//��� ������� �������� �����.
				else  DeleteEl(&Stack, &t);//11
			}
		}
		//� ��������������� ������� ��� ������� ������.
		else//12
		{
			if (t->Id->Flag)//13
				//������� ��������������� �������.
			{
				if (t->Id->Key == E) //14 ==,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
				{
					TempU = Stack;
					while (TempU != NULL)//15
					{
						cout << TempU->Element->Id->Key << " ";
						ResVec.push_back(TempU->Element->Id->Key);
						TempU = TempU->Sled;
					}

					cout << B << endl;
					ResVec.push_back(B);
				}
				t->Id->Flag = FALSE;
			
			}
			t = Stack->Element;
			if (t->Next != NULL)//16
				//�������� �������� ����� ���������� 
				//�� ��������� ������� ������ ���������...
			{
				DeleteEl(&Stack, &t);
				W_S(&Stack, t->Next);
			}
			//��� ������� �������� �����.
			else  DeleteEl(&Stack, &t);//17
		}
		
	}
	
	//ResVec.push_back('0');//������� ������ ��4
	//reverse(ResVec.begin(), ResVec.end());
//met
	return ResVec;
}
#endif

////////////////////////////////////////////////////////////////////
//std::vector<int> Spisok::OutputGraph(int B, int E, svqz *Stack)
//{
//
//	svqz TempU;
//	std::vector<int> ResVec;
//	 TempU = *Stack;
//		
//		while (TempU != NULL)
//		{
//			cout << TempU->Element->Id->Key << " ";
//			ResVec.push_back(TempU->Element->Id->Key);
//			TempU = TempU->Sled;	
//		}
//	
//		cout << B << endl;
//		ResVec.push_back(B);
//		
//		return ResVec;
//}
//Metka:
//	TempU = Stack;
//	
//	while (TempU != NULL)
//	{
//		cout << TempU->Element->Id->Key << " ";
//		ResVec.push_back(TempU->Element->Id->Key);
//		TempU = TempU->Sled;	
//	}
//
//	cout << B << endl;
//	ResVec.push_back(B);

//using namespace std;
//struct Edge {
//	int begin;
//	int end;
//};
//void mySearch(int mas[5][5], int req)
//{
//	const int n = 5;
//	stack<int> Stack,Res;
//	stack<Edge> Edges;
//	Edge e;
//	int nodes[n]; // ������� �����
//	for (int i = 0; i < n; i++) // ������� ��� ������� ����� 0
//		nodes[i] = 0;
//	
//	req--;
//	Stack.push(0); // �������� � ������� ������ �������
//	while (!Stack.empty())
//	{ // ���� ���� �� ����
//		int node = Stack.top(); // ��������� �������
//		Stack.pop();
//		if (nodes[node] == 2) continue;
//		nodes[node] = 2; // �������� �� ��� ����������
//		for (int j = n - 1; j >= 0; j--)
//		{ // ��������� ��� ��� ��� ������� �������
//			if (mas[node][j] == 1 && nodes[j] != 2)
//			{ // ���� ������� ������� � �� ����������
//				Stack.push(j); // ��������� �� � c���
//				nodes[j] = 1; // �������� ������� ��� ������������
//				e.begin = node; e.end = j;
//				Edges.push(e);
//				if (node == req) break;
//			}
//		}
//		//cout << node + 1 << endl; // ������� ����� �������
//	}
//	cout << "���� �� ������� " << req + 1 << ": ";
//	cout << req + 1;
//	while (!Edges.empty())
//	{
//		e = Edges.top();
//		Edges.pop();
//		if (e.end == req)
//		{
//			
//			req = e.begin;
//			cout << " <- " << req + 1;
//			Res.push(req + 1);
//		}
//		
//	}
//	return;
//}
///////////////////////////////////////////////////////////////////////////////////////////////////////
//#include <cstdint>
//#include <memory>
//#include <vector>
//#include <iostream>
//using namespace std;
//#include <iostream>
//#define TRUE 1
//#define FALSE 0
//typedef int Boolean;
//typedef struct Leader *Lref; // ���: ��������� �� ������������ ����.
//typedef struct Trailer *Tref; // ���: ��������� �� ������� ����.
//
////�������� ���� ������������� ����.
//typedef struct Leader
//{
//	char Key; //��� ������������� ����.
//	int Count; //���������� ����������������.
//	Boolean Flag; //���� ��������� ���� ��� ������.
//	Tref Trail; //��������� �� ������ ���������.
//	Lref Next; //��������� �� ��������� ���� � ������ ������������ �����.
//};
//
////�������� ���� �������� ����.
//typedef struct Trailer
//{
//	Lref Id;
//	Tref Next;
//};
//
////�������� ���� ���� �������.
//typedef Lref TipElement; //��������� �� ����� ������������� ������.
//typedef struct zven *svqz;
//typedef struct zven
//{
//	TipElement element; //��������� �� ������ ���������.
//	svqz next;
//};
//
//class Spisok
//{
//private:
//	Lref Head; //��������� �� ������ ������ ������������ �����.
//	Lref Tail; //��������� �� ��������� �������
//	// � ����� ������ ������������ �����.
//	void Delete_SP(svqz *, svqz *, TipElement *);
//	void Add_SP(svqz *, svqz *, TipElement);
//	void SearchGraph(char, Lref *);
//	bool MySearchGraph(char);
//public:
//	Spisok() {//������������� ������ ������������ �����.
//		Head = Tail = new (Leader);
//	}
//	Lref GetHead() { return Head; }
//	Lref GetTail() { return Tail; }
//	bool MakeGraph(std::vector<char>);
//	void PrintGraph();
//	std::vector<char> Go_width(Lref, char, char);
//};
//
//void Spisok::SearchGraph(char w, Lref *h)
////������� ���������� ��������� �� ������������ ����
////� ������ w � �����, �������� ���������� ����� � ���������� Head.
//{
//	*h = Head; (*Tail).Key = w;
//	while ((**h).Key != w) *h = (**h).Next;
//	if (*h == Tail)
//		//� ������ ������������ ����� ��� ���� � ������ w.
//		//�������� ��� � ����� ������ Head.
//	{
//		Tail = new (Leader); (**h).Count = 0;
//		(**h).Trail = NULL; (**h).Next = Tail;
//	}
//}
//
//bool Spisok::MySearchGraph(char w)
////������� ���������� ��������� �� ������������ ����
////� ������ w � �����, �������� ���������� ����� � ���������� Head.
//{
//	Lref h = Head;
//	(*Tail).Key = w;
//	while ((h)->Key != w) h = (h)->Next;
//	if (h == Tail)
//		return false;
//	else return true;
//}
//
//bool Spisok::MakeGraph(std::vector<char> myvect)
////������� ���������� ��������� Head �� ���������
////�����, ��������������� ���������������� �����.
//{
//	if (!myvect.empty())
//	{
//		char x, y;
//		Lref p, q; //������� ���������.
//		Tref t, r; //������� ���������.
//		Boolean Res; //���� ������� ����.
//		int i = 0;
//		x = myvect[i];
//		i++;
//		while (x != '0')
//		{
//			y = myvect[i];
//			i++;
//			//���������, ���������� �� � ����� ���� (x,y)?
//			SearchGraph(x, &p); SearchGraph(y, &q);
//			r = (*p).Trail; Res = FALSE;
//			while ((r != NULL) && (!Res))
//				if ((*r).Id == q) Res = TRUE;
//				else r = (*r).Next;
//				if (!Res) //���� ���� �����������, �� �������� � � ����.
//				{
//					t = new (Trailer); (*t).Id = q;
//					(*t).Next = (*p).Trail; (*p).Trail = t; (*q).Count++;
//				}
//				x = myvect[i];
//				i++;
//		}
//		return true;
//	}
//	else
//	{
//
//		std::cout << "���� �� �����������.";
//		return false;
//	}
//}
//
//void Spisok::PrintGraph()
////����� ��������� �����, �������� ����������
////Head � ��������������� ���������������� �����.
//{
//	Lref p; //������� ���������.
//	Tref q; //������� ���������.
//
//	p = Head;
//	while (p != Tail)
//	{
//		std::cout << (*p).Key << "("; q = (*p).Trail;
//		while (q != NULL)
//		{
//			std::cout << (*(*q).Id).Key; q = (*q).Next;
//		}
//		std::cout << ")"; p = (*p).Next; std::cout << " ";
//	}
//}
//
//void Spisok::Add_SP(svqz *L, svqz *R, TipElement elem)
////���������� �������� elem � �������, �������� ����������� L � R.
//{
//	svqz K = new (zven);
//
//	K->element = elem; K->next = NULL;
//	if (*L == NULL)
//	{
//		(*L) = K; (*R) = K;
//	}
//	else { (*R)->next = K; (*R) = K; }
//}
//
//void Spisok::Delete_SP(svqz *L, svqz *R, TipElement *A)
////�������� �������� �� �������, �������� ����������� L � R �
////��������� ���������� �������� � ���������� A.
//{
//	svqz q;
//
//	if ((*L) != NULL)
//		if ((*L)->next != NULL)
//		{
//			(*A) = (*L)->element; q = (*L);
//			(*L) = (*L)->next; delete q;
//		}
//		else {
//			(*A) = (*L)->element; delete *L;
//			(*L) = (*R) = NULL;
//		}
//}
//
//std::vector<char> Spisok::Go_width(Lref H, char B, char E)
//���� � �����, �������� ���������� H, ����� ��������� B � E.
//{
	//svqz L; //��������� �� ������ ���p���.
	//svqz R; //��������� �� �����  ���p���.
	//Lref p; //������� ���������.
	//Tref t; //������� ���������.
	//char  Pred[255]; //������� Pred[i] �������� ������� �����,
	////"��������������" ������.
	//char i;
	//std::vector<char> ResVec; 
	//if (MySearchGraph(B) && MySearchGraph(E))
	//{
	//	L = R = NULL; // ���������� ������ ���p���.
	//	//��������� ��������� �� ������� B � �������� ��� � �������.
	//	p = H;
	//	while (p != Tail)
	//	{
	//		if (p->Key == B)
	//		{
	//			Add_SP(&L, &R, p);
	//			p->Flag = FALSE;
	//		}
	//		p = p->Next;
	//	}
	//	//���� ���p��� �� �����...
	//	while (L != NULL)
	//	{
	//		Delete_SP(&L, &R, &p);
	//		t = p->Trail;
	//		while (t != NULL)
	//		{
	//			if (t->Id->Flag)
	//			{
	//				Add_SP(&L, &R, t->Id);
	//				t->Id->Flag = FALSE;
	//				Pred[(int)(t->Id->Key - '0')] = p->Key;
	//			}
	//			t = t->Next;
	//		}
	//	}
	//	i = E;
	//	ResVec.push_back(i);
	//	std::cout << E << ' ';
	//	while (i != B)
	//	{
	//		ResVec.push_back(Pred[(int)(i - '0')]);
	//		std::cout << Pred[(int)(i - '0')] << ' '; i = Pred[(int)(i - '0')];

	//	}
	//	std::cout << endl;
	//	return ResVec;
	//}
	//else
	//{
	//	std::cout << "��������� ��� �������� ������� �� �������";
	//	ResVec = {};
	//	return ResVec;
	//}

	



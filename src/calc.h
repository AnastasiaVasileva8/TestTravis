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
typedef struct L *Lref; // Тип: указатель на заголовочный узел.
typedef struct T *Tref; // Тип: указатель на дуговой узел.

//Описание типа заголовочного узла.
typedef struct L
{
	int Key; //Имя заголовочного узла.
	int Count; //Количество предшественников.
	Boolean Flag; //Флаг посещения узла при обходе.
	Tref Trail; //Указатель на список смежности.
	Lref Next; //Указатель на следующий узел в списке заголовочных узлов.
} Leader;

//Описание типа дугового узла.
typedef struct T
{
	Lref Id;
	Tref Next;
} Trailer;

//Описание типа узла стека.
typedef Tref TipElement;
typedef struct Zveno *svqz;
typedef struct Zveno
{
	TipElement Element; //Указатель на список смежности.
	svqz Sled;
} St;

class Spisok
{
private:
	Lref Head; //Указатель на голову списка заголовочных узлов.
	Lref Tail; //Указатель на фиктивный элемент 
	// в конце списка заголовочных узлов.
	void SearchGraph(int, Lref *);
	void W_S(svqz *, TipElement);
	void DeleteEl(svqz *, TipElement *);
public:
	Spisok() {//Инициализация списка заголовочных узлов.
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
//	Lref t; //Рабочий указатель для перемещения 
//	// по списку заголовочных звеньев.
//	//Построение графа и вывод его структуры Вирта.
//	A.MakeGraph();
//	A.PrintGraph(); cout << endl;
//	//Определение пути между двумя заданными вершинами графа.
//	t = A.GetHead();
//	while (t != A.GetTail())
//	{
//		(*t).Flag = TRUE; t = (*t).Next;
//	}
//	cout << "Введите начальную вершину пути: "; cin >> B;
//	cout << "Введите конечную вершину пути : "; cin >> E;
//	cout << "Искомый путь: ";
//	A.Path_Depth_First_Search(B, E); cout << endl;
//	system("pause");
//}

void Spisok::SearchGraph(int w, Lref *h)
//Функция возвращает указатель на заголовочный узел 
//с ключом w в графе, заданном структурой Вирта с указателем Head. 
{
	*h = Head; (*Tail).Key = w;
	while ((**h).Key != w) *h = (**h).Next;
	if (*h == Tail)
		//В списке заголовочных узлов нет узла с ключом w.
		//Поместим его в конец списка Head.
	{
		Tail = new (Leader); (**h).Count = 0;
		(**h).Trail = NULL; (**h).Next = Tail;
	}
}

//void Spisok::MakeGraph()
bool Spisok::MakeGraph(std::vector<int> myvect)
//Функция возвращает указатель Head на структуру
//Вирта, соответствующую ориентированному графу.
{
	if (!myvect.empty())
	{
		int x, y;
		Lref p, q; //Рабочие указатели.
		Tref t, r; //Рабочие указатели.
		Boolean Res; //Флаг наличия дуги.
		int i = 0;
		x = myvect[i];
		i++;
		while (x != 0)
		{
			y = myvect[i];
			i++;
			//Определим, существует ли в графе дуга (x,y)?
			SearchGraph(x, &p); SearchGraph(y, &q);
			r = (*p).Trail; Res = FALSE;
			while ((r != NULL) && (!Res))
				if ((*r).Id == q) Res = TRUE;
				else r = (*r).Next;
				if (!Res) //Если дуга отсутствует, то поместим её в граф.
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

		std::cout << "Граф не существуетю.";
		return false;
	}
}
//Функция возвращает указатель Head на структуру 
//Вирта, соответствующую ориентированному графу.
//{
//	int x, y;
//	Lref p, q; //Рабочие указатели.
//	Tref t, r; //Рабочие указатели.
//	Boolean Res; //Флаг наличия дуги.
//	cout << "Вводите начальную вершину дуги: ";
//	cin >> x;
//	while (x != 0)
//	{
//		cout << "Вводите конечную вершину дуги: "; cin >> y;
//		//Определим, существует ли в графе дуга (x,y)?
//		SearchGraph(x, &p); SearchGraph(y, &q);
//		r = (*p).Trail; Res = FALSE;
//		while ((r != NULL) && (!Res))
//			if ((*r).Id == q) Res = TRUE;
//			else r = (*r).Next;
//			if (!Res) //Если дуга отсутствует, то поместим её в граф.
//			{
//				t = new (Trailer); (*t).Id = q;
//				(*t).Next = (*p).Trail; (*p).Trail = t; (*q).Count++;
//			}
//			cout << "Вводите начальную вершину дуги: "; cin >> x;
//	}
//}

void Spisok::PrintGraph()
//Вывод структуры Вирта, заданной указателем 
//Head и соответствующей ориентированному графу.
{
	Lref p; //Рабочий указатель.
	Tref q; //Рабочий указатель.

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
//Помещение элемента el в стек stk.
{
	svqz q = new (St);
	(*q).Element = el; (*q).Sled = *stk; *stk = q;
}

void Spisok::DeleteEl(svqz *stk, TipElement *klad)
//Удаление звена из стека, заданного указателем *stk. 
//Значение информационного поля удаляемого звена сохраня- 
//ется в параметре klad.
{
	svqz q;

	if (*stk == NULL) cout << "Попытка выбора из пустого стека!\n";
	else
	{
		*klad = (**stk).Element; q = *stk; *stk = (**stk).Sled; delete q;
	}
}

std::vector<int> Spisok::Path_Depth_First_Search(int B, int E)
//Путь между вершинами B и E в графе, заданном указателем Head.
{
	Lref s, r = 0; //
	Tref t;
	svqz TempU; //Рабочий указатель для перемещения по стеку.                
	std::vector<int>ResVec;
	int i;
	svqz Stack = NULL; //Стек пуст.
	//Определим указатель на вершину B
	s = Head;
	
	while (s != Tail)//1
	{
		if (s->Key == B)  r = s;
		s = s->Next;
	}
	//Посетим первую непосещенную вершину графа и 
	//поместим ее в первоначально пустой стек.
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
		//Рассмотрим "верхушку" стека.
		t = Stack->Element;
		if (t->Id->Trail != NULL)//5
			//У рассматриваемой вершины есть смежные вершины.
		{
			if (t->Id->Flag)//6
				//У рассматриваемой вершины есть
				//непосещенные смежные вершины.
			{
				//Посетим рассматриваемую вершину
				//и поместим указатель на ее список смежности в стек.
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
			//У рассматриваемой вершины нет
			//непосещенных смежных вершин.
			else//9
			{
				t = Stack->Element;
				if (t->Next != NULL)//10
					//Заменяем верхушку стека указателем 
					//на следующий элемент списка смежности...
				{
					DeleteEl(&Stack, &t);
					W_S(&Stack, t->Next);
					
				}
				//или удаляем верхушку стека.
				else  DeleteEl(&Stack, &t);//11
			}
		}
		//У рассматриваемой вершины нет смежных вершин.
		else//12
		{
			if (t->Id->Flag)//13
				//Посетим рассматриваемую вершину.
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
				//Заменяем верхушку стека указателем 
				//на следующий элемент списка смежности...
			{
				DeleteEl(&Stack, &t);
				W_S(&Stack, t->Next);
			}
			//или удаляем верхушку стека.
			else  DeleteEl(&Stack, &t);//17
		}
		
	}
	
	//ResVec.push_back('0');//инекция ошибок лр4
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
//	int nodes[n]; // вершины графа
//	for (int i = 0; i < n; i++) // исходно все вершины равны 0
//		nodes[i] = 0;
//	
//	req--;
//	Stack.push(0); // помещаем в очередь первую вершину
//	while (!Stack.empty())
//	{ // пока стек не пуст
//		int node = Stack.top(); // извлекаем вершину
//		Stack.pop();
//		if (nodes[node] == 2) continue;
//		nodes[node] = 2; // отмечаем ее как посещенную
//		for (int j = n - 1; j >= 0; j--)
//		{ // проверяем для нее все смежные вершины
//			if (mas[node][j] == 1 && nodes[j] != 2)
//			{ // если вершина смежная и не обнаружена
//				Stack.push(j); // добавляем ее в cтек
//				nodes[j] = 1; // отмечаем вершину как обнаруженную
//				e.begin = node; e.end = j;
//				Edges.push(e);
//				if (node == req) break;
//			}
//		}
//		//cout << node + 1 << endl; // выводим номер вершины
//	}
//	cout << "Путь до вершины " << req + 1 << ": ";
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
//typedef struct Leader *Lref; // Тип: указатель на заголовочный узел.
//typedef struct Trailer *Tref; // Тип: указатель на дуговой узел.
//
////Описание типа заголовочного узла.
//typedef struct Leader
//{
//	char Key; //Имя заголовочного узла.
//	int Count; //Количество предшественников.
//	Boolean Flag; //Флаг посещения узла при обходе.
//	Tref Trail; //Указатель на список смежности.
//	Lref Next; //Указатель на следующий узел в списке заголовочных узлов.
//};
//
////Описание типа дугового узла.
//typedef struct Trailer
//{
//	Lref Id;
//	Tref Next;
//};
//
////Описание типа узла очереди.
//typedef Lref TipElement; //Указатель на звено заголовочного списка.
//typedef struct zven *svqz;
//typedef struct zven
//{
//	TipElement element; //Указатель на список смежности.
//	svqz next;
//};
//
//class Spisok
//{
//private:
//	Lref Head; //Указатель на голову списка заголовочных узлов.
//	Lref Tail; //Указатель на фиктивный элемент
//	// в конце списка заголовочных узлов.
//	void Delete_SP(svqz *, svqz *, TipElement *);
//	void Add_SP(svqz *, svqz *, TipElement);
//	void SearchGraph(char, Lref *);
//	bool MySearchGraph(char);
//public:
//	Spisok() {//Инициализация списка заголовочных узлов.
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
////Функция возвращает указатель на заголовочный узел
////с ключом w в графе, заданном структурой Вирта с указателем Head.
//{
//	*h = Head; (*Tail).Key = w;
//	while ((**h).Key != w) *h = (**h).Next;
//	if (*h == Tail)
//		//В списке заголовочных узлов нет узла с ключом w.
//		//Поместим его в конец списка Head.
//	{
//		Tail = new (Leader); (**h).Count = 0;
//		(**h).Trail = NULL; (**h).Next = Tail;
//	}
//}
//
//bool Spisok::MySearchGraph(char w)
////Функция возвращает указатель на заголовочный узел
////с ключом w в графе, заданном структурой Вирта с указателем Head.
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
////Функция возвращает указатель Head на структуру
////Вирта, соответствующую ориентированному графу.
//{
//	if (!myvect.empty())
//	{
//		char x, y;
//		Lref p, q; //Рабочие указатели.
//		Tref t, r; //Рабочие указатели.
//		Boolean Res; //Флаг наличия дуги.
//		int i = 0;
//		x = myvect[i];
//		i++;
//		while (x != '0')
//		{
//			y = myvect[i];
//			i++;
//			//Определим, существует ли в графе дуга (x,y)?
//			SearchGraph(x, &p); SearchGraph(y, &q);
//			r = (*p).Trail; Res = FALSE;
//			while ((r != NULL) && (!Res))
//				if ((*r).Id == q) Res = TRUE;
//				else r = (*r).Next;
//				if (!Res) //Если дуга отсутствует, то поместим её в граф.
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
//		std::cout << "Граф не существуетю.";
//		return false;
//	}
//}
//
//void Spisok::PrintGraph()
////Вывод структуры Вирта, заданной указателем
////Head и соответствующей ориентированному графу.
//{
//	Lref p; //Рабочий указатель.
//	Tref q; //Рабочий указатель.
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
////Добавление элемента elem в очередь, заданную указателями L и R.
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
////Удаление элемента из очереди, заданной указателями L и R и
////помещение удаленного элемента в переменную A.
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
//Путь в графе, заданном указателем H, между вершинами B и E.
//{
	//svqz L; //Указатель на начало очеpеди.
	//svqz R; //Указатель на конец  очеpеди.
	//Lref p; //Рабочий указатель.
	//Tref t; //Рабочий указатель.
	//char  Pred[255]; //Элемент Pred[i] содержит вершину графа,
	////"предшествующую" данной.
	//char i;
	//std::vector<char> ResVec; 
	//if (MySearchGraph(B) && MySearchGraph(E))
	//{
	//	L = R = NULL; // Построение пустой очеpеди.
	//	//Определим указатель на вершину B и поместим его в очередь.
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
	//	//Пока очеpедь не пуста...
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
	//	std::cout << "Начальная или конечная вершина не найдена";
	//	ResVec = {};
	//	return ResVec;
	//}

	



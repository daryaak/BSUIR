#include "Altorithm.h"

inline void SetColor(int text);

void SetColor(int text)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((14 << 4) | text));
}

template <class T>
void Algorithm<T>::Add(T Elem, Queue<T>& obj)
{
	obj.PushHead(Elem);
	return;
}

template <class T>
void Algorithm<T>::Delete_Element(int num, Queue<T>& obj, int pick)
{
	T temp;
	if (pick == 1) temp = obj.DeleteFromHead();
	if (pick == 2) temp = obj.DeleteFromTail();
	if (pick == 3) temp = obj.Delete_(num);
}

template <class T>
Queue<T> Algorithm<T>::Search(Iterator<T> Begin, Iterator<T> End, T Temp)
{
	Queue<T> Queue;
	++End;
	for (; Begin != End; ++Begin)
	{
		if (*Begin == Temp) Queue.PushTail(*Begin);
	}
	return Queue;
}

template <class T>
void Algorithm<T> ::update(Queue<T>& q, int tempNum)
{
	if (q.QueueEmpty())
	{
		cout << "Очередь пуста" << endl;
		return;
	}

	q[tempNum - 1].Change();
}

template <class T>
void Algorithm<T> ::SortFromMin(Iterator<T> Begin, Iterator<T> End, T temp)
{
	Iterator<T> Minimal;
	Iterator<T> j;
	for (; Begin != End; ++Begin)
	{
		Minimal = Begin;
		j = Begin;
		for (; j != End; ++j)
		{
			temp.ReplaceField(*Minimal);
			if (*j < temp)
			{
				Minimal = j;
			}
		}
		if (Minimal != Begin)
		{
			T tmp = *Begin;
			*Begin = *Minimal;
			*Minimal = tmp;
		}
	}
}

template <class T>
void Algorithm<T> ::SortFromMax(Iterator<T> Begin, Iterator<T> End, T temp)
{
	Iterator<T> Maximal;
	Iterator<T> j;
	for (; Begin != End; ++Begin)
	{
		Maximal = Begin;
		j = Begin;
		for (; j != End; ++j)
		{
			temp.ReplaceField(*Maximal);
			if (*j > temp)
			{
				Maximal = j;
			}
		}
		if (Maximal != Begin)
		{
			T tmp = *Begin;
			*Begin = *Maximal;
			*Maximal = tmp;
		}
	}
}

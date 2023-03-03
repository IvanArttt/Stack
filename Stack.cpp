#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <exception>

template<typename T>
class Stack
{
	struct Node
	{
		T _value;
		T _max;
		Node* _prev;
		Node* _next;
		Node(T value, T max, Node* prev, Node* next)
		{
			this->_max = max;
			this->_value = value;
			this->_prev = prev;
			this->_next = next;
		}
		~Node()
		{
			if (this->_prev) this->_prev->_next = nullptr;
			if (this->_next) delete(this->_next);

		}
	};

	Node* _first, * _last;

public:
	Stack();
	Stack(T*, T*);
	~Stack();
	bool Push(T);
	T Pop();
	void Output();
	bool Empty();
	T Max();
};


template<typename T>
Stack<T>::Stack()
{
	_first = _last = nullptr;
}

template<typename T>
bool Stack<T>::Push(T val)
{
	Stack<T>::Node* p;
	try
	{
		if (!this->_first)
		{
			p = new Stack<T>::Node(val, val, nullptr, nullptr);
			this->_first = p;
		}
		else
		{
			if (val > this->_first->_max) p = new Stack<T>::Node(val, val, this->_first, nullptr);
			else p = new Stack<T>::Node(val, this->_first->_max, this->_first, nullptr);
			this->_first->_next = p;
		}
		if (!_last)
		{
			this->_last = p;
			this->_first = p;
		}
		else
		{
			this->_first = p;
		}
	}
	catch (std::bad_alloc ex)
	{
		printf_s("%s\n", ex.what());
		return false;
	}
	return true;
}

template<typename T>
T Stack<T>::Pop()
{
	if (!this->_first) throw "Empty";
	T tmp = this->_first->_value;
	Stack<T>::Node* tmp1 = this->_first->_prev;
	if (this->_first == this->_last) this->_last = tmp1;
	delete(this->_first);
	this->_first = tmp1;
	return tmp;
}



template<typename T>
Stack<T>::~Stack()
{
	Stack<T>::Node* pNode = _first;
	while (pNode)
	{
		Stack<T>::Node* tmp = pNode->_prev;
		delete(pNode);
		pNode = tmp;
	}
}


template<typename T>
bool Stack<T>::Empty()
{
	return !_last;
}

template<typename T>
void Stack<T>::Output()
{
	Stack<T>::Node* pNode = _first;
	printf_s("          Stack         \n");
	printf_s("------------------------\n");
	while (pNode)
	{
		printf_s("|%10d, %-10d|\n", pNode->_value, pNode->_max);
		printf_s("------------------------\n");
		pNode = pNode->_prev;
	}
}


template<typename T>
T Stack<T>::Max()
{
	return this->_first->_max;
}


template<typename T>
Stack<T>::Stack(T* begin, T* end)
{
	while (begin != end)
	{
		this->Push(*begin);
		++begin;
	}
}




int main()
{
	srand(time(NULL));
	Stack<int> a;
	int n = 100;
	for (int i = 0; i < n; i++)
	{
		a.Push(rand() % n);
	}
	a.Output();
	for (int i = 0; i < n / 2; i++)
	{
		printf_s("%d\n", a.Pop());
	}
	a.Output();
	for (int i = 0; i < n / 2; i++)
	{
		printf_s("%d\n", a.Pop());
	}
	a.Output();
	a.Push(111);
	a.Push(112);
	a.Output();
	printf_s("%d\n", a.Empty());
	a.Pop();
	a.Pop();
	a.Output();
	printf_s("%d\n", a.Empty());
	return 0;
}

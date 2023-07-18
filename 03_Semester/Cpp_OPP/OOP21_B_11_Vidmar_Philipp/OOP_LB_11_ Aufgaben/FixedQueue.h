#pragma once
#include <iostream>
#include <queue>
template <typename T, int len>

class FixedQueue
{
private:
	std::queue<T> myqueue;
	int size;
public:
	void push(T elem) {
		if (size >= len) {
			//älterste == erste[0] durch ersetzen wird es zum jüngsten -> letzte
			myqueue.pop();
			myqueue.push(elem);
		}
		else {
			size++;
			myqueue.push(elem);
		}
	}
	T pop() {
		size--;
		T temp = myqueue.front();
		myqueue.pop();
		return temp;
	}
	T& front()
	{
		return myqueue.front();
	}
	T& back()
	{
		return myqueue.back();
	}
	int getsize()
	{
		return size;
	}
};


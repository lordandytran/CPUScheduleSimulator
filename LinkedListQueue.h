/***
Queue Header. Contains Linked List implementation of queue
***/

#ifndef LINKEDLISTQUEUE_H
#define LINKEDLISTQUEUE_H
#include <iostream>

#include "CPUEvent.h"
using namespace std;

template <class T>
class LinkedListQueue {

private:

	//Linked List Nodes for queue
	struct QueueNode {

		//Value stored in each node
		T value;

		//Pointer to next node
		QueueNode *next;
	};

	//Pointer to the front of queue
	QueueNode *front;

	//Pointer to end of queue
	QueueNode *end;



public:
	//Size of queue
	int size;

	//Constructor
	LinkedListQueue();

	//Destructor
	~LinkedListQueue();

	//Queue Operations
	void enqueue(T);
	T dequeue(T&);
	T peek();
	int getSize();
	bool isEmpty();
	void enqueuePriority(T, bool(*)(T, T));


};


//Constructor implementation
//Creates an empty queue
template <class T>
LinkedListQueue<T>::LinkedListQueue() {
	front = NULL;
	end = NULL;
	size = 0;
}


//Destructor implementation
//clears the list
template <class T>
LinkedListQueue<T>::~LinkedListQueue() {
	T temp; //dequeues to temp value 
	while (!isEmpty()) {
		dequeue(temp);
	}
}


//Enqueue implementation
//Adds a value to the queue
template <class T>
void LinkedListQueue<T>::enqueue(T item) {
	QueueNode *temp;

	temp = new QueueNode;
	temp->value = item;
	temp->next = NULL;

	if (isEmpty()) {
		front = temp;
		end = temp;
	}
	else {
		end->next = temp;
		end = temp;
	}

	size++;
}


//Dequeue implementation
//Removes a value in the queue
template <class T>
T LinkedListQueue<T>::dequeue(T &item) {
	QueueNode *temp;

	if (isEmpty()) {
		cout << "Queue is empty" << endl;
	}
	else {
		item = front->value;
		temp = front;
		front = front->next;
		//delete temp;
		size--;
	}
	return item;
}


//Peek implementation
//Returns front value of queue
template <class T>
T LinkedListQueue<T>::peek() {
	return front->value;
}


//isEmpty implementation
//Checks whether the queue is empty
template <class T>
bool LinkedListQueue<T>::isEmpty() {
	if (size == 0)
		return true;
	return false;
}

//Returns size to queue
template<class T>
int LinkedListQueue<T>::getSize() {
	return size;
}

//Priority Enqueue implementation
//Adds a value to the queue in sorted order
//Passed a compare function based on values being compared.
template <class T>
inline void LinkedListQueue<T>::enqueuePriority(T item, bool(*)(T, T)) {
	QueueNode *temp;
	QueueNode *traverse;
	QueueNode *previous = NULL;

	temp = new QueueNode;
	temp->value = item;
	temp->next = NULL;

	if (isEmpty()) {
		front = temp;
		end = temp;
	}
	else {
		traverse = front;
		while (traverse != NULL && compare(traverse->value, item)) {
			previous = traverse;
			traverse = traverse->next;
		}
		if (previous == NULL) {
			front = temp;
			temp->next = traverse;
		}
		else {
			previous->next = temp;
			traverse->next = traverse;
		}
	}

	size++;
}

#endif

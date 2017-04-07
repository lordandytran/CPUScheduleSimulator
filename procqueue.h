#ifndef PROCQUEUE_H
#define PROCQUEUE_H

template <class T>
class PQueue {
public:
    struct QueueNode {
        T data;
        QueueNode* next;
    };
    QueueNode* front;
    QueueNode* back;
    int size;
    PQueue();
    void enqueue(T);
    void dequeue(T&);
    bool empty();
    T peek();
};

template <class T>
PQueue<T>::PQueue() {
    front = nullptr;
    back = nullptr;
    size = 0;
}

template <class T>
bool PQueue<T>::empty() {
    return size == 0;
}

template <class T>
void PQueue<T>::enqueue(T item) {
    QueueNode* newNode = new QueueNode;
    newNode->data = item;
    newNode->next = nullptr;
    if(empty()) {
        front = newNode;
        back = front;
    }
    else {
        back->next = newNode;
        back = newNode;
    }
    size++;
}

template <class T>
void PQueue<T>::dequeue(T& item) {
    if(empty()) {
        return;
    }
    else {
        QueueNode* temp = front;
        front = front->next;
        item = temp->data;
        delete temp;
    }
    size--;
}

template <class T>
T PQueue<T>::peek() {
    return front->data;
}

#endif //PROCQUEUE_H

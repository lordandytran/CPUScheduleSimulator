#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <vector>

template <class T>
class PriorityQueue {
public:
    PriorityQueue(int(*)(T,T));
    void enqueue(T);
    void dequeue(T&);
    bool empty();
private:
    std::vector<T> root;
    int(*comp)(T,T);
    void bubbleUp(int);
    void bubbleDown(int);
};

template <class T>
PriorityQueue<T>::PriorityQueue(int(*compare)(T item1,T item2)) {
    comp = compare;
}

template <class T>
void PriorityQueue<T>::enqueue(T item) {
    root.push_back(item);
    bubbleUp((int)root.size() - 1);
}

template <class T>
void PriorityQueue<T>::dequeue(T& item) {
    item = root[0];
    root[0] = root[root.size() - 1];
    root.pop_back();
    bubbleDown(0);
}

template <class T>
bool PriorityQueue<T>::empty() {
    return root.empty();
}

template <class T>
void PriorityQueue<T>::bubbleUp(int index) {
    if(index == 0) {
        return;
    }
    int pIndex = (index - 1) / 2;
    if(comp(root[pIndex], root[index]) == -1) {
        T temp = root[pIndex];
        root[pIndex] = root[index];
        root[index] = temp;
        bubbleUp(pIndex);
    }
}

template <class T>
void PriorityQueue<T>::bubbleDown(int index) {
    int length = (int)root.size();
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    if(leftChild >= length)
        return;

    int minIndex = index;

    if(comp(root[index], root[leftChild]) == -1) {
        minIndex = leftChild;
    }

    if((rightChild < length) && comp(root[minIndex], root[rightChild]) == -1) {
        minIndex = rightChild;
    }

    if(minIndex != index) {
        T temp = root[index];
        root[index] = root[minIndex];
        root[minIndex] = temp;
        bubbleDown(minIndex);
    }
}

#endif //PRIORITYQUEUE_H

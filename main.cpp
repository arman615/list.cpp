#include <iostream>
#include <stdexcept>

template <class T>
class List {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };
    Node* head;
    Node* tail;
    int size;

public:
    List() : head(nullptr), tail(nullptr), size(0) {}

    ~List() {
        clear();
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        ++size;
    }

    void pop_back() {
        if (!tail) return;
        Node* temp = tail;
        tail = tail->prev;
        if (tail)
            tail->next = nullptr;
        else
            head = nullptr;
        delete temp;
        --size;
    }

    void push_front(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        ++size;
    }

    void pop_front() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        if (head)
            head->prev = nullptr;
        else
            tail = nullptr;
        delete temp;
        --size;
    }

    void insert(const T& value, int index) {
        if (index == 0) {
            push_front(value);
            return;
        }
        if (index >= size) {
            push_back(value);
            return;
        }
        Node* newNode = new Node(value);
        Node* current = head;
        for (int i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;
        ++size;
    }

    void removeAt(int index) {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        if (index == 0) {
            pop_front();
            return;
        }
        if (index == size - 1) {
            pop_back();
            return;
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        --size;
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

    T& operator[](int index) {
        if (index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    int getSize() const {
        return size;
    }

    bool empty() const {
        return size == 0;
    }
};

int main() {
    List<int> lst;

    lst.push_back(5);
    lst.push_back(10);
    lst.push_front(3);
    lst.insert(7, 2);

    std::cout << "Elements in the list: ";
    for (int i = 0; i < lst.getSize(); ++i) {
        std::cout << lst[i] << " ";
    }
    std::cout << std::endl;

    lst.pop_front();
    lst.pop_back();
    lst.removeAt(1);

    std::cout << "Final elements in the list: ";
    for (int i = 0; i < lst.getSize(); ++i) {
        std::cout << lst[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

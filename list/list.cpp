#include "list.hpp"
#include <stack> // Aggiunta dell'inclusione mancante

namespace lasd {
    /* ************************************************************************** */

    // Specific constructor from TraversableContainer
    template<typename Data>
    List<Data>::List(const TraversableContainer<Data> &container) {
        container.Traverse([this](const Data &data) {
            InsertAtBack(data);
        });
    }

    // Specific constructor from MappableContainer
    template<typename Data>
    List<Data>::List(MappableContainer<Data> &&container) {
        container.Map([this](Data &data) {
            InsertAtBack(std::move(data));
        });
    }

    // Copy constructor
    template<typename Data>
    List<Data>::List(const List<Data> &other) {
        if (!other.Empty()) {
            Node *current = other.head;
            while (current != nullptr) {
                InsertAtBack(current->data);
                current = current->next;
            }
        }
    }

    // Destructor
    template<typename Data>
    List<Data>::~List() {
        Clear();
    }

    // Copy assignment
    template<typename Data>
    List<Data> &List<Data>::operator=(const List<Data> &other) {
        if (this != &other) {
            Clear();

            Node *current = other.head;
            while (current != nullptr) {
                InsertAtBack(current->data);
                current = current->next;
            }
        }

        return *this;
    }

    // Move constructor
    template<typename Data>
    List<Data>::List(List&& other) noexcept {
        head = other.head;
        tail = other.tail;
        size = other.size;
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    // Move assignmentst
    template <typename Data>
    List<Data> &List<Data>::operator=(List &&other) noexcept
    {
        if (this != &other)
        {
            std::swap(head, other.head);
            std::swap(tail, other.tail);
            std::swap(size, other.size);
        }
        return *this;
    }

    // Comparison operators
    template<typename Data>
    bool List<Data>::operator==(const List<Data> &other) const noexcept {
        if (size != other.size) {
            return false;
        }

        Node *thisCurrent = head;
        Node *otherCurrent = other.head;

        while (thisCurrent != nullptr) {
            if (thisCurrent->data != otherCurrent->data) {
                return false;
            }

            thisCurrent = thisCurrent->next;
            otherCurrent = otherCurrent->next;
        }

        return true;
    }

    template<typename Data>
    bool List<Data>::operator!=(const List<Data> &other) const noexcept {
        return !(*this == other);
    }

    // Specific member functions
    template<typename Data>
    void List<Data>::InsertAtFront(const Data &value) {
        Node *newNode = new Node(value);

        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }

        size++;
    }

    template<typename Data>
    void List<Data>::InsertAtFront(Data &&value) noexcept {
        Node *newNode = new Node(std::move(value));

        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }

        size++;
    }

    template<typename Data>
    void List<Data>::RemoveFromFront() {
        if (Empty()) {
            throw std::length_error("Empty list");
        }

        Node *temp = head;

        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
        }

        delete temp;
        size--;
    }

    template<typename Data>
    Data List<Data>::FrontNRemove() {
        if (size == 0)
            throw std::length_error("Length error!");
        Data result = head->data;  // Crea una copia
        RemoveFromFront();
        return result;  // Restituisci per valore
    }

    template<typename Data>
    void List<Data>::InsertAtBack(const Data &value) {
        Node *newNode = new Node(value);

        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        size++;
    }

    template<typename Data>
    void List<Data>::InsertAtBack(Data &&value) noexcept {
        Node *newNode = new Node(std::move(value));

        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        size++;
    }

    template<typename Data>
    void List<Data>::RemoveFromBack() {
        if (Empty()) {
            throw std::length_error("Empty list");
        }

        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node *current = head;

            while (current->next != tail) {
                current = current->next;
            }

            delete tail;
            tail = current;
            tail->next = nullptr;
        }

        size--;
    }

    template<typename Data>
    Data List<Data>::BackNRemove() {
        if (Empty()) {
            throw std::length_error("Empty list");
        }

        Data value;

        if (head == tail) {
            value = std::move(head->data);
            delete head;
            head = tail = nullptr;
        } else {
            Node *current = head;

            while (current->next != tail) {
                current = current->next;
            }

            value = std::move(tail->data);
            delete tail;
            tail = current;
            tail->next = nullptr;
        }

        size--;

        return value;
    }

    // Specific member functions (inherited from MutableLinearContainer)
    template<typename Data>
    Data &List<Data>::operator[](ulong index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }

        return GetNodeAt(index)->data;
    }

    template<typename Data>
    Data &List<Data>::Front() {
        if (Empty()) {
            throw std::length_error("Empty list");
        }

        return head->data;
    }

    template<typename Data>
    Data &List<Data>::Back() {
        if (Empty()) {
            throw std::length_error("Empty list");
        }

        return tail->data;
    }

    // Specific member functions (inherited from LinearContainer)
    template<typename Data>
    const Data &List<Data>::operator[](ulong index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }

        return GetNodeAt(index)->data;
    }

    template<typename Data>
    const Data &List<Data>::Front() const {
        if (Empty()) {
            throw std::length_error("Empty list");
        }

        return head->data;
    }

    template<typename Data>
    const Data &List<Data>::Back() const {
        if (Empty()) {
            throw std::length_error("Empty list");
        }

        return tail->data;
    }

    // Specific member function (inherited from MappableContainer)
    template<typename Data>
    void List<Data>::Map(MapFun fun) {
        PreOrderMap(fun);
    }

    // Specific member function (inherited from PreOrderMappableContainer)
    template<typename Data>
    void List<Data>::PreOrderMap(MapFun fun) {
        Node *current = head;

        while (current != nullptr) {
            fun(current->data);
            current = current->next;
        }
    }

    // Specific member function (inherited from PostOrderMappableContainer)
    template<typename Data>
    void List<Data>::PostOrderMap(MapFun fun) {

        if (!Empty()) {
            std::stack<Node *> stack;
            Node *current = head;

            while (current != nullptr) {
                stack.push(current);
                current = current->next;
            }

            while (!stack.empty()) {
                fun(stack.top()->data);
                stack.pop();
            }
        }
    }

    // Specific member function (inherited from TraversableContainer)
    template<typename Data>
    void List<Data>::Traverse(TraverseFun fun) const {
        PreOrderTraverse(fun);
    }

    // Specific member function (inherited from PreOrderTraversableContainer)
    template<typename Data>
    void List<Data>::PreOrderTraverse(TraverseFun fun) const {
        Node *current = head;

        while (current != nullptr) {
            fun(current->data);
            current = current->next;
        }
    }

    // Specific member function (inherited from PostOrderTraversableContainer)
    template<typename Data>
    void List<Data>::PostOrderTraverse(TraverseFun fun) const {
        if (!Empty()) {
            std::stack<Node *> stack;
            Node *current = head;

            while (current != nullptr) {
                stack.push(current);
                current = current->next;
            }

            while (!stack.empty()) {
                fun(stack.top()->data);
                stack.pop();
            }
        }
    }

    // Specific member function (inherited from ClearableContainer)
    template<typename Data>
    void List<Data>::Clear() {
        while (!Empty()) {
            RemoveFromFront();
        }
    }

    // Auxiliary functions
    template<typename Data>
    typename List<Data>::Node *List<Data>::GetNodeAt(ulong index) const {
        Node *current = head;

        for (ulong i = 0; i < index && current != nullptr; i++) {
            current = current->next;
        }

        return current;
    }

    /* ************************************************************************** */
}
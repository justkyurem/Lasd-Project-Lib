#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {
    /* ************************************************************************** */

    template<typename Data>
    class List : virtual public MutableLinearContainer<Data>,
                 virtual public ClearableContainer {
    protected:
        using Container::size;

        struct Node {
            // Data
            Data data;
            Node *next = nullptr;

            /* ********************************************************************** */

            // Specific constructors
            Node() = default;

            explicit Node(const Data &value) : data(value) {
            }

            explicit Node(Data &&value) noexcept : data(std::move(value)) {
            }

            /* ********************************************************************** */

            // Copy constructor
            Node(const Node &other) : data(other.data), next(nullptr) {
            }

            // Move constructor
            Node(Node &&other) noexcept : data(std::move(other.data)), next(other.next) {
                other.next = nullptr;
            }

            /* ********************************************************************** */

            // Destructor
            virtual ~Node() = default;

            /* ********************************************************************** */

            // Comparison operators
            bool operator==(const Node &other) const noexcept {
                return (data == other.data);
            }

            bool operator!=(const Node &other) const noexcept {
                return !(*this == other);
            }

            /* ********************************************************************** */

            // Specific member functions
        };

        Node *head = nullptr;
        Node *tail = nullptr;

    public:
        // Default constructor
        List() = default;

        /* ************************************************************************ */

        // Specific constructor
        List(const TraversableContainer<Data> &container); // A list obtained from a TraversableContainer
        List(MappableContainer<Data> &&container); // A list obtained from a MappableContainer

        /* ************************************************************************ */

        // Copy constructor
        List(const List &other);

        // Move constructor
        List(List &&other) noexcept;

        /* ************************************************************************ */

        // Destructor
        virtual ~List();

        /* ************************************************************************ */

        // Copy assignment
        List &operator=(const List &other);

        // Move assignment
        List &operator=(List &&other) noexcept;

        /* ************************************************************************ */

        using LinearContainer<Data>::operator==;
        using LinearContainer<Data>::operator!=;

        // Comparison operators
        bool operator==(const List &other) const noexcept;

        bool operator!=(const List &other) const noexcept;

        /* ************************************************************************ */

        // Specific member functions

        void InsertAtFront(const Data &value); // Copy of the value
        void InsertAtFront(Data &&value) noexcept; // Move of the value
        void RemoveFromFront(); // (must throw std::length_error when empty)
        Data FrontNRemove(); // (must throw std::length_error when empty)

        void InsertAtBack(const Data &value); // Copy of the value
        void InsertAtBack(Data &&value) noexcept; // Move of the value
        void RemoveFromBack(); // (must throw std::length_error when empty)
        Data BackNRemove(); // (must throw std::length_error when empty)

        /* ************************************************************************ */

        // Specific member functions (inherited from MutableLinearContainer)

        Data &operator[](ulong index) override;

        // Override MutableLinearContainer member (must throw std::out_of_range when out of range)

        Data &Front() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

        Data &Back() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

        /* ************************************************************************ */

        // Specific member functions (inherited from LinearContainer)

        const Data &operator[](ulong index) const override;

        // Override LinearContainer member (must throw std::out_of_range when out of range)

        const Data &Front() const override; // Override LinearContainer member (must throw std::length_error when empty)

        const Data &Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

        /* ************************************************************************ */

        // Specific member function (inherited from MappableContainer)

        using typename MappableContainer<Data>::MapFun;

        void Map(MapFun fun) override; // Override MappableContainer member

        /* ************************************************************************ */

        // Specific member function (inherited from PreOrderMappableContainer)

        void PreOrderMap(MapFun fun) override; // Override PreOrderMappableContainer member

        /* ************************************************************************ */

        // Specific member function (inherited from PostOrderMappableContainer)

        void PostOrderMap(MapFun fun) override; // Override PostOrderMappableContainer member

        /* ************************************************************************ */

        // Specific member function (inherited from TraversableContainer)

        using typename TraversableContainer<Data>::TraverseFun;

        void Traverse(TraverseFun fun) const override; // Override TraversableContainer member

        /* ************************************************************************ */

        // Specific member function (inherited from PreOrderTraversableContainer)

        void PreOrderTraverse(TraverseFun fun) const override; // Override PreOrderTraversableContainer member

        /* ************************************************************************ */

        // Specific member function (inherited from PostOrderTraversableContainer)

        void PostOrderTraverse(TraverseFun fun) const override; // Override PostOrderTraversableContainer member

        /* ************************************************************************ */

        // Specific member function (inherited from ClearableContainer)

        void Clear() override; // Override ClearableContainer member

    protected:
        // Auxiliary functions

        Node *GetNodeAt(ulong index) const;
    };

    /* ************************************************************************** */
}

#include "list.cpp"

#endif
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : virtual public MutableLinearContainer<Data>,
               virtual public ResizableContainer {
private:

  // ...

protected:

  using Container::size;

  Data* elements = nullptr;  // Array di elementi

public:

  // Default constructor
  Vector() = default;

  /* ************************************************************************ */

  // Specific constructors
  explicit Vector(unsigned long newSize); // A vector with a given initial dimension
  Vector(const TraversableContainer<Data>& container); // A vector obtained from a TraversableContainer
  Vector(MappableContainer<Data>&& container); // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector& other);

  // Move constructor
  Vector(Vector&& other) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~Vector();

  /* ************************************************************************ */

  // Copy assignment
  Vector& operator=(const Vector& other);

  // Move assignment
  Vector& operator=(Vector&& other) noexcept;

  /* ************************************************************************ */

  using LinearContainer<Data>::operator==;
  using LinearContainer<Data>::operator!=;

  // Comparison operators
  bool operator==(const Vector& other) const noexcept;
  bool operator!=(const Vector& other) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  Data& operator[](unsigned long index) override; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)

  Data& Front() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  Data& Back() override; // Override MutableLinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data& operator[](unsigned long index) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

  const Data& Front() const override; // Override LinearContainer member (must throw std::length_error when empty)

  const Data& Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)

  void Resize(unsigned long newSize) override; // Override ResizableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() override; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!
  void Swap(Vector& other) noexcept;

};

/* ************************************************************************** */

template <typename Data>
class SortableVector : virtual public Vector<Data>,
                       virtual public SortableLinearContainer<Data> {

private:

  // ...

protected:

  // using Container::???;

  // ...

public:

  // Default constructor
  SortableVector() = default;

  /* ************************************************************************ */

  // Specific constructors
  explicit SortableVector(unsigned long newSize) : Vector<Data>(newSize) {} // A vector with a given initial dimension

  SortableVector(const TraversableContainer<Data>& container) : Vector<Data>(container) {} // A vector obtained from a TraversableContainer

  SortableVector(MappableContainer<Data>&& container) : Vector<Data>(std::move(container)) {} // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  SortableVector(const SortableVector& other) : Vector<Data>(other) {}

  // Move constructor
  SortableVector(SortableVector&& other) noexcept : Vector<Data>(std::move(other)) {}

  /* ************************************************************************ */

  // Destructor
  virtual ~SortableVector() = default;

  /* ************************************************************************ */

  // Copy assignment
  SortableVector& operator=(const SortableVector& other) {
    Vector<Data>::operator=(other);
    return *this;
  }

  // Move assignment
  SortableVector& operator=(SortableVector&& other) noexcept {
    Vector<Data>::operator=(std::move(other));
    return *this;
  }

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)

  void Sort() override;

protected:

  // Auxiliary functions, if necessary!
  void QuickSort(unsigned long left, unsigned long right);
  unsigned long Partition(unsigned long left, unsigned long right);
  void Swap(unsigned long i, unsigned long j);

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
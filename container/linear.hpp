#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class LinearContainer : virtual public PreOrderTraversableContainer<Data>,
                       virtual public PostOrderTraversableContainer<Data> {

public:

  // Destructor
  virtual ~LinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  LinearContainer& operator=(const LinearContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  LinearContainer& operator=(LinearContainer&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  virtual bool operator==(const LinearContainer&) const noexcept;
  virtual bool operator!=(const LinearContainer&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data& operator[](ulong) const = 0; // (non-mutable version; concrete function must throw std::out_of_range when out of range)

  virtual const Data& Front() const = 0; // (non-mutable version; concrete function must throw std::length_error when empty)

  virtual const Data& Back() const = 0; // (non-mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  void Traverse(TraverseFun) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member

  /* ************************************************************************** */

  // Specific member function (inherited from TraversableContainer)

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

  template <typename Accumulator>
  Accumulator Fold(FoldFun<Accumulator>, const Accumulator&) const; // Non implementare qui, usa linear.cpp

  /* ************************************************************************** */

  // Specific member function (inherited from PreOrderTraversableContainer)

  template <typename Accumulator>
  Accumulator PreOrderFold(FoldFun<Accumulator>, const Accumulator&) const; // Non implementare qui, usa linear.cpp

  /* ************************************************************************** */

  // Specific member function (inherited from PostOrderTraversableContainer)

  template <typename Accumulator>
  Accumulator PostOrderFold(FoldFun<Accumulator>, const Accumulator&) const; // Non implementare qui, usa linear.cpp

};

/* ************************************************************************** */

template <typename Data>
class MutableLinearContainer : virtual public LinearContainer<Data>,
                              virtual public PreOrderMappableContainer<Data>,
                              virtual public PostOrderMappableContainer<Data> {


public:

  // Destructor
  virtual ~MutableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableLinearContainer& operator=(const MutableLinearContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  MutableLinearContainer& operator=(MutableLinearContainer&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  using LinearContainer<Data>::operator[];
  using LinearContainer<Data>::Front;
  using LinearContainer<Data>::Back;

  // Specific member functions

  virtual Data& operator[](ulong) = 0; // (mutable version; concrete function must throw std::out_of_range when out of range)

  virtual Data& Front() = 0; // (mutable version; concrete function must throw std::length_error when empty)

  virtual Data& Back() = 0; // (mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  void Map(MapFun) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  void PreOrderMap(MapFun) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  void PostOrderMap(MapFun) override; // Override PostOrderMappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class SortableLinearContainer : virtual public MutableLinearContainer<Data> {

private:

  // ...

protected:

  // Auxiliary member functions
  virtual void QuickSort(ulong, ulong);
  virtual ulong Partition(ulong, ulong);

public:

  // Destructor
  virtual ~SortableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  SortableLinearContainer& operator=(const SortableLinearContainer&) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  SortableLinearContainer& operator=(SortableLinearContainer&&) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member function

  virtual void Sort() {
    if (this->Size() > 1) {
      QuickSort(0, this->Size() - 1);
    }
  }

};

/* ************************************************************************** */

}

#include "linear.cpp"

#endif
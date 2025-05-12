namespace lasd {

/* ************************************************************************** */

// LinearContainer

// Comparison operators
template <typename Data>
bool LinearContainer<Data>::operator==(const LinearContainer<Data>& other) const noexcept {
  if (this->Size() != other.Size()) {
    return false;
  }

  for (ulong i = 0; i < this->Size(); i++) {
    if ((*this)[i] != other[i]) {
      return false;
    }
  }

  return true;
}

template <typename Data>
bool LinearContainer<Data>::operator!=(const LinearContainer<Data>& other) const noexcept {
  return !(*this == other);
}

// Specific member function (inherited from TraversableContainer)

template <typename Data>
void LinearContainer<Data>::Traverse(TraverseFun fun) const {
  PreOrderTraverse(fun);
}

// Specific member function (inherited from PreOrderTraversableContainer)

template <typename Data>
void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const {
  for (ulong i = 0; i < this->Size(); i++) {
    fun((*this)[i]);
  }
}

// Specific member function (inherited from PostOrderTraversableContainer)

template <typename Data>
void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const {
  for (ulong i = this->Size(); i > 0; i--) {
    fun((*this)[i - 1]);
  }
}

// Specific member function (inherited from TraversableContainer)

template <typename Data>
template <typename Accumulator>
Accumulator LinearContainer<Data>::Fold(FoldFun<Accumulator> fun, const Accumulator& accum) const {
  return PreOrderFold(fun, accum);
}

// Specific member function (inherited from PreOrderTraversableContainer)

template <typename Data>
template <typename Accumulator>
Accumulator LinearContainer<Data>::PreOrderFold(FoldFun<Accumulator> fun, const Accumulator& accum) const {
  Accumulator accumulator = accum;

  for (ulong i = 0; i < this->Size(); i++) {
    accumulator = fun((*this)[i], accumulator);
  }

  return accumulator;
}

// Specific member function (inherited from PostOrderTraversableContainer)

template <typename Data>
template <typename Accumulator>
Accumulator LinearContainer<Data>::PostOrderFold(FoldFun<Accumulator> fun, const Accumulator& accum) const {
  Accumulator accumulator = accum;

  for (ulong i = this->Size(); i > 0; i--) {
    accumulator = fun((*this)[i - 1], accumulator);
  }

  return accumulator;
}

/* ************************************************************************** */

// MutableLinearContainer

// Specific member function (inherited from MappableContainer)

template <typename Data>
void MutableLinearContainer<Data>::Map(MapFun fun) {
  PreOrderMap(fun);
}

// Specific member function (inherited from PreOrderMappableContainer)

template <typename Data>
void MutableLinearContainer<Data>::PreOrderMap(MapFun fun) {
  for (ulong i = 0; i < this->Size(); i++) {
    fun((*this)[i]);
  }
}

// Specific member function (inherited from PostOrderMappableContainer)

template <typename Data>
void MutableLinearContainer<Data>::PostOrderMap(MapFun fun) {
  for (ulong i = this->Size(); i > 0; i--) {
    fun((*this)[i - 1]);
  }
}

/* ************************************************************************** */

// SortableLinearContainer

// Protected member functions

template <typename Data>
void SortableLinearContainer<Data>::QuickSort(ulong left, ulong right) {
  if (left < right) {
    ulong pivot = Partition(left, right);
    
    if (pivot > 0) {
      QuickSort(left, pivot - 1);
    }
    
    QuickSort(pivot + 1, right);
  }
}

template <typename Data>
ulong SortableLinearContainer<Data>::Partition(ulong left, ulong right) {
  ulong pivotIndex = left + (right - left) / 2;
  Data pivotValue = (*this)[pivotIndex];
  
  // Sposta il pivot alla fine
  std::swap((*this)[pivotIndex], (*this)[right]);
  
  ulong storeIndex = left;
  
  for (ulong i = left; i < right; i++) {
    if ((*this)[i] <= pivotValue) {
      std::swap((*this)[i], (*this)[storeIndex]);
      storeIndex++;
    }
  }
  
  // Sposta il pivot alla sua posizione finale
  std::swap((*this)[storeIndex], (*this)[right]);
  
  return storeIndex;
}

/* ************************************************************************** */

}
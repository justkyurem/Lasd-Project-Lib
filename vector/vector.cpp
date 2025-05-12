namespace lasd {

/* ************************************************************************** */

// Specific constructor with size
template <typename Data>
Vector<Data>::Vector(unsigned long newSize) {
  elements = new Data[newSize]{};
  size = newSize;
}

// Specific constructor from TraversableContainer
template <typename Data>
Vector<Data>::Vector(const TraversableContainer<Data>& container) {
  size = container.Size();
  elements = new Data[size]{};

  unsigned long index = 0;
  container.Traverse([this, &index](const Data& data) {
    elements[index++] = data;
  });
}

// Specific constructor from MappableContainer
template <typename Data>
Vector<Data>::Vector(MappableContainer<Data>&& container) {
  size = container.Size();
  elements = new Data[size]{};

  unsigned long index = 0;
  container.Map([this, &index](Data& data) {
    elements[index++] = std::move(data);
    return Data{};
  });
}

// Copy constructor
template <typename Data>
Vector<Data>::Vector(const Vector<Data>& other) {
  elements = new Data[other.size]{};
  std::copy(other.elements, other.elements + other.size, elements);
  size = other.size;
}

// Move constructor
template <typename Data>
Vector<Data>::Vector(Vector<Data>&& other) noexcept {
  Swap(other);
}

// Destructor
template <typename Data>
Vector<Data>::~Vector() {
  delete[] elements;
}

// Copy assignment
template <typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& other) {
  if (this != &other) {
    Vector<Data> temp(other);
    Swap(temp);
  }
  return *this;
}

// Move assignment
template <typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& other) noexcept {
  if (this != &other) {
    Swap(other);
  }
  return *this;
}

// Comparison operators
template <typename Data>
bool Vector<Data>::operator==(const Vector<Data>& other) const noexcept {
  if (size != other.size) {
    return false;
  }

  for (unsigned long i = 0; i < size; i++) {
    if (elements[i] != other.elements[i]) {
      return false;
    }
  }

  return true;
}

template <typename Data>
bool Vector<Data>::operator!=(const Vector<Data>& other) const noexcept {
  return !(*this == other);
}

// Specific member functions (inherited from MutableLinearContainer)
template <typename Data>
Data& Vector<Data>::operator[](unsigned long index) {
  if (index >= size) {
    throw std::out_of_range("Index out of range");
  }
  return elements[index];
}

template <typename Data>
Data& Vector<Data>::Front() {
  if (size == 0) {
    throw std::length_error("Empty vector");
  }
  return elements[0];
}

template <typename Data>
Data& Vector<Data>::Back() {
  if (size == 0) {
    throw std::length_error("Empty vector");
  }
  return elements[size - 1];
}

// Specific member functions (inherited from LinearContainer)
template <typename Data>
const Data& Vector<Data>::operator[](unsigned long index) const {
  if (index >= size) {
    throw std::out_of_range("Index out of range");
  }
  return elements[index];
}

template <typename Data>
const Data& Vector<Data>::Front() const {
  if (size == 0) {
    throw std::length_error("Empty vector");
  }
  return elements[0];
}

template <typename Data>
const Data& Vector<Data>::Back() const {
  if (size == 0) {
    throw std::length_error("Empty vector");
  }
  return elements[size - 1];
}

// Specific member function (inherited from ResizableContainer)
template <typename Data>
void Vector<Data>::Resize(unsigned long newSize) {
  if (newSize == size) {
    return;
  }

  if (newSize == 0) {
    Clear();
    return;
  }

  Data* newElements = new Data[newSize]{};

  unsigned long minSize = (size < newSize) ? size : newSize;
  for (unsigned long i = 0; i < minSize; i++) {
    newElements[i] = std::move(elements[i]);
  }

  delete[] elements;
  elements = newElements;
  size = newSize;
}

// Specific member function (inherited from ClearableContainer)
template <typename Data>
void Vector<Data>::Clear() {
  delete[] elements;
  elements = nullptr;
  size = 0;
}

// Auxiliary functions
template <typename Data>
void Vector<Data>::Swap(Vector<Data>& other) noexcept {
  std::swap(elements, other.elements);
  std::swap(size, other.size);
}

/* ************************************************************************** */

// SortableVector implementation

template <typename Data>
void SortableVector<Data>::Sort() {
  if (this->size > 1) {
    QuickSort(0, this->size - 1);
  }
}

template <typename Data>
void SortableVector<Data>::QuickSort(unsigned long left, unsigned long right) {
  if (left < right) {
    unsigned long pivot = Partition(left, right);

    if (pivot > 0) {
      QuickSort(left, pivot - 1);
    }

    QuickSort(pivot + 1, right);
  }
}

template <typename Data>
unsigned long SortableVector<Data>::Partition(unsigned long left, unsigned long right) {
  unsigned long pivot = right;
  unsigned long i = left;

  for (unsigned long j = left; j < right; j++) {
    if (this->elements[j] <= this->elements[pivot]) {
      Swap(i, j);
      i++;
    }
  }

  Swap(i, right);
  return i;
}

template <typename Data>
void SortableVector<Data>::Swap(unsigned long i, unsigned long j) {
  if (i != j) {
    std::swap(this->elements[i], this->elements[j]);
  }
}

/* ************************************************************************** */

}
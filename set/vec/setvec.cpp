namespace lasd {

/* ************************************************************************** */

// Auxiliary protected functions
template <typename Data>
ulong SetVec<Data>::FindIndex(const Data& data) const {
  // Ricerca binaria per trovare l'indice di un elemento
  if (size == 0 || Vector<Data>::elements == nullptr) {
    return size;  // Elemento non trovato
  }

  ulong left = 0;
  ulong right = size - 1;

  while (left <= right) {
    ulong mid = left + (right - left) / 2;

    if (Vector<Data>::elements[mid] == data) {
      return mid;
    }

    if (Vector<Data>::elements[mid] < data) {
      left = mid + 1;
    } else {
      if (mid == 0) {
        break;
      }
      right = mid - 1;
    }
  }

  return size;
}

template <typename Data>
ulong SetVec<Data>::FindInsertionIndex(const Data& data) const {
  if (size == 0 || Vector<Data>::elements == nullptr) {
    return 0;
  }

  ulong left = 0;
  ulong right = size - 1;

  while (left <= right) {
    ulong mid = left + (right - left) / 2;

    if (Vector<Data>::elements[mid] == data) {
      return mid;
    }

    if (Vector<Data>::elements[mid] < data) {
      left = mid + 1;
    } else {
      if (mid == 0) {
        break;
      }
      right = mid - 1;
    }
  }

  return left;
}

template <typename Data>
void SetVec<Data>::ShiftRight(ulong index) {
  ulong newSize = size + 1;
  Data* newElements = new Data[newSize]{};

  // Copia gli elementi prima del punto di inserimento
  for (ulong i = 0; i < index && i < size; i++) {
    newElements[i] = Vector<Data>::elements[i];
  }

  // Copia l'elemento da inserire (shift ->)
  for (ulong i = index; i < size; i++) {
    newElements[i + 1] = Vector<Data>::elements[i];
  }

  // Rimpiazza il vecchio array
  delete[] Vector<Data>::elements;
  Vector<Data>::elements = newElements;
  size = newSize;
}

template <typename Data>
void SetVec<Data>::ShiftLeft(ulong index) {
  if (size == 0 || Vector<Data>::elements == nullptr) {
    return;
  }

  if (size == 1) {
    // se c'è solo un elemento, lo rimuoviamo
    delete[] Vector<Data>::elements;
    Vector<Data>::elements = nullptr;
    size = 0;
    return;
  }

  // Crea un nuovo array di dimensione size - 1
  ulong newSize = size - 1;
  Data* newElements = new Data[newSize]{};

  // Copia gli elementi prima del punto di rimozione
  for (ulong i = 0; i < index && i < size; i++) {
    newElements[i] = Vector<Data>::elements[i];
  }

  // Copia gli elementi dopo il punto di rimozione (shift <-)
  for (ulong i = index + 1; i < size; i++) {
    newElements[i - 1] = Vector<Data>::elements[i];
  }

  delete[] Vector<Data>::elements;
  Vector<Data>::elements = newElements;
  size = newSize;
}

// Specific constructors

template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data>& container) : Vector<Data>() {
  // Vettore temporaneo per raccogliere gli elementi
  std::vector<Data> tempElements;

  container.Traverse([&tempElements](const Data& data) {
    tempElements.push_back(data);
  });

  // Inserimento degli elementi uno per uno per garantire l'ordinamento e l'unicità
  for (const auto& data : tempElements) {
    Insert(data);
  }
}

template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data>&& container) : Vector<Data>() {
  std::vector<Data> tempElements;

  container.Map([&tempElements](Data& data) {
    tempElements.push_back(std::move(data));
  });

  for (auto& data : tempElements) {
    Insert(std::move(data));
  }
}

// Copy constructor
template <typename Data>
SetVec<Data>::SetVec(const SetVec<Data>& other) : Vector<Data>(other) {}

// Move constructor
template <typename Data>
SetVec<Data>::SetVec(SetVec<Data>&& other) noexcept : Vector<Data>(std::move(other)) {}

// Copy assignment
template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(const SetVec<Data>& other) {
  Vector<Data>::operator=(other);
  return *this;
}

// Move assignment
template <typename Data>
SetVec<Data>& SetVec<Data>::operator=(SetVec<Data>&& other) noexcept {
  Vector<Data>::operator=(std::move(other));
  return *this;
}

// Comparison operators
template <typename Data>
bool SetVec<Data>::operator==(const SetVec<Data>& other) const noexcept {
  return Vector<Data>::operator==(other);
}

template <typename Data>
inline bool SetVec<Data>::operator!=(const SetVec<Data>& other) const noexcept {
  return !(*this == other);
}

// Specific member functions (inherited from OrderedDictionaryContainer)

template <typename Data>
const Data& SetVec<Data>::Min() const {
  if (size == 0 || Vector<Data>::elements == nullptr) {
    throw std::length_error("Empty set");
  }

  return Vector<Data>::elements[0]; // Min e' il primo elemento in un set ordinato
}

template <typename Data>
Data SetVec<Data>::MinNRemove() {
  if (size == 0 || Vector<Data>::elements == nullptr) {
    throw std::length_error("Empty set");
  }

  Data min = Vector<Data>::elements[0];
  ShiftLeft(0);

  return min;
}

template <typename Data>
void SetVec<Data>::RemoveMin() {
  if (size == 0 || Vector<Data>::elements == nullptr) {
    throw std::length_error("Empty set");
  }

  ShiftLeft(0);
}

template <typename Data>
const Data& SetVec<Data>::Max() const {
  if (size == 0 || Vector<Data>::elements == nullptr) {
    throw std::length_error("Empty set");
  }

  return Vector<Data>::elements[size - 1]; // Max e' l'ultimo elemento in un set ordinato
}

template <typename Data>
Data SetVec<Data>::MaxNRemove() {
  if (size == 0 || Vector<Data>::elements == nullptr) {
    throw std::length_error("Empty set");
  }

  Data max = Vector<Data>::elements[size - 1];
  ShiftLeft(size - 1);

  return max;
}

template <typename Data>
void SetVec<Data>::RemoveMax() {
  if (size == 0 || Vector<Data>::elements == nullptr) {
    throw std::length_error("Empty set");
  }

  ShiftLeft(size - 1);
}

template <typename Data>
const Data& SetVec<Data>::Predecessor(const Data& data) const {
  if (size == 0 || Vector<Data>::elements == nullptr) {
    throw std::length_error("Empty set");
  }

  // Trov a l'indice del predecessore (elements[i] < data e elements[i+1] >= data)
  ulong index = FindInsertionIndex(data);

  if (index == 0) {
    throw std::length_error("Predecessor not found");
  }

  return Vector<Data>::elements[index - 1];
}

template <typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data& data) {
  if (size == 0 || Vector<Data>::elements == nullptr) {
    throw std::length_error("Empty set");
  }

  // Trova l'indice del predecessore (elements[i] < data e elements[i+1] >= data)
  ulong index = FindInsertionIndex(data);

  if (index == 0) {
    throw std::length_error("Predecessor not found");
  }

  Data pred = Vector<Data>::elements[index - 1];
  ShiftLeft(index - 1);

  return pred;
}

template <typename Data>
void SetVec<Data>::RemovePredecessor(const Data& data) {
  if (size == 0 || Vector<Data>::elements == nullptr) {
    throw std::length_error("Empty set");
  }

  // Trova l'indice del predecessore (elements[i] < data e elements[i+1] >= data)
  ulong index = FindInsertionIndex(data);

  if (index == 0) {
    throw std::length_error("Predecessor not found");
  }

  ShiftLeft(index - 1);
}

template <typename Data>
const Data& SetVec<Data>::Successor(const Data& data) const {
  if (size == 0 || Vector<Data>::elements == nullptr) {
    throw std::length_error("Empty set");
  }

  // Trova l'indice del successore (elements[i] > data)
  ulong index = FindInsertionIndex(data);

  if (index >= size || Vector<Data>::elements[index] == data) {
    if (index + 1 >= size) {
      throw std::length_error("Successor not found");
    }
    index++;
  }

  return Vector<Data>::elements[index];
}

template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data& data) {
  if (size == 0 || Vector<Data>::elements == nullptr) {
    throw std::length_error("Empty set");
  }

  // Trova l'indice del successore (elements[i] > data)
  ulong index = FindInsertionIndex(data);

  if (index >= size || Vector<Data>::elements[index] == data) {
    if (index + 1 >= size) {
      throw std::length_error("Successor not found");
    }
    index++;
  }

  Data succ = Vector<Data>::elements[index];
  ShiftLeft(index);

  return succ;
}

template <typename Data>
void SetVec<Data>::RemoveSuccessor(const Data& data) {
  if (size == 0 || Vector<Data>::elements == nullptr) {
    throw std::length_error("Empty set");
  }

  // Trova l'indice del successore (elements[i] > data)
  ulong index = FindInsertionIndex(data);

  if (index >= size || Vector<Data>::elements[index] == data) {
    if (index + 1 >= size) {
      throw std::length_error("Successor not found");
    }
    index++;
  }

  ShiftLeft(index);
}

// Specific member functions (inherited from DictionaryContainer)

template <typename Data>
bool SetVec<Data>::Insert(const Data& data) {
  // Controlla se l'elemento esiste già
  if (size > 0 && Vector<Data>::elements != nullptr) {
    ulong index = FindInsertionIndex(data);

    if (index < size && Vector<Data>::elements[index] == data) {
      return false;
    }

    // Se non esiste, inseriscilo mantenendo l'ordinamento
    ShiftRight(index);
    Vector<Data>::elements[index] = data;
  } else {
    Vector<Data>::elements = new Data[1];
    Vector<Data>::elements[0] = data;
    size = 1;
  }

  return true;
}

template <typename Data>
bool SetVec<Data>::Insert(Data&& data) {
  if (size > 0 && Vector<Data>::elements != nullptr) {
    ulong index = FindInsertionIndex(data);

    if (index < size && Vector<Data>::elements[index] == data) {
      return false;
    }

    // Se non esiste, inseriscilo mantenendo l'ordinamento
    ShiftRight(index);
    Vector<Data>::elements[index] = std::move(data);
  } else {
    Vector<Data>::elements = new Data[1];
    Vector<Data>::elements[0] = std::move(data);
    size = 1;
  }

  return true;
}

template <typename Data>
bool SetVec<Data>::Remove(const Data& data) {
  if (size == 0 || Vector<Data>::elements == nullptr) {
    return false;
  }

  ulong index = FindIndex(data);

  if (index >= size) {
    return false;
  }
  
  ShiftLeft(index);
  return true;
}

/* ************************************************************************** */

}
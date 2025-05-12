namespace lasd {

/* ************************************************************************** */

// Auxiliary protected functions
template <typename Data>
void SetLst<Data>::InsertInOrder(const Data& data) {
  if (size == 0 || data <= head->data) {
    // Inserimento in testa
    this->InsertAtFront(data);
    return;
  }

  // Trovo la posizione corretta
  typename List<Data>::Node* current = head;
  while (current->next != nullptr && current->next->data < data) {
    current = current->next;
  }

  // Creo un nuovo nodo
  typename List<Data>::Node* newNode = new typename List<Data>::Node(data);

  // Lo inserisco nella lista
  newNode->next = current->next;
  current->next = newNode;

  // Se inserito alla fine, aggiorno tail
  if (newNode->next == nullptr) {
    List<Data>::tail = newNode;
  }

  size++;
}

template <typename Data>
void SetLst<Data>::InsertInOrder(Data&& data) {
  if (size == 0 || data <= head->data) {
    // Inserimento in testa
    this->InsertAtFront(std::move(data));
    return;
  }

  // Trovo la posizione corretta
  typename List<Data>::Node* current = head;
  while (current->next != nullptr && current->next->data < data) {
    current = current->next;
  }

  // Creo un nuovo nodo
  typename List<Data>::Node* newNode = new typename List<Data>::Node(std::move(data));

  // Lo inserisco nella lista
  newNode->next = current->next;
  current->next = newNode;

  // Se inserito alla fine, aggiorno tail
  if (newNode->next == nullptr) {
    List<Data>::tail = newNode;
  }

  size++;
}

// Specific constructors

template <typename Data>
SetLst<Data>::SetLst(const TraversableContainer<Data>& container) {
  container.Traverse([this](const Data& data) {
    this->Insert(data);  // Usa Insert invece di InsertAtBack per garantire unicità
  });
}

template <typename Data>
SetLst<Data>::SetLst(MappableContainer<Data>&& container) {
  container.Map([this](Data& data) {
    this->Insert(std::move(data));  // Usa Insert invece di InsertAtBack per garantire unicità
  });
}

// Copy constructor
template <typename Data>
SetLst<Data>::SetLst(const SetLst<Data>& other) : List<Data>() {
  other.Traverse([this](const Data& data) {
    this->Insert(data);  // Usa Insert per mantenere l'ordinamento
  });
}

// Move constructor
template <typename Data>
SetLst<Data>::SetLst(SetLst<Data>&& other) noexcept : List<Data>(std::move(other)) {}

// Copy assignment
template <typename Data>
SetLst<Data>& SetLst<Data>::operator=(const SetLst<Data>& other) {
  if (this != &other) {
    this->Clear();
    other.Traverse([this](const Data& data) {
      this->Insert(data);  // Usa Insert per mantenere l'ordinamento
    });
  }
  return *this;
}

// Move assignment
template <typename Data>
SetLst<Data>& SetLst<Data>::operator=(SetLst<Data>&& other) noexcept {
  List<Data>::operator=(std::move(other));
  return *this;
}

// Comparison operators
template <typename Data>
bool SetLst<Data>::operator==(const SetLst<Data>& other) const noexcept {
  return List<Data>::operator==(other);
}

template <typename Data>
inline bool SetLst<Data>::operator!=(const SetLst<Data>& other) const noexcept {
  return !(*this == other);
}

// Specific member functions (inherited from OrderedDictionaryContainer)

template <typename Data>
const Data& SetLst<Data>::Min() const {
  if (size == 0) {
    throw std::length_error("Empty set");
  }

  return head->data;  // In una lista ordinata, il minimo è in testa
}

template <typename Data>
Data SetLst<Data>::MinNRemove() {
  if (size == 0) {
    throw std::length_error("Empty set");
  }

  return this->FrontNRemove();  // In una lista ordinata, il minimo è in testa
}

template <typename Data>
void SetLst<Data>::RemoveMin() {
  if (size == 0) {
    throw std::length_error("Empty set");
  }

  this->RemoveFromFront();  // In una lista ordinata, il minimo è in testa
}

template <typename Data>
const Data& SetLst<Data>::Max() const {
  if (size == 0) {
    throw std::length_error("Empty set");
  }

  return List<Data>::tail->data;  // In una lista ordinata, il massimo è in coda
}

template <typename Data>
Data SetLst<Data>::MaxNRemove() {
  if (size == 0) {
    throw std::length_error("Empty set");
  }

  return this->BackNRemove();  // In una lista ordinata, il massimo è in coda
}

template <typename Data>
void SetLst<Data>::RemoveMax() {
  if (size == 0) {
    throw std::length_error("Empty set");
  }

  this->RemoveFromBack();  // In una lista ordinata, il massimo è in coda
}

template <typename Data>
const Data& SetLst<Data>::Predecessor(const Data& data) const {
  if (size == 0) {
    throw std::length_error("Empty set");
  }

  typename List<Data>::Node* pred = FindPointerToPredecessor(data);
  if (pred == nullptr) {
    throw std::length_error("Predecessor not found");
  }

  return pred->data;
}

template <typename Data>
Data SetLst<Data>::PredecessorNRemove(const Data& data) {
  if (size == 0) {
    throw std::length_error("Empty set");
  }

  typename List<Data>::Node* pred = FindPointerToPredecessor(data);
  if (pred == nullptr) {
    throw std::length_error("Predecessor not found");
  }

  Data value = pred->data;

  if (pred == head) {
    this->RemoveFromFront();
  } else {
    typename List<Data>::Node* current = head;
    while (current->next != pred) {
      current = current->next;
    }

    current->next = pred->next;

    if (pred == List<Data>::tail) {
      List<Data>::tail = current;
    }

    delete pred;
    size--;
  }

  return value;
}

template <typename Data>
void SetLst<Data>::RemovePredecessor(const Data& data) {
  if (size == 0) {
    throw std::length_error("Empty set");
  }

  typename List<Data>::Node* pred = FindPointerToPredecessor(data);
  if (pred == nullptr) {
    throw std::length_error("Predecessor not found");
  }

  if (pred == head) {
    this->RemoveFromFront();
  } else {
    typename List<Data>::Node* current = head;
    while (current->next != pred) {
      current = current->next;
    }

    current->next = pred->next;

    if (pred == List<Data>::tail) {
      List<Data>::tail = current;
    }

    delete pred;
    size--;
  }
}

template <typename Data>
const Data& SetLst<Data>::Successor(const Data& data) const {
  if (size == 0) {
    throw std::length_error("Empty set");
  }

  typename List<Data>::Node* succ = FindPointerToSuccessor(data);
  if (succ == nullptr) {
    throw std::length_error("Successor not found");
  }

  return succ->data;
}

template <typename Data>
Data SetLst<Data>::SuccessorNRemove(const Data& data) {
  if (size == 0) {
    throw std::length_error("Empty set");
  }

  typename List<Data>::Node* succ = FindPointerToSuccessor(data);
  if (succ == nullptr) {
    throw std::length_error("Successor not found");
  }

  Data value = succ->data;

  if (succ == head) {
    this->RemoveFromFront();
  } else {
    typename List<Data>::Node* current = head;
    while (current->next != succ) {
      current = current->next;
    }

    current->next = succ->next;

    if (succ == List<Data>::tail) {
      List<Data>::tail = current;
    }

    delete succ;
    size--;
  }

  return value;
}

template <typename Data>
void SetLst<Data>::RemoveSuccessor(const Data& data) {
  if (size == 0) {
    throw std::length_error("Empty set");
  }

  typename List<Data>::Node* succ = FindPointerToSuccessor(data);
  if (succ == nullptr) {
    throw std::length_error("Successor not found");
  }

  if (succ == head) {
    this->RemoveFromFront();
  } else {
    typename List<Data>::Node* current = head;
    while (current->next != succ) {
      current = current->next;
    }

    current->next = succ->next;

    if (succ == List<Data>::tail) {
      List<Data>::tail = current;
    }

    delete succ;
    size--;
  }
}

// Specific member functions (inherited from DictionaryContainer)

template <typename Data>
bool SetLst<Data>::Insert(const Data& data) {
  // Prima controlla se l'elemento esiste già
  if (this->Exists(data)) {
    return false;
  }

  // Se non esiste, inseriscilo mantenendo l'ordinamento
  InsertInOrder(data);
  return true;
}

template <typename Data>
bool SetLst<Data>::Insert(Data&& data) {
  // Prima controlla se l'elemento esiste già
  if (this->Exists(data)) {
    return false;
  }

  // Se non esiste, inseriscilo mantenendo l'ordinamento
  InsertInOrder(std::move(data));
  return true;
}

template <typename Data>
bool SetLst<Data>::Remove(const Data& data) {
  if (size == 0) {
    return false;
  }

  if (head->data == data) {
    this->RemoveFromFront();
    return true;
  }
  
  typename List<Data>::Node* current = head;
  while (current->next != nullptr && current->next->data != data) {
    current = current->next;
  }
  
  if (current->next == nullptr) {
    return false;  // Elemento non trovato
  }
  
  typename List<Data>::Node* temp = current->next;
  current->next = temp->next;
  
  if (temp == List<Data>::tail) {
    List<Data>::tail = current;
  }
  
  delete temp;
  size--;
  
  return true;
}

// Auxiliary member functions

template <typename Data>
typename List<Data>::Node* SetLst<Data>::FindPointerToMin() const {
  return head;  // In una lista ordinata, il minimo è in testa
}

template <typename Data>
typename List<Data>::Node* SetLst<Data>::FindPointerToMax() const {
  return List<Data>::tail;  // In una lista ordinata, il massimo è in coda
}

template <typename Data>
typename List<Data>::Node* SetLst<Data>::FindPointerToPredecessor(const Data& data) const {
  if (size == 0 || data <= head->data) {
    return nullptr;  // Non c'è predecessore
  }
  
  typename List<Data>::Node* current = head;
  typename List<Data>::Node* predecessor = nullptr;
  
  while (current != nullptr && current->data < data) {
    predecessor = current;
    current = current->next;
  }
  
  return predecessor;
}

template <typename Data>
typename List<Data>::Node* SetLst<Data>::FindPointerToSuccessor(const Data& data) const {
  if (size == 0 || data >= List<Data>::tail->data) {
    return nullptr;  // Non c'è successore
  }
  
  typename List<Data>::Node* current = head;
  
  while (current != nullptr && current->data <= data) {
    current = current->next;
  }
  
  return current;
}

template <typename Data>
typename List<Data>::Node* SetLst<Data>::FindPointerTo(const Data& data) const {
  typename List<Data>::Node* current = head;
  
  while (current != nullptr && current->data != data) {
    current = current->next;
  }
  
  return current;
}

/* ************************************************************************** */

}
namespace lasd {


// DictionaryContainer

// Specific member functions

template <typename Data>
bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data>& container) {
  bool result = true;

  container.Traverse([this, &result](const Data& data) {
    result &= this->Insert(data);
  });

  return result;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data>&& container) {
  bool result = true;

  container.Map([this, &result](Data& data) {
    result &= this->Insert(std::move(data));
  });

  return result;
}

template <typename Data>
bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data>& container) {
  bool result = true;

  container.Traverse([this, &result](const Data& data) {
    result &= this->Remove(data);
  });

  return result;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data>& container) {
  bool result = false;

  container.Traverse([this, &result](const Data& data) {
    result |= this->Insert(data);
  });

  return result;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data>&& container) {
  bool result = false;

  container.Map([this, &result](Data& data) {
    result |= this->Insert(std::move(data));
  });

  return result;
}

template <typename Data>
bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data>& container) {
  bool result = false;

  container.Traverse([this, &result](const Data& data) {
    result |= this->Remove(data);
  });

  return result;
}

// OrderedDictionaryContainer

// Specific member functions

template <typename Data>
void OrderedDictionaryContainer<Data>::RemoveMin() {
  if (this->Empty()) {
    throw std::length_error("Empty container");
  }

  this->Remove(this->Min());
}

template <typename Data>
Data OrderedDictionaryContainer<Data>::MinNRemove() {
  if (this->Empty()) {
    throw std::length_error("Empty container");
  }

  Data min = this->Min();
  this->Remove(min);
  return min;
}

template <typename Data>
void OrderedDictionaryContainer<Data>::RemoveMax() {
  if (this->Empty()) {
    throw std::length_error("Empty container");
  }

  this->Remove(this->Max());
}

template <typename Data>
Data OrderedDictionaryContainer<Data>::MaxNRemove() {
  if (this->Empty()) {
    throw std::length_error("Empty container");
  }

  Data max = this->Max();
  this->Remove(max);
  return max;
}

template <typename Data>
void OrderedDictionaryContainer<Data>::RemovePredecessor(const Data& data) {
  this->Remove(this->Predecessor(data));
}

template <typename Data>
Data OrderedDictionaryContainer<Data>::PredecessorNRemove(const Data& data) {
  Data predecessor = this->Predecessor(data);
  this->Remove(predecessor);
  return predecessor;
}

template <typename Data>
void OrderedDictionaryContainer<Data>::RemoveSuccessor(const Data& data) {
  this->Remove(this->Successor(data));
}

template <typename Data>
Data OrderedDictionaryContainer<Data>::SuccessorNRemove(const Data& data) {
  Data successor = this->Successor(data);
  this->Remove(successor);
  return successor;
}


}
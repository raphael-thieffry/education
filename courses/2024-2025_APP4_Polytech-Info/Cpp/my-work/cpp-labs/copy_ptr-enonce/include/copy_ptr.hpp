#pragma once

#include <type_traits>

/// FR | Fonctionne comme unique_ptr, mais permet de faire une copie d'objet.
/// EN | Works like unique_ptr, with the addition of copy semantics.
/// http://en.cppreference.com/w/cpp/memory/unique_ptr
template <class T> class copy_ptr {
private:
  /// FR | Le pointeur lui-meme
  /// EN | The pointer itself
  T *ptr_;

public:
  /// FR | Implementez le destructeur.
  /// EN | Implement the destructor.

  ~copy_ptr() {
    if(ptr_) {
      delete ptr_;
    }
  }

  /// [FR]
  /// Constructeur par pointeur de type T*. La valeur doit etre soit nullptr,
  /// soit un pointeur vers une valeur deja allouee.

  /// [EN]
  /// Constructor by pointer of type T*. Value must be either nullptr,
  /// or a pointer to a pre-allocated value.
  
  copy_ptr() noexcept : ptr_(nullptr) {}

  copy_ptr(T *ptr) : ptr_(ptr) {}

  // Constructeurs (move et copy) | Constructors (move and copy)

  // Transfert | Move:
  copy_ptr(copy_ptr &&other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  }

  // Copie | Copy
  copy_ptr(const copy_ptr &other) : ptr_(new T(*other.ptr_)) {}

  // operator= (move & copy)

  // Transfert | Move
  copy_ptr &operator=(copy_ptr &&other) noexcept {
    if (this != &other) {
      delete ptr_;
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }
    return *this;
  }

  // Copie | Copy
  copy_ptr &operator=(const copy_ptr &other) {
    if (this != &other) {
      delete ptr_;
      ptr_ = new T(*other.ptr_);
    }
    return *this;
  }

  /// FR | Echange le pointeur de l'objet avec celui d'other.
  /// EN | Swap the pointer held by the object with other's.
  
  void swap(copy_ptr &other) noexcept {
    std::swap(ptr_, other.ptr_);
  }

  /// FR | Renvoie true si le pointeur tient une valeur, sinon false.
  /// EN | Returns true if the pointer holds a value, otherwise false.
  
  bool holds_value() const noexcept {
    return ptr_ != nullptr;
  }

  /// FR | Renvoie le pointeur vers la ressource.
  /// EN | Returns a pointer to the resource.
  
  T *get() const noexcept {
    return ptr_;
  }

  /// [FR]
  /// Renvoie une reference vers la ressource. Permet de "depointer" la valeur,
  /// comme avec un pointeur normal.
  ///
  /// [EN]
  /// Returns a reference to the resource. This allows "depointing" a value,
  /// just like a regular pointer.
  // T& ref() const noexcept {
  //   return *ptr_;
  // }

  T& operator*() const noexcept {
    return *ptr_;
  }

  /// [FR]
  /// Indirection, permet d'utiliser la fleche, comme avec un pointeur normal.
  ///
  /// [EN]
  /// Indirection, allows the arrow thing, just like a regular pointer.
  
  T *operator->() const noexcept {
    return ptr_;
  }
  
};
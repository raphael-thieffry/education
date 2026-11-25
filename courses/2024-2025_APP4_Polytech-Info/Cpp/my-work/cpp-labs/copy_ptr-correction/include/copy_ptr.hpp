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

  /**c*/
  // [FR]
  /// 1. Verifie si le pointeur pointe vers une ressource
  /// 2. Si oui, supprime la ressource (operator delete)

  // [EN]
  /// 1. Checks if the pointer holds a resource
  /// 2. If so, deallocates it (operator delete)
  ~copy_ptr() {
    if (ptr_) {
      // FR | Desallocation de la ressource au bout du pointeur
      // EN | Deallocation of the resource held by the pointer
      delete ptr_;
    }
  }
  /*c**/

  /// [FR]
  /// Constructeur par pointeur de type T*. La valeur doit etre soit nullptr,
  /// soit un pointeur vers une valeur deja allouee.

  /// [EN]
  /// Constructor by pointer of type T*. Value must be either nullptr,
  /// or a pointer to a pre-allocated value.
  /**c*/
  copy_ptr(T *ptr) noexcept : ptr_(ptr) {}
  /*c**/

  copy_ptr() noexcept : ptr_(nullptr) {}

  // Constructeurs (move et copy) | Constructors (move and copy)

  // Transfert | Move:
  /**c*/

  // [FR]
  // 1. On prend la valeur du pointeur dont on devient responsable
  // 2. On met la valeur de l'autre pointeur a nullptr
  //    pour qu'il n'en soit plus responsable
  //
  // [EN]
  // 1. We copy the value of the pointer, of which we become responsible
  // 2. We set the other pointer's value to nullptr to ensure it's not
  //    responsible of it anymore
  copy_ptr(copy_ptr &&other)
      : // FR | Copie du pointeur de other
        // EN | Copying other's pointer
        ptr_(other.ptr_) {
    // FR | On nullifie other pour eviter qu'il desalloue la memoire
    // EN | We nullify other to ensure it doesn't deallocate the memory
    other.ptr_ = nullptr;
  }
  /*c**/

  // Copie | Copy
  /**c*/
  copy_ptr(copy_ptr const &other) {
    if constexpr (std::is_polymorphic<T>::value) {
      ptr_ = other.ptr_->clone();
    } else {
      ptr_ = new T(*(other.ptr_));
    }
  }
  /*c**/

  // operator= (move & copy)

  // Transfert | Move
  /**c*/
  copy_ptr &operator=(copy_ptr &&other) {
    // [FR]
    // Nous allons ecraser la valeur du pointeur par une nouvelle.
    // On fait donc attention a bien desallouer l'ancienne ressource
    // (s'il y en a une) avant de l'ecraser.

    // [EN]
    // We're about to replace the pointer's value by another's.
    // We make sure to properly deallocate the current ressource
    // (if any) before erasing the pointer.
    if (ptr_) {
      delete ptr_;
    }

    // FR | On copie le pointeur de l'autre copy_ptr (mais pas sa memoire)
    // EN | We copy other's pointer (but not its buffer)
    ptr_ = other.ptr_;

    // FR | Puis on nullifie son pointeur pour s'assurer qu'il ne desalloue rien
    // EN | Then we nullify its pointer to ensure it doesn't deallocate anything
    other.ptr_ = nullptr;

    // FR | Puis on retourne une reference a l'objet lui-meme, par convention
    // EN | Then we return a reference to the object itself, by convention
    return *this;
  }
  /*c**/

  // Copie | Copy
  /**c*/
  copy_ptr &operator=(copy_ptr const &other) {
    if (ptr_) {
      delete ptr_;
    }

    // FR | Cas de la copie, on verifie que le type detenu est polymorphe
    // FR | In case of copy, we check whether the contained type is polymorphic
    if constexpr (std::is_polymorphic<T>::value) {
      // FR | S'il l'est on s'appuie sur la methode clone() de la classe
      // EN | If so then we rely on the clone() method of the class
      ptr_ = other.ptr_->clone();
    } else {
      // FR | Autrement, on peut simplement faire une copie
      // EN | Otherwise, we can simply make a copy
      ptr_ = new T(*(other.ptr_));
    }

    return *this;
  }
  /*c**/

  /// FR | Echange le pointeur de l'objet avec celui d'other.
  /// EN | Swap the pointer held by the object with other's.
  /**c*/
  void swap(copy_ptr &other) noexcept {
    // FR | A la main
    // EN | By hand
    /*
    T* temp = other.ptr_;
    other.ptr_ = ptr_;
    ptr_ = temp;
    */

    // FR | Avec std::swap
    // EN | Using std::swap
    using std::swap;
    swap(ptr_, other.ptr_);
  }
  /*c**/

  /// FR | Renvoie true si le pointeur tient une valeur, sinon false.
  /// EN | Returns true if the pointer holds a value, otherwise false.
  /**c*/
  operator bool() const noexcept {
    // FR | Cette operation est la meme que caster un pointeur en booleen.
    // EN | This operation is the same as casting a pointer to a bool.
    return ptr_;
  }
  /*c**/

  /// FR | Renvoie le pointeur vers la ressource.
  /// EN | Returns a pointer to the resource.
  /**c*/
  T *get() const noexcept { return ptr_; }
  /*c**/

  /// [FR]
  /// Renvoie une reference vers la ressource. Permet de "depointer" la valeur,
  /// comme avec un pointeur normal.
  ///
  /// [EN]
  /// Returns a reference to the resource. This allows "depointing" a value,
  /// just like a regular pointer.
  /**c*/
  T &operator*() const { return *ptr_; }
  /*c**/

  /// [FR]
  /// Indirection, permet d'utiliser la fleche, comme avec un pointeur normal.
  ///
  /// [EN]
  /// Indirection, allows the arrow thing, just like a regular pointer.
  /**c*/
  T *operator->() const noexcept { return ptr_; }
  /*c**/
};

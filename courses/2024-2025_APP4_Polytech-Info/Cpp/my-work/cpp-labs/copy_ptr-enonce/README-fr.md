# `copy_ptr`

## Instructions generales

Comme d'habitude:

```sh
mkdir build
cd build
cmake ../
make
```

## Partie 1: La semantique de `copy_ptr`

On souhaite un "smart pointer" a la `std::unique_ptr` ayant une semantique de
deplacement similaire a `unique_ptr`, et une semantique de copie permettant de
copier l'element stocke d'un pointeur a l'autre (voir `tests/copy_ptr.cpp`).

Sa semantique doit premettre:
- de deplacer, et copier les objets de sorte a ce qu'il n'y ait jamais deux
  pointeurs qui pointent vers un meme objet,
- qu'un objet detenu par un `copy_ptr` soit systematiquement detruit,
- et qu'un meme objet pointe par un `copy_ptr` ne soit jamais detruit plus d'une
  fois.

Pour cela, implementez toutes les methodes dans `include/local/copy_ptr.hpp`,
a savoir:

- Les constructeurs par copie/deplacement
- Les operateurs d'assignation (`operator=`) par copie/deplacement
- Le destructeur
- Les membres `operator*`, `operator->`, `get()`, `swap()`, `operator bool()`,
  etc. (ie. tous les membres suivis de `// TODO`)

Lancez `make` pour compiler et executer les tests sur cette partie du sujet.

## Partie 2: Quid du polymorphisme?

Un probleme se pose lorsqu'on utilise `copy_ptr` avec des classes polymorphes
(ie. avec de l'heritage). A savoir, la copie d'une classe fille dans une classe
mere peut faire du slicing si la classe fille a des membres qui ne font pas
partie de la classe mere, ce qui peut induire une perte de donnees et des
erreurs a l'execution.

Modifiez `copy_ptr` de maniere a ce qu'une copie de pointeur appelle la methode
virtuelle `clone()` de l'element pointe pour obtenir un nouveau pointeur vers
une copie de ce dernier. Chaque classe fille devra donc surcharger `clone()`
pour implementer sa propre methode de clonage.

Vous verrez dans le fichier `tests/copy_ptr_poly.cpp` des tests qui peuvent vous
servir d'exemples pour ameliorer l'implementation de `copy_ptr`.

NB: Vous pouvez utiliser [le type trait `is_polymorphic`](
https://en.cppreference.com/w/cpp/types/is_polymorphic) pour distinguer les
types polymorphes des autres.

Lancez `make run_test_copy_ptr_poly` pour compiler et executer les tests
sur cette partie du sujet.

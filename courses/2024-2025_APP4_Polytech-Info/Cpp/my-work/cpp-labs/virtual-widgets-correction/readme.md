# Virtual widgets

Dans cet exercices vous partirez d'une structure de widgets pour implementer
une GUI qui s'affichera dans la console. La structure initiale vous est donnee,
vous devez suivre les consignes pour l'ameliorer.

A chaque etape, un nouveau main vous est donne pour vous donner une idee de
l'API qui sera attendue. Ce sera donc a vous de l'implementer.

**Vous devez ajouter des tests pour chaque etape.**

## Version 0 - Point de depart

La structure vous est donnee dans `version-0.cpp`. Vous avez disposez de
plusieurs types:

- `canvas_t`, une interface pour tout ce sur quoi on peut dessiner
- `box_t`, un rectangle a dessiner sur un canvas
- `label_t`, un label a dessiner sur un canvas
- `button_t`, un bouton a dessiner sur un canvas
  (combinaison de `box_t` et `label_t`)

Le main ne fait rien de special a part creer un bouton, un canvas, et dessiner
le bouton sur le canvas (depuis une fonction **du bouton**).

Sortie attendue:

```
---------------------------
|                         |
|                         |
|                         |
|   ~~~~~~~~~~~~~~~~      |
|   ~ Hello World! ~      |
|   ~~~~~~~~~~~~~~~~      |
|                         |
|                         |
|                         |
---------------------------
```

:arrow_right: Ajoutez vos tests

## Version 1 - Interface `blittable_t`

1.  Rajouter une interface virtuelle `blittable_t`. Tout objet heritant de cette
    interface doit implementer une fonction `blit` qui prend un canvas en entree
    pour se dessiner dessus.

2.  Dans le type `ascii_art_t`, rajouter un stockage d'objets polymorphes
    heritant de `blittable_t` pour stocker les objets a dessiner sur le canvas.
    On doit pouvoir ajouter des objets avec `add` via un `unique_ptr` ou
    directement en passant un objet par transfert.
    La fonction `display` d'`ascii_art_t` devra dessiner chaque objet
    dans l'ordre d'ajout.

Sortie attendue:

```
---------------------------
|                         |
|                         |
|                         |
|   ~~~~~~~~~~~~~~~~      |
|   ~ Hello World! ~      |
|   ~~~~~~~~~~~~~~~~      |
|   ~~~~~~~~~~~~~~~~      |
|   ~ Hello World! ~      |
|   ~~~~~~~~~~~~~~~~      |
---------------------------
```

:arrow_right: Ajoutez vos tests

## Version 2 - Type `group_t`

3.  Rajouter un type `group_t` qui herite de `blittable_t`, qui permet de
    stocker et dessiner plusieurs objets ajoutes avec la methode `add`.
    La methode `add` de `ascii_art_t` ne fait plus que transferer les objets
    a la methode `add` de `group_t`.

    **Vous devez pouvoir faire un `group_t`
    contenant des `group_t` (a tester).**

4.  Refaire button en vous appuyant sur `group_t`.

Sortie attendue:

```
---------------------------
|                         |
|                         |
|                         |
|   ~~~~~~~~~~~~~~~~      |
|   ~ Hello World! ~      |
|   ~~~~~~~~~~~~~~~~      |
|   ~~~~~~~~~~~~~~~~      |
|   ~ Hello World! ~      |
|   ~~~~~~~~~~~~~~~~      |
---------------------------
```

:arrow_right: Ajoutez vos tests

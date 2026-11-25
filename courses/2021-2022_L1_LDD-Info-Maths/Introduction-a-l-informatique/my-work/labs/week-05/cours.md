---
jupytext:
  notebook_metadata_filter: rise
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
    jupytext_version: 1.10.3
kernelspec:
  display_name: C++14
  language: C++14
  name: xcpp14
rise:
  auto_select: first
  autolaunch: false
  centered: false
  controls: false
  enable_chalkboard: true
  height: 100%
  margin: 0
  maxScale: 1
  minScale: 1
  scroll: true
  slideNumber: true
  start_slideshow_at: selected
  transition: none
  width: 90%
---

+++ {"slideshow": {"slide_type": "slide"}}

# Tableaux, compilation, portée des variables

+++ {"slideshow": {"slide_type": "subslide"}}

## Au programme

1. [Tableaux (introduction)](cours-tableaux.md)
2. [Premiers programmes compilés](cours-programmes-compiles.md)
3. [Portée des variables](cours-portee-des-variables.md)

+++ {"slideshow": {"slide_type": "subslide"}}

## Résumé du cours

+++ {"slideshow": {"slide_type": "fragment"}}

### Les tableaux

-   **Valeurs composites homogènes** pour manipuler des collections de données
-   Construction: **Déclaration**, **Allocation**, **Initialisation**
-   Utilisation

+++ {"slideshow": {"slide_type": "fragment"}}

### Fonctions: la portée des variables

-   Variables locales
-   Variables globales
-   Portée définie par les blocs (contexte lexical)

+++ {"slideshow": {"slide_type": "fragment"}}

### Premiers programmes compilés

-   Édition d'un fichier `programme.cpp` avec une fonction `main`
-   Compilation: `g++ programme.cpp -o programme`
-   Exécution: `./programme`

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

# Modèle d'exécution, collections

+++ {"slideshow": {"slide_type": "slide"}}

## Résumé de l'épisode précédent

### Motivation

**Manipulation de collections de données**

**Fil conducteur**: Implantation d'un annuaire

+++ {"slideshow": {"slide_type": "fragment"}}

### Tableau

-   Un **tableau** est une valeur **composite** formée de plusieurs
    valeurs du même type
-   Construction:
    1.  Déclaration
    2.  Allocation
    3.  Initialisation

+++ {"slideshow": {"slide_type": "fragment"}}

**<div style="color:red; text-align:center;">Fonctionnement? Sémantique?</div>**

+++ {"slideshow": {"slide_type": "fragment"}}

**<p style="color: red; text-align: center; font-weight:bold;">Généralisations?</p>**

+++ {"slideshow": {"slide_type": "subslide"}}

## Au programme

1. [Prélude: exemple jouet de piratage par débordement](cours-login.md)
2. [Modèle de mémoire et tableaux](cours-memoire-tableaux.md)
3. [Collections](cours-collections.md)

+++ {"slideshow": {"slide_type": "subslide"}}

## Résumé du cours

+++ {"slideshow": {"slide_type": "fragment"}}

-   Motivation: un exemple de piratage par débordement
-   Un modèle de mémoire raffiné avec pile et tas
-   Sémantique:
    - Allocation des tableaux sur le tas
    - Accès à `t[i]`
    - Affectation de tableaux
	- Passage de tableaux aux fonctions par valeur

+++ {"slideshow": {"slide_type": "fragment"}}

-   Notion de collection
-   Autres collections
-   Boucle `for each`
-   `auto` ♣

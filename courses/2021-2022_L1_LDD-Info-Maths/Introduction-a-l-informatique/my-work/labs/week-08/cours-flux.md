---
jupytext:
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
    jupytext_version: 1.10.3
kernelspec:
  display_name: C++17
  language: C++17
  name: xcpp17
---

# Notion de flux de données

-   Nous avons utilisé la même syntaxe pour écrire à l’écran ou dans un
    fichier: `xxx << expression`
-   Nous avons utilisé la même syntaxe pour lire au clavier ou depuis un
    fichier: `xxx >> variable`

Notez que le sens des chevrons `<<` et `>>` met en valeur dans quel sens
se déplacent les informations: de `expression` vers `xxx` ou de `xxx`
vers `variable`.

+++

-   Un **flux sortant** est un dispositif où l’on peut écrire des données *l’une après
    l’autre*
-   Un **flux entrant** est un dispositif où l’on peut lire des données *l’une après
    l’autre*

+++

## Exemples de flux sortants de données

-   `cout`: *sortie standard* du programme  
    Typiquement: écran  
    ♣ Avec tampon
-   `cerr`: *sortie d’erreur* du programme  
    ♣ Sans tampon
-   fichiers (`ofstream`)
-   chaînes de caractères (`ostringstream`)
-   connexion avec un autre programme ...

+++

## Exemples de flux entrants de données

-   `cin`: *entrée standard* du programme  
    Typiquement: clavier
-   fichiers (`ifstream`)
-   chaînes de caractères (`istringstream`)
-   connexion avec un autre programme ...

+++

## Résumé

Dans ce cours, nous avons vu:

-   Comment lire et écrire dans des fichiers en C++

-   Un concept uniforme pour lire et écrire: les *flux*

    -   Entrée et sortie standard d’un programme: `cin`, `cout`

    -   Fichiers: `ifstream`, `ofstream`

    -   Chaînes de caractères: `istringstream`, `ostringstream`

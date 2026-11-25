# TP4 - Techniques de Partitionnement et Fuzzing


Welcome to TP4! 

## Student Information
**Name:** Raphaël Thieffry

## Exercise 1: Partitioning

1. Caracteristiques associées au type double
    - Signe/Zero
    - Entier/Decimal
   Ces caractéristiques permettent de définir les partitions suivantes:

| Signe/Zero | Entier/Decimal |
|------------|----------------|
| Positif    | Entier         |
| Négatif    | Decimal        |
| Zero       |                |
Avec Zero+Decimal impossible

Qui forment bien une partition complète de l'ensemble des nombres réels.

2. Combien de tests pour prendre en compte tous les blocs ?
    - 3 blocs pour le signe
    - 2 blocs pour le type
    - 3 arguments
    - (3 * 2)^3 = 216 tests

3. Combien de tests si side2 et side3 sont fixés ?
    - 3 blocs pour le signe
    - 2 blocs pour le type
    - 1 argument
    - (3 * 2)^1 = 6 tests

4. Fait
5. Caracteristiques liées à la fonctionnalité de TriangleType

On veut avoir plusieurs partitions de $\mathbb{R}^3$, où chaque partition
correspond à une caracteristique de la fonctionnalité. On a donc:
- (2 côtés sont égaux)/(3 cotés sont egaux)/(Aucun n'est égal)
- Un des coté est negatif/tous positif
- Un des coté est nul/tous non nuls
- Respecte la propriété d'être un triangle ($\exists$ 2 cotés tq a+b>=c)

| Côtés égaux | Positifs | Non nul  | Respecte tri |
|-------------|----------|----------|--------------|
| 2 (A1)      | Oui (B1) | Oui (C1) | Oui (D1)     |
| 3 (A2)      | Non (B2) | Non (C2) | Non (D2)     |
| 0 (A3)      |          |          |              |

6. Pairwise testing (hors respecte tri)
    - (A1, B1, C1) = (A1, B1), (A1, C1), (B1, C1)
    - (A1, B2, C2) = (A1, B2), (A1, C2), (B2, C2)
    - (A2, B1, C2) = (A2, B1), (A2, C2), (B1, C2)
    - (A2, B2, C1) = (A2, B2), (A2, C1), (B2, C1)
    - (A3, B1, C2) = (A3, B1), (A3, C2), (B1, C2)
    - (A3, B1, C1) = (A3, B1), (A3, C1), (B1, C1)
    - (A3, B2, C1) = (A3, B2), (A3, C1), (B2, C1)

Ce qui donne 7 tests testant chaque paire possible
   

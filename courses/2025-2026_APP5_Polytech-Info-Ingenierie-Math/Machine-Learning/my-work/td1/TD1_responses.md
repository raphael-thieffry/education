# TD1

## Exercice 1
### Question 1.
Représentation matricielle :

| Transaction | A | B | C | D | E | F |
|-------------|---|---|---|---|---|---|
| t1          | 0 | 1 | 1 | 1 | 0 | 0 |
| t2          | 1 | 1 | 1 | 0 | 1 | 0 |
| t3          | 1 | 1 | 1 | 1 | 0 | 1 |
| t4          | 0 | 0 | 0 | 1 | 1 | 0 |
| t5          | 1 | 1 | 0 | 0 | 0 | 0 |
| t6          | 1 | 0 | 1 | 0 | 1 | 1 |
| t7          | 1 | 1 | 0 | 0 | 1 | 1 |
| t8          | 0 | 0 | 0 | 1 | 0 | 1 |
| t9          | 0 | 0 | 1 | 0 | 1 | 0 |
| t10         | 1 | 1 | 0 | 0 | 0 | 1 |

Représentation verticale :
| A   | B   | C | D | E | F |
|-----|-----|---|---|---|---|
| t2  | t1  | t1| t1| t2| t3 |
| t3  | t2  | t2| t3| t4| t6 |
| t5  | t3  | t3| t4| t6| t7 |
| t6  | t5  | t6| t8| t7| t8 |
| t7  | t7  | t9|   | t9| t10 |
| t10 | t10 |   |   |   |    |

### Question 2.
On a $L = \{ACD, CE, BCE, ABCE, E, D, BC, F, CDF, EF \}$.

(support = cover = un ensemble)

| Itemset    | Freq (absolue)      | Support          |  Freq (relative) |
|-------------|---------------------|------------------| ------------------|
|ACD |       1  | $\{t3\}$ | $\frac{1}{10} = 0.1$ |
|CE |       3  | $\{t2, t6, t9\}$ | $\frac{3}{10} = 0.3$ |
|BCE |       1  | $\{t2\}$ | $\frac{1}{10} = 0.1$ |
|ABCE |       1  | $\{t2\}$ | $\frac{1}{10} = 0.1$ |
|E |       5  | $\{t2, t4, t6, t7, t9\}$ | $\frac{5}{10} = 0.5$ |
|D |       4  | $\{t1, t2, t3, t4\}$ | $\frac{4}{10} = 0.4$ |
|BC |       3  | $\{t1, t2, t3\}$ | $\frac{3}{10} = 0.3$ |
|F |       5  | $\{t3, t6, t7, t8, t10\}$ | $\frac{5}{10} = 0.5$ |
|CDF |       1  | $\{t3\}$ | $\frac{1}{10} = 0.1$ |
|EF |       2  | $\{t6, t7\}$ | $\frac{2}{10} = 0.2$ |

### Question 3.

Itemsets frequent pour des valeurs $ \alpha \in \{5, 6, 7, 8, 9, 10\}$

| $\alpha$ | Itemsets fréquents               |
|----------|----------------------------------|
| 10       | Aucun                            |
| 9        | Aucun                            |
| 8        | Aucun                            |
| 7        | Aucun                            |
| 6        | $\{A, B\}$                       |
| 5        | $\{A, B, AB, C, E, F\}$          |

### Question 4.

Si on prend comme critère de comparaison une relation d'inclusion,alors on a $A \subseteq AB$ donc $A$ et $AB$ sont comparables.

Au contraire, $A$ et $C$ ne sont pas comparables car $A \not\subset C$ et $C \not\subset A$.

## Exercice 2.
### Question 1.

On cherche à montrer que : 
$Q \subseteq P ⇒ cover(P) \subseteq cover(Q)$

Soit $Q \subseteq P$,

On sait que $\forall R, cover(R) := \{T_i ∈ D : R ⊆ T_i\}$.

Ainsi, on a 
$$ cover(P) := \{T_i ∈ D : P ⊆ T_i\} $$
et 
$$ cover(Q) := \{T_i ∈ D : Q ⊆ T_i\} $$

On voit que :
$$ cover(Q) = \{T_i ∈ D : Q ⊆ P \subseteq T_i\}$$
$$ = \{T_i ∈ D : P ⊆ T_i\} \sqcup \{ T_i ​\in D : Q \subseteq T_i​ \wedge P \not \subseteq T_i\}$$
$$ = cover(P) \sqcup \{T_i ​\in D : Q \subseteq T_i​ \wedge P \not \subseteq T_i\}$$

En langage naturel, le support de $Q$ est constitué des $T_i$ de la base avec $P$ dedans ($Q \subseteq P$) et des autres $T_i$ dans lesquels $Q$ rentre, mais pas $P$

D'où $cover(P) \subseteq cover(Q)$

### Question 2.

On veut montrer (1) que :
$Q ⊆ P ⇒ freq(P) ≤ freq(Q)$

On sait que $freq(P) = |cover(P)|$ et $freq(Q) = |cover(Q)|$.
D'après la question 1, on a $cover(P) ⊆ cover(Q)$.
Donc, on a $|cover(P)| ≤ |cover(Q)|$,
Donc, $freq(P) ≤ freq(Q)$.

Soit $α ∈ ℕ$,
On montre ensuite (2) que $Q ⊆ P ∧ freq(P) ≥ α ⇒ freq(Q) ≥ α$

Soit $Q ⊆ P$ et $freq(P) ≥ α$.
On sait que $freq(P) \leq freq(Q)$ d'après la première partie.
Donc, on a $freq(Q) ≥ freq(P) ≥ α$.
Donc, $freq(Q) ≥ α$.


## Exercice 3.

$D_2$ la base de données suivante :
| Transaction |   |   |   |   |   |
|-------------|---|---|---|---|---|
| t1          | A |   | C | D |   |
| t2          |   | B | C |   | E |
| t3          | A | B | C |   | E |
| t4          |   | B |   |   | E |
| t5          | A | B | C |   | E |
| t6          |   | B | C |   | E |

### Question 1.

1. Itemsets fréquents pour $α = 3$ de taille 1 :

| Itemset | Freq (absolue) | Support | Frequent ? |
|---------|-----------------|---------|---|
| A       | 3               | $\{t1, t3, t5\}$ | Oui |
| B       | 5               | $\{t2, t3, t4, t5, t6\}$ | Oui |
| C       | 5               | $\{t1, t2, t3, t5, t6\}$ | Oui |
| D       | 1               | $\{t1\}$ | Non |
| E       | 5               | $\{t2, t3, t4, t5, t6\}$ | Oui |

1. Etage 2, on rajoute A, B, C ou E aux résultats précédents :

| Itemset | Freq (absolue) | Support | Frequent ? |
|---------|-----------------|---------|---|
| AB      | 2               | $\{t3, t5\}$ | Non |
| AC      | 3               | $\{t1, t3, t5\}$ | Oui |
| AE      | 2               | $\{t3, t5\}$ | Non |
| BA      | 2               | $\{t3, t5\}$ | Non |
| BC      | 4               | $\{t2, t3, t5, t6\}$ | Oui |
| BE      | 5               | $\{t2, t3, t4, t5, t6\}$ | Oui |
| CA      | 3               | $\{t1, t3, t5\}$ | Oui |
| CB      | 4               | $\{t2, t3, t5, t6\}$ | Oui |
| CE      | 4               | $\{t2, t3, t5, t6\}$ | Oui |
| EA      | 2               | $\{t3, t5\}$ | Non |
| EB      | 5               | $\{t2, t3, t4, t5, t6\}$ | Oui |
| EC      | 4               | $\{t2, t3, t5, t6\}$ | Oui |

On a donc $\{ AC, BC, BE, CA, CB, CE, EB, EC \}$

3. On recommence et on obtient (au niveau 3) : 
   $\{BCE, BEC,  CBE, CEB, EBC, ECB\}$ (tous de frequence 3)

Au niveau 4 on s'arrète parce qu'aucune des possibilité n'est fréquente
### Question 2.

Même chose mais avec ordre lexicographique, et donc on évite les doublons : 

1. Etape 1 : idem
2. Etape 2 :
   
| Itemset | Freq (absolue) | Support | Frequent ? |
|---------|-----------------|---------|---|
| AB      | 2               | $\{t3, t5\}$ | Non |
| AC      | 3               | $\{t1, t3, t5\}$ | Oui |
| AE      | 2               | $\{t3, t5\}$ | Non |
| BC      | 4               | $\{t2, t3, t5, t6\}$ | Oui |
| BE      | 5               | $\{t2, t3, t4, t5, t6\}$ | Oui |
| CE      | 4               | $\{t2, t3, t5, t6\}$ | Oui |

On a $\{AC, BC, BE, CE\}$

3. Etape 3 : 

On réitère et on obtient 

$\{BCE\}$

Qu'on ne peut plus étendre au niveau 4 avec l'ordre lexicographique

### Question 3.

<!-- Très étrangement, en appliquant Apriori avec child et un ordre lexicographique, on a un calcul plus lent ? Cela peut sans doute s'expliquer grace aux HashSet de la version "classique" à chaque étape qui éliminent les candidats doublons -->

Contrairement à ce qu'on pouvait attendre, ici, avec mon implémentation, Apriori sans ordre lexicographique est plus rapide (en temps) même avec de gros jeux de données et un grand $\alpha$ (par exemple, mushroom, avec $\alpha=0.5$).

On peut imaginer que la version "ordre lexicographique" a un trop gros surcout sur les petits itemsets, ce qui pourrait expliquer ce resultat.

Si on revient au cours, on se rend compte que l'interet de la modification se trouve surtout sur les **grands** itemset (génération des enfants dépendante de k la taille de l'itemset). 
Ainsi, pour des grandes valeurs de frequence minimum, ça n'est pas très interessant puisqu'on limite la possibilité d'atteindre ces "grands" itemsets.

En faisant quelques tests rapides, j'ai pu voir (en temps) que :
- Pour $\alpha = 0.5$ on a $3 \times AprioriLex \approx Apriori$ 
- Pour $\alpha = 0.25$ on a $2 \times AprioriLex \approx Apriori$ 
- Pour $\alpha = 0.15$ on a $1.3 \times AprioriLex \approx Apriori$ (l'ordre de grandeur de la durée d'execution ici sur mushroom est autour de 5min chacun)

Ce qui tend à confirmer mon hypothèse sur l'observation de ce resultat

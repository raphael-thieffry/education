# TD2

## Exercice 1
### Question 1

On a $M_\alpha = \{ABC^3, DE^3, EF^5\}$

Ces itemsets constituent la frontière entre les frequents et les nons frequents. Pour lister les frequents, il suffit donc de lister les sous-itemsets de ces itemsets. On trouve alors $\{A, B, C, D, E, F, AB, AC, BC, DE, EF, ABC\}$

Avec ce nouvel ensemble d'itemsets fermés ($C_\alpha = \{ABC^3, ABE^3, DE^3, EF^5\}$), on trouve les itemsets fréquents suivants : 
$\{A, B, C, D, E, F, AB, AC, BC, AE, BE, DE, EF, ABC, ABE\}$ (les sous itemsets d'un fermé frequent sont aussi fréquents).

### Question 2

On sait que les itemsets maximaux sont inclus dans les intemsets frequents fermés, donc on va juste calculer les fermés et regarder lesquels sont maximaux.

Si on fait LCM rapidement, on trouve :

<!-- - $closure(\empty)$ => $\empty$
- $closure(A)$ (frequent) => $AC = closure(AC)$
- $closure(B)$ (frequent) => $closure(BC) = BCE$, $closure(BE) = BE$ 
- $closure(C)$ (frequent) => $closure(C) = C$ 
- $closure(E)$ (frequent) => (aucun item à mettre ensuite dans l'ordre lexicographique)
  
- $closure(AC\_)$ 
  - $ACD$ (infrequent, on passe)
  - $ACE$ (infrequent, on passe)
- $closure(BE\_)$ => (aucun item à mettre ensuite dans l'ordre lexicographique)
- $closure(C\_)$
  - $CD$ (infrequent, on passe)
  - $CE$ (infrequent, on passe)
- $closure(BCE\_)$
  - aucun itemset avec ce prefixe n'est fréquent -->

- closure(∅) => ∅

- A (fréquent) => closure(A) = AC  (donc closure(AC) = AC)
  - AC_
    - ACD  — non fréquent, on passe
    - ACE  — non fréquent, on passe
    (fin de la récursion pour AC)

- B (fréquent) => closure(B) = B
  - BC (fréquent) => closure(BC) = BCE
    - BCE_
      (aucun itemset fréquent avec ce préfixe)
    (fin de la récursion pour BC -> BCE)
  - BD (non fréquent)
  - BE (fréquent) => closure(BE) = BE
    - BE_
      (aucun item à ajouter ensuite dans l’ordre lexicographique)
    (fin de la récursion pour BE)

- C (fréquent) => closure(C) = C
  - C_
    - CD  — non fréquent, on passe
    - CE (fréquent) => closure(CE) = BCE
    (fin de la récursion pour C)

- D (non fréquent)

- E (fréquent) => closure(E) = E
  (aucun item à ajouter ensuite dans l’ordre lexicographique ; fin de la récursion)

Donc, on a $\{AC, BE, C, BEC\}$

Puisque les maximaux sont ceux où la frequence des sur-ensembles est inférieure au seuil, on trouve que les itemsets maximaux sont $\{AC, BEC\}$


## Exercice 2
### Question 3

En faisant pareil que precedement, mais de façon plus claire : 

- $closure(\empty)$ => $\empty$
  - $A$ (frequent) => $closure(A) = A$
    - $AB$ (frequent) => $closure(AB) = AB$
      - $ABC$ (infrequent, on passe)
      - $ABD$ (infrequent, on passe)
      - $ABE$ (infrequent, on passe)
      - $ABF$ (frequent) => $closure(ABF) = ABF$
        - (fin de recursion)
    - $AC$ (frequent) => $closure(AC) = AC$
      - $ACD$ (infrequent, on passe)
      - $ACE$ (infrequent, on passe)
      - $ACF$ (infrequent, on passe)
    - $AD$ (infrequent, on passe)
    - $AE$ (frequent) => $closure(AE) = AE$
      - $AEF$ (infrequent, on passe)
    - $AF$ (frequent) => $closure(AF) = AF$ 
      - (fin de recursion)
  - $B$ (frequent) => $closure(B) = B$
    - $BC$ (frequent) => $closure(BC) = BC$
      - $BCD$ (infrequent, on passe)
      - $BCE$ (infrequent, on passe)
      - $BCF$ (infrequent, on passe)
    - $BD$ (infrequent, on passe) 
    - $BE$ (infrequent, on passe)
    - $BF$ (frequent) => $closure(BF) = ABF$
      - (fin de recursion)
  - $C$ (frequent) => $closure(C) = C$
    - $CD$ (infrequent, on passe)
    - $CE$ (frequent) => $closure(CE) = CE$
      - $CEF$ (infrequent, on passe)
    - $CF$ (infrequent, on passe) 
  - $D$ (frequent) => $closure(D) = D$
    - $DE$ (infrequent, on passe)
    - $DF$ (infrequent, on passe)
  - $E$ (frequent) => $closure(E) = E$
    - $EF$ (infrequent, on passe)
  - $F$ (frequent) => $closure(F) = F$
    - (fin de recursion)

On conclue en voyant que les fermés sont :
$\{A, AB, AF, ABF, AC, AE, B, BC, C, CE, D, E, F\}$
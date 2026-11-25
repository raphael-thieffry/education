# Rapport Raphaël Thieffry
### L'ensemble des cas de tests peut être restrouvé dans /src/test/test.java
## Swap 1
Je n'ai pas détecté de faute avec ma suite de tests
## Swap 2
Je n'ai pas non plus détecté de faute sur cette version avec ma suite
de tests
## Swap 3
Cette version a un problème : en effet, dans le cas d'un swap
qui a levé une erreur (un seul process), quand on la catch, l'état a changé alors que la spécification le précise bien :
_Cette opération lève une
exception ErreurSysteme s'il n'existe aucun processus en attente de la ressource et **laisse l'état
inchangé.**_
On se retrouve donc sans processus actif.
## Swap 4
Cette version ne passe pas non plus les tests :
- Comme la version 3, swap change l'état après une erreur (waiting list non-vide dans le cas d'un seul process).
- Ceci fait fail un autre de mes test, car,
en effet, dans ce cadre là, si on swap 2x en catchant l'erreur,
le deuxieme swap ne leve pas d'erreur, la liste d'attente n'étant pas vide.
## Swap 5
Le problème qui se dégage de cette version semble être l'operateur d'égalité utilisé dans
isCurrent(p). En effet, si on a :
```java
Systeme s = new Systeme();
Processus p = new Processus("p");
Processus pBis = new Processus("p");
s.init();
s.add(p);
```
Dans ce cas isCurrent(pBis) renverra false alors qu'il doit renvoyer true selon la spécification:
_Deux instances de
Processus de même nom désignent le même processus._

On s'en rend compte à travers mes asserts dans les cas de test de la fonction add, mais
également dans mon test paramétrique pour n processus où je n'ai aucune variable
représentant les processus utilisés, et où chaque instance est differente.

## Swap 6
Cette version passe mes tests.

## Swap 7
La raison de l'echec des tests est la même que pour le Swap 5

## Swap 8
Cette version ne leve pas d'erreur quand on swap un systeme vide (sans processus), ce qui est contraire à la spécification.

## Swap 9
Cette version leve une Runtime Exception plutot qu'une "Erreur Systeme", ce qui est incorrect par rapport à la description donnée:
```java
public void swap() throws ErreurSysteme;
```

## Swap 10
Cette version add les processus directement sur le current.

L'ancien current semble alors envoyé dans la waiting list, ce qui ne correspond pas à la spécification :
_S'il n'existe aucun
processus dans le système, p devient le processus courant qui détient la ressource, **sinon il est
ajouté à la liste des processus en attente.**_


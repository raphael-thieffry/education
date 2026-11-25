# Questions
## 1.
**Decision 1 :**
```java  
client.getDeliveryCountry().equalsIgnoreCase("france")
&& client.getDeliveryZipcode() / 1000 <= METROPOLITAN_ZIPCODE_LIMIT
```
Cette decision est composée de plusieurs conditions :
- client.getDeliveryCountry().equalsIgnoreCase("france")
- client.getDeliveryZipcode() / 1000 <= METROPOLITAN_ZIPCODE_LIMIT

**Decision 2 :**
```java
(client.hasPremiumAccount() && order.getValue() >= PREMIUM_DISCOUNT_MINIMUM)
|| order.hasSpecialShippingDiscount()
```
Même chose pour celle ci :
- client.hasPremiumAccount()
- order.getValue() >= PREMIUM_DISCOUNT_MINIMUM
- order.hasSpecialShippingDiscount()
## 2.
Pour tester les decisions il faut donc faire en sorte d'avoir chaque
decision à vrai ou faux dans chaque test.
On peut donc faire en sorte d'avoir vrai/faux et faux/vrai pour une couverture complete.
## 3.
Il faut tester chaque condition une à une. 
On peut prendre quelqu'un dans la situation suivante :
- France outre mer, tres gros zicode, Premium, grande valeur, special
Et quelqu'un dans une situation completement inverse de sorte que chaque condition
soit testée true/false

## 4./5. MC/DC
Decisions : loc | ta (local, tarif avantageux)  
Conditions : F | PZ | P | GV | SSD (France, petit zip, premium, grosse valeur, special shipping discount)

On a actuellement le tableau suivant (1) :

| F | PZ | P | GV | SSD | loc | ta | test     |
|---|----|---|----|-----|-----|----|----------|
| T | F  | T | T  | T   | F   | T  | bayrou   |
| T | T  | F | F  | F   | T   | F  | jeand    |
| F | T  | F | F  | F   | F   | F  | gunther  |
| F | T  | T | T  | T   | F   | T  | vladimir |

Ce qui pour la 1ere decision donne :

| F | PZ | loc |
|---|----|-----|
| T | F  | F   |
| T | T  | T   |
| F | T  | F   |
| F | T  | F   |

On répond bien à MC/DC ici :  
Pour F, les lignes 2 et 3 montre son influence  
Pour PZ, les lignes 1 et 2 le montre

Pour la 2eme decision on a :

| P  | GV | SSD | ta |
|----|----|-----|----|
 | T  | T  | T   | T  |
 | F  | F  | F   | F  |
 | F  | F  | F   | F  |
 | T  | T  | T   | T  |
Ici on ne répond pas du tout à MC/DC et il faut rajouter des tests :  
(FFT), (TFT), (FTT) pour pouvoir montrer l'influence.

Après avoir rajouté ces 3 tests on voit que :

| P | GV | SSD | ta | nomtest |
|---|----|-----|----|---------|
| T | T  | T   | T  | -       |
| F | F  | F   | F  | -       |
| F | F  | F   | F  | -       |
| T | T  | T   | T  | -       |
| F | F  | T   | T  | mcdc1   |
| T | F  | T   | F  | mcdc2   |
| F | T  | T   | F  | mcdc3   |

P est influent via les lignes 7 et 1  
GV est influent via les lignes 6 et 1  
SSD via les lignes 5 et 2  

## 6.
Chemins : des combinaisons de branches au final. CAD que du du coup,
on veut les 4 combinaisons de sorties de decision.  
Avec mes 4 premiers Tests du tableau (1), on voit que toutes les combinaisons sont gérées sauf True True.  
Il me faut donc quelqu'un de france métropolitaine qui soit rentré dans le deuxieme if.
Dans le cadre de la question précédente, le cas de test mcdc3 avec jeand remplit cette fonction.

Tous les chemins sont donc couverts.
## 7.

Pour recapituler, les 4 tests bayrou, jeand, gunther et mcdc3 couvrent tous les chemins.
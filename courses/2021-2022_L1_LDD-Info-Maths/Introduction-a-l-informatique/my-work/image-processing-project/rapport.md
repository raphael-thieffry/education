---
jupytext:
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
    jupytext_version: 1.11.5
kernelspec:
  display_name: C++17
  language: C++17
  name: xcpp17
---

# Rapport de projet

+++

## Auteurs

- Thieffry Raphaël, raphael.thieffry@universite-paris-saclay.fr, LDDIM2
- Wendels Jeremy, jeremy.wendels@universite-paris-saclay.fr, LDDIM2

+++

## Résumé du travail effectué

- Partie 2: réalisée, documentée testée (creation d'une fonction split() par Jeremy pour la gestion des lignes de getline() + gestion de tous les commentaires -> partie 2,3,6)
- Partie 3: réalisée, documentée testée 
- Partie 4: réalisée, documentée testée (hors 4.8, fonction de lissage faite à part)
- Partie 5: réalisée, documentée testée (gros problème d'execution TIN, jeremy a reussi à le faire fonctionner) 
- Partie 6: réalisée, documentée testée 
- Partie 7: réalisée, documentée testée (sauf sfml, grosses difficultées pour l'installer, et une fois installée, fait conflit avec le type "Image")

+++

## Démonstration

```{code-cell}
! make all
```

Ici, on montre que [TIN](TIN.cpp) fonctionne :

```{code-cell}
! ./TIN -e -c images/Billes.256.pgm -o TIN_img/seuilBille.pgm
```

Par ailleurs tous les tests fonctionnent et produisent des images :

```{code-cell}
! ./superpixel-test
```

```{code-cell}
! ./pgm-test
```

```{code-cell}
! ./ppm-test
```

```{code-cell}
! ./seuillage-test
```

```{code-cell}
! ./sobel-test
```

```{code-cell}
! ./gris-couleurs-test
```

Après avoir tout executé, on peut verifier que les images à notre disposition dans les dossiers associés (superpixel, seuillage, doubleseuillage, sobel, pgm et ppm) repondent bien à ce qu'on attendait de nos fonctions. Les images notables sont celles produites par superpixel-test, avec le contour bleu.

Ici nous pouvons voir comment fonctionne notre gestion des [commentaires](pgm-tout-en-un.cpp) : (voir [brain.pgm](images/brain.pgm) )

```{code-cell}
! info-111 g++ pgm-tout-en-un.cpp -o pgm-tout-en-un
```

```{code-cell}
! ./pgm-tout-en-un
```

Ainsi nous avons réussi à passer les commentaires lors de la lecture de chaque image. Maintenant, nous pouvons nous attarder sur la maniere dont nous avons géré les bords bleus des [superpixels](superpixel.cpp).

+++

## Organisation du travail


Nous nous sommes réparti les questions de telle sorte que je (Raphaël) prenais les questions paires et m'occupais du rapport, et Jeremy les questions impaires, et s'occupait des bugs de dernière minute.

Au debut nous avions pensé à travailler avec un dossier partagé, au travers d'un ftp, mais ça s'est vite presenté comme ingérable. Alors nous avons commencé à travailler chacun un peu de notre coté. Cependant, la question 5 étant indispensable pour faire les suivantes, et la commande make inaccessible sur windows, cela nous a fait changer d'organisation.
    
Jeremy a un mac, et avec une extension de VisualStudio Code appelée live-share, nous avons pu travailler en meme temps sur les memes fichiers, en me permettant au passage d'utiliser la commande make grace a un terminal partagé. Ainsi, puisque nous ne pouvions pas nous voir le week-end pour travailler, nous avons néanmoins pu avancer à distance.

Enfin, nous avons eu l'aide de Nathan Smets, qui avait deja un projet fonctionnel au moment où nous avons commencé la derniere question, ce qui nous a grandement aidé a mettre en place des tests.
En effet, pour la question 7.2, les seuls tests dans le fichier "superpixel-test" concernent la toute dernière fonction, laquelle depend des deux precedentes. Nous avons eu un bug, et pour l'identifier parmis ces 3 fonctions, cela aurait difficile sans son aide. Nous ne nous somme néanmoins pas inspiré de son travail, et nous sommes contenté d'intervertir fonction apres fonction pour voir d'où venait le problème.

Nous avons chacun autour de 20 heures de travail

+++

## Prise de recul


Raphael:
En ce qui me concerne, j'entamerais le projet non pas sur Windows, qui est relativement invivable face à un projet comme celui là, mais plutot sur Ubuntu que j'ai en dual boot sur mon ordinateur, mais que je n'ai pas pris le temps de configurer correctement jusqu'a maintenant pour bien m'en servir. Par ailleurs je pense que nous sommes d'accord pour commencer à nous interesser à l'outil git pour l'organisation.
Ceci dit, ce projet m'a fait decouvrir l'algorithme des K-moyennes, qui, puisque decrit de maniere vague dans le sujet, m'a fait chercher sur internet et decouvrir quelques unes des possibilités d'utilisation de ce dernier. J'aime beaucoup le fait d'économiser la charge de données à manipuler de cette manière et je me renseignerai pendant les vacances.

Jeremy:
On a rencontré des conflits dans les imports. J'ai appris à mieux optimiser les imports (comme std par exemple). L'import de sfml s'est mal passé, avec des conflits dus à la repetition du type Image et d'un module inclus dans sfml nommé egalement Image. Et meme en modifiant le nom du type, une autre erreur survient a cause du "namesapce sf" de sfml.


Pour conclure, disons simplement que corriger des bugs imprévus inclus depuis le départ dans le fichier TIN.cpp la veille de la soutenance fut une belle épreuve

```{code-cell}

```

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

# Exercice 4 du TD

```{code-cell}
#include <cstdio>
int monnaie(int prix, int somme,int reste50,int reste20,int reste10,int reste5){
    int du = somme-prix;
    int npieces50 = du/50;
    while(npieces50 > reste50){
        npieces50 = npieces50-1;
    }
    int du2 = du-(npieces50*50);
    int npieces20 = du2/20;
    while(npieces20 > reste20){
        npieces20 = npieces20-1;
    }
    int du3 = du2-(npieces20*20);
    int npieces10 = du3/10;
    while(npieces10 > reste10){
        npieces10 = npieces10-1;
    }
    int du4 = du3-(npieces10*10);
    int npieces5 = du4/5;
    if(npieces5 > reste5){
        printf("Il n'y a plus assez de monnaie");
    }else{
        printf("%d", npieces50);
        printf("\n");
        printf("%d", npieces20);
        printf("\n");
        printf("%d", npieces10);
        printf("\n");
        printf("%d", npieces5);
    }
    return 0;
}
```

```{code-cell}
monnaie(110,200,0,0,0,25)
```

```{code-cell}

```

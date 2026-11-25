#include<stdio.h>
#include<stdlib.h>
#include"rarray.h"

RArray init(int c) {
  RArray res;
  int *t = malloc(sizeof(int) * c);
  res.tab = t;
  res.nb = c;
  res.cap = c;
  return res;
}

int size(RArray r) {
  return r.nb;
}

int get(RArray r, int ind) {
  if(0 <= ind && ind < r.nb) {
    return r.tab[ind];
  }
  return 0;
}

void clear(RArray *r) {
  for(int i = 0; i < r->nb; i++) {
    r->tab[i] = 0;
  }
}

int contains(RArray r, int val) {
  for(int i = 0; i < r.cap; i++) {
    if(r.tab[i] == val) {
      return 1;
    }
  }
  return 0;
}

int indexR(RArray r, int val) {
  for(int i = 0; i < r.nb; i++) {
    if(r.tab[i] == val) {
      return i;
    }
  }
  return -1;
}

void resize(RArray *r) {
  r->cap = r->cap * 2;
  int *t = malloc(sizeof(int) * r->cap);
  for(int i = 0; i < r->nb; i++) {
    t[i] = r->tab[i];
  }
}

void add(RArray *r, int val) {
  if(r->nb >= r->cap) {
    resize(r);
  }
  r->tab[r->nb] = val;
  r->nb++;
}

int removeInd(RArray *r, int ind) {
  if(0 <= ind && ind < r->nb) {
    int res = r->tab[ind];
    for(int i = ind; i < r->nb - 1; i++) {
      r->tab[i] = r->tab[i+1];
    }
    r->nb = r->nb - 1;
    return res;
  }
  return 0;
}

void afficher(RArray r) {
  printf("tab = [");
  for(int i = 0; i < r.cap; i++) {
    printf("%d ", r.tab[i]);
  }
  printf("] nb = %d ", r.nb);
  printf("cap = %d\n", r.cap);
}

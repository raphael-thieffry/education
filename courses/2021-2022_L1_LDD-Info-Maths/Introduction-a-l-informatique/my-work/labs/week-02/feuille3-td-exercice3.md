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

# Exercice 3 du TD

+++ {"deletable": false, "editable": false, "nbgrader": {"cell_type": "markdown", "checksum": "2e57e78059192b39c2b74eb955f04d95", "grade": false, "grade_id": "cell-1b21180343eef5af", "locked": true, "schema_version": 3, "solution": false}}

Consultez l'énoncé de TD et faites ici l'exercice 3 du TD (vous aurez besoin d'ajouter de nouvelles cellules). Pour ceux qui ont déjà vu cet exercice en TD, essayez de le refaire par vous-même sans consulter ce que vous avez fait en TD.

```{code-cell}
double max2(double a, double b) {
    if ( a < b ) {
        return b; 
    } else {
        return a;
    }
}
```

```{code-cell}
double max3(double d, double e,double f) {
    return max2(d, max2(e,f));
}
```

```{code-cell}
double moy(double m1, double m2, double m3, double p1, double p2){
    return max3(m1,m2,m3)*(3./5)+max2(p1,p2)*(2./5);
}
```

```{code-cell}

```

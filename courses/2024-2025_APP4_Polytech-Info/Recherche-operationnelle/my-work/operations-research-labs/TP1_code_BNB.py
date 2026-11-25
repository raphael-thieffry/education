import numpy as np
from scipy.optimize import linprog
""" 
    TP noté Recherche operationnelle
    Raphaël THIEFFRY
    Polytech APP4, 2024-2025
"""
def branch(x,bounds,tol):
    i = (np.abs(x - np.round(x)) < tol).argmin()    #ici on récupère une coordonnée qui n'est pas entiere (tableau de boolean, on en prend un == à 0)
    f = np.floor(x[i])                              #on la floor
    bounds1 = [z for z in bounds]                   #on copie bounds
    bounds1[i] = (bounds1[i][0], f)                 #on y remplace la contrainte sur i par une contrainte que x[i] doit être plus petit que f
    bounds2 = [z for z in bounds]                   #idem
    bounds2[i] = (f+1,bounds2[i][1])                #idem mais l'inverse  
    return bounds1, bounds2                         #nouvelles contraintes pour la recursion

def BnB(S,c,A_ub,b_ub,bounds,tol=1e-8,x=None,fun=np.inf):
    if S.success:
        if S.fun >= fun:
            return x, fun                                    #Cas j'ai pas de solution mieux, je renvoie x, fun ?
        if (np.abs(S.x - np.round(S.x)) < tol).all():        #Si c'est tous des entiers (et que je suis pas rentré au dessus)
            return S.x, S.fun                                #cas d'arret, on remonte la solution temporaire
        bounds1, bounds2 = branch(S.x,bounds,tol)
        S1 = linprog(c,A_ub=A_ub,b_ub=b_ub,bounds=bounds1)
        S2 = linprog(c,A_ub=A_ub,b_ub=b_ub,bounds=bounds2)
        x1, fun1 = BnB(S1,c,A_ub,b_ub,bounds1,x=x,fun=fun)
        x2, fun2 = BnB(S2,c,A_ub,b_ub,bounds2,x=x1,fun=fun1) #On met à jour le best croisé jusque là dans la rec
        return x2, fun2                                      #best entre moi et mes enfants
    return x, fun #Si j'ai rien je renvoie le meilleur que j'ai eu jusque là

print("ex1-5")
print("     Détail en commentaires")

print("ex5/6")
c = np.array([1, 1, 1])
A_ub = np.array([
    [5, 2, 3],
    [2, 7, 5]
])
b_ub = np.array([42, 52])
bounds = [(0, None), (0, None), (0, None)]
S = linprog(-c, A_ub=A_ub, b_ub=b_ub, bounds=bounds)

print(BnB(S,-c,A_ub,b_ub,bounds,tol=1e-8,x=None,fun=np.inf))
Sin = linprog(-c, A_ub=A_ub, b_ub=b_ub, bounds=bounds, integrality=1)
print(Sin.x, Sin.fun)

print("     On a des solutions differentes qui minimisent la fonction objectif de la meme manière (-12) en respectant la matrice A")

print("ex7")

print("""      Il s'agit de choisir l'ordre de recursion bnb1/bnb2 en 
      fonction du resultat de S1.fun et S2.fun, et d'ignorer la 
      seconde branche sous certaines conditions""")

print("ex8 -> passe, voir fin")

print("Application : ")
print("     Détail en commentaires")
# On aura x=[nbnuc, nbgaz, nbsol, nbeol, 
#            nbactnucpri, nbactnucete, nbactnucaut, nbactnuchiv,
#            nbactgazpri, nbactgazete, nbactgazaut, nbactgazhiv,
#            nbactsolpri, nbactsolete, nbactsolaut, nbactsolhiv,
#            nbacteolpri, nbacteolete, nbacteolaut, nbacteolhiv]
# Fonction objectif : c^Tx
prixsvariables = [100000]*8+[0]*8
c = np.array([4*900000, 4*100000, 4*2000, 4*400]+prixsvariables) # Prix annuel global, à minimiser (on prend en compte toutes les saisons)

Co2variable = [10000]*4+[1180000]*4+[0]*8
# Il faut lier les les activés au total de construits
# nbactmodesaison <= nbmode <=> nbactmodesaison-nbmode <= 0 \forall saison, mode
activations = [
    ([-1]+3*[0]) + ([1, 0, 0, 0]) + [0] * 12,
    ([-1]+3*[0]) + ([0, 1, 0, 0]) + [0] * 12,
    ([-1]+3*[0]) + ([0, 0, 1, 0]) + [0] * 12,
    ([-1]+3*[0]) + ([0, 0, 0, 1]) + [0] * 12,
    ([0, -1, 0, 0]) + 4*[0] + ([1, 0, 0, 0]) + [0] * 8,
    ([0, -1, 0, 0]) + 4*[0] + ([0, 1, 0, 0]) + [0] * 8,
    ([0, -1, 0, 0]) + 4*[0] + ([0, 0, 1, 0]) + [0] * 8,
    ([0, -1, 0, 0]) + 4*[0] + ([0, 0, 0, 1]) + [0] * 8,
    ([0, 0, -1, 0]) + 8*[0] + ([1, 0, 0, 0]) + [0] * 4,
    ([0, 0, -1, 0]) + 8*[0] + ([0, 1, 0, 0]) + [0] * 4,
    ([0, 0, -1, 0]) + 8*[0] + ([0, 0, 1, 0]) + [0] * 4,
    ([0, 0, -1, 0]) + 8*[0] + ([0, 0, 0, 1]) + [0] * 4,
    ([0, 0, 0, -1]) + 12*[0] + ([1, 0, 0, 0]),
    ([0, 0, 0, -1]) + 12*[0] + ([0, 1, 0, 0]),
    ([0, 0, 0, -1]) + 12*[0] + ([0, 0, 1, 0]),
    ([0, 0, 0, -1]) + 12*[0] + ([0, 0, 0, 1])
]
A = np.array([ 
    [0]*4+([-10000]+[0]*3)+([-2400]+[0]*3)+([-40]+[0]*3)+([-8]+[0]*3),  # printemps - la production saisoniere minimale par saison en fonction des usine activés
    [0]*5+([-10000]+[0]*3)+([-2400]+[0]*3)+([-50]+[0]*3)+([-8]+[0]*2),  # ete (on ajoute des 0 à gauche pour decaler les saisons)
    [0]*6+([-10000]+[0]*3)+([-2400]+[0]*3)+([-38]+[0]*3)+([-8]+[0]*1),  # automne
    [0]*7+([-10000]+[0]*3)+([-2400]+[0]*3)+([-32]+[0]*3)+([-8]),        # hiver
    [70000, 20000, 80, 48]+Co2variable          #Co2 trimestriel max
]+activations)
#print("A : ", A)
b = np.array([
    -110000, #production saisonière minimale par saison
    -90000, 
    -120000, 
    -150000,
    30000000 #Co2 max par an (on compte les activés sur l'année)
    ]+[0]*16)
# A<=b pour nous ici, donc A_ub

#contraintes/bounds
bounds = [(0, 8), (0, None), (0, 500), (0, 2000)]+[(0, None)]*16 #impact social + activé/desactivé

print(BnB(S,c,A,b,bounds))
Sin = linprog(c, A_ub=A, b_ub=b, bounds=bounds, integrality=1)
print(Sin.x, Sin.fun)
#print(A@Sin.x)

print("ex8")

def BnB2(S,c,A_ub,b_ub,bounds,tol=1e-8,x=None,fun=np.inf):
    # print("rec", S.x, S.fun)
    if S.success:
        if S.fun >= fun:
            # print("Pas la bonne voie ici S.fun >= fun")
            return x, fun                                    #Cas j'ai pas de solution, je renvoie x, fun ?
        if (np.abs(S.x - np.round(S.x)) < tol).all():        #Si c'est tous des entiers
            return S.x, S.fun                                #cas d'arret, on remonte
        bounds1, bounds2 = branch(S.x,bounds,tol)

        S1 = linprog(c,A_ub=A_ub,b_ub=b_ub,bounds=bounds1)
        S2 = linprog(c,A_ub=A_ub,b_ub=b_ub,bounds=bounds2)
        # print("bounds1 : ", bounds1)
        #print("S1 : ", S1.x, S1.fun)
        # print("bounds2 : ", bounds2)
        #print("S2 : ", S2.x, S2.fun)
        res = (None, np.inf)
        if((S1.fun is not None) and (S2.fun is None or S1.fun < S2.fun)):
            res = BnB2(S1,c,A_ub,b_ub,bounds1,x=x,fun=fun)
            if((S2.fun is not None and res[1] is not None) and res[1] > S2.fun): # on poursuit si on peut trouver mieux dans la seconde branche
                return BnB2(S2,c,A_ub,b_ub,bounds2,x=res[0],fun=res[1])
        else: 
            res = BnB2(S1,c,A_ub,b_ub,bounds1,x=x,fun=fun)
            if((S1.fun is not None and res[1] is not None) and res[1] > S1.fun): # idem
                return BnB2(S1,c,A_ub,b_ub,bounds2,x=res[0],fun=res[1]) 

        # print("1 : ", x1, fun1)
        # print("2 : ", x2, fun2)
        return res
    #print("failure")
    return x, fun #Si j'ai rien je renvoie le meilleur que j'ai eu jusque là
print("     test BnB2 avec l'ex5")
c = np.array([1, 1, 1])
A_ub = np.array([
    [5, 2, 3],
    [2, 7, 5]
])
b_ub = np.array([42, 52])
bounds = [(0, None), (0, None), (0, None)]
S = linprog(-c, A_ub=A_ub, b_ub=b_ub, bounds=bounds)

print(BnB2(S,-c,A_ub,b_ub,bounds,tol=1e-8,x=None,fun=np.inf))
Sin = linprog(-c, A_ub=A_ub, b_ub=b_ub, bounds=bounds, integrality=1)
print(Sin.x, Sin.fun)
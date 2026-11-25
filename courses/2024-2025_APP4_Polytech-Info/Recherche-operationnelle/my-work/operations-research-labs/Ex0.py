import numpy as np
from scipy.optimize import linprog

c = np.array([1,2,3])
A_ub = np.array([[-1,2,-1],[1,2,3]])
b_ub = np.array([-5,30])
bounds = [(1,4),(2,5),(3,6)]

print("Forme initiale")
print(linprog(c,A_ub=A_ub,b_ub=b_ub,bounds=bounds,method='highs-ds'))

A_ub = np.concatenate((A_ub,np.identity(3),-np.identity(3)))
b_ub = np.concatenate((b_ub,np.array([4,5,6,-1,-2,-3])))

print("\nForme canonique")
print(linprog(c,A_ub=A_ub,b_ub=b_ub))

c = np.concatenate((c,np.zeros(8)))
A_eq = np.concatenate((A_ub,np.identity(8)),axis=1)
b_eq = b_ub

print("\nForme standard")
print(linprog(c,A_eq=A_eq,b_eq=b_eq))

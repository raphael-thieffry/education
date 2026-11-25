import numpy as np
from scipy.optimize import linprog

c = np.array([15,8])
A_ub = np.array([[1,1]])
b_ub = np.array([80])
bounds = [(30,80),(10,30)]

print(linprog(-c,A_ub=A_ub,b_ub=b_ub,bounds=bounds))
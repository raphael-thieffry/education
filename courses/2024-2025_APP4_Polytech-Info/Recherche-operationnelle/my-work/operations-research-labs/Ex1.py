import numpy as np
from scipy.optimize import linprog

c = np.array([66,84])
A_ub = np.array([[3,4],[1,3],[2,2]])
b_ub = np.array([4200,2250,2600])
bounds = [(0,1100),(0,None)]

print(linprog(-c,A_ub=A_ub,b_ub=b_ub,bounds=bounds))
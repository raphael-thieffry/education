import numpy as np
from scipy.optimize import linprog

#Question 2
c = np.array([120]*3+[-50,-60])
A_ub = np.array([[3,4,1,-3,-2],[5,2,2,-2,-3],[2,3,5,-3,-3]])
b_ub = np.zeros(3)
bounds = [(0,100),(0,100),(0,200),(0,None),(0,None)]

print(linprog(-c,A_ub=A_ub,b_ub=b_ub,bounds=bounds))

#Question 5
c = np.array([50,60])
A_ub = np.array([[-3,-2],[-2,-3],[-3,-3]])
b_ub = np.array([-900,-1100,-1500])

print(linprog(c,A_ub=A_ub,b_ub=b_ub))

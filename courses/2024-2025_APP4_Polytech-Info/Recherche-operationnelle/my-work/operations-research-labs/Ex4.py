import numpy as np
from scipy.optimize import linprog

M = np.ones((1,10))

P = np.array([[0]+[1]*5+[0]*4])
R = np.array([[0]*6+[1]*2+[0]*2])

A1 = np.zeros((1,10))
A1[0,3] = 1
A1[0,2] = -1
A2 = np.zeros((1,10))
A2[0,2] = 1
A2[0,1] = -1
A3 = np.zeros((1,10))
A3[0,5] = 1
A3[0,4] = -1

B = np.zeros((1,10))
B[0,1] = 1
B[0,3] = -2

C = np.array([[0]+[2]*5+[0]*2+[-1,0]])

D = np.zeros((1,10))
D[0,6] = 2
D[0,7] = -3

A_ub = np.concatenate((M,P,-P,R,-R,A1,A2,A3,B,C))
b_ub = 100*np.array([50,15,-3,20,-5]+[0]*5)

A_eq = D
b_eq = np.array([0])

c = 0.001*np.array([2]+[3]*5+[4]*2+[5,1])

bounds = [(200,1000)]+[(0,1500)]*5+[(0,2000)]*2+[(600,3000)]+[(300,600)]

print(linprog(-c,A_ub=A_ub,b_ub=b_ub,A_eq=A_eq,b_eq=b_eq,bounds=bounds))
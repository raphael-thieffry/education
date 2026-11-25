from itertools import count
from labyrinthe import labyrinthe
import enumeration as en
# C = createlaby(int(input("largeur")), int(input("hauteur")))
# C.adjacence()
# print(C)
# for k, v in C.D.items():
# 	print(f"{k} : {v}")

# L = createlaby(2, 2)
# #L.add_droite
# PL = labyrinthe(2, 2).pseudo()
# print(L)
# # L.adjacence()
# # for k, v in L.D.items():
# # 	print(f"{k} : {v}")
# print("L : ", L.estLaby())
# print("PL : ", PL.estLaby())

# n = 4
# m = 4
# i = 0
# List = [labyrinthe(m, n, full=True)]
# while i < 100000:
# 	L = createlaby(n, m)
# 	if L not in List:
# 		print(L)
# 		List.append(L)
# 	i += 1

# L = createlaby(15, 15)
# print(L)
# print(L.estLaby())
# L.base[4][0].add_bas()
# print(L)
# print(L.estLaby())

L = labyrinthe(4, 4)
L.to_png("L")
L1 = L.copy()
L.base[0][1].add_bas()
L.base[0][1].add_droite()
print(L)
print(L1)
print("----------------\n")
L = labyrinthe(4, 4).generate()
L.to_png("L1")
print(L)
print(L.estLaby())
print("----------------\n")
L2 = en.allLaby(3,3)
print(len(L2))
for laby in L2:
    print(laby)
print("----------------\n")
print(L)
print(en.countVraiLaby(5,5))
print("----------------\n")
tab = en.allPseudos(2,2)
print(len(tab))
print(en.countVraiLaby(5,5))

a=en.allBoolean(2,2)
print(a)


from labyrinthe import labyrinthe
import numpy as np
def permutUnique01(nb0,nb1)->list[list] :
	if(nb0 == 0):
		return [nb1*[1]]
	elif(nb1 == 0):
		return [nb0*[0]]
	else:
		startsW0 = permutUnique01(nb0-1,nb1)
		startsW0FR = []
		for l in startsW0:
			lcop = l +[]
			startsW0FR.append([0] + lcop)
		startsW1 = permutUnique01(nb0,nb1-1)
		startsW1FR = []
		for l in startsW1:
			lcop = l + []
			startsW1FR.append([1] + lcop)
		return startsW0FR + startsW1FR

def allLaby(m, n):
		nbNonMurs = n*m-1
		listPermut = permutUnique01(nbNonMurs,2*m*n-nbNonMurs)
		listLaby = []
		for p in listPermut:
			l = labyrinthe(m,n)
			l.fromBooleanArray(p,m,n)
			if(l.connexe()):
				listLaby.append(l)
		return listLaby

def countVraiLaby(n,m):
	l = labyrinthe(n,m) #vide
	lapl = l.matriceLaplace()
	a = np.delete(lapl, 0, axis=0)
	b = np.delete(a, 0, axis=1)
	return round(np.linalg.det(b))


def allBoolean(i, j):
    zero = 2*i*j
    r=0
    l =[]
    res= []
    cpt=0
    max = "1"*zero
    while  max!=r :
        l=[]
        r=f"{cpt:0>{zero}b}"
        for i in range(zero):
            l.append(int(r[i]))
        res.append(l)
        cpt+=1
    return res

def allPseudos(n,m):
	perm = allBoolean(n,m)
	res = []
	for e in perm:
		l = labyrinthe(n,m)
		l.fromBooleanArray(e,m,n)
		b = True
		for i in range(len(l.base)):
			if l.base[i][n-1].droite == False:
				b = False
		for i in range(len(l.base[0])):
			if l.base[m-1][i].bas == False:
				b = False
		if b :
			res.append(l)
	print(len(perm))
	return res

def countPseudos(n,m):
	return 2**((n-1)*(m-1)+(n-1)+(m-1))

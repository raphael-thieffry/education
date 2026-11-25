from case import case
from color import Color
from random import randint
from time import sleep
from os import system
import copy
import numpy as np
from IPython.display import Image, display




def coord(current, dir):
		if not (current[0] + dir[0] < 0 or current[1] + dir[1] < 0):
			return (current[0] + dir[0], current[1] + dir[1])
		else:
			return -1

class labyrinthe:
	def __init__(self, w, h, full=False):
		'''
		crée un pseudo labyrinthe vide
		'''
		self.w, self.h = w, h
		self.base = []
		self.start, self.end = (0, 0), (w, h)
		for y in range(1, h + 1):
			L = []
			if y == h:
				bas = True or full
			else:
				bas = False or full
			for x in range(1, w + 1):
				c = case(w, h, x, y, bas, False or full)
				if x == w:
					c.add_droite()
				L.append(c)
			self.base.append(L)
		self.adjacence()

	def full(self):
		'''
		met des murs sur chaque chase du labyrinthe courant
		'''
		for line in self.base:
			for c in line:
				c.add_droite()
				c.add_bas()
		return self

	def pseudo(self):
		'''
		crée un pseudo labyrinthe aléatoire
		'''
		D = {0: (False, False), 1: (True, False),
			 2: (False, True), 3: (True, True)}
		self.__init__(self.w, self.h)
		for ligne in self.base:
			for c in ligne:
				R = D[randint(0, 3)]
				if R[0]:
					c.add_droite()
				if R[1]:
					c.add_bas()
		return self

	def rm_case_above(self, coord):
		'''
		retire le mur separant la case courante (de coordonées coord) de la case au dessus
		'''
		x, y = coord
		if x < 0 or y < 0 or y > len(self.base) - 1 or x > len(self.base[0]) - 1:
			return self
		self.base[y - 1][x].rm_bas()
		return self

	def rm_case_below(self, coord):
		'''
		retire le mur separant la case courante (de coordonées coord) de la case au dessous
		'''
		x, y = coord
		if x < 0 or y < 0 or y > len(self.base) - 1 or x > len(self.base[0]) - 1:
			return self
		self.base[y][x].rm_bas()
		return self

	def rm_case_right(self, coord):
		'''
		retire le mur separant la case courante (de coordonées coord) de la case à droite
		'''
		x, y = coord
		if x < 0 or y < 0 or y > len(self.base) - 1 or x > len(self.base[0]) - 1:
			return self
		self.base[y][x].rm_droite()
		return self

	def rm_case_left(self, coord):
		'''
		retire le mur separant la case courante (de coordonées coord) de la case à gauche
		'''
		x, y = coord
		if x < 0 or y < 0 or y > len(self.base) - 1 or x > len(self.base[0]) - 1:
			return self
		self.base[y][x - 1].rm_droite()
		return self

	def nbBordures(self):
		'''
			Compte le nombre de murs dans un labyrinthe
		'''
		b = 0
		for ligne in self.base:
			for c in ligne:
				if c.bas == False:
					b += 1
				if c.droite == False:
					b += 1
		return b #SUPPOSE QUE LES BORDS DROITS ET BAS DU LABYRINTHE SOIENT CONSID2R2S COMME DES MURS

	def adjacence(self):
		"""
		Creer une liste d'adjacence à partir d'un labyrinthe

		--Créer par Johanne & Jérémy--
		"""
		self.adj = {}
		for ligne in self.base:
			for c in ligne:
				self.adj[c.x, c.y] = []

		for ligne in self.base:
			for c in ligne:
				x, y = (c.x, c.y)
				if not c.bas:
					self.adj[(x, y)].append((x, y + 1))
					self.adj[(x, y + 1)].append((x, y))
				if not c.droite:
					self.adj[(x, y)].append((x + 1, y))
					self.adj[(x + 1, y)].append((x, y))

	def resetVisited(self):
		'''
		Met toutes les cases du labyrinthe comme non visitées
		by raphael
		'''
		for l in self.base:
			for c in l:
				c.visited = False

	def getCase(self, coord):
		'''
		Donne la case correspondant à une certaine coordonée dans le labyrinthe
		by raphael
		'''
		return self.base[coord[1]][coord[0]]

	def cycle(self):
		'''return a boolean : True if the graph is cylcic, else false'''
		self.adjacence()
		for sommet in self.adj:
			visites = []
			# print(visites)
			pile = [sommet]
			while len(pile) > 0:
				s = pile.pop()
				if s in visites:
					return True
				visites.append(s)
				# print(visites)
				for voisin in self.adj[s]:
					# print("voisin : ",voisin)
					if voisin not in visites:
						pile.append(voisin)
		return False
	
	def connexe(self):
		'''
		True si le labyrinthe est connexe, false sinon
		'''
		self.resetVisited()
		pile = []
		visited = []
		x = randint(0, self.w-1)
		y = randint(0, self.h-1)
		current = (x, y)
		pile.append(current)
		caseCurrent = self.getCase(current)
		caseCurrent.visited = True
		visited.append(current)
		dir = [(0, 1), (0, -1), (1, 0), (-1, 0)]
		while len(pile) > 0:
			s = pile[-1]
			voisins = []
			for d in dir:  # 4 iterations, peu gourmand
				c = coord(s, d)
				if not (c == -1):
					if not (c[0] > len(self.base[0]) - 1 or c[1] > len(self.base) - 1):
						deplacPossible = True
						caseS = self.base[s[1]][s[0]]
						caseC = self.base[c[1]][c[0]]
						if d == (0,1):
							if caseS.bas == True : #mur en haut de c
								deplacPossible = False
						elif d == (0,-1):
							if caseC.bas == True : #mur en bas de c, en haut de s
								deplacPossible = False
						elif d == (1,0):
							if caseS.droite == True : #mur à gauche de c, à droite de s
								deplacPossible = False
						else:
							if caseC.droite == True : #mur à gauche de s, à droite de c
								deplacPossible = False
						if deplacPossible != False:
							if self.getCase(c).visited == False:
								voisins.append((coord(s, d), d))
			if len(voisins) != 0:
				ind = randint(0, len(voisins) - 1)
				d = voisins[ind][1]
				pile.append(voisins[ind][0])
				visited.append(voisins[ind][0])
				next = self.getCase(voisins[ind][0])
				next.visited = True
			else:
				pile.pop()
			# system("clear")
			# print(lab)
			# sleep(0.1)
		self.resetVisited()
		return len(visited)-((self.w)*(self.h)) == 0

	def estLaby(self):
		'''
		verifie si un pseudo labyrinthe est un vrai labyrinthe ou pas
		'''
		#self.adjacence()
		a = self.nbBordures()
		return self.connexe() and (a == (self.h*self.w)-1)

	def __repr__(self):
		'''
		Affiche le labyrinthe sous forme de listes de cases
		'''
		s = ""
		for t in self.base:
			s += str(t) + '\n'
		return s

	def __str__(self):
		'''
		Fonction d'affichage du labyrinte
		'''
		s = ""
		print(Color.red + (2 * self.w + 1)*'_' + Color.end)
		for t in self.base:
			s += Color.bold + Color.red + '|' + Color.end
			for c in t:
				s += str(c)
			s += '\n'
		return s

	def __eq__(self, other):
		'''
		verifie l'égalité de 2 labyrinthe
		'''
		if (self.w, self.h) == (other.w, other.h):
			for i in range(self.h):
				for j in range(self.w):
					if self.base[i][j] != other.base[i][j]:
						return False
			return True
		return False

	def __ne__(self, other):
		'''
		l'opposée de l'égalité
		'''
		return not self == other

	def copy(self):
		'''
		crée une copie de labyrinthe
		'''
		return copy.deepcopy(self)
	
	def generate(self):
		'''
		génere un vrai labyrinthe avec l'algorithme de l'exploration exhaustive
		'''
		self.__init__(self.w, self.h, full=True)
		pile = []
		visited = []
		x = randint(0, self.w-1)
		y = randint(0, self.h-1)
		current = (x, y)
		pile.append(current)
		visited.append(current)
		caseCurrent = self.getCase(current)
		caseCurrent.visited = True
		dir = [(0, 1), (0, -1), (1, 0), (-1, 0)]
		while len(pile) > 0:
			s = pile[-1]
			voisins = []
			for d in dir:  # 4 iterations, peu gourmand
				c = coord(s, d)
				if not (c == -1):
					if not (c[0] > len(self.base[0]) - 1 or c[1] > len(self.base) - 1):
						if self.getCase(c).visited == False:
							voisins.append((coord(s, d), d))
			if len(voisins) != 0:
				ind = randint(0, len(voisins) - 1)
				d = voisins[ind][1]
				if d == dir[0]:
					self.rm_case_below(s)
				elif d == dir[1]:
					self.rm_case_above(s)
				elif d == dir[2]:
					self.rm_case_right(s)
				else:
					self.rm_case_left(s)

				pile.append(voisins[ind][0])
				visited.append(voisins[ind][0])
				next = self.getCase(voisins[ind][0])
				next.visited = True
			else:
				pile.pop()
			# system("clear")
			# print(lab)
			# sleep(0.1)
		self.resetVisited()
		return self
	
	def fromBooleanArray(self, t, m, n):
		'''
		Convertit un array de taille 2*n*m en son labyrinthe correspondant
		fonction necessitant de verifier les bordures apres usage
		'''
		if(not len(t) == 2*m*n):
			raise Exception("Mauvais format pour t")

		self.full()
		b = int(len(t)/2)
		mursV = t[:b]
		mursH = t[b:]
		for y, line in enumerate(self.base):
			for x, c in enumerate(line):
				ind = y*len(line)+x
				if mursV[ind] == 0:
					c.rm_droite()
				if mursH[ind] == 0:
					c.rm_bas()

	def matriceLaplace(self):
		'''
		Donne la matrice de laplace du graphe correspondant au labyrinthe
		'''
		self.adjacence()
		#print(self.adj)
		nbIndices = self.w*self.h
		M = np.zeros((nbIndices, nbIndices))
		lineCount = 0
		for k, v in self.adj.items():
			degre = len(v)
			x = k[0]-1
			y = k[1]-1
			casesAdjInd = []
			for coord in v:
				casesAdjInd.append((coord[1]-1)*self.w+coord[0]-1)
				#print(coord,coord[1]*self.w+coord[0])
			indCase = y*self.w+x
			M[lineCount, indCase] = degre
			for c in casesAdjInd:
				M[lineCount,c] = -1
			lineCount +=1
		return M
	
	def solution(self):
		pile = []
		current = self.start
		pile.append(current)
		caseCurrent = self.getCase(current)
		caseCurrent.visited = True
		dir = [(0, 1), (0, -1), (1, 0), (-1, 0)]
		while pile[-1] != (self.end[0] - 1, self.end[1] - 1):
			s = pile[-1]
			voisins = []
			for d in dir:  # 4 iterations, peu gourmand
				c = coord(s, d)
				case = self.getCase(s)
				if not (c == -1):
					if not (c[0] > len(self.base[0]) - 1 or c[1] > len(self.base) - 1):
						nextCase = self.getCase(c)
						if d == (0, 1): 
							condition = not case.bas
						elif d == (0, -1): 
							condition = not nextCase.bas
						elif d == (1, 0):
							condition = not case.droite
						else:
							condition = not nextCase.droite

						if condition and not nextCase.visited:
							voisins.append((c, d))

			if len(voisins) != 0:
				ind = randint(0, len(voisins) - 1)
				pile.append(voisins[ind][0])
				next = self.getCase(voisins[ind][0])
				next.visited = True
			else:
				pile.pop()
		self.resetVisited()
		return pile
		

		

		

	def to_png(self, filename:str="labyrinthe"):
		'''
		Convertit le labyrinthe en image
		'''
		print(f"{Color.blue}Converting labyrinthe to png... {Color.end}", end="", flush=True)
		to_pbm_picture(self, filename)
		if self.w > 50 or self.h > 50:
			system(f"convert -scale {2*max(self.w, self.h)+1} img/{filename}.pbm {filename}.png")
		else:
			system(f"convert -scale {2*max(self.w, self.h)*10+1} img/{filename}.pbm {filename}.png")
		print(f"{Color.green}Success !{Color.end}")
		system(f"rm img/*.pbm")

		print(f"{Color.blue}Filename : {Color.red}{filename}.png{Color.end}")
		im = Image(filename=f"{filename}.png")
		return im
	
	def resolve(self, filename:str="labyrinthe"):
		print(f"{Color.orange}Resolving the labyrinthe... {Color.end}", end="", flush=True)
		r = self.solution()
		print(f"{Color.green}OK {Color.end}")
		print(f"{Color.blue}Creating the animation of the solution... {Color.end}", end="", flush=True)
		to_gif(self, r, filename)
		if self.w > 30 or self.h > 30:
			system(f"convert -scale {2*max(self.w, self.h)+1} -delay 10 img/*.pgm {filename}_solution.gif")
		else:
			system(f"convert -scale {2*max(self.w, self.h)*10+1} -delay 10 img/*.pgm {filename}_solution.gif")
		print(f"{Color.green}Success !{Color.end}")
		system(f"rm img/*.pgm")

		print(f"{Color.blue}Filename : {Color.red}{filename}_solution.gif{Color.end}")

	def affiche(self):
		self.to_png("output")
		im = Image(filename="output.png")
		system("rm -f output.png")
		system("clear")
		display(im)
		return



def write_file_pgm(filename,j, T, w, h): 
    system("mkdir -p img")
    with open(f"img/{filename}_{j+1:04}.pgm", 'w') as f:
            f.write('P3\n')
            f.write(f'{2*w+1} {2*h+1}\n')
            f.write('255\n')
            for line in T:
                for c in line:
                    if c == 0:    
                        f.write(f'255 255 255 ')
                    elif c == 1:
                        f.write(f'0 0 0 ')
                    elif c == 2:
                        f.write(f'255 0 0 ')
                f.write('\n')

def write_file_pbm(filename, T, w, h): 
    system("mkdir -p img")
    with open(f"img/{filename}.pbm", 'w') as f:
            f.write('P1\n')
            f.write(f'{2*w+1} {2*h+1}\n')
            for line in T:
                for c in line:
                    f.write(f'{c} ')
                f.write('\n')



def to_gif(l: labyrinthe, r : list, filename: str):
    """
    Convert labyrinthe solution to a gif
    """
    base = l.base
    w, h = l.w, l.h
    T = []
    for y in range(2*h+1):
        L = []
        for x in range(2*w+1):
            if(y == 0 or x == 0 or x == 2*w or y == 2*h or x%2==0 or y%2==0):
                L.append(1)
            else:
                L.append(0)
        T.append(L)
    
    T[l.start[1]*2+1][0] = 0
    T[2*l.end[1]-1][2*w] = 0

    for line in base:
        for c in line:
            if not c.droite:
                T[2*(c.y - 1) + 1][2*c.x] = 0
            if not c.bas:
                T[2*c.y][2*(c.x - 1) +1] = 0

    j = 1

    write_file_pgm(filename, j, T, w, h)
    T[l.start[1]*2+1][0] = 2
    j += 1
    write_file_pgm(filename, j, T, w, h)



    for i in range(len(r) - 1):
        c = r[i]
        c_n = r[i + 1]
        if c_n[0] > c[0]:
            T[2*(c[1]) + 1][2*c[0] + 2] = 2
        
        elif c_n[0] < c[0]:
            T[2*(c[1]) + 1][2*c[0]] = 2
        elif c_n[1] > c[1]:
            T[2*(c[1]) + 2][2*c[0]+1] = 2
        elif c_n[1] < c[1]:
            T[2*(c[1])][2*c[0]+1] = 2
        

        T[2*(c[1]) + 1][2*c[0] + 1] = 2
        j+=1
        write_file_pgm(filename, j, T, w, h)

    j+=1

    T[2*l.end[1]-1][2*w] = 2
    T[2*l.end[1]-1][2*w-1] = 2
    write_file_pgm(filename, j, T, w, h)

def to_pbm_picture(l: labyrinthe, filename: str):
    """
    Convert a labyrinthe to a PBM picture
    """
    base = l.base
    w, h = l.w, l.h
    T = []
    for y in range(2*h+1):
        L = []
        for x in range(2*w+1):
            if(y == 0 or x == 0 or x == 2*w or y == 2*h or x%2==0 or y%2==0):
                L.append(1)
            else:
                L.append(0)
        T.append(L)
    T[l.start[1]*2+1][0] = 0
    T[2*l.end[1]-1][2*w] = 0

    for line in base:
        for c in line:
            if not c.droite:
                T[2*(c.y - 1) + 1][2*c.x] = 0
            if not c.bas:
                T[2*c.y][2*(c.x - 1) +1] = 0

    write_file_pbm(filename, T, w, h)

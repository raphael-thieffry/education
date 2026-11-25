from color import Color

class case:
	def __init__(self, w, h, x, y, bas=False, droite=False):
		'''
			initialise une case
			x et y sont compris respectivement entre 1 et w et entre 1 et h
		'''
		self.bas, self.droite = bas, droite
		self.x, self.y = x, y
		self.w, self.h = w, h
		self.coord = (self.x, self.y)
		self.visited = False
	def add_bas(self):
		self.bas = True

	def add_droite(self):
		self.droite = True

	def rm_bas(self):
		self.bas = False

	def rm_droite(self):
		self.droite = False

	def __str__(self):
		s = ""
		if self.bas:
			s += Color.red + '_' + Color.end
		elif self.h == self.y:
			s += Color.red + '_' + Color.end
		else:
			s += ' ' + Color.end
		if self.droite:
			s += Color.red + '|' + Color.end
		else:
			s += ' ' + Color.end
		return s

	def __repr__(self):
		s1 = ' ' if self.bas else ''
		s2 = ' ' if self.droite else ''
		return f"({self.bas}"+s1+',' + ' ' + f"{self.droite}"+s2+')'

	def __eq__(self, other):
		return self.bas == other.bas and self.droite == other.droite

	def __ne__(self, other):
		return not self == other


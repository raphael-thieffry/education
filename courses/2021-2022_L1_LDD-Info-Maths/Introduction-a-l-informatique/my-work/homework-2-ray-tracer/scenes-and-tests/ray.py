from math import sqrt
from csv import DictReader
from sys import argv, exit
import corrige_ray

## Question 0

NOM = "Thieffry"
PRENOM = "Raphaël"
EMAIL = "raphael.thieffry@universite-paris-saclay.fr"

### Opérations sur les vecteurs
### (section 4.1 de l'énoncé)
### Un vecteur est simplement représenté par un couple (x, y)

## Question 1

def add(v1, v2):
  """Addition de deux vecteurs"""
  return (v1[0]+v2[0],v1[1]+v2[1],v1[2]+v2[2])

def sub(v1, v2):
  """Différence de deux vecteurs"""
  return (v1[0]-v2[0],v1[1]-v2[1],v1[2]-v2[2])

def mul(k, v):
  """Multiplication par une constante"""
  return (k*v[0],k*v[1],k*v[2])

def dot(v1, v2):
  """Produit scalaire de deux vecteurs"""
  return v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2]

def norm(v):
  """Norme d'un vecteur """
  return sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2])

def normalize(v):
  n = norm(v)
  return (v[0]/n,v[1]/n,v[2]/n)

## Question 2

def test_add():
  """Fonction de test pour add"""
  assert add((1,1,1),(1,1,1)) == (2,2,2)
  assert add((1,3,1),(2,1,1)) == (3,4,2) 

test_add()

def test_sub():
  """Fonction de test pour sub"""
  assert sub((1,1,1),(1,1,1)) == (0,0,0)
  assert sub((0,0,0),(2,1,1)) == (-2,-1,-1) 

test_sub()

def test_mul():
  """Fonction de test pour mul"""
  assert mul(1,(1,1,1)) == (1,1,1)
  assert mul(-3,(2,1,1)) == (-6,-3,-3)

test_mul()

def test_dot():
  """Fonction de test pour dot"""
  assert dot((128,13,0),(-13, 128, 0)) == 0
  assert dot((1,1,1),(1,1,-2)) == 0

test_dot()

def test_norm():
  """Fonction de test pour norm"""
  assert norm((0,0,1)) == 1
  assert norm((sqrt(2)/2,sqrt(2)/2,0)) == 1

test_norm()

def test_normalize():
  """Fonction de test pour normalize"""
  assert normalize((0,0,545513201654313213246432131684894)) == (0,0,1)
  assert normalize((17*sqrt(2)/2,17*sqrt(2)/2,0)) == (sqrt(2)/2,sqrt(2)/2,0)

test_normalize()



### Opérations sur les images
### (section 4.2 de l'énoncé)
### Une image est représentée par un triplet (i, w, h) où :
### - i est un bytearray de taille w * h * 3
### - w est la largeur de l'image (en pixels)
### - h est la hauteur de l'image (en pixels)

## Question 3
def init_image(w, h):
  """Initialise une image de w pixels de large et h pixel de haut"""
  return (bytearray(w*h*3),w,h)

## Question 4
def set_pixel(img, x, y, c):
  """Met le pixel au coordonnées (x, y) à la couleur c. C'est un est
  triplet (r, v, b) de valeurs. Les valeurs supérieures à 1 (resp. inférieures à
  0) sont mises à 1 (resp. 0).
  """
  w = img[1]
  h = img[2]
  r = c[0]
  g = c[1]
  b = c[2]
  if c[0] > 1:
        r = 1
  elif c[0] < 0:
        r = 0
  if c[1] > 1:
        g = 1
  elif c[1] < 0:
        g = 0
  if c[2] > 1:
        b = 1
  elif c[2] < 0:
        b = 0
  r = r*255
  g = g*255
  b = b*255
  img[0][y*3*w + 3*x] = int(r)
  img[0][y*3*w + 3*x + 1] = int(g)
  img[0][y*3*w + 3*x + 2] = int(b)
  return img

### Fonction donnée, ne pas modifier
def save_image(chemin, img):
  """Écrit l'image img dans le fichier dont le chemin est donné. Si
  le fichier existe, il est supprimé. L'image est stockée au format PPM"""
  buff, w, h = img
  with open(chemin, "wb") as f:
    f.write(b'P6\n')
    f.write(str(w).encode())
    f.write(b' ')
    f.write(str(h).encode())
    f.write(b'\n255\n')
    f.write(buff)

## Question 5
def test_img():
  """Test des fonctions set_pixel et init_image"""
  save_image("black100.ppm",init_image(100, 100))
  
  test = init_image(696,696)
  centerX = test[1]/2
  centerY = test[2]/2
  for i in range(test[2]): #height
      for j in range(test[1]): #width
         test = set_pixel(test, j, i, (1,0,1)) #met la couleur par default, c'est a dire le fond, en rose
         if i%10 == 0 or j%10 == 0:
             test = set_pixel(test, j, i, (0,0,1)) #si c'est un pixel de la grille des lignes separées par 10pixels, alors on le met en bleu
         if min(centerX,centerY)-64 > norm((centerX-j, centerY-i, 0)) > min(centerX,centerY)-70: #si le pixel est compris dans un entourage de 3 pixels autour du cercle ayant pour rayon la distance au bord moins 67, alors on le met en vert
             test = set_pixel(test, j, i, (0,1,0))
  save_image("carresbleusfondrose.ppm",test) #l'image que l'on attend est donc un cercle vert d'epaisseur 6px sur un fond rose quadrillé de lignes bleues
### Attention, si vous faites une génération d'image un peu coûteuse, vous pouvez
### commenter l'appel ci-dessous après avoir testé

#test_img()

### Fonctions de ray tracing
### Section 5 de l'énoncé

## Question 6
def pixel_to_point(w, h, xmin, xmax, ymin, ymax, px, py):
  """Convertit un pixel (px, py) en un point du plan."""
  return corrige_ray.pixel_to_point(w, h, xmin, xmax, ymin, ymax, px, py)

## Question 7
def sphere_intersect (c, r, v, d):
  """Calcule l'intersection entre une sphere de centre c (vecteur) et de rayon r
     (flottant) et une droite passant par v (vecteur) et de direction d (vecteur)
  """
  return corrige_ray.sphere_intersect(c, r, v ,d)

INF = float('inf')

## Question 8
def nearset_intersection(objs, o, d):
  """Renvoie la sphère la plus proche qui intersecte la droite partant de o dans
  la direction d, ainsi que la distance d'intersection depuis o. S'il n'y a pas
  d'intersection, renvoie (None, INF)"""
  return corrige_ray.nearset_intersection(objs, o, d)

## Question 9
def compute_color (obj, v, n, l):
  """calcule la couleur du point v se trouvant à la surface de l'objet obj.
  n est le vecteur normal au point d'intersection et l le vecteur unitaire dans
  la direction de la source de lumière.
  """
  return corrige_ray.compute_color(obj, v, n, l)


## NE PAS MODIFIER LE CODE CI-DESSOUS
def trace(w, h, xmin, xmax, ymin, ymax, camera, light,objs):

  img = init_image(w, h)

  for py in range(h):
    for px in range(w):
      x, y = pixel_to_point(w, h, xmin, xmax, ymin, ymax, px, py)
      p = (x, y, 0)
      vp = sub(p, camera)
      d = normalize(vp)

      obj, dist = nearset_intersection(objs, camera, d)
      if obj is None:
        couleur = (0, 0, 0)
      else:
        x_point = add(camera, mul(dist, d))
        l = normalize(sub(light, x_point))
        obstacle, dist_obst = nearset_intersection(objs, x_point, l)
        if dist_obst < norm(sub(light, x_point)):
          couleur = (0, 0, 0)
        else:
          n = normalize (sub(x_point, obj["center"]))
          couleur = compute_color(obj, camera, n, l)

      set_pixel(img, px, h - py - 1, couleur)

  return img



### Lecture de description de scene
###

def read_vector(s):
  fields = s.split(",")
  if len(fields) != 3:
    raise ValueError("Erreur de chargement")
  return [ float (n) for n in fields ]

def load_scene (chemin):
  """Charge un fichier de description de scène. En cas d'erreur, la fonction
     lève une exception 'Exception("Erreur de chargement")'
  """
  try:
    with open (chemin, "r") as f:
      w = int (f.readline())
      h = int (f.readline())
      xmin = float(f.readline())
      xmax = float(f.readline())
      ymin = float(f.readline())
      ymax = float(f.readline())
      camera = read_vector(f.readline())
      light = read_vector(f.readline())
      objects = list(DictReader(f, delimiter=";"))
      for obj in objects:
        obj['center'] = read_vector(obj['center'])
        obj['radius'] = float(obj['radius'])
        obj['ambiant'] = read_vector(obj['ambiant'])
        obj['diffuse'] = read_vector(obj['diffuse'])
        obj['specular'] = read_vector(obj['specular'])
        obj['shininess'] = min(100, max(0, float(obj['shininess'])))
        obj['reflection'] = min(1, max(0, float(obj['reflection'])))
    return (w, h, xmin, xmax, ymin, ymax, camera, light, objects)
  except:
      raise ValueError("Erreur de chargement")

def usage():
  print(f"Usage: {argv[0]} <fichier.scene>")
  exit (1)

if __name__ == "__main__":
  if len (argv) != 2:
    usage()

  fichier = argv[1]
  if len(fichier) < 6 or fichier[-6:] != ".scene":
    usage()

  out = fichier[0:-6] + ".ppm"

  w, h, xmin, xmax, ymin, ymax, camera, lum, objs = load_scene(fichier)
  img = trace(w, h, xmin, xmax, ymin, ymax, camera, lum, objs)
  save_image(out, img)

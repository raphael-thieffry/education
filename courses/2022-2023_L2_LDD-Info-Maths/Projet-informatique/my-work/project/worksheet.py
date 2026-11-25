from modules.open_digraph import *
import inspect

#graphe chaine test
n0 = node(0, 'a', [], [1])
n1 = node(1, 'b', [0], [2])
n2 = node(2, 'c', [1], [3])
n3 = node(3, 'd', [2], [4])
n4 = node(4, 'e', [3], [])
g = open_digraph([0], [4], [n0, n1, n2, n3, n4])
g2 = open_digraph.empty()

print(inspect.getsource(g2.add_input_id))
print(inspect.getfile(g2.add_input_id))
print(inspect.getdoc(g2.add_input_id))
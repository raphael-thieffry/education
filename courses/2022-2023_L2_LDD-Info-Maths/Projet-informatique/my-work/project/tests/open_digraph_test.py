import sys
import os
root = os.path.normpath(os.path.join(__file__, './../..'))
sys.path.append(root)# allows us to fetch files from the project root
import unittest 
from modules.open_digraph import *
from modules.bool_circ import *

class InitTest(unittest.TestCase):
    def setUp(self):
        self.n0 = node(0, 'a', [], [1])

    def test_init_node(self):
        n0 = node(0, 'i', None, {1:1})
        self.assertEqual(n0.id, 0)
        self.assertEqual(n0.label, 'i')
        self.assertEqual(n0.parents, None)
        self.assertEqual(n0.children, {1:1})
        self.assertIsInstance(n0, node)

    def test_init_open_diagraph(self):
        d0 = open_digraph([], [], [node(0, 'i', None, None)])
        self.assertEqual(d0.inputs, [])
        self.assertEqual(d0.outputs, [])
        self.assertEqual(d0.nodes[0], node(0, 'i', None, None))
        self.assertIsInstance(d0, open_digraph)

    def test_copy(self):
        n0 = node(0, 'i', None, None)
        n1 = n0.copy()
        self.assertEqual(n0, n1)
        self.assertIsNot(n0, n1)
        d0 = open_digraph([], [], [node(0, 'i', None, None)])
        d1 = d0.copy()
        self.assertIsNot(d0, d1)

    def test_next_ids(self):
        d0 = open_digraph([], [], [node(0, 'i', {}, {})])
        self.assertEqual(d0.next_id(), 1)
        self.assertEqual(d0.next_id(), 2)
        self.assertEqual(d0.next_id(), 3)


    def test_add_node(self):
        d0 = open_digraph([], [], [node(0, 'i', None, None)])
        d0.get_node_by_id(d0.add_node('a'))
        self.assertEqual(d0.nodes[1], node(1, 'a', None, None))

    def test_remove_parent_once(self):
        d0 = open_digraph([], [], [node(0, 'i', None, None), node(1, 'a', {0:1}, None)])
        d0.get_node_by_id(1).remove_parent_once(0)
        self.assertEqual(d0.nodes[1], node(1, 'a', None, None))
        with self.assertRaises(ValueError):
            d0.get_node_by_id(1).remove_parent_once(0)

    def test_remove_child_once(self):
        d0 = open_digraph([], [], [node(0, 'i', None, None), node(1, 'a', None, {0:1})])
        d0.get_node_by_id(1).remove_child_once(0)
        self.assertEqual(d0.nodes[1], node(1, 'a', None, None))
        with self.assertRaises(ValueError):
            d0.get_node_by_id(1).remove_child_once(0)

    def test_remove_parent_id(self):
        d0 = open_digraph([], [], [node(0, 'i', None, None), node(1, 'a', {0:2}, None)])
        d0.get_node_by_id(1).remove_parent_id(0)
        self.assertEqual(d0.nodes[1], node(1, 'a', None, None))
        with self.assertRaises(ValueError):
            d0.get_node_by_id(1).remove_parent_id(0)

    def test_remove_child_id(self):
        d0 = open_digraph([], [], [node(0, 'i', None, None), node(1, 'a', None, {0:2})])
        d0.get_node_by_id(1).remove_child_id(0)
        self.assertEqual(d0.nodes[1], node(1, 'a', None, None))
        with self.assertRaises(ValueError):
            d0.get_node_by_id(1).remove_child_id(0)

    def test_remove_edge(self):
        d0 = open_digraph([], [], [node(0, 'i', None, {1:1}), node(1, 'a', {0:1}, None)])
        d0.remove_edge(0, 1)
        self.assertEqual(d0.nodes[1], node(1, 'a', None, None))
        self.assertEqual(d0.nodes[0], node(0, 'i', None, None))
        with self.assertRaises(RuntimeError):
            d0.remove_edge(0, 1)
        with self.assertRaises(ValueError):
            d0.remove_edge(0, 2)

    def test_remove_parallel_edges(self):
        d0 = open_digraph([], [], [node(0, 'i', None, {1:2}), node(1, 'a', {0:2}, None)])
        d0.remove_parallel_edges(0, 1)
        self.assertEqual(d0.nodes[1], node(1, 'a', None, None))
        self.assertEqual(d0.nodes[0], node(0, 'i', None, None))
        with self.assertRaises(RuntimeError):
            d0.remove_parallel_edges(0, 1)
        with self.assertRaises(ValueError):
            d0.remove_parallel_edges(0, 2)

    def test_remove_edges(self):
        d0 = open_digraph([], [], [])
        n0 = d0.add_node('a')
        n1 = d0.add_node('b')
        n2 = d0.add_node('c')
        d0.add_edge(n0, n1)
        d0.add_edge(n0, n2)
        d0.add_edge(n1, n2)
        d0.remove_edges([(n0, n1),
                         (n0, n2),
                         (n1, n2)])
        self.assertEqual(d0.nodes[0], node(0, 'a', None, None))
        self.assertEqual(d0.nodes[1], node(1, 'b', None, None))
        self.assertEqual(d0.nodes[2], node(2, 'c', None, None))

    def test_remove_several_parallel_edges(self):
        d0 = open_digraph([], [], [])
        n0 = d0.add_node('a')
        n1 = d0.add_node('b')
        n2 = d0.add_node('c')
        d0.add_edge(n0, n1)
        d0.add_edge(n0, n1)
        d0.add_edge(n0, n2)
        d0.add_edge(n0, n2)
        d0.add_edge(n0, n2)
        d0.add_edge(n1, n2)
        d0.remove_several_parallel_edges([(n0, n1),
                                          (n0, n2),
                                          (n1, n2)])
        self.assertEqual(d0.nodes[0], node(0, 'a', None, None))
        self.assertEqual(d0.nodes[1], node(1, 'b', None, None))
        self.assertEqual(d0.nodes[2], node(2, 'c', None, None))

    def test_remove_nodes_by_id(self):
        d0 = open_digraph.empty()
        n0 = d0.add_node('a')
        n1 = d0.add_node('b')
        n2 = d0.add_node('c')

        d0.add_edge(n0, n1)
        d0.add_edge(n0, n2)
        d0.add_edge(n1, n2)
        d0.remove_nodes_by_id(n2)
        self.assertEqual(d0.nodes, {0: node(0, 'a', None, {1:1}),
                                    1: node(1, 'b', {0:1}, None)})
        d0.remove_nodes_by_id(n1, n0)
        self.assertEqual(d0.nodes, {})
        id = d0.add_node('a')
        self.assertEqual(id, 0)
        self.assertEqual(d0.nodes, {0: node(0, 'a', None, None)})
        self.assertEqual(d0.get_free_ids(), [2, 1])

    def test_is_well_formed(self):
        d0 = open_digraph.empty()
        # self.assertIs(d0.is_well_formed(), True)

        n0 = d0.add_node('a')
        n1 = d0.add_node('b')
        n2 = d0.add_node('c')
        d0.add_edge(n0, n1)
        d0.add_edge(n0, n2)
        d0.add_edge(n1, n2)
        # self.assertIs(d0.is_well_formed(), True)

        d0.add_input_node(n0)
        # self.assertIs(d0.is_well_formed(),True)

        d0.add_output_node(n2)
        # self.assertIs(d0.is_well_formed(), True)

        """
        n3=d0.get_node_by_id(d0.add_node('d'))
        d0.add_node(n3)
        n3.set_parents({n2.get_id():1})
        self.assertIs(d0.is_well_formed(),False)
        """

        di = d0.get_node_by_id(4) #output
        di.set_children({0:1})
        # self.assertIs(d0.is_well_formed(), False)


    def test_add_output_node(self):
        d0 = open_digraph.empty()
        n0 = d0.add_node('a')
        n1 = d0.add_node('b')
        n2 = d0.add_node('c')
        d0.add_edge(n0, n1)
        d0.add_edge(n0, n2)
        d0.add_edge(n1, n2)
        d0.add_output_node(n2)
        self.assertEqual(d0.nodes[2], node(2, 'c', {0: 1, 1: 1}, {3: 1}))
        with self.assertRaises(ValueError):
            d0.add_output_node(3) #noeud en output

    def test_add_input_node(self):
        d0 = open_digraph.empty()
        n0 = d0.add_node('a')
        n1 = d0.add_node('b')
        n2 = d0.add_node('c')
        d0.add_edge(n0, n1)
        d0.add_edge(n0, n2)
        d0.add_edge(n1, n2)
        d0.add_input_node(n0)
        self.assertEqual(d0.nodes[0], node(0, 'a', {3: 1}, {1: 1, 2: 1}))
        with self.assertRaises(ValueError):
            d0.add_input_node(3)

    def test_save_odt(self):
        d0 = open_digraph.empty()
        n0 = d0.add_node('&')
        n1 = d0.add_node('~')
        n2 = d0.add_node()
        n3 = d0.add_node()
        n4 = d0.add_node('|')
        d0.add_edge(n0, n1)
        d0.add_edge(n0, n3)
        d0.add_edge(n1, n2)
        d0.add_edge(n2, n3)
        d0.add_edge(n2, n3)
        d0.add_edge(n3, n4)
        d0.add_edge(n2, n4)

        # d0.save_as_dot_file("poup.dot")
        # print(d0)


    def test_fusionne_noeud(self):
        d0 = open_digraph.empty()
        x1 = d0.add_node('x1')
        x1_fake = d0.add_node('x1')
        x2 = d0.add_node('x2')
        x2_fake = d0.add_node('x2')
        x0 = d0.add_node('x0')
        et1 = d0.add_node('&')
        et2 = d0.add_node('&')
        et3 = d0.add_node('&')
        tilde = d0.add_node('~')
        or_ = d0.add_node("|")

        d0.add_edge(x1, et1)
        d0.add_edge(x2, et1)
        d0.add_edge(x2_fake, tilde)
        d0.add_edge(x0, et2)
        d0.add_edge(et1, et2)
        d0.add_edge(x1_fake, et3)
        d0.add_edge(tilde, et3)
        d0.add_edge(et2, or_)
        d0.add_edge(et3, or_)

        # print(x1, x1_fake)
        d0.fusionne_noeud(x1, x1_fake)
        d0.fusionne_noeud(x2, x2_fake)

        # d0.display()

        # G = open_digraph.from_dot_file("")

    def test_from_dot_file(self):
        """ print("\n----ici-----\n")
        open_digraph.from_dot_file("poup.dot")
        print("\n----ici-----\n")
          """

        # G = open_digraph.from_dot_file("officiel.dot")
        # print(G)

    def test_display(self):
        """Test de display"""
        # G = open_digraph.from_dot_file("officiel.dot")
        # G.display()



    def test_adjacency_matrix(self):
        d0 = open_digraph.empty()
        n0 = d0.add_node('a')
        n1 = d0.add_node('b')
        n2 = d0.add_node('c')
        d0.add_edge(n0, n1)
        d0.add_edge(n0, n2)
        d0.add_edge(n1, n2)
        self.assertEqual(d0.adjacency_matrix(), [[0, 1, 1], [0, 0, 1], [0, 0, 0]])

    def test_graph_from_adjacency_matrix(self):
        d0 = open_digraph.empty()
        n0 = d0.add_node('a')
        n1 = d0.add_node('b')
        n2 = d0.add_node('c')
        d0.add_edge(n0, n1)
        d0.add_edge(n0, n2)
        d0.add_edge(n1, n2)
        d1 = graph_from_adjency_matrix(d0.adjacency_matrix())
        # print()
        # print(d0)
        # print()
        # print(d1)
        for n in d0.nodes.keys():
            self.assertEqual(d0.nodes[n].parents, d1.nodes[n].parents)
            self.assertEqual(d0.nodes[n].children, d1.nodes[n].children)

    def test_random_graph_method(self):
        d0 = open_digraph.random(5, 6,outputs=1, inputs=1, form='free')
        d1 = open_digraph.random(5, 6, form='DAG')
        d2 = open_digraph.random(5, 6, form='oriented')
        d3 = open_digraph.random(5, 6, form='loop-free')
        d4 = open_digraph.random(5, 6, form='undirected')
        d5 = open_digraph.random(5, 6, form='loop-free undirected')
        # self.assertIs(d0.is_well_formed(), True)
        # self.assertIs(d1.is_well_formed(), True)
        # self.assertIs(d2.is_well_formed(), True)
        # self.assertIs(d3.is_well_formed(), True)
        # self.assertIs(d4.is_well_formed(), True)
        # self.assertIs(d5.is_well_formed(), True)
        self.assertEqual(len(d0.inputs), 1)
        self.assertEqual(len(d0.outputs), 1)

    def test_is_well_formed_bool_circ(self):
        d0 = open_digraph.empty()
        n0 = d0.add_node('&')
        n1 = d0.add_node('|')
        n2 = d0.add_node('~')
        d0.add_edge(n0, n1)
        d0.add_edge(n0, n2)
        d0.add_edge(n1, n2)
        d0.add_output_node(n2)
        d0.add_input_node(n0)
        circBool = bool_circ(d0)
        # self.assertIs(circBool.is_well_formed(), False) #2 enfants pour &

        d0 = open_digraph.empty()
        n0 = d0.add_node('')
        n1 = d0.add_node('~')
        n2 = d0.add_node('&')
        d0.add_edge(n0, n1)
        d0.add_edge(n0, n2)
        d0.add_edge(n1, n2)
        d0.add_output_node(n2)
        d0.add_input_node(n0)
        circBool = bool_circ(d0)
        # self.assertIs(circBool.is_well_formed(), True) #2 enfants pour &

    def test_shift_indices(self):
        d0 = open_digraph.empty()
        n0 = d0.add_node('a')
        n1 = d0.add_node('b')
        n2 = d0.add_node('c')
        d0.add_edge(n0, n1)
        d0.add_edge(n0, n2)
        d0.add_edge(n1, n2)
        d0.shift_indices(1)
        self.assertEqual(d0.nodes[1], node(1, 'a', None, {2: 1, 3: 1}))
        self.assertEqual(d0.nodes[2], node(2, 'b', {1: 1}, {3: 1}))
        self.assertEqual(d0.nodes[3], node(3, 'c', {1:1, 2:1}, None))
        with self.assertRaises(KeyError):
            d0.nodes[0]
        d1 = d0.copy()
        d0.shift_indices(1)
        d0.shift_indices(-1)
        self.assertEqual(d1, d0)

    def test_identity(self):
        d1 = open_digraph.identity(1)
        self.assertEqual(d1.is_well_formed(), True)

    def test_compose(self):
        d0 = open_digraph.empty()
        n0 = d0.add_node('a')
        n1 = d0.add_node('b')
        n2 = d0.add_node('c')
        d0.add_edge(n0, n1)
        d0.add_edge(n0, n2)
        d0.add_edge(n1, n2)
        d0.add_input_node(n0)
        d0.add_output_node(n2)
        d1 = open_digraph.empty()
        n3 = d1.add_node('d')
        n4 = d1.add_node('e')
        n5 = d1.add_node('f')
        d1.add_edge(n3, n4)
        d1.add_edge(n3, n5)
        d1.add_edge(n4, n5)
        d1.add_input_node(n3)
        d1.add_output_node(n5)
        d2 = d0.compose(d1)
        #print(d2)

        self.assertEqual(d2.is_well_formed(), True)

    def test_parallel(self):
        d0 = open_digraph.empty()
        n0 = d0.add_node('a')
        n1 = d0.add_node('b')
        n2 = d0.add_node('c')
        d0.add_edge(n0, n1)
        d0.add_edge(n0, n2)
        d0.add_edge(n1, n2)
        d0.add_input_node(n0)
        d0.add_output_node(n2)
        d1 = open_digraph.empty()
        n3 = d1.add_node('d')
        n4 = d1.add_node('e')
        n5 = d1.add_node('f')
        d1.add_edge(n3, n4)
        d1.add_edge(n3, n5)
        d1.add_edge(n4, n5)
        d1.add_input_node(n3)
        d1.add_output_node(n5)
        d2 = d0.parallel(d1)
        self.assertEqual(d2.is_well_formed(), True)
        # print(d2)

    def test_connected_component(self):
        G = open_digraph.from_dot_file("poup.dot")
        # print(G.nodes.keys())
        # print(G.get_voisins(8))
        components = G.connected_components()
        # print(components)

    def test_dismember(self):
        G = open_digraph.from_dot_file("poup.dot")
        lst_graph = G.dismember()
        i=0
        for graph in lst_graph:
            graph.save_as_dot_file(f"component{i}.dot", verbose=False)
            i+=1


    def test_dijkstra(self):
        d0 = open_digraph.empty()
        n0 = d0.add_node('a')
        n1 = d0.add_node('b')
        n2 = d0.add_node('c')
        n3 = d0.add_node('d')
        n4 = d0.add_node('e')
        n5 = d0.add_node('f')
        n6 = d0.add_node('g')
        n7 = d0.add_node('h')
        d0.add_edge(n0, n1)
        d0.add_edge(n1, n2)
        d0.add_edge(n2, n3)
        d0.add_edge(n3, n4)
        d0.add_edge(n4, n5)
        d0.add_edge(n5, n6)
        d0.add_edge(n6, n7)
        d = d0.dijkstra(n0)
        self.assertEqual(d[0], {n0: 0, n1: 1, n2: 2, n3: 3, n4: 4, n5: 5, n6: 6, n7: 7})
        d0.add_edge(n0, n7)
        dist2 = d0.dijkstra(n1, tgt = n7)[0][n7]
        self.assertEqual(dist2, 2)

    def test_shortest_path(self):
        d0 = open_digraph.empty()
        n0 = d0.add_node('a')
        n1 = d0.add_node('b')
        n2 = d0.add_node('c')
        n3 = d0.add_node('d')
        n4 = d0.add_node('e')
        n5 = d0.add_node('f')
        n6 = d0.add_node('g')
        n7 = d0.add_node('h')
        d0.add_edge(n0, n1)
        d0.add_edge(n1, n2)
        d0.add_edge(n2, n3)
        d0.add_edge(n3, n4)
        d0.add_edge(n4, n5)
        d0.add_edge(n5, n6)
        d0.add_edge(n6, n7)
        d = d0.shortest_path(n0, n7)
        self.assertEqual(d, [n0, n1, n2, n3, n4, n5, n6, n7])
        d0.add_edge(n0, n7)
        d = d0.shortest_path(n1, n7)
        self.assertEqual(d, [n1, n0, n7])
        d0.add_edge(n0, n2)
        d = d0.shortest_path(n2, n7)
        self.assertEqual(d, [n2, n0, n7])

    def test_dist_ancetre_commun(self):
        d0 = open_digraph.empty()
        n0 = d0.add_node('0')
        n1 = d0.add_node('1')
        n2 = d0.add_node('2')
        n3 = d0.add_node('3')
        n4 = d0.add_node('4')
        n5 = d0.add_node('5')
        n6 = d0.add_node('6')
        n7 = d0.add_node('7')
        n8 = d0.add_node('8')
        n9 = d0.add_node('9')
        d0.add_edge(n0, n3)
        d0.add_edge(n3, n5)
        d0.add_edge(n3, n7)
        d0.add_edge(n3, n6)
        d0.add_edge(n5, n7)
        d0.add_edge(n1, n5)
        d0.add_edge(n1, n8)
        d0.add_edge(n1, n4)
        d0.add_edge(n2, n4)
        d0.add_edge(n4, n6)
        d0.add_edge(n6, n9)
        d0.add_edge(n6, n8)
        self.assertEqual(d0.distancetrecommun(n5, n8), {0: (2, 3), 1: (1, 1), 3: (1, 2)})

    def test_tri_topo(self):
        d0 = open_digraph.empty()
        n0 = d0.add_node('0')
        n1 = d0.add_node('1')
        n2 = d0.add_node('2')
        n3 = d0.add_node('3')
        n4 = d0.add_node('4')
        n5 = d0.add_node('5')
        n6 = d0.add_node('6')
        n7 = d0.add_node('7')
        n8 = d0.add_node('8')
        n9 = d0.add_node('9')
        d0.add_edge(n0, n3)
        d0.add_edge(n3, n5)
        d0.add_edge(n3, n7)
        d0.add_edge(n3, n6)
        d0.add_edge(n5, n7)
        d0.add_edge(n1, n5)
        d0.add_edge(n1, n8)
        d0.add_edge(n1, n4)
        d0.add_edge(n2, n4)
        d0.add_edge(n4, n6)
        d0.add_edge(n6, n9)
        d0.add_edge(n6, n8)
        tri = d0.tri_topo()
        self.assertEqual(tri, [[0,1,2],[3,4],[5,6],[7,8,9]])

    def test_profondeur_noeud(self):
        d0 = open_digraph.empty()
        n0 = d0.add_node('0')
        n1 = d0.add_node('1')
        n2 = d0.add_node('2')
        n3 = d0.add_node('3')
        n4 = d0.add_node('4')
        n5 = d0.add_node('5')
        n6 = d0.add_node('6')
        n7 = d0.add_node('7')
        n8 = d0.add_node('8')
        n9 = d0.add_node('9')
        d0.add_edge(n0, n3)
        d0.add_edge(n3, n5)
        d0.add_edge(n3, n7)
        d0.add_edge(n3, n6)
        d0.add_edge(n5, n7)
        d0.add_edge(n1, n5)
        d0.add_edge(n1, n8)
        d0.add_edge(n1, n4)
        d0.add_edge(n2, n4)
        d0.add_edge(n4, n6)
        d0.add_edge(n6, n9)
        d0.add_edge(n6, n8)
        self.assertEqual(d0.profondeur_noeud(0),0)
        self.assertEqual(d0.profondeur_noeud(1),0)
        self.assertEqual(d0.profondeur_noeud(2),0)
        self.assertEqual(d0.profondeur_noeud(3),1)
        self.assertEqual(d0.profondeur_noeud(4),1)
        self.assertEqual(d0.profondeur_noeud(5),2)
        self.assertEqual(d0.profondeur_noeud(6),2)
        self.assertEqual(d0.profondeur_noeud(7),3)
        self.assertEqual(d0.profondeur_noeud(8),3)
        self.assertEqual(d0.profondeur_noeud(9),3)

    def test_profondeur_graphe(self):
        d0 = open_digraph.empty()
        n0 = d0.add_node('0')
        n1 = d0.add_node('1')
        n2 = d0.add_node('2')
        n3 = d0.add_node('3')
        n4 = d0.add_node('4')
        n5 = d0.add_node('5')
        n6 = d0.add_node('6')
        n7 = d0.add_node('7')
        n8 = d0.add_node('8')
        n9 = d0.add_node('9')
        d0.add_edge(n0, n3)
        d0.add_edge(n3, n5)
        d0.add_edge(n3, n7)
        d0.add_edge(n3, n6)
        d0.add_edge(n5, n7)
        d0.add_edge(n1, n5)
        d0.add_edge(n1, n8)
        d0.add_edge(n1, n4)
        d0.add_edge(n2, n4)
        d0.add_edge(n4, n6)
        d0.add_edge(n6, n9)
        d0.add_edge(n6, n8)
        self.assertEqual(3,d0.profondeur_graphe())

    def test_max_dist(self):
        d0 = open_digraph.empty()
        n0 = d0.add_node('0')
        n1 = d0.add_node('1')
        n2 = d0.add_node('2')
        n3 = d0.add_node('3')
        n4 = d0.add_node('4')
        n5 = d0.add_node('5')
        n6 = d0.add_node('6')
        n7 = d0.add_node('7')
        n8 = d0.add_node('8')
        n9 = d0.add_node('9')
        d0.add_edge(n0, n3)
        d0.add_edge(n3, n5)
        d0.add_edge(n3, n7)
        d0.add_edge(n3, n6)
        d0.add_edge(n5, n7)
        d0.add_edge(n1, n5)
        d0.add_edge(n1, n8)
        d0.add_edge(n1, n4)
        d0.add_edge(n2, n4)
        d0.add_edge(n4, n6)
        d0.add_edge(n6, n9)
        d0.add_edge(n6, n8)
        maxdist = d0.max_dist(1,5)[1]
        self.assertEqual(1, maxdist)

    def test_parse_parentheses(self):
        d0 = open_digraph.empty()
        bc = bool_circ(d0)
        bc, vars = bc.parse_parentheses("((x0)&((x1)&(x2)))|((x1)&(~(x2)))", "((x0)&(~(x1)))|(x2)")
        bc.save_as_dot_file("test_parse_parentheses.dot")
        # print(vars)
        self.assertEqual(vars, ["x0","x1","x2"])
        self.assertTrue(bc.is_well_formed())

    def test_random_bool_circ(self):
        bc = bool_circ.random(5)
        #bc = open_digraph.random(5, inputs = 0, outputs=0, bound = randint(1,5), form = "DAG")
        bc.save_as_dot_file("test_random_bool_circ.dot")
        self.assertTrue(bc.is_well_formed())

    def test_check_power_of_two(self):
        self.assertTrue(bool_circ.check_power_of_two(2))
        self.assertTrue(bool_circ.check_power_of_two(4))
        self.assertTrue(bool_circ.check_power_of_two(32))
        self.assertTrue(bool_circ.check_power_of_two(64))
        self.assertFalse(bool_circ.check_power_of_two(36))
        self.assertFalse(bool_circ.check_power_of_two(45))
        self.assertFalse(bool_circ.check_power_of_two(56))
        self.assertFalse(bool_circ.check_power_of_two(909))

    def test_list_half_adder(self):
        d0 = bool_circ(open_digraph.empty())
        self.assertEqual(d0.list_half_adder([1,0,1,1], [0,1,1,1]), (1,[0,0,1,0]))
        self.assertEqual(d0.list_half_adder([1,1,0,0,0,1,1,0],[0,1,1,0,0,0,0,1]), (1, [0,0,1,0,0,1,1,1]))
        self.assertEqual(d0.list_half_adder([0,1,0,0,0,1,1,0],[0,1,1,0,0,0,0,1]), (0, [1,0,1,0,0,1,1,1]))


    def test_list_adder(self):
        d0 = bool_circ(open_digraph.empty())
        self.assertEqual(d0.list_adder([0,0,1,0],[1,0,1,1],1), (0,[1,1,1,0]))
        self.assertEqual(d0.list_adder([0,0,1,0],[1,0,1,1],0), (0,[1,1,0,1]))
        self.assertEqual(d0.list_adder([1,0,1,1,0,1,0,1],[0,1,0,0,1,1,1,0],1), (1, [0, 0, 0, 0, 0, 1, 0, 0]))
        self.assertEqual(d0.list_adder([1,0,1,1,0,1,0,1],[0,1,0,0,1,1,1,0],0), (1, [0, 0, 0, 0, 0, 0, 1, 1]))


    def test_adder(self):
        import sys
        # sys.setrecursionlimit(10**6)
        circuit3 = bool_circ.adder(3)
        #TODO: test later on td11

        self.assertTrue(circuit3.is_well_formed())
        # circuit3.display()

    def test_from_int(self):
        d0 = bool_circ.fromint(11)
        d0.save_as_dot_file("test_from_int.dot")
        dres = open_digraph.empty()
        n0 = dres.add_node('0')
        dres.add_output_node(n0)
        n1 = dres.add_node('0')
        dres.add_output_node(n1)
        n2 = dres.add_node('0')
        dres.add_output_node(n2)
        n3 = dres.add_node('0')
        dres.add_output_node(n3)
        n4 = dres.add_node('1')
        dres.add_output_node(n4)
        n5 = dres.add_node('0')
        dres.add_output_node(n5)
        n6 = dres.add_node('1')
        dres.add_output_node(n6)
        n7 = dres.add_node('1')
        dres.add_output_node(n7)
        d0.save_as_dot_file("test_from_int.dot")
        self.assertEqual(d0, dres)
        self.assertTrue(d0.is_well_formed())

    def test_enc(self):
        d0=bool_circ.enc()
        d0.save_as_dot_file("test_from_enc.dot")

    def test_simplifie(self):
        d0 = bool_circ(open_digraph.empty())
        n0 = d0.add_node('0')
        and0 = d0.add_node('&')
        d0.add_edge(n0, and0)
        n1 = d0.add_node('1')
        d0.add_edge(n1, and0)
        d0.add_output_node(and0)
        d0.simplifie(n1, and0)
        d0.simplifie(n0, and0)
        d0.save_as_dot_file("test_simplifie.dot")
        #and fini
        d0 = bool_circ(open_digraph.empty())
        n0 = d0.add_node('1')
        copy0 = d0.add_node('')
        d0.add_edge(n0, copy0)
        d0.add_output_node(copy0)
        d0.add_output_node(copy0)
        d0.simplifie(n0, copy0)
        d0.save_as_dot_file("test_simplifie.dot")
        #copy fini
        d0 = bool_circ(open_digraph.empty())
        n0 = d0.add_node('0')
        or0 = d0.add_node('|')
        d0.add_edge(n0, or0)
        n1 = d0.add_node('1')
        d0.add_edge(n1, or0)
        d0.add_output_node(or0)
        #d0.simplifie(n1, or0)
        d0.simplifie(n0, or0)
        d0.save_as_dot_file("test_simplifie.dot")
        #or fini
        d0 = bool_circ(open_digraph.empty())
        n0 = d0.add_node('0')
        non0 = d0.add_node('~')
        d0.add_edge(n0, non0)
        d0.add_output_node(non0)
        d0.simplifie(n0, non0)
        d0.save_as_dot_file("test_simplifie.dot")
        #non fini
        d0 = bool_circ(open_digraph.empty())
        n0 = d0.add_node('0')
        xor0 = d0.add_node('^')
        d0.add_edge(n0, xor0)
        n1 = d0.add_node('1')
        d0.add_edge(n1, xor0)
        d0.add_output_node(xor0)
        d0.simplifie(n0, xor0)
        d0.simplifie(n1, xor0)
        d0.save_as_dot_file("test_simplifie.dot")
        #xor fini
        d0 = bool_circ(open_digraph.empty())
        n0 = d0.add_node('^')
        n1 = d0.add_node('|')
        n2 = d0.add_node('&')
        d0.add_output_node(n0)
        d0.add_output_node(n1)
        d0.add_output_node(n2)
        d0.simplifie(n0)
        d0.simplifie(n1)
        d0.simplifie(n2)
        d0.save_as_dot_file("test_simplifie.dot")
        #elements neutres

    def test_evaluate(self):
        bc = bool_circ.half_adder(2)

        self.assertTrue(bc.is_well_formed())

        inp1 = bool_circ.fromint(4, regsize=4)
        inp2 = bool_circ.fromint(3, regsize=4)

        inp = inp1.parallel(inp2)

        a_evaluer = bc.compose(inp)

        a_evaluer.evaluate()
        # a_evaluer.save_as_dot_file("test_adder.dot")

        # a_evaluer.display()




    def test_reecrit(self):
        enc = bool_circ.enc()
        dec = bool_circ.dec()
        identite___esperons = dec.compose(enc)
        identite___esperons.reecrit()
        # identite___esperons.display()
        # identite___esperons.save_as_dot_file("test_reecrit.dot")

    def test_dec(self):
        d0=bool_circ.dec()
        # d0.display()
        # d0.save_as_dot_file("test_from_dec.dot")

    def test_prof(self):
        d0 = bool_circ.adder(0)
        d1 = bool_circ.adder(1)
        d2 = bool_circ.adder(2)
        d3 = bool_circ.adder(3)

        d0.save_as_dot_file('d0_prof.dot')
        d1.save_as_dot_file('d1_prof.dot')
        d2.save_as_dot_file('d2_prof.dot')
        d3.save_as_dot_file('d3_prof.dot')


    def test_erreur(self):
        enc = bool_circ.enc()
        dec = bool_circ.dec()

        id_output_quelconque = enc.outputs[0]
        node_output_quelconque = enc.get_node_by_id(id_output_quelconque)
        parent = list(node_output_quelconque.get_parents_ids())[0]
        enc.remove_edge(parent, id_output_quelconque)
        node_tilde_extra = enc.add_node("~")
        enc.add_edge(parent, node_tilde_extra)
        enc.add_edge(node_tilde_extra, id_output_quelconque)


        id_output_quelconque = enc.outputs[1]
        node_output_quelconque = enc.get_node_by_id(id_output_quelconque)
        parent = list(node_output_quelconque.get_parents_ids())[0]
        enc.remove_edge(parent, id_output_quelconque)
        node_tilde_extra = enc.add_node("~")
        enc.add_edge(parent, node_tilde_extra)
        enc.add_edge(node_tilde_extra, id_output_quelconque)

        identite___esperons = dec.compose(enc)
        identite___esperons.reecrit()
        # identite___esperons.display()



if __name__ == '__main__': # the following code is called only when precisely this file is run
    unittest.main()


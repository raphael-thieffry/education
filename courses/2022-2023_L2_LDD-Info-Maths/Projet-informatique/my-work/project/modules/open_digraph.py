from typing import Dict,List, Tuple
from .matrix import *
from .node import *
from random import randint
import random
import os
import sys
root = os.path.normpath(os.path.join(__file__, './..'))
sys.path.append(root)# allows us to fetch files from the project root

import mx.open_digraph_dot_mx as dotmodule
dot = dotmodule.dot
import mx.open_digraph_longueur_mx as longueurmodule
longueur = longueurmodule.longueur
import mx.open_digraph_compositions_mx as compomodule
compo = compomodule.compo
import mx.open_digraph_structure_mx as structmodule
structure = structmodule.structure
import mx.open_digraph_manipulate_mx as manipulatemodule
manipulate = manipulatemodule.manipulate


class open_digraph(dot, longueur, compo, structure, manipulate): # for open directed graph
    def __init__(self, inputs, outputs, nodes : List[node]):
        '''
        inputs: int list; the ids of the input nodes
        outputs: int list; the ids of the output nodes
        nodes: node iter;
        max_ids: int; the maximum id of every node the graph has seen unitil now (does not shrink when the max is removed)
        '''
        self.inputs = inputs
        self.outputs = outputs
        self.nodes = {n.id:n  for n in nodes} # self.nodes: <int,node> dict
        self.free_ids = []
        self.max_ids = 0
        if len(self.nodes) > 0:
            self.max_ids = max(self.nodes.keys())+1

    def __init2__(self, graph):
        self.inputs = graph.get_input_ids()
        self.outputs = graph.get_output_ids()
        self.nodes = {n.get_id():n  for n in graph.get_nodes()}
        self.free_ids = []
        self.max_ids = 0
        if len(self.nodes) > 0:
            self.max_ids = max(self.nodes.keys())+1
        

    def __eq__(self, other):
        if not isinstance(other, open_digraph):
            return False
        return self.inputs == other.inputs and self.outputs == other.outputs and self.nodes == other.nodes

    def __str__(self):
        return '(\033[34;1minputs: \033[0;33m' + str(self.inputs) + ' \033[0;34;1moutputs:\033[0;33m ' + str(self.outputs) + ' \033[0;34;1mnodes:\033[0m ' + str(self.nodes) + '\033[0m)'
    def __repr__(self):
        return self.__str__()

    def copy(self):
        return open_digraph(self.inputs.copy(), self.outputs.copy(), [node.copy() for node in self.nodes.values()])

    def get_input_ids(self):
        return self.inputs
    def get_output_ids(self):
        return self.outputs
    def get_id_node_map(self):
        return self.nodes
    def get_nodes(self):
        return self.nodes.values()
    def get_node_ids(self):
        return self.nodes.keys()
    def get_node_by_id(self, id):
        return self.nodes[id]
    def get_nodes_by_ids(self, id_list):
        return [self.nodes[id] for id in id_list]
    def get_free_ids(self): 
        return self.free_ids
    def set_inputs_ids(self, new_inputs):
        self.inputs = new_inputs
    def set_outputs_ids(self, new_outputs):
        self.outputs = new_outputs
    def add_input_id(self, new_input):
        self.inputs.append(new_input)
    def add_output_id(self, new_output):
        self.outputs.append(new_output)
    @classmethod
    def empty(cls) : 
        g = cls([], [], [])
        return g
    
    @classmethod
    def random(cls, n, bound, inputs=0, outputs=0, form="free"):
        """Gives a random graph given the parameters.

        Args:
            n (int): number of node
            bound (int): maximum value of the multiplicities
            inputs (int, optional): number of inputs. Defaults to 0.
            outputs (int, optional): number of outputs. Defaults to 0.
            form (str, optional): must be one of the following: free, DAG, oriented, loop-free, undirected, loop-free undirected. Defaults to "free".

        Raises:
            ValueError: if form is not one of the following: free, DAG, oriented, loop-free, undirected, loop-free undirected.

        Returns:
            open_digraph: a random graph
        """
        if form=="free":
            g = graph_from_adjency_matrix(random_int_matrix(n-inputs-outputs,bound,null_diag=False)) #ok
        elif form=="DAG":
            g = graph_from_adjency_matrix(random_triangular_int_matrix(n,bound, null_diag=True))#ok
        elif form=="oriented":
            g = graph_from_adjency_matrix(random_oriented_int_matrix(n, bound, null_diag=False))#ok
        elif form=="loop-free":
            g = graph_from_adjency_matrix(random_int_matrix(n,bound,null_diag=True))#ok
        elif form=="undirected":
            g = graph_from_adjency_matrix(random_symetric_int_matrix(n,bound,null_diag=False))#ok
        elif form=="loop-free undirected":
            g = graph_from_adjency_matrix(random_symetric_int_matrix(n,bound,null_diag=True))#ok
        else:
            raise ValueError("form must be one of the following: free, DAG, oriented, loop-free, undirected, loop-free undirected")
        
        for i in range(inputs):
            g.add_input_node(randint(0,n-inputs-outputs-1))
        for i in range(outputs):
            g.add_output_node(randint(0,n-outputs-inputs-1))
        return g

    @classmethod 
    def identity(cls, n):
        """Gives the identity graph of size n.

        Args:
            n (int): the size of the graph

        Returns:
            open_digraph: the identity graph of size n.
        """
        g = cls.empty()
        listofnodes = []
        for i in range(n):
            id = g.add_node()
            g.add_input_node(id)
            g.add_output_node(id)
        return g


    def fusionne_noeud(self,id1, id2):
        if self.nodes[id1].label != self.nodes[id2].label:
            raise RuntimeError("Labels don't match !!!! arghhhhhh")
        # sinon implicite
        if self.nodes[id2].parents != None:
            for parent_id in self.nodes[id2].parents:
                self.add_edge(parent_id, id1)
        if self.nodes[id2].children != None:
            for child_id in self.nodes[id2].children:
                self.add_edge(id1, child_id)
        
        self.remove_nodes_by_id(id2)

        return id1


        

def graph_from_adjency_matrix(matrix_):
    """Gives a graph from an adjacency matrix.

    Args:
        matrix_ (list): the adjaceboolncy matrix

    Returns:
        open_digraph: the graph
    """
    d0 = open_digraph.empty()
    n = len(matrix_)

    for i in range(n):
        d0.add_node(f'{i}')

    for i,line in enumerate(matrix_):
        for j,val in enumerate(line):
            if val!=0:
                d0.add_edges([(i,j),]*val)
    return d0







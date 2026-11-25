from typing import Dict,List, Tuple

import os
import sys
root = os.path.normpath(os.path.join(__file__, './..'))
sys.path.append(root)# allows us to fetch files from the project root
from node import *

class manipulate():
    def next_id(self) -> int:
        """Gets the next available id for a node.

        Returns:
            int: the next available id
        """
        if self.free_ids != []:
            return self.free_ids.pop()
        else:
            self.max_ids += 1
            return self.max_ids-1

    def add_edge(self, src : int, tgt : int) -> None : 
        """Adds an edge between two nodes.

        Args:
            src (int): the id of the source node
            tgt (int): the id of the target node

        Raises:
            ValueError: if the source or target node is not in the graph
        """
        src = self.get_node_by_id(src)
        tgt = self.get_node_by_id(tgt)
        #TODO : changer type node en int
        if(tgt.id <= self.max_ids and tgt.id not in self.free_ids 
            and src.id <= self.max_ids and src.id not in self.free_ids):
            tgt.add_parent(src)
            src.add_child(tgt)
        else:
            raise ValueError("The node is not in the graph")

    def add_edges(self, edges : list) -> None : 
        """Adds a list of edges to the graph.

        Args:
            edges (list): a list of edges, each edge being a tuple of two nodes
        """
        for edge in edges : 
            self.add_edge(edge[0], edge[1])
    
    def add_node(self, label : str = '', parents : dict = None, children : dict = None) -> int : 
        """Adds a node to the graph.

        Args:
            label (str, optional): label of the node to add. Defaults to ''.
            parents (dict, optional): parents of the node to add. Defaults to None.
            children (dict, optional): children of the node to add. Defaults to None.

        Returns:
            int: the id of the added node
        """
        #TODO : demander si on peut ajouter direct un noeud (genre add_node(node(...)))
        new_node = node(self.next_id(), label, None, None)
        self.nodes[new_node.get_id()] = new_node
        if(parents is not None): 
            for parent in parents:
                self.add_edge(parent.id, new_node.id)
        if(children is not None):
            for child in children:
                self.add_edge(new_node.id, child.id)
        return new_node.get_id()


    def remove_edge(self, src : int, tgt : int) -> None:
        """Removes an edge between two nodes.

        Args:
            src (int): id of the source node
            tgt (int): id of the target node

        Raises:
            ValueError: if the source or target node is not in the graph
        """
        if(tgt < self.max_ids and tgt not in self.free_ids
        and src < self.max_ids and src not in self.free_ids):
            try :
                self.nodes[tgt].remove_parent_once(src)
                self.nodes[src].remove_child_once(tgt)
            except ValueError as e:
                raise RuntimeError(f"Remove edge : try remove_parent_once & remove_child_once. Erreur : {e}")
        else : 
            raise ValueError("The node is not in the graph")


    def remove_parallel_edges(self, src : int, tgt : int) -> None:
        """Removes all parallel edges between two nodes.

        Args:
            src (int): id of the source node
            tgt (int): id of the target node

        Raises:
            ValueError: if the source or target node is not in the graph
        """
        if(tgt < self.max_ids and tgt not in self.free_ids
        and src < self.max_ids and src not in self.free_ids):
            try :
                self.nodes[tgt].remove_parent_id(src)
                self.nodes[src].remove_child_id(tgt)
            except ValueError as e:
                raise RuntimeError(f"Remove edge : try remove_parent_id & remove_child_id. Erreur : {e}")
        else : 
            raise ValueError("The node is not in the graph")
    

    def remove_several_parallel_edges(self, pairs : List[Tuple[int, int]]) -> None:
        """Removes all parallel edges between several pairs of nodes.

        Args:
            pairs (List[Tuple[int, int]]): a list of pairs of nodes
        """
        for (src, tgt) in pairs:
            self.remove_parallel_edges(src, tgt)
        
    def remove_edges(self, pairs : List[Tuple[int, int]]) -> None:
        """
        Removes one edge between several pairs of nodes.
        """
        for (src, tgt) in pairs:
            self.remove_edge(src, tgt)
    
    def remove_nodes_by_id(self, *args: int) -> None:
        """Removes several nodes from the graph.

        Raises:
            ValueError: if the node is not in the graph
        """
        for id in args:
            if id <= self.max_ids and id not in self.free_ids:
                n = self.get_node_by_id(id)
                if n.parents is not None:
                    self.remove_several_parallel_edges([(p_id, id) for p_id in n.parents.keys()])
                if n.children is not None:
                    self.remove_several_parallel_edges([(id, c_id) for c_id in n.children.keys()])
                del self.nodes[id]
                if id in self.inputs:
                    self.inputs.remove(id)
                if id in self.outputs:
                    self.outputs.remove(id)
                self.free_ids.append(id)
            else:
                raise ValueError(f"The node (id = {id}) is not in the graph")


    


    def add_input_node(self, idpointed : int) -> None:
        """Adds an input node to the graph and connects it to the node with the given id.

        Args:
            idpointed (int): id of the node to point to

        Raises:
            ValueError: if the node is not in the graph or you're trying to point to an input node
        """
        if idpointed in self.nodes.keys() and idpointed not in self.inputs:
            n = self.add_node()
            self.get_node_by_id(n).set_label("i" + str(n))
            self.inputs.append(n)
            self.add_edge(n, idpointed)
        else:
            raise ValueError("The node is not in the graph or you're trying to point to an input node")

    def add_output_node(self, idpointed : int) -> None:
        """Adds an output node to the graph and connects it to the node with the given id.

        Args:
            idpointed (int): id of the node to point to

        Raises:
            ValueError: if the node is not in the graph or you're trying to make an output node point to another output node
        """
        if idpointed in self.nodes.keys() and idpointed not in self.outputs:
            n = self.add_node()
            self.get_node_by_id(n).set_label("o" + str(n))
            self.outputs.append(n)
            self.add_edge(idpointed, n)
        else:
            raise ValueError("The node is not in the graph or you're trying to make an output node point to another output node")
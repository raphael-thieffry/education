class structure():
    def is_cyclic(self):
        """Checks if the graph is cyclic.
        returns True if the graph is cyclic, False otherwise."""
        g = self.copy()
        if(g.nodes=={}):
            return False
        else:
            tobeRemoved = None
            for id, node in g.nodes.items():
                if node.outdegree() == 0:
                    tobeRemoved = node.id
            if(tobeRemoved==None):
                return True
            g.remove_nodes_by_id(tobeRemoved)
            return g.is_cyclic()
        
    def max_id(self):
            """Gives the maximum id of the graph.

            Returns:
                int: the maximum id of the graph.
            """
            if self.nodes=={}:
                raise ValueError("The graph is empty")
            return max(self.nodes.keys())

    def min_id(self):
        """Gives the minimum id of the graph.

        Returns:
            int: the minimum id of the graph.
        """
        if self.nodes=={}:
            raise ValueError("The graph is empty")
        return min(self.nodes.keys())
    
    def is_well_formed(self):
        """
            check if open_digraph instance is well formed
              1- input and output nodes are registered by id in nodes(dict: int->Node)
              2- input nodes have one child and no parents
              3- output nodes have one parent and no child
              4- Node instances registered by id in nodes have the correct id (.get_id())
              5- multiplicities coincide in connected instances of Node in nodes(dict: int->Node)
        """
        # check for 1
        for id in self.inputs:
            if id not in self.nodes:
                print("input not in graph")
                return False
        for id in self.outputs:
            if id not in self.nodes:
                print("output not in graph")
                return False
        # check for 2
        for id in self.inputs:
            if self.nodes[id].parents != None:
                print("input has parents")
                return False
            dico = self.nodes[id].children
            if len(dico)!=1 or list(dico.values())[0]!=1:
                print("input has more than one child")
                return False
        # check for 3
        for id in self.outputs:
            if self.nodes[id].children != None:
                print("output has children")
                return False
            dico = self.nodes[id].parents
            if len(dico)!=1 or list(dico.values())[0]!=1:
                print("output has more than one parent")
                return False
        # check for 4
        for id in self.nodes:
            if self.nodes[id].get_id()!=id:
                print("node has wrong id")
                return False
        # check for 5
        for id in self.nodes:
            lst = self.nodes[id].get_children_ids()
            for child_id in lst:
                if self.nodes[id].children[child_id]!=self.nodes[child_id].parents[id]:
                    print("multiplicity error")
                    return False
        return True

    def assert_is_well_formed(self)->None:
        """raise runtime error if open_digraph instance is not well formed"""
        if not self.is_well_formed():
            raise RuntimeError("graph is not well formed")
        
    def uniqueForEveryId(self):
        """Gives a dictionary that associates to every id a unique number.

        Returns:
            dict: a dictionary that associates to every id a unique number.
        """
        dic = {}
        current = 0
        for id in self.nodes.keys():
            dic[id] = current
            current+=1
        return dic
    
    def adjacency_matrix(self):
        """Gives the adjacency matrix of the graph."""
        dic = self.uniqueForEveryId()
        n = len(dic)
        matrix = [[0]*n for _ in range(n)]
        for id in self.get_node_ids():
            for child_id in self.nodes[id].get_children_ids():
                matrix[dic[id]][dic[child_id]] = self.nodes[id].children[child_id]
        return matrix
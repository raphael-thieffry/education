class compo():
    def shift_indices(self, n):
        """Shifts the indices of the graph by n.

        Args:
            n (int): the shift
        Returns:
            None
        """
        self.max_ids += n
        for id, node in self.nodes.items():
            node.id+=n
            if(not(node.children==None)):
                node.children = {id+n:mult for id, mult in node.children.items()}
            if(not(node.parents==None)):
                node.parents = {id+n:mult for id, mult in node.parents.items()}
        self.nodes = {id+n:node for id, node in self.nodes.items()}
        self.inputs = [id+n for id in self.inputs]
        self.outputs = [id+n for id in self.outputs]
        self.free_ids = [id+n for id in self.free_ids]

    def iparallel(self, g):
        """Gives the parallel composition of the graph and g. Modifies the graph.

        Args:
            g (open_digraph): the graph

        Returns:
            None
        """
        g2 = g.copy()
        self.shift_indices(-self.min_id())
        g2.shift_indices(-g2.min_id()+self.max_id()+1)
        self.max_ids = g2.max_ids

        self.nodes.update(g2.nodes)
        self.inputs += g2.inputs
        self.outputs += g2.outputs

    def parallel(self, g):
        """Gives the parallel composition of the graph and g.

        Args:
            g (open_digraph): the graph

        Returns:
            open_digraph: the parallel composition of the graph and g.
        """
        g1 = self.copy()
        g2 = g.copy()
        g1.shift_indices(-g1.min_id())
        g2.shift_indices(-g2.min_id()+g1.max_id()+1)
        g1.max_ids = g2.max_ids

        g1.nodes.update(g2.nodes)
        g1.inputs += g2.inputs
        g1.outputs += g2.outputs
        return g1

    def icompose(self, g):
        """Gives the composition of the graph and g. Modifies the graph.

        /!\ deprecated, new version below in methode "compose", to be adapted

        Args:
            g (open_digraph): the graph

        Returns:
            None
        """
        g2 = g.copy()
        self.shift_indices(-self.min_id())
        g2.shift_indices(-g2.min_id()+self.max_id()+1)
        self.max_ids = g2.max_ids
        if(len(g2.outputs)!=len(self.inputs)):
            raise ValueError("The number of inputs of g must be equal to the number of outputs of the graph")
        for i in range(len(g2.outputs)):
            self.add_edge(g2.outputs[i],self.inputs[i])
        self.nodes.update(g2.nodes)
        self.inputs = g2.inputs

    def compose(self, g):
        """Gives the composition of the graph and g.

        Args:
            g (open_digraph): the graph

        Returns:
            open_digraph: the composition of the graph and g.
        """
        g1 = self.copy()
        g2 = g.copy()
        g1.shift_indices(-g1.min_id())
        g2.shift_indices(-g2.min_id()+g1.max_id()+1)
        g1.nodes.update(g2.nodes)
        g1.max_ids = g2.max_ids
        if(len(g2.outputs)!=len(g1.inputs)):
            raise ValueError("The number of inputs of g must be equal to the number of outputs of the graph")
        
        parentsg2outputs = [list(g2.get_node_by_id(o).get_parents_ids())[0] for o in g2.outputs]
        filsg1inputs = [list(g1.get_node_by_id(i).get_children_ids())[0] for i in g1.inputs]

        for i in range(len(filsg1inputs)):
            g1.add_edge(parentsg2outputs[i],filsg1inputs[i])

        #enleve les inputs/outputs en trop
        for i in range(len(g1.inputs)):
            torem = g1.inputs.pop(0)
            g1.remove_nodes_by_id(torem)       
        for o in g2.outputs:
            g1.remove_nodes_by_id(o)

        g1.inputs = g2.inputs
        return g1
    
    # def connected_components(self):
    #     g=self.copy()
    #     cpt_comp_connexe=0
    #     if g==open_digraph.empty():
    #         return 0
    #     else:
    #         for id, node in g.nodes.items():
    #             if node.indegree()==0:
    #                 cpt_comp_connexe+=1
    #                 g.aux_connected_components(node,cpt_comp_connexe,{})
    #         return cpt_comp_connexe
             
            
    #def aux_connected_components(node,r,dico):
        


    def get_voisins(self, id, voisins=set()):
        if id in voisins:
            return voisins

        voisins.add(id)
        if self.nodes[id].parents != None:
            for parent_id in self.nodes[id].parents:
                self.get_voisins(parent_id, voisins)
        if self.nodes[id].children != None:
            for child_id in self.nodes[id].children:
                self.get_voisins(child_id, voisins)
        return voisins

    def connected_components(self):
        dico = dict()
        idcc = -1
        ids = set(self.nodes.keys())

        # chercher tous les voisins directes
        while len(ids)!=0:
            idcc += 1
            id = list(ids)[0]
            voisins = self.get_voisins(id, voisins=set())
            ids = ids - voisins
            for voisin in voisins:
                dico[voisin] = idcc
        return idcc+1,dico
    
    def dismember(self):
        """Dismembers the graph into a list of graphs.
        """
        idcc, components = self.connected_components()
        lst_components = [[id for id in components if components[id]==i]
                          for i in range(idcc)]
        lst_graph = []
        for component_ids in lst_components:
            g = self.__class__.empty()
            new_nodes = {id:node for (id,node) in zip(self.nodes, self.nodes.values()) if id in component_ids}
            g.nodes = new_nodes
            lst_graph.append(g)
        return lst_graph
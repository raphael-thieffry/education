class longueur():
    def dijkstra(self, src, direction = None, tgt = None):
        """Gives the shortest path from src to all the nodes of the graph. Dijkstra algorithm.
        """
        Q = [src]
        dist = {src:0}
        prev={}
        while Q != []:
            u = min(Q, key = lambda x: dist[x])
            if tgt != None and u == tgt:
                return dist, prev
            Q.remove(u)
            if direction == 1 :
                neighbours = self.nodes[u].children
            elif direction == -1 :
                neighbours = self.nodes[u].parents 
            else :
                d1 = self.nodes[u].children if self.nodes[u].children != None else {}
                d2 = self.nodes[u].parents if self.nodes[u].parents != None else {}
                neighbours = d1|d2
            if neighbours == None:
                continue
            for v in neighbours:
                if v not in dist: 
                    Q.append(v)
                if v not in dist or dist[v]>dist[u]+1:
                    dist[v]=dist[u]+1
                    prev[v]=u
                
        return dist, prev

    def shortest_path(self, src, tgt):
        """Gives the shortest path from src to tgt. Dijkstra algorithm.
        """
        dist, prev = self.dijkstra(src, tgt = tgt)
        path = []
        u = tgt
        while u != src:
            path.append(u)
            u = prev[u]
        path.append(src)
        path.reverse()
        return path
    
    def distancetrecommun(self, n1:int, n2:int):
        """Returns a dictionary where each common ancestor of n1 and n2 is associated to its distance to n1 and n2.
        """
        dist1, prev1 = self.dijkstra(n1, direction = -1)
        dist2, prev2 = self.dijkstra(n2, direction = -1)
        dist = {}
        for k in dist1.keys() & dist2.keys():
            dist[k] = (dist1[k], dist2[k])
        return dist
    
    def get_cofeuilles(self):
        """Returns the list of the co-leaves of the graph.
        return a list of ids.
        """
        return [id for id in self.nodes if self.nodes[id].indegree()==0]

    def tri_topo(self):
        """Returns a topological sort of the graph.
        returns a list of lists of ids.
        """
        g = self.copy()
        f = g.get_cofeuilles()
        if f == []:
            if g.nodes != {}:
                raise ValueError("The graph is not acyclic.")
            else:
                return f
        else:
            g.remove_nodes_by_id(*f)
            return [f] + g.tri_topo()
        
    def max_dist(self, u, v):
        """Returns the maximum distance between u and v.

        Args:
            u (int): Node id
            v (int): Node id

        Returns:
            _type_ : The longest path and its length between u and v.
        """
        t = self.tri_topo()
        ui = -1
        for i, l in enumerate(t):
            if u in l:
                ui = i
        if(ui == -1):
            raise ValueError("u is not in the graph.")
        dist = {u:0}
        prev = {} #id noaud : id predecesseur
        flag = False
        for i in range(ui+1, len(t)):
            for w in t[i]:
                wnode = self.get_node_by_id(w)
                if wnode.parents == None:
                    continue
                parentsdansdist = False
                parentavecladistmax = None
                distmax = 0
                for p in wnode.parents:
                    if p in dist :
                        parentsdansdist = True
                        if dist[p] >= distmax:
                            distmax = dist[p]
                            parentavecladistmax = p
                if parentsdansdist:
                    dist[w] = distmax + 1
                    prev[w] = parentavecladistmax
                if w == v:
                    flag = True
                    break
            if flag:
                break
        if not flag:
            raise ValueError("v n'est pas accessible.")
        path = []
        ubis = v
        while ubis != u:
            path.append(ubis)
            ubis = prev[ubis]
        path.append(u)
        path.reverse()
        return (path, dist[v])

    def profondeur_noeud(self,node):
        """Return the depth of a node in a  graph
        Starts at 0
        node is the id of the node"""
        lst=self.tri_topo()
        for i in range (len(lst)):
            for j in range (len(lst[i])):
                    if lst[i][j]==node:
                        return i
        raise ValueError("node not in graphe")

    def profondeur_graphe(graphe):
        """Return the depth of the graph
        Starts at 0"""
        return len(graphe.tri_topo())-1
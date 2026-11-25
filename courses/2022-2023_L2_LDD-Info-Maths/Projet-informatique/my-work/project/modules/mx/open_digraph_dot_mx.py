import re
import os


class dot():
    def save_as_dot_file(self,path,verbose=False):
        """Saves the graph as a dot file.

        Args:
            path (string): path to the file
            verbose (bool, optional): _description_. Defaults to True.
        """
        contenu= 'digraph G {\n'
        for node_id in self.nodes:
            if verbose:
                label = "'"+self.nodes[node_id].label +"'"+ f":{node_id}"
            else:
                label = self.nodes[node_id].label
            if len(label)!=0:
                    contenu += f"v{node_id}"
                    contenu += f" [label=\"{label}\"];"
                    contenu += "\n"
        
        for node_id, node_ in self.nodes.items():
            children_ids = node_.children
            if children_ids!=None and len(children_ids)!=0:
                for child_id, multiplicite in children_ids.items():
                    for _ in range(multiplicite):
                        contenu += f"v{node_id} -> v{child_id};\n"

        contenu += "}"
        with open(path, "w") as fichier:
            fichier.write(contenu)

    @classmethod
    def from_dot_file(cls, path):
        with open(path, "r") as fichier:
            contenu = fichier.readlines()
        
        del contenu[0]
        del contenu[-1]
        contenu = [ligne[:-2] for ligne in contenu]
        nom_noeuds = dict()
        for i,ligne in enumerate(contenu):
            declaration = re.findall('\S+ \[label="\S*"\]', ligne)
            if declaration!=[]:
                declaration = declaration[0]
                nom = re.findall('\S+ ', declaration)[0].strip()
                label = re.findall('".*"', declaration)[0][1:-1].strip()
                nom_noeuds[nom] = label

        G = cls.empty()
        # print(nom_noeuds, contenu)
        for noeud_vid in nom_noeuds:
            id = G.add_node(label=nom_noeuds[noeud_vid])
            nom_noeuds[noeud_vid] = id
        for  ligne in contenu :
            aretes = ligne.split("->")
            aretes = [arete.strip() for arete in aretes]
            for noeud in range(len(aretes)-1):
                # print(ligne , aretes)
                if aretes[noeud] not in nom_noeuds:
                    id = G.add_node()
                    nom_noeuds[aretes[noeud]] = id
                if aretes[noeud+1] not in nom_noeuds:
                    id = G.add_node()
                    nom_noeuds[aretes[noeud+1]] = id                
                
                id1 = nom_noeuds[aretes[noeud]]
                id2 = nom_noeuds[aretes[noeud+1]]
                G.add_edge(id1, id2)
        return G
    
    def display(self, verbose=False):
        self.save_as_dot_file('.temp.dot', verbose=verbose)
        os.system("dot -Tpdf .temp.dot -o .temp.pdf")
        os.system("open .temp.pdf")
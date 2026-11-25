from .open_digraph import *


class bool_circ(open_digraph):

    def is_well_formed(self):
        """Checks if the graph is well formed.

        Returns:
            bool: True if the graph is well formed, False otherwise.
        """

        for id, node in self.nodes.items():
            if node.get_label() == '' and node.indegree() != 1:
                print("copie avec + d'un parent")
                return False
            if (
                    node.get_label() == '^' or node.get_label() == '&' or node.get_label() == '|') and node.outdegree() != 1:
                print("operateur avec + d'un enfant")
                print(node.get_id())
                return False
            if node.get_label() == '~' and (node.outdegree() != 1 or node.indegree() != 1):
                print("negation avec + d'un enfant ou + d'un parent")
                return False
            if node.get_label() == '1' and (node.outdegree() != 1 or node.indegree() != 0):
                print("1 avec + d'un enfant ou un parent")
                return False
            if node.get_label() == '0' and (node.outdegree() != 1 or node.indegree() != 0):
                print("0 avec + d'un enfant ou un parent")
                return False
        return self.is_cyclic() == False and open_digraph.is_well_formed(self)  # and self.graph.is_oriented()==True

    def copy(self):
        """Makes a copy of the graph.

        Returns:
            bool_circ: the copy of the graph
        """
        return bool_circ(open_digraph.copy(self))

    def __init__(self, graph):
        """Initializes the bool_circ class.

        Args:
            graph (open_digraph): the graph
        """

        # demander si il faut changer les labels
        if (isinstance(graph, open_digraph)):
            super().__init2__(graph)
        elif (not (self.is_well_formed(graph))):
            raise ValueError("The graph is not well formed")
        else:
            self = open_digraph.empty()

    def parse_parentheses(self, *args):
        """Parses a string to get the list of the nodes.

        Args:
            s (str): the string

        Returns:
            list: the list of the nodes
        """
        self = open_digraph.empty()

        valid_chars = ['^', '&', '|', '~', '(', ')', '']
        var_list = {}  # name associated with id
        s2 = ''
        for s in args:
            current_node = self.add_node()
            self.add_output_node(current_node)
            for c in s:
                if c == '(':
                    n = self.get_node_by_id(current_node)
                    n.set_label(n.get_label() + s2)

                    p = self.add_node()
                    self.add_edge(p, current_node)
                    current_node = p

                    s2 = ''
                elif c == ')':
                    n = self.get_node_by_id(current_node)
                    if s2 not in valid_chars:
                        n.set_label('')
                        if s2 not in var_list:
                            var_list[s2] = [current_node]
                        else:
                            # print(f"je fusionne {var_list[s2]} ({self.get_node_by_id(var_list[s2][0]).get_label()}) et {current_node} ({self.get_node_by_id(current_node).get_label()})")
                            var_list[s2].append(current_node)
                    else:
                        n.set_label(n.get_label() + s2)
                    current_node = list(n.get_children_ids())[0]
                    s2 = ''
                else:
                    s2 += c
            s2 = ''

        for k, v in var_list.items():
            self.add_input_node(v[0])
            for i in range(1, len(v)):
                self.fusionne_noeud(v[0], v[i])

        return self, list(var_list.keys())

    @classmethod
    def random(cls, n, binary=['^', '&', '|'], unary=['~'], inputs=None, outputs=None):
        """Gives a random graph.

        Args:
            n (int): the number of nodes
            inputs (int): the number of input nodes
            outputs (int): the number of output nodes
            form (str, optional): the form of the graph. Defaults to "free".

        Returns:
            open_digraph: the random graph
        """
        g = super().random(n, inputs=0, outputs=0, bound=randint(1, 5), form="DAG")
        for id, node in list(g.nodes.items()).copy():
            if node.indegree() == 0:  # pas de parent
                g.add_input_node(id)
                # indegree = 1 maintenant
            if node.outdegree() == 0:  # pas d'enfant
                g.add_output_node(id)
                # outdegree = 1 maintenant
        if inputs != None:
            # modifie la quantié d'inputs
            if len(g.inputs) > inputs:
                # trop d'inputs
                gi = g.inputs.copy()
                aSup = []
                for i in range(len(g.inputs) - inputs):
                    # selectionne aléatoirement ceux qu'il faut supprimer
                    aSup.append(gi.pop(randint(0, len(g.inputs) - 1)))

                while len(aSup) >= 2:
                    # fusionne les noeuds à supprimer tant qu'il n'en reste au moins 2
                    cp1 = aSup.pop(randint(0, len(aSup) - 1))
                    cp2 = aSup.pop(randint(0, len(aSup) - 1))
                    cpParent = g.add_node(label='')
                    nd1 = g.get_node_by_id(cp1)
                    nd2 = g.get_node_by_id(cp2)
                    nd1.set_label('')
                    nd2.set_label('')
                    g.add_edge(cpParent, cp1)
                    g.add_edge(cpParent, cp2)
                    aSup.append(cpParent)
                # reste 1 input en trop (le dernier de aSup)
                cp1 = aSup.pop(randint(0, len(aSup) - 1))
                i = g.inputs[randint(0, len(g.inputs) - 1)]
                cpDouble = g.add_node(label='')
                nd1 = g.get_node_by_id(cp1)
                input = g.get_node_by_id(i)
                filsInput = list(input.get_children_ids())[0]
                g.remove_edge(i, filsInput)
                g.add_edge(cpDouble, filsInput)
                g.add_edge(cpDouble, cp1)
                g.add_edge(i, cpDouble)
            elif len(g.inputs) < inputs:
                # pas assez d'inputs

                # liste noeuds non inputs
                nonInputs = [n for n in g.nodes.keys() if n not in g.inputs and n not in g.outputs]
                for i in range(inputs - len(g.inputs)):
                    g.add_input_node(nonInputs[randint(0, len(nonInputs) - 1)])
        if outputs != None:
            # modifie la quantié d'outputs
            if len(g.outputs) > outputs:
                # trop d'inputs
                go = g.outputs.copy()
                aSup = []
                for i in range(len(g.outputs) - outputs):
                    # selectionne aléatoirement ceux qu'il faut supprimer
                    aSup.append(go.pop(randint(0, len(g.outputs) - 1)))

                while len(aSup) >= 2:
                    # fusionne les noeuds à supprimer tant qu'il n'en reste au moins 2 grace à des operations binaires
                    cp1 = aSup.pop(randint(0, len(aSup) - 1))
                    cp2 = aSup.pop(randint(0, len(aSup) - 1))
                    cpFils = g.add_node(label=binary[randint(0, len(binary) - 1)])
                    nd1 = g.get_node_by_id(cp1)
                    nd2 = g.get_node_by_id(cp2)
                    nd1.set_label(binary[randint(0, len(binary) - 1)])
                    nd2.set_label(binary[randint(0, len(binary) - 1)])
                    g.add_edge(cp1, cpFils)
                    g.add_edge(cp2, cpFils)
                    aSup.append(cpFils)
                # reste 1 input en trop (le dernier de aSup)
                cp1 = aSup.pop(randint(0, len(aSup) - 1))
                o = g.outputs[randint(0, len(g.outputs) - 1)]
                cpBinFusionne = g.add_node(label=binary[randint(0, len(binary) - 1)])
                nd1 = g.get_node_by_id(cp1)  # noeud aggregeant tous les trucs à supprimer
                output = g.get_node_by_id(o)  # noeud dans lequel faut tout aggreg
                parentOutput = list(output.get_parents_ids())[0]
                g.remove_edge(parentOutput, o)
                g.add_edge(parentOutput, cpBinFusionne)
                g.add_edge(cp1, cpBinFusionne)
                g.add_edge(cpBinFusionne, o)
            elif len(g.outputs) < outputs:
                # pas assez d'outputs

                # liste noeuds non inputs
                nonOutputs = [n for n in g.nodes.keys() if n not in g.outputs and n not in g.inputs]
                for i in range(outputs - len(g.outputs)):
                    g.add_output_node(nonOutputs[randint(0, len(nonOutputs) - 1)])

        for id, node in list(g.nodes.items()).copy():

            if id in g.inputs or id in g.outputs:
                continue

            if node.outdegree() == 1:
                if node.indegree() == 1:
                    # operateur unaire
                    node.set_label(random.choice(unary))
                elif node.indegree() > 1:  # indegree > 1
                    # operateur binaire
                    node.set_label(random.choice(binary))
            elif node.outdegree() > 1:  # outdegree > 1
                if node.indegree() == 1:
                    # operateur unaire
                    node.set_label('')  # copie
                elif node.indegree() > 1:  # indegree > 1
                    # on va faire u => uep et op est créé exnihilo

                    parentsU = node.parents.copy()  # on garde les parents de u avec multiplicité
                    g.remove_several_parallel_edges(
                        [(p, id) for p in parentsU.keys()])  # on enlève les aretes parents => u
                    node.set_label('')  # on met le label de u à vide

                    idop = g.add_node()  # on crée op
                    nodeop = g.get_node_by_id(idop)
                    nodeop.set_label(random.choice(binary))  # on lui donne un label
                    for p, mul in parentsU.items():  # on crée les aretes parentsU => op
                        for i in range(mul):
                            g.add_edge(p, idop)

                    g.add_edge(idop, id)  # on crée l'arete op => u

        return g

    @classmethod
    def check_power_of_two(cls, n):
        while True:
            if n % 2 == 1:
                return False
            elif n == 2:
                return True

            n = n // 2
        return True

    @classmethod
    def list_half_adder(cls, registre1, registre2):
        n = len(registre1)
        m = len(registre2)
        assert n == m, "les deux registres ne sont pas meme longueurs"
        assert bool_circ.check_power_of_two(n), "la longueur des registres n'est pas une puissance de deux"
        carry = 0
        result = []
        for i in range(n - 1, -1, -1):
            somme = registre1[i] + registre2[i] + carry
            result.append(somme % 2)
            carry = somme // 2

        result.reverse()
        return carry, result

    @classmethod
    def list_adder(cls, registre1, registre2, carry):
        n = len(registre1)
        m = len(registre2)
        assert n == m, "les deux registres ne sont pas meme longueurs"
        assert bool_circ.check_power_of_two(n), "la longueur des registres n'est pas une puissance de deux"
        result = []
        for i in range(n - 1, -1, -1):
            somme = registre1[i] + registre2[i] + carry
            result.append(somme % 2)
            carry = somme // 2

        result.reverse()
        return carry, result

    @classmethod
    def adder(cls, n, circuit=None) -> open_digraph:
        # todo: make sure to label as input and output nodes
        """
            Makes an adder boolean graph,
            the returned graph has 2 registers of size 2^n and a carry input node
            It contains 2^n output nodes and a carry output nodes
            Args:
                n: the log2 of the register size of the requested adder
            Returns: bool_circ

        """

        def make_adder0():
            a = circuit.add_node()
            b = circuit.add_node()
            c = circuit.add_node()
            d = circuit.add_node("^")
            e = circuit.add_node()
            f = circuit.add_node("^")
            g = circuit.add_node("&")
            h = circuit.add_node("|")
            i = circuit.add_node("&")
            circuit.add_output_node(f)
            circuit.add_input_node(a)
            circuit.add_input_node(b)
            circuit.add_edge(a, d)
            circuit.add_edge(a, i)
            circuit.add_edge(b, d)
            circuit.add_edge(b, i)
            circuit.add_edge(d, e)
            circuit.add_edge(c, g)
            circuit.add_edge(c, f)
            circuit.add_edge(e, f)
            circuit.add_edge(e, g)
            circuit.add_edge(g, h)
            circuit.add_edge(i, h)
            return c, h

        assert (circuit is None) or \
               type(circuit) == type(bool_circ(open_digraph.empty())), \
            "Doit etre un circuit booleen"

        if n == 0 and circuit is not None:
            c, h = make_adder0()
            circuit.add_output_node(h)
            return c

        elif n == 0 and circuit is None:
            circuit = bool_circ(open_digraph.empty())
            c, h = make_adder0()
            circuit.add_input_node(c)
            circuit.add_output_node(h)
            return circuit

        else:
            if circuit is None:
                circuit = bool_circ(open_digraph.empty())

                retenu = cls.adder(2 ** n - 1, circuit)
                assert len(circuit.inputs) % 2 == 0
                registre1 = [node_id for i, node_id in enumerate(circuit.inputs) if i % 2 == 0]
                registre2 = [node_id for i, node_id in enumerate(circuit.inputs) if i % 2 == 1]
                circuit.inputs = registre1 + registre2
                circuit.add_input_node(retenu)
                return circuit

            else:
                retenu = cls.adder(n - 1, circuit)
                c, h = make_adder0()
                circuit.add_edge(h, retenu)
                return c

    @classmethod
    def half_adder(cls, n):
        """
            Simplement un adder sans retenue en input.
        """
        adder = cls.adder(n)
        trucaremplacerpar0 = adder.get_node_by_id(adder.inputs[-1])
        trucaremplacerpar0.set_label('0')
        # print("voici outputs avant remove", adder.outputs)
        adder.inputs.remove(trucaremplacerpar0.id)
        return adder

    @classmethod
    def fromint(cls, n, regsize=8):
        """
            Forme un registre (type: bool_circ) representant n en binaire.
        Args:
            regsize=8: nombre d'output du registre.
        """
        circuit = bool_circ(open_digraph.empty())
        bits = list(bin(n % (2 ** regsize))[2:])
        for bit in [0] * (regsize - len(bits)) + bits:
            id = circuit.add_node(str(bit))
            circuit.add_output_node(id)
        return circuit

    def simplifie(self, a, b=None):
        """prend 2 ids ou 1 seul et simplifie selon des regles connues

        Args:
            a int: id du premier noeud
            b int | None: id du deuxieme noeud potentiel

        Returns:
            bool: True si simplification a eu lieu, False sinon
        """
        if b is None:
            # elements neutres
            if (nodea := self.get_node_by_id(a)).label in ['|', '^']:
                if nodea.indegree() == 0 and nodea.outdegree() == 1:
                    nodea.set_label('0')

            if (nodea := self.get_node_by_id(a)).label == '&':
                if nodea.indegree() == 0 and nodea.outdegree() == 1:
                    nodea.set_label('1')
        else:
            nodea = self.get_node_by_id(a)
            nodeb = self.get_node_by_id(b)

            def gere_copie(self: open_digraph, ida: int, idb: int):
                """ check : in from a, out from a, in from b, out from b"""
                nodea = self.get_node_by_id(ida)
                nodeb = self.get_node_by_id(idb)
                if (nodea.indegree() != 0 or nodea.outdegree() != 1) or nodeb.indegree() != 1 or \
                        list(nodeb.get_parents_ids())[0] != a:
                    return
                # a est 0 ou 1
                # b est copie
                self.remove_edge(ida, idb)
                label = self.get_node_by_id(ida).label
                filsCp = list(self.get_node_by_id(idb).get_children_ids())
                for f in filsCp:
                    current = self.add_node(label)
                    self.add_edge(current, f)
                self.remove_nodes_by_id(idb)
                self.remove_nodes_by_id(ida)

            def gere_non(self: open_digraph, ida: int, idb: int):
                """check : in from a, out from a, in from b, out from b"""
                # a est 0 ou 1
                # b est non
                nodea = self.get_node_by_id(ida)
                nodeb = self.get_node_by_id(idb)
                if (
                        nodea.indegree() != 0 or nodea.outdegree() != 1) or nodeb.indegree() != 1 or nodeb.outdegree() != 1 or \
                        list(nodeb.get_parents_ids())[0] != a:
                    return
                self.remove_edge(ida, idb)
                label = self.get_node_by_id(ida).label
                filsNon = list(self.get_node_by_id(idb).get_children_ids())[0]
                self.remove_nodes_by_id(idb)
                self.remove_nodes_by_id(ida)
                if label == '0':
                    label = '1'
                elif label == '1':
                    label = '0'
                replacement = self.add_node(label)
                self.add_edge(replacement, filsNon)

            def gere_and(self: open_digraph, ida: int, idb: int):
                # a est 0 ou 1
                # b est and
                nodea = self.get_node_by_id(ida)
                nodeb = self.get_node_by_id(idb)
                if nodea.indegree() != 0 or nodea.outdegree() != 1 or nodeb.outdegree() != 1:
                    print("noeuds invalides")
                    print(nodea.indegree(), nodea.outdegree(), nodeb.outdegree())
                    return
                label = nodea.label
                if label == '0':
                    filsand = list(nodeb.get_children_ids())[0]
                    self.remove_nodes_by_id(ida)
                    parentsandsauf0 = list(nodeb.get_parents_ids())
                    self.remove_nodes_by_id(idb)
                    zero = self.add_node('0')
                    self.add_edge(zero, filsand)
                    for p in parentsandsauf0:
                        cp = self.add_node('')
                        self.add_edge(p, cp)
                if label == '1':
                    self.remove_nodes_by_id(ida)

            def gere_or(self: open_digraph, ida: int, idb: int):
                # a est 0 ou 1
                # b est or
                nodea = self.get_node_by_id(ida)
                nodeb = self.get_node_by_id(idb)
                if nodea.indegree() != 0 or nodea.outdegree() != 1 or nodeb.outdegree() != 1:
                    return
                label = nodea.label
                if label == '0':
                    self.remove_nodes_by_id(ida)
                if label == '1':
                    filsor = list(nodeb.get_children_ids())[0]
                    self.remove_nodes_by_id(ida)
                    parentsorsauf1 = list(nodeb.get_parents_ids())
                    self.remove_nodes_by_id(idb)
                    one = self.add_node('1')
                    self.add_edge(one, filsor)
                    for p in parentsorsauf1:
                        cp = self.add_node('')
                        self.add_edge(p, cp)

            def gere_xor(self: open_digraph, ida: int, idb: int):
                # a est 0 ou 1
                # b est xor
                nodea = self.get_node_by_id(ida)
                nodeb = self.get_node_by_id(idb)
                if nodea.indegree() != 0 or nodea.outdegree() != 1 or nodeb.outdegree() != 1:
                    return
                label = nodea.label
                if label == '0':
                    self.remove_nodes_by_id(ida)
                if label == '1':
                    filsxor = list(nodeb.get_children_ids())[0]
                    self.remove_nodes_by_id(ida)
                    non = self.add_node('~')
                    self.add_edge(non, filsxor)
                    self.add_edge(idb, non)
                    self.remove_edge(idb, filsxor)

            alabel = nodea.get_label()
            blabel = nodeb.get_label()
            abtuple = (alabel, blabel)
            if abtuple == ('0', ''):
                gere_copie(self, a, b)
                return True
            elif abtuple == ('', '0'):
                gere_copie(self, b, a)
                return True
            elif abtuple == ('1', ''):
                gere_copie(self, a, b)
                return True
            elif abtuple == ('', '1'):
                gere_copie(self, b, a)
                return True
            elif abtuple == ('0', '~'):
                gere_non(self, a, b)
                return True
            elif abtuple == ('~', '0'):
                gere_non(self, b, a)
                return True
            elif abtuple == ('1', '~'):
                gere_non(self, a, b)
                return True
            elif abtuple == ('~', '1'):
                gere_non(self, b, a)
                return True
            elif abtuple == ('0', '&'):
                gere_and(self, a, b)
                return True
            elif abtuple == ('&', '0'):
                gere_and(self, b, a)
                return True
            elif abtuple == ('1', '&'):
                gere_and(self, a, b)
                return True
            elif abtuple == ('&', '1'):
                gere_and(self, b, a)
                return True
            elif abtuple == ('0', '|'):
                gere_or(self, a, b)
                return True
            elif abtuple == ('|', '0'):
                gere_or(self, b, a)
                return True
            elif abtuple == ('1', '|'):
                gere_or(self, a, b)
                return True
            elif abtuple == ('|', '1'):
                gere_or(self, b, a)
                return True
            elif abtuple == ('0', '^'):
                gere_xor(self, a, b)
                return True
            elif abtuple == ('^', '0'):
                gere_xor(self, b, a)
                return True
            elif abtuple == ('1', '^'):
                gere_xor(self, a, b)
                return True
            elif abtuple == ('^', '1'):
                gere_xor(self, b, a)
                return True
            else:
                return False

    @classmethod
    def enc(cls):
        """ encodeur
            Entrée: la classe bool_circ
            Sortie: circuit booleen correspondant à l'encodeur
        """
        # return cls.parse_parentheses("(((x0)^(x1))^(x3))",
        # "(((x0)^(x2))^(x3))",
        # "(x0)","(((x1)^(x2))^(x3))",
        # "(x1)", "(x2)", "(x3)")[0]
        circuit = bool_circ(open_digraph.empty())
        x0 = circuit.add_node()
        circuit.add_input_node(x0)

        x1 = circuit.add_node()
        circuit.add_input_node(x1)

        x2 = circuit.add_node()
        circuit.add_input_node(x2)

        x3 = circuit.add_node()
        circuit.add_input_node(x3)

        x4 = circuit.add_node("^")
        x5 = circuit.add_node("^")
        x6 = circuit.add_node("^")

        circuit.add_edge(x0, x4)
        circuit.add_edge(x0, x5)

        circuit.add_edge(x1, x4)
        circuit.add_edge(x1, x6)

        circuit.add_edge(x2, x5)
        circuit.add_edge(x2, x6)

        circuit.add_edge(x3, x4)
        circuit.add_edge(x3, x5)
        circuit.add_edge(x3, x6)

        circuit.add_output_node(x4)
        circuit.add_output_node(x5)
        circuit.add_output_node(x0)
        circuit.add_output_node(x6)
        circuit.add_output_node(x1)
        circuit.add_output_node(x2)
        circuit.add_output_node(x3)

        return circuit

    @classmethod
    def dec(cls):
        """decodeur
            Entrée: la classe bool_circ
            Sortie: circuit booleen correspondant au decodeur
        """
        # n1="( ( (x0)^(x1) ) ^(x3) )"
        # n2="( ( (x0)^(x2) ) ^(x3) )"
        # n3="(x0)"
        # n4="( ( (x1)^(x2) ) ^(x3) )"
        # n5="(x1)"
        # n6="(x2)"
        # n7="(x3)"
        # a1="( (" + n1 + "&" + n2 + ")" + "&" + "( ~" + n4 + ") )"
        # a2="( (" + n1 + "&" + n4 + ")" + "&" + "( ~" + n2 + ") )"
        # a3="( (" + n2 + "&" + n4 + ")" + "&" + "( ~" + n1 + ") )"
        # a4="( (" + n1 + "&" + n2 + ")" + "&" +  n4 +   ")"
        # return cls.parse_parentheses("("+ a1 + "^" + n3 + ")" ,
        #                          "("+ a2 + "^" + n5 + ")" ,
        #                          "("+ a3 + "^" + n6 + ")" ,
        #                          "("+ a4 + "^" + n7 + ")" , )[0]

        ## n'a pas fonctionne!
        circuit = bool_circ(open_digraph.empty())

        a = circuit.add_node()
        b = circuit.add_node()
        c = circuit.add_node()
        d = circuit.add_node()

        e = circuit.add_node("^")
        f = circuit.add_node("^")
        g = circuit.add_node("^")

        h = circuit.add_node()
        i = circuit.add_node()
        j = circuit.add_node()

        k = circuit.add_node("&")
        l = circuit.add_node("~")
        m = circuit.add_node("^")
        n = circuit.add_node("~")
        o = circuit.add_node("~")  #
        p = circuit.add_node("&")
        q = circuit.add_node("^")
        r = circuit.add_node("&")  #
        s = circuit.add_node("&")
        t = circuit.add_node("^")
        u = circuit.add_node("^")

        circuit.add_input_node(e)
        circuit.add_input_node(f)
        circuit.add_input_node(a)
        circuit.add_input_node(g)
        circuit.add_input_node(b)
        circuit.add_input_node(c)
        circuit.add_input_node(d)

        circuit.add_output_node(m)
        circuit.add_output_node(q)
        circuit.add_output_node(t)
        circuit.add_output_node(u)

        circuit.add_edge(a, e)
        circuit.add_edge(a, f)
        circuit.add_edge(a, m)

        circuit.add_edge(b, e)
        circuit.add_edge(b, g)
        circuit.add_edge(b, q)

        circuit.add_edge(c, f)
        circuit.add_edge(c, g)
        circuit.add_edge(c, t)

        circuit.add_edge(d, e)
        circuit.add_edge(d, f)
        circuit.add_edge(d, g)
        circuit.add_edge(d, u)

        circuit.add_edge(e, h)
        circuit.add_edge(f, i)
        circuit.add_edge(g, j)

        circuit.add_edge(h, k)
        circuit.add_edge(h, p)
        circuit.add_edge(h, o)
        circuit.add_edge(h, s)

        circuit.add_edge(i, k)
        circuit.add_edge(i, n)
        circuit.add_edge(i, r)
        circuit.add_edge(i, s)

        circuit.add_edge(j, l)
        circuit.add_edge(j, p)
        circuit.add_edge(j, r)
        circuit.add_edge(j, s)

        circuit.add_edge(l, k)
        circuit.add_edge(n, p)
        # circuit.add_edge(o,q) source des enmerdes
        circuit.add_edge(o, r)

        circuit.add_edge(k, m)
        circuit.add_edge(p, q)
        circuit.add_edge(r, t)
        circuit.add_edge(s, u)
        return circuit

    def check_all_linked_directly_to_ouput(self: open_digraph, listofnodes):
        """Check if all nodes in listofnodes are linked directly to an output.

        Args:
            listofnodes (list): list of nodes

        Returns:
            bool: True if all nodes are linked directly to an output, False otherwise
        """
        for n in listofnodes:
            enfants = list(self.get_node_by_id(n).get_children_ids())
            if len(enfants) == 0:
                raise Exception("Cofeuille sans enfant")
            if len(enfants) > 1:
                raise Exception("Cofeuille avec plus d'un enfant")
            if (not enfants[0] in self.outputs or (
                    self.get_node_by_id(n).get_label() != '0' and self.get_node_by_id(n).get_label() != '1')):
                return False
        return True

    def evaluate(self):
        """Applique simplifie sur les noeuds du graph tant que simplifie quelque chose ie tant que les noeuds sans parents ne sont pas reliés à une sortie.
        """
        cof = self.get_cofeuilles()
        i = 0
        while not self.check_all_linked_directly_to_ouput(cof):
            print("evaluating... cof : ", cof)
            for c in cof:
                simp = False
                cnode = self.get_node_by_id(c)
                if (cnode.get_label() != '0' and cnode.get_label() != '1'):
                    simp = self.simplifie(c)
                    # print("il y a visiblement un probleme si j'ai que ça qui apparait")
                else:
                    gossede01 = list(cnode.get_children_ids())[0]
                    print(self.get_node_by_id(gossede01).get_label(), "(id :", gossede01, ") est le fils de ",
                          cnode.get_label(), "( Output ? ", gossede01 in self.outputs, ")")
                    print([self.get_node_by_id(o).get_label() for o in self.outputs])
                    simp = self.simplifie(c, gossede01)
                    print("simplification ? :", simp)
                if (simp):
                    # self.save_as_dot_file("test_adder"+str(i)+".dot")
                    i += 1
            cof = self.get_cofeuilles()

    def simplifie_reecriture(self, a, b=None):
        """Applique les regles de la feuille 12 aux noeuds a et b. Doit marcher peu importe l'ordre des noeuds a et b.
        return True si simplification a eu lieu, False sinon."""
        if b == None:
            return self.simplifie(a)

        if not (self.simplifie(a, b)):
            def gereAssocXor(self, a, b):
                """Gère le cas où a et b sont des noeuds associatifs de type xor. a parent de b."""
                na = self.get_node_by_id(a)
                nb = self.get_node_by_id(b)
                if na.get_label() != '^':
                    print("echec xor")
                    return False
                if nb.get_label() != '^':
                    print("echec xor")
                    return False
                if a not in list(nb.get_parents_ids()):
                    print("echec xor")
                    return False
                if a == b:
                    print("echec xor")
                    return False
                aparents = list(na.get_parents_ids())
                for pa in aparents:
                    self.add_edge(pa, b)
                self.remove_nodes_by_id(a)
                return True

            def gereAssocCopy(self, a, b):
                """Gère le cas où a et b sont des noeuds de type copy. a parent de b."""
                na = self.get_node_by_id(a)
                nb = self.get_node_by_id(b)
                if na.get_label() != '':
                    print("echec copy")
                    return False
                if nb.get_label() != '':
                    print("echec copy")
                    return False
                if a not in list(nb.get_parents_ids()):
                    print("echec copy")
                    return False
                if a == b:
                    print("echec copy")
                    return False
                bfils = list(nb.get_children_ids())
                for f in bfils:
                    self.add_edge(a, f)
                self.remove_nodes_by_id(b)
                return True

            def gereInvolXor(self, a, b):
                """ a est un noeud sans label et b un xor"""
                na = self.get_node_by_id(a)
                nb = self.get_node_by_id(b)
                if na.get_label() == "" and nb.get_label() == "^" and b in list(
                        na.get_children_ids()) and na.indegree() == 1 and nb.outdegree() == 1:
                    nb_edge = na.children[b]
                    if nb_edge == 1:
                        print("echec involXor")
                        print("-> " + str(a) + " " + str(b) + " " + str(na.get_label()) + " " + str(nb.get_label()))
                        return False
                    self.remove_parallel_edges(a, b)
                    if nb_edge % 2 != 0:
                        self.add_edge(a, b)
                    return True
                else:
                    print("echec involXor")
                    print("-> " + str(a) + " " + str(b) + " " + str(na.get_label()) + " " + str(nb.get_label()))
                    return False

            def gereEffacement(self, a, b):
                """ a est un noeud avec un operateur booleen (unaire ou binaire) et b un noeud sans label"""
                na = self.get_node_by_id(a)
                nb = self.get_node_by_id(b)
                if na.get_label() in ['^', '&', '|', '~', '1', '0'] and nb.get_label() == "" and b in list(
                        na.get_children_ids()) and na.outdegree() == 1 and na.indegree() >= 1 and nb.indegree() == 1 and nb.outdegree() == 0:
                    aparents = list(na.get_parents_ids())
                    self.remove_nodes_by_id(a)
                    self.remove_nodes_by_id(b)
                    for ap in aparents:
                        c = self.add_node("")
                        self.add_edge(ap, c)
                    return True
                else:
                    print("echec effacement")
                    print("-> " + str(a) + " " + str(b) + " " + str(na.get_label()) + " " + str(nb.get_label()))
                    return False

            def gereNonTraversXor(self, a, b):
                """Gère le cas où a est NON et b un xor"""
                na = self.get_node_by_id(a)
                nb = self.get_node_by_id(b)
                if na.get_label() == "~" and nb.get_label() == "^" and b in list(
                        na.get_children_ids()) and na.outdegree() == 1 and na.indegree() == 1 and nb.outdegree() == 1:
                    aparents = list(na.get_parents_ids())[0]
                    self.add_edge(aparents, b)
                    self.remove_edge(a, b)
                    self.remove_edge(aparents, a)
                    benfants = list(nb.get_children_ids())[0]
                    self.remove_edge(b, benfants)
                    self.add_edge(b, a)
                    self.add_edge(a, benfants)
                    return True
                else:
                    print("echec nonTraversXor")
                    print("-> " + str(a) + " " + str(b) + " " + str(na.get_label()) + " " + str(nb.get_label()))
                    return False

            def gereNonTraversCopy(self, a, b):
                """ Gère le cas où a est non et b un noeud sans label"""
                na = self.get_node_by_id(a)
                nb = self.get_node_by_id(b)
                if na.get_label() == "~" and nb.get_label == "" and b in list(
                        na.get_children_ids()) and na.outdegree() == 1 and na.indegree() == 1 and nb.indegree() == 1 and nb.outdegree() >= 1:
                    aparents = na.get_parents_ids()
                    self.remove_nodes_by_id(a)
                    self.add_edge(aparents, b)
                    benfants = list(nb.get_children_ids())
                    self.remove_several_parallel_edges([(b, c_id) for c_id in benfants])
                    for eb in benfants:
                        c = self.add_node("~")
                        self.add_edge(b, c)
                        self.add_edge(c, eb)
                    return True
                else:
                    print("echec nonTraversCopy")
                    print("-> " + str(a) + " " + str(b) + " " + str(na.get_label()) + " " + str(nb.get_label()))
                    return False

            def gereInvolutionNon(self, a, b):
                """ Gère le cas où a et b sont deux non"""
                na = self.get_node_by_id(a)
                nb = self.get_node_by_id(b)
                if na.get_label() == "~" and nb.get_label() == "~" and b in list(
                        na.get_children_ids()) and na.outdegree() == 1 and na.indegree() == 1 and nb.indegree() == 1 and nb.outdegree() == 1 and a != b:
                    aparents = na.get_parents_ids()
                    benfants = nb.get_children_ids()
                    self.add_edge(aparents, benfants)
                    self.remove_nodes_by_id(a)
                    self.remove_nodes_by_id(b)
                    return True
                else:
                    print("echec involutionNon")
                    print("-> " + str(a) + " " + str(b) + " " + str(na.get_label()) + " " + str(nb.get_label()))
                    return False

            nodea = self.get_node_by_id(a)
            nodeb = self.get_node_by_id(b)
            alabel = nodea.get_label()
            blabel = nodeb.get_label()
            abtuple = (alabel, blabel)

            # useless in a little while
            """ try:    
                nb_edges_a_to_b = nodea.children[b]
            except KeyError:
                nb_edges_a_to_b = 0
            try:
                nb_edges_b_to_a = nodeb.children[a]
            except KeyError:
                nb_edges_b_to_a = 0 """
            print("A et B", abtuple)
            if abtuple == ('^', '^') and (gereAssocXor(self, a, b) or gereAssocXor(self, b, a)):
                print("assoc xor ->", a, b)
                return True
            elif abtuple == ('', '') and (gereAssocCopy(self, a, b) or gereAssocCopy(self, b, a)):
                print("assoc copy ->", a, b)
                return True
            elif abtuple == ('', '^') and gereInvolXor(self, a, b):
                # le 1er arg est la copie and nb_edges_a_to_b > 1
                print("invol xor ->", a, b)
                return True
            elif abtuple == ('^', '') and gereInvolXor(self, b, a):
                print("invol xor ->", a, b)
                return True
            elif alabel in ['^', '&', '|', '~', '1', '0'] and blabel == "" and gereEffacement(self, a, b):
                print("effacement ->", a, b)
                return True
            elif blabel in ['^', '&', '|', '~', '1', '0'] and alabel == "" and gereEffacement(self, b, a):
                print("effacement ->", a, b)
                return True
            elif abtuple == ('~', '^') and gereNonTraversXor(self, a, b):
                print("non travers xor ->", a, b)
                return True
            elif abtuple == ('^', '~') and gereNonTraversXor(self, b, a):
                print("non travers xor ->", a, b)
                return True
            elif abtuple == ('~', '') and gereNonTraversCopy(self, a, b):
                print("non travers copy ->", a, b)
                return True
            elif abtuple == ('', '~') and gereNonTraversCopy(self, b, a):
                print("non travers copy ->", a, b)
                return True
            elif abtuple == ('~', '~') and (gereInvolutionNon(self, a, b) or gereInvolutionNon(self, b, a)):
                print("involution non ->", a, b)
                return True
            else:
                print("pas de simplification ->", a, b)
                return False
        else:
            # print("j'ai simplifié classiquement")
            return True  # simplification classique

    def reecrit(self):
        """
            Cette methode simplifie successivement le circuit jusqu'a ce qu'on ne puisse plus simplifier.
        """
        print([s.get_label() for s in self.nodes.values()])
        simplificationEffectuee = False
        for indn, n in self.nodes.items():
            for f in list(n.get_children_ids()):
                if self.simplifie_reecriture(indn) or self.simplifie_reecriture(indn, f):
                    simplificationEffectuee = True
                    break
            """ if(indn == 14):
                self.save_as_dot_file("intermediaire.dot")
                input() """
            if simplificationEffectuee:
                break

        if simplificationEffectuee:
            self.reecrit()
        else:
            # self.save_as_dot_file("intermediaire.dot")
            return

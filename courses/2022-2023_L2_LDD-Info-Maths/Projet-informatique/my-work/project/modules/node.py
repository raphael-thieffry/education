from typing import Dict,List, Tuple

class node:
    def __init__(self, identity, label, parents, children):
        '''
        identity: int; its unique id in the graph
        label: string;
        parents: int->int dict; maps a parent node's id to its multiplicity
        children: int->int dict; maps a child node's id to its multiplicity
        '''
        self.id = identity
        self.label = label
        self.parents = parents
        self.children = children
        
    # def str_dic(dic): 
    #     return '{' + ', '.join([str(k) + ':' + str(v) for k, v in dic.items()]) + '}'

    def __eq__(self, other):
        return self.id == other.id and self.label == other.label and self.parents == other.parents and self.children == other.children

    def __str__(self):
        return '(\033[33mid: \033[0;92m' + str(self.id) + ' \033[33mlabel: \033[0;31m' + self.label + '\033[33m parents: \033[0;31m' + str(self.parents) + ' \033[33mchildren:\033[0;31m ' + str(self.children) + '\033[0m)'

    def __repr__(self):
        return self.__str__()

    def copy(self):
        if(self.parents is None):
            newparents = None
        else:
            newparents = self.parents.copy()
        if(self.children is None):
            newchildren = None
        else:
            newchildren = self.children.copy()
        return node(self.id, self.label, newparents, newchildren)

    def get_id(self):
        return self.id
    def get_label(self):
        return self.label
    def get_parents_ids(self):
        if self.parents is None:
            return []
        return self.parents.keys()
    def get_children_ids(self):
        if self.children is None:
            return []
        return self.children.keys()

    def set_id(self, new_id:int):
        self.id = new_id

    def set_label(self, new_label:str):
        self.label = new_label

    def set_parents(self, new_parents: Dict[int,int]):
        self.parents = new_parents

    def set_children(self, new_children: Dict[int,int]):
        self.children = new_children

    def add_child(self, child) -> None:
        """Adds a child to the node. If the child is already in the node, increments its multiplicity.
            Args:
                child: node; the child to add
        """
        if self.children is not None:
            if child.get_id() in self.children.keys():
                self.children[child.get_id()] += 1
            else:
                self.children[child.get_id()] = 1
        else:
            self.children = {child.get_id():1}
    
    def add_parent(self, parent):
        """Adds a parent to the node. If the parent is already in the node, increments its multiplicity.
            Args:
                parent: node; the parent to add
        """
        if self.parents is not None:
            if parent.get_id() in self.parents.keys():
                self.parents[parent.get_id()] += 1
            else:
                self.parents[parent.get_id()] = 1
        else:
            self.parents = {parent.get_id():1}

    def remove_parent_once(self, id : int) -> None:
        if self.parents != None and id in self.parents:
            self.parents[id] -= 1
            if self.parents[id] == 0:
                del self.parents[id]
            if self.parents == {}:
                self.parents = None
        else:
            raise ValueError('Parent id not found')

    def remove_child_once(self, id : int) -> None:
        if self.children != None and id in self.children:
            self.children[id] -= 1
            if self.children[id] == 0:
                del self.children[id]
            if self.children == {}:
                self.children = None
        else:
            raise ValueError('Child id not found')

    def remove_parent_id(self, id : int) -> None:
        if self.parents != None and id in self.parents:
            del self.parents[id]
            if self.parents == {}:
                self.parents = None
        else:
            raise ValueError('Parent id not found')

    
    def remove_child_id(self, id : int) -> None:
        if self.children != None and id in self.children:
            del self.children[id]
            if self.children == {}:
                self.children = None
        else:
            raise ValueError('Child id not found')

    def indegree(self):
        """Returns the indegree of the node.

        Returns:
            int: the indegree of the node
        """
        if self.parents is None:
            return 0
        return sum(self.parents.values())

    def outdegree(self):
        """Returns the outdegree of the node."""
        if self.children is None:
            return 0
        return sum(self.children.values())

    def degree(self):
        """Returns the degree of the node.

        Returns:
            int: the degree of the node
        """
        return self.indegree() + self.outdegree()
    
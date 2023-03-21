class tree_root:
    def __init__(self, __value, __node_type) -> None:
        self.arms:list[__node_type] = [__node_type(self, __value)]


    def AddNode(self, __value:int):
        return self.arms[0].AddNode(__value)

        
    def printTree(self):
        return self.arms[0].printTree()


    def depthTree(self) -> int:
        return self.arms[0].depthTree()


    def searchNode(self, __value):
        return self.arms[0].searchNode(__value)

    
    def delNode(self, __value):
        return self.arms[0].delNode(__value)
    

class tree_node:
    def __init__(self, __parent, __value) -> None:
        self.parent:tree_node = __parent
        self.arms:list[tree_node] = [None, None]
        self.value = __value
        self.amount = 1


    def AddNode(self, __value:int):
        # if self
        if __value == self.value:
            self.amount += 1
        
        # arm left
        if __value < self.value:
            if self.arms[0] == None:
                self.arms[0] = tree_node(self, __value)
            else: self.arms[0].AddNode(__value)

        # arm right
        if __value > self.value:
            if self.arms[1] == None:
                self.arms[1] = tree_node(self, __value)
            else: self.arms[1].AddNode(__value)

        
    def printTree(self):
        print(self._printTree())

    
    def _printTree(self) -> str:
        __ret = self.String()
        if self.arms[0]: __ret += "\n├" + self.arms[0]._printTree().replace("\n", "\n│")
        if self.arms[1]: __ret += "\n├" + self.arms[1]._printTree().replace("\n", "\n│├")
        return __ret
        


    def depthTree(self) -> int:
        __arm_0_depth = self.arms[0].depthTree() if self.arms[0] else 0
        __arm_1_depth = self.arms[1].depthTree() if self.arms[1] else 0
        return 1 + max(__arm_0_depth, __arm_1_depth)


    def searchNode(self, __value):
        # if self
        if __value == self.value: return self

        # arm left
        if self.arms[0]:
            __found_arm = self.arms[0].searchNode(__value)
            if __found_arm: return __found_arm

        # arm left
        if self.arms[1]:
            __found_arm = self.arms[1].searchNode(__value)
            if __found_arm: return __found_arm

        return 

    
    def delNode(self, __value):
        __node_to_del = self.searchNode(__value)
        __node_to_add = None

        # find how to treat
        ## no hands
        if not __node_to_del.arms[0] and not __node_to_del.arms[1]:
            __node_to_add = None

        ## two hands; left has right
        if (__node_to_del.arms[0] and __node_to_del.arms[1]) and (__node_to_del.arms[0].arms[1]):
            __node_to_add = __node_to_del.arms[0].arms[1]
            while __node_to_add.arms[1]:
                __node_to_add = __node_to_add.arms[1]

            __node_to_add.delNode(__node_to_add.value)
            __node_to_add.arms[0] = __node_to_del.arms[0]
            __node_to_add.arms[1] = __node_to_del.arms[1]
        ## two hands; left has no right
        if (__node_to_del.arms[0] and __node_to_del.arms[1]) and (not __node_to_del.arms[0].arms[1]):
            __node_to_add = __node_to_del.arms[0]
            __node_to_add.arms[1] = __node_to_del.arms[1]   

        ## one hand left
        if __node_to_del.arms[0] and not __node_to_del.arms[1]:
            __node_to_add = __node_to_del.arms[0]

        ## one hand right
        if not __node_to_del.arms[0] and __node_to_del.arms[1]:
            __node_to_add = __node_to_del.arms[1]


        # set to parent
        if __node_to_del.parent.arms[0] == __node_to_del: __node_to_del.parent.arms[0] = __node_to_add
        elif __node_to_del.parent.arms[1] == __node_to_del: __node_to_del.parent.arms[1] = __node_to_add


    def String(self):
        return f"{self.value}x{self.amount}"






##############################################################
# Создать двоичное дерево поиска (в узлах хранятся целые положительные числа). 
# Программа должна запрашивать количество элементов дерева, 
# далее значения, хранящиеся в элементах, создаются генератором случайных чисел. 
# Для готового дерева реализовать операции:
# а) добавление нового узла в дерево;
# б) обход дерева (прямой, обратный или симметричный – по выбору) и печать элементов дерева на экран;
# в) вычисление глубины (высоты) дерева;
# г) поиск конкретного элемента в дереве
# д*) удаление определенного узла в дереве;


if __name__ == "__main__":
    import random
    RND_MIN = 0
    RND_MAX = 100


    main_tree = tree_root(random.randint(RND_MIN, RND_MAX), tree_node)

    # fill tree
    print("Программа запрашивать количество элементов дерева")
    __elements_amount = int(input())
    for _ in range(__elements_amount): main_tree.AddNode(random.randint(RND_MIN, RND_MAX))
    

    # main loop
    __request = " "
    while __request:
        print("Для готового дерева операции:")
        print("1 а) добавление нового узла в дерево;")
        print("2 б) обход дерева (прямой, обратный или симметричный – по выбору) и печать элементов дерева на экран;")
        print("3 в) вычисление глубины (высоты) дерева;")
        print("4 г) поиск конкретного элемента в дереве")
        print("5 д*) удаление определенного узла в дереве;")
        __request = input()

        # а
        if __request in "а1":
            __value = int(input())
            main_tree.AddNode(lambda node: node.value == __value)

        
        # б
        if __request in "б2":
            main_tree.printTree()
        
        # в
        if __request in "в3":
            print(main_tree.depthTree())

        # г
        if __request in "г4":
            __value = int(input())
            print(main_tree.searchNode(__value))
        
        #д
        if __request in "д5":
            __value = int(input())
            main_tree.delNode(__value)
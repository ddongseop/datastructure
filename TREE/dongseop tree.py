level = 0
degree = 0

class TNODE:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

    def __str__(self):
        return str(self.data)

class TREEs:
    def __init__(self, Type):
        root = [None for i in range(10)]    
        self.root = root
        self.current = -1
        self.count = 0
        self.type = Type

    def create(self, data):
        new = TNODE(data)

        self.root[self.count] = new
        self.current = self.count
        self.count += 1

    def insert_node(self, target, data):
        new = TNODE(data)

        if target.left == None:
            target.left = new

        else:
            tmp = target.left
            if self.type == 0:
                if (tmp.right != None):
                    print("  [Error] Binary tree can't have three child\n")
                    return
            while tmp.right:
                tmp = tmp.right
            tmp.right = new

    def search(self, tmp1, data):
        if tmp1 == None:
            return None
        
        if tmp1.data == data:
            return tmp1

        tmp2 = self.search(tmp1.left, data)
        if tmp2:
            return tmp2

        tmp2 = self.search(tmp1.right, data)
        if tmp2:
            return tmp2

        return None

    def print(self, root, tmp1):
        tmp2 = tmp1.left

        if root == tmp1:
            print("  ({}".format(root.data),end='')
        if root.left == None:
            print(")")
            return
        print("(",end='')

        while (tmp2):
            print("{}".format(tmp2.data),end='')

            if tmp2.left != None:
                self.print(root, tmp2)
            if tmp2.right != None:
                print(",",end='')
            tmp2 = tmp2.right
            
        print(")",end='')

        if root==tmp1:
             print(")")

    def moveIndex(self, index):
        if self.root[index] == None:
            print("  [Error] Tree did not created\n")
            print("  Index initialized to 0\n")
            self.current = 0
            return
        self.current = index

    def get_parent(self, root, target):
        if root==target:
            return None
        search = root.left
        answer = root

        while search:
            tmp = search

            while search:
                if search == target:
                    return answer
                if search != tmp and search.left != None:
                    answer2 = self.get_parent(search, target)
                    if answer2:
                        return answer2

                search = search.right

            answer = tmp
            search = tmp.left

        return None

    def get_sibling(self, target):
        if self.root[self.current] == target:
            print("  [Error] Root has no sibling\n")
            return
        search = self.get_parent(self.root[self.current], target).left

        print("  {",end='')
        while search:
            if search != target:
                print("{}".format(search.data),end='')
            if (search.right != target and search.right != None):
                print(",",end='')
            search = search.right

        print("}\n")

    def get_child(self, target):
        if target.left == None:
            print("  [Error] No child (leaf node)\n")
            return

        tmp = target.left

        print("  {",end = '')

        while tmp.right:
            print("{},".format(tmp.data),end = '')
            tmp = tmp.right

        print("{}".format(tmp.data),end = '')
        print("}\n")

    def level_of_node(self, target):
        level = 0

        tmp = target

        while True:

            if self.root[self.current] == tmp:
                return level
            else:
                tmp = self.get_parent(self.root[self.current], tmp)
                level += 1

    def level_of_tree(self, search):
        if search == None:
            return

        global level
        
        self.level_of_tree(search.left)
        self.level_of_tree(search.right)

        if self.level_of_node(search) > level:
            level = self.level_of_node(search)

    def delete_node(self, target):
        if target.left != None:
            print("  [Error] Target is parent node\n")
            return 0
        if self.root[self.current] == target:
            self.root[self.current] = None

            print("  Delete finished : {}\n".format(target.data))
            del target

            return 1

        else:
            tmp = self.get_parent(self.root[self.current], target)

            if tmp.left == target:
                tmp.left = tmp.left.right

                print("  Delete finished : {}\n".format(target.data))
                del target

            else:
                tmp = tmp.left
                while tmp.right != target:
                    tmp = tmp.right
                tmp.right = tmp.right.right

                print("  Delete finished : {}\n".format(target.data))
                del target

        return 0

    def get_ancestors(self, target):
        if target == self.root[self.current]:
            print("  [Error] Root has no ancestor\n")
            return

        tmp = target
        print("  ", end = '')

        while True:
            tmp = self.get_parent(self.root[self.current], tmp)

            print("{} ".format(tmp.data), end = '')

            if tmp==self.root[self.current]:
                break

        print("\n")

    def get_descendants(self, target):
        if target.left == None:
            print("  [Error] No child (leaf node)\n")
            return

        tmp = target.left
        print("  (", end = '')

        while tmp:
            print("{}".format(tmp.data), end = '')

            if tmp.left != None:
                self.print(target, tmp)

            if tmp.right != None:
                print(",", end = '')

            tmp = tmp.right

        print(")\n")

    def degree_of_node(self, target):
        degree = 0

        search = target.left

        while search!=None:
            degree += 1
            search = search.right

        return degree

    def degree_of_tree(self, search):
        if search == None:
            return

        global degree
        
        self.degree_of_tree(search.left)
        self.degree_of_tree(search.right)

        if self.degree_of_node(search) > degree:
            degree = self.degree_of_node(search)

    def count_node(self, search):
        if search == None:
            return 0

        return self.count_node(search.left) + self.count_node(search.right) + 1

    def insert_sibling(self, target, data):
        new = TNODE(data)

        if self.type == 0:
            if target.right != None:
                print("  [Error] Binary tree can't have three child\n")
                return

        tmp = target
        while tmp.right:
            tmp = tmp.right

        tmp.right = new

    def join_trees(self, data, index1, index2):
        if self.root[index1] == None or self.root[index2] == None:
            print("  [Error] Please check index\n")

        self.create(data)
        left = self.copy(self.root[index1])
        right = self.copy(self.root[index2])

        self.root[self.current].left = left
        left.right = right

    def copy(self, search):
        if search == None:
            return None
        else:
            new = TNODE(search.data)

            new.left = self.copy(search.left)
            new.right = self.copy(search.right)

            return new

    def clear(self, search):
        if search == None:
            return
        self.clear(search.left)
        self.clear(search.right)

        del search

print("\n");
print("───────────────────────────────────────────────────\n")
print("\t      C O M M A N D   H E L P E R                                                      \n")
print("───────────────────────────────────────────────────\n")
print("  +^@      : Create new tree with root @							             \n")
print("             (you can create up to 10)							             \n")
print("  +A(B)    : Insert B as child of A							             \n")
print("             (+A(B,C,D) available)								     \n")
print("  S(@)     : Get sibling of @									     \n")
print("  T        : Print current tree									     \n")
print("  M@       : Move to tree index of @								     \n")
print("  P(@)     : Get parent of @									     \n")
print("  C(@)     : Get child of @									     \n")
print("  L(@)     : Get level of @									     \n")
print("  L        : Get level of tree									     \n")
print("  -@       : Delete node which has data @							     \n")
print("             (You can only delete leaf node)						             \n")
print("  A(@)     : Get ancestors of @									     \n")
print("  D(@)     : Get descendants of @								     \n")
print("  G(@)     : Get degree of @									     \n")
print("  G        : Get degree of tree								             \n")
print("  #        : Count number of node of tree							     \n")
print("  =+A(B)   : Insert B as sibling of A								     \n")
print("             (=+A(B,C) available)							             \n")
print("  J(@,a,b) : Make new tree with root @ and join						             \n")
print("             two trees 'Index' of 'a' and 'b'	 					             \n")
print("  K        : Clear all tree                                                                           \n")
print("───────────────────────────────────────────────────\n")
print("  The length of command must be shorter than 30				 \n")
print("  Make a space between commands					         \n")
print("  Programmed by 2019310181 Dongseop Lee					 \n")
print("───────────────────────────────────────────────────\n")   


answer = []
Type = int(input("  1.general tree  2.binary tree\n  >> "))

if Type == 1:
    Mtree = TREEs(1)
else:
    Mtree = TREEs(0)

while True:

    answer = input("  >> ") #command 입력받음

    long = len(answer)

    i = 0

    while i < long:
        if answer[i] == '+':
            if answer[i+1] == '^':
                if Mtree.count >= 10:
                    print("  [Error] You can't create Tree more\n")
                else:
                    Mtree.create(answer[i+2])
                i += 2
                
            elif answer[i+2] == '(':
                target = Mtree.search(Mtree.root[Mtree.current], answer[i+1])
            
                if target == None:
                    print("  [Error] Can't find {}\n".format(answer[i+1]))
                    while answer[i] != ')':
                        i += 1
                    i += 1
                    continue

                j = i+3

                while answer[j] != ')':
                    if answer[j] == ',':
                        j += 1
                        continue

                    if Mtree.search(Mtree.root[Mtree.current], answer[j]) != None:
                        print("  [Error] {} already exist\n".format(answer[j]))
                        j += 1
                        continue

                    Mtree.insert_node(target, answer[j])
                    j += 1

                while answer[i] != ')':
                    i += 1

        elif answer[i] == 'T':
            i += 1
            continue

        elif answer[i] == 'M':
            Mtree.moveIndex(int(answer[i+1]))
            i+= 1

        elif answer[i] == 'P':
            target = Mtree.search(Mtree.root[Mtree.current], answer[i+2])
                                  
            if target == None:
                print("  [Error] Can't find {}\n".format(answer[i+2]))

                i += 4
                continue

            parent = Mtree.get_parent(Mtree.root[Mtree.current], target)

            if parent == None:
                print("  [Error] This node is root\n")
            else:
                print("  Parent of {} is {}\n".format(answer[i+2], parent.data))
            i += 3

        elif answer[i] == 'S':
            target = Mtree.search(Mtree.root[Mtree.current], answer[i+2])

            if target == None:
                print("  [Error] Can't find {}\n".format(answer[i+2]))

                i += 4
                continue
            
            Mtree.get_sibling(target)
            i += 3

        elif answer[i] == 'C':
            target = Mtree.search(Mtree.root[Mtree.current], answer[i+2])

            if target == None:
                print("  [Error] Can't find {}\n".format(answer[i+2]))

                i += 4
                continue

            Mtree.get_child(target)

            i += 3

        elif answer[i] == 'L':
            if long > 1:
                if answer[i+1] == '(':
                    target = Mtree.search(Mtree.root[Mtree.current], answer[i+2])

                    if target == None:
                        print("  [Error] Can't find {}\n".format(answer[i+2]))

                        i += 4
                        continue

                    print("  Level of {} is {}\n".format(answer[i+2], Mtree.level_of_node(target)))
                    i += 3
                else:
                    print("  [Error] Check your command\n")
                    while answer[i] != ')':
                        i += 1
            else:
                Mtree.level_of_tree(Mtree.root[Mtree.current])
                print("  Level of tree is {}\n".format(level))

        elif answer[i] == '-':
            target = Mtree.search(Mtree.root[Mtree.current], answer[i+1])

            if target == None:
                print("  [Error] Can't find {}\n".format(answer[i+1]))
                    
                i += 2
                continue
            
            signal = Mtree.delete_node(target)

            if signal == 1: #tree 자체가 삭제됐을 경우 
                print("  Current tree is deleted, Index is modified\n")

                j = Mtree.current
                
                while Mtree.root[j+1] != None:
                    Mtree.root[j] = Mtree.root[j+1]
                    j += 1
                    
                Mtree.root[j] = None
                Mtree.count -= 1

                if Mtree.count != 0:
                    index = int(input("  Select Index of Tree : "))
                    Mtree.moveIndex(index)

                else:
                    print("  There is no Tree to select\n")

            i += 1
                
                    
        elif answer[i] == 'A':
            target = Mtree.search(Mtree.root[Mtree.current], answer[i+2])

            if target == None:
                print("  [Error] Can't find {}\n".format(answer[i+2]))

                i += 4
                continue

            Mtree.get_ancestors(target)
            i += 3

        elif answer[i] == 'D':
            target = Mtree.search(Mtree.root[Mtree.current], answer[i+2])

            if target == None:
                print("  [Error] Can't find {}\n".format(answer[i+2]))

                i += 4
                continue

            Mtree.get_descendants(target)
            i += 3

        elif answer[i] == 'G':
            if long > 1:
                if answer[i+1] == '(':
                    target = Mtree.search(Mtree.root[Mtree.current], answer[i+2])

                    if target == None:
                        print("  [Error] Can't find {}\n".format(answer[i+2]))

                        i += 4
                        continue

                    print("  Degree of {} is {}\n".format(answer[i+2], Mtree.degree_of_node(target)))

                    while answer[i] != ')':
                        i += 1
                else:
                    print("  [Error] Check your command\n")
                    while answer[i] != ')':
                        i += 1
            else:
                Mtree.degree_of_tree(Mtree.root[Mtree.current])
                print("  Degree of tree is {}\n".format(degree))

        elif answer[i] == '#':
            print("  {}\n".format(Mtree.count_node(Mtree.root[Mtree.current])))

        elif answer[i] == '=':
            if answer[i+1] == '+' and answer[i+3] == '(':
                target = Mtree.search(Mtree.root[Mtree.current], answer[i+2])

                if target == None:
                    print("  [Error] Can't find {}\n".format(answer[i+2]))

                    while answer[i] != ')':
                        i += 1
                    i += 1
                    continue

                j = i + 4
                
                while answer[j] != ')':
                    if answer[j] == ',':
                        j += 1
                        continue
                    
                    if Mtree.search(Mtree.root[Mtree.current], answer[j]) != None:
                        print("  [Error] {} already exist\n".format(answer[j]))
                        j += 1
                        continue
                    
                    Mtree.insert_sibling(target, answer[j])
                    j += 1

                while answer[i] != ')':
                    i += 1

            else:
                print("  [Error] Check your command\n")
                while answer[i] != ')':
                    i += 1

        elif answer[i] == 'J':
            if answer[i+1] == '(':
                Mtree.join_trees(answer[i+2], int(answer[i+4]), int(answer[i+6]))
                while answer[i] != ')':
                    i += 1
            else:
                print("  [Error] Check your command\n")
                while answer[i] != ')':
                    i += 1

        elif answer[i] == 'K':
            Mtree.current = Mtree.count - 1
            for j in range (0, Mtree.count, 1):
                Mtree.clear(Mtree.root[Mtree.current])
                Mtree.current -= 1

            Mtree.count = 0
            print("  Clear finished\n")

        i += 1

    if Mtree.count > 0:
        print("")
        Mtree.print(Mtree.root[Mtree.current], Mtree.root[Mtree.current])
        print("  Index of current root : {} / {}\n".format(Mtree.current, Mtree.count - 1))

    else:
        print("")
        print("  Nothing to print\n")

height = 0
i = 0

class NODE:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None

    def __str__(self):
        return str(self.data)

class BST:
    def __init__(self):
        self.root = None
        self.OnOff = 0 #create를 할건지 insert를 할건지 구분해주는 속성

    def create(self, data):
        new = NODE(data)
        self.root = new
        self.OnOff = 1

    def print(self, tmp):
        if tmp==None:
            return
        if self.root == tmp:
            print("  (", end='')

        print("{}".format(tmp.data),end='')

        if (tmp.left != None or tmp.right !=None):
            print("(", end='')
            self.print(tmp.left)
            print(",", end='')
            self.print(tmp.right)
            print(")",end='')

        if self.root == tmp:
            print(")")

    def insert_node(self, data):
        tmp = self.root
        p_tmp =None

        while tmp != None:
            if tmp.data == data:
                print("  [Error] Data already exist\n")
                return
            p_tmp = tmp

            if data > tmp.data:
                tmp = tmp.right

            else:
                tmp = tmp.left

        new = NODE(data)

        if data > p_tmp.data:
            p_tmp.right = new
        else:
            p_tmp.left = new

    def get_parent(self, search, target): #target이 None이 아니라는 걸 알고 사용하기
        if search == None:
            return None
        if (search.left == target or search.right == target):
            return search

        adress = self.get_parent(search.left, target)
        if adress:
            return adress
        adress = self.get_parent(search.right, target)
        if adress:
            return adress
        return None

    def inorder_traversal(self, traverse):
        if traverse == None:
            return
        if self.root == traverse:
            print("  ", end='')

        self.inorder_traversal(traverse.left)
        print("{} ".format(traverse.data), end='')
        self.inorder_traversal(traverse.right)

        if self.root == traverse:
            print("\n")

    def right_root_left_traversal(self, traverse):
        if traverse == None:
            return
        if self.root == traverse:
            print("  ", end='')

        self.right_root_left_traversal(traverse.right)
        print("{} ".format(traverse.data), end='')
        self.right_root_left_traversal((traverse.left))

        if self.root == traverse:
            print("\n")

    def get_min(self):
        tmp = self.root
        while tmp.left != None:
            tmp = tmp.left
        return tmp.data

    def get_max(self):
        tmp = self.root
        while tmp.right != None:
            tmp = tmp.right

        return tmp.data

    def find_node(self, data):
        tmp = self.root
        while tmp != None:
            if data == tmp.data:
                return tmp
            elif data > tmp.data:
                tmp = tmp.right
            else:
                tmp = tmp.left

        return tmp

    def find_path(self, target):
        print("  Root", end='')
        tmp = self.root

        while tmp.data != target.data:
            if target.data > tmp.data:
                print(" > Right", end='')
                tmp = tmp.right
            else:
                print(" > Left", end='')
                tmp = tmp.left

        print("\n")

    def delete_node(self, data):
        if self.OnOff == 0: #BST empty
            print("  [Error] Nothing to delete\n")
            return -1
        target = self.find_node(data)
        if target == None:
            print("  [Error] Can't find target\n")
            return -1

        if target.left == None and target.right == None: #자식노드가 아예 없을 때
            if target == self.root:
                item = target.data
                del target
                self.root = None
                self.OnOff = 0

            else:
                p_target = self.get_parent(self.root, target)

                if p_target.right == target:
                    p_target.right = target.left
                    item = target.data
                    del target

                else:
                    p_target.left = target.left
                    item = target.data
                    del target

        elif target.left != None and target.right == None: #왼쪽에만 자식이 있을 때
            if target == self.root:
                self.root = target.left
                item = target.data
                del(target)

            else:
                p_target = self.get_parent(self.root, target)

                if p_target.right == target:
                    p_target.right = target.left
                    item = target.data
                    del target

                else:
                    p_target.left = target.left
                    item = target.data
                    del target

        elif target.left == None and target.right !=None: #오른쪽에만 자식이 있을 때
            if target == self.root:
                self.root = target.right
                item = target.data
                del target

            else:
                p_target = self.get_parent(self.root, target)

                if p_target.right == target:
                    p_target.right = target.right
                    item = target.data
                    del target

                else:
                    p_target.left = target.right
                    item = target.data
                    del target

        else: #자식 노드가 2개일 때, (*) left most 값을 후계자 노드로 지정
            heir = target.left

            while heir.right != None:
                heir = heir.right

            item = target.data
            heir_data = heir.data

            self.delete_node(heir.data)
            target.data = heir_data

        return item

    def height_of_node(self, target):
        height = 0

        while target != self.root:
            target = self.get_parent(self.root, target)
            height += 1

        return height

    def height(self, tmp):
        global height

        if tmp == None:
            return

        self.height(tmp.left)
        self.height(tmp.right)

        if self.height_of_node(tmp) > height:
            height = self.height_of_node(tmp)

    def get_right_child(self, data):
        target = self.find_node(data)
        if target == None:
            print("  [Error] Can't find target\n")
            return -1
        if target.right == None:
            return -2

        return target.right.data

    def get_left_child(self, data):
        target = self.find_node(data)
        if target == None:
            print("  [Error] Can't find target\n")
            return -1
        if target.left == None:
            return -2

        return target.left.data

    def count_node(self, tmp):
        if tmp == None:
            return 0

        return self.count_node(tmp.left) + self.count_node(tmp.right) + 1

    def clear(self):
        if self.root == None:
            print("  [Error] Already Empty\n")
            return

        while True:
            if self.root == None:
                print("  Clear finished\n")
                break

            self.delete_node(self.root.data)

    def destroy(self):
        if self.root != None:
            print("  [Error] Please clear BST first\n")
            return 0

        del self
        return 1

def is_number(factor):  #factor가 숫자인지 확인하는 함수
    try:
        float(factor)
        return 1
    except ValueError:
        return 0

def StN(answer): #String to Number
    global i
    number = 0
    tmp = long - i
    for j in range(tmp):
        if is_number(answer[i]):
            number = number * 10
            number += int(answer[i])
            i += 1


    return number


print("")
print("─────────────────────────────────────────────────────────────")
print("\t      C O M M A N D   H E L P E R									")
print("─────────────────────────────────────────────────────────────")
print("  +@   : Create BST (at first), Insert Node with Data @				                        ")
print("         (you can insert consecutively)								        ")
print("  P    : Print all Data of BST										")
print("  I    : Inorder Traversal (From a small number)				    	                        ")
print("  R    : Right Root Left Traversal (From a large number)			                                ")
print("  N    : Get Minimum										        ")
print("  M    : Get Maximum											")
print("  F@   : Find Node with Data @ and Search Path						                ")
print("  -@   : Delete Node wiht Data @									        ")
print("  H    : Get Height of BST										")
print("  H(@) : Get Height of Node wih Data @								        ")
print("  G(@) : Get Right Child of Node with Data @ 						                ")
print("  L(@) : Get Left Child of Node with Data @							        ")
print("  ^(@) : Get Parent of Node with Data @                                                                  ")
print("  #    : Count Node                                                                                      ")
print("  C    : Clear BST                                                                                       ")
print("  D    : Destroy BST                                                                                     ")
print("─────────────────────────────────────────────────────────────")
print("  The length of command must be shorter than 30						                ")
print("  Make a space between commands										")
print("  Programmed by 2019310181 Dongseop Lee								        ")
print("─────────────────────────────────────────────────────────────")

answer = []
signal = 1
Mbst = BST()

while signal:
    answer = input("  >> ")
    long = len(answer)

    i = 0

    while i < long:
        if answer[i] == '+' and Mbst.OnOff == 0:
            i += 1
            Mbst.create(StN(answer))
            i -= 1
        elif answer[i] == '+' and Mbst.OnOff == 1:
            i += 1
            Mbst.insert_node(StN(answer))
            i -= 1
        elif answer[i] == 'P':
            i += 1
            continue
        elif answer[i] == 'I':
            Mbst.inorder_traversal(Mbst.root)
        elif answer[i] == 'R':
            Mbst.right_root_left_traversal(Mbst.root)
        elif answer[i] == 'N':
            print("  Minimum : {}\n".format(Mbst.get_min()))
        elif answer[i] == 'X':
            print("  Maximum : {}\n".format(Mbst.get_max()))
        elif answer[i] == 'F':
            i += 1
            tmp = Mbst.find_node(StN(answer))
            i -= 1

            if tmp == None:
                print("  [Error] Not Exist!\n")
            else:
                Mbst.find_path(tmp)
        elif answer[i] == '-':
            i += 1
            tmp = Mbst.delete_node(StN(answer))
            if tmp != -1:
                print("  Deleted : {}\n".format(tmp))
            i -= 1
        elif answer[i] == 'H':
            if long > 1: #H(@)
                if answer[i+1] == '(':
                    i += 2
                    tmp = StN(answer)

                    target = Mbst.find_node(tmp)
                    if target == None:
                        print("  [Error] Can't find target\n")
                        i += 1
                        continue
                    print("  Height of {} is {}\n".format(tmp, Mbst.height_of_node(target)))
                else:
                    print("  [Error] Check your command\n")
                    break
            else: #그냥 H
                if Mbst.OnOff == 0:
                    print("  [Error] Empty BST\n")
                    i += 1
                    continue
                Mbst.height(Mbst.root)
                print("  Height of BST is {}\n".format(height))

        elif answer[i] == 'G':
            i += 2
            tmp = StN(answer)
            rc = Mbst.get_right_child(tmp)

            if rc == -1:
                i += 1
                continue
            elif rc == -2:
                print("  Right child of {} is NULL\n".format(tmp))
            else:
                print("  Right child of {} is {}\n".format(tmp, rc))

        elif answer[i] == 'L':
            i += 2
            tmp = StN(answer)
            lc = Mbst.get_left_child(tmp)

            if lc == -1:
                i += 1
                continue
            elif lc == -2:
                print("  Left child of {} is NULL\n".format(tmp))
            else:
                print("  Left child of {} is {}\n".format(tmp, lc))
        elif answer[i] == '#':
            print("  Count of node : {}\n".format(Mbst.count_node(Mbst.root)))
        elif answer[i] == 'C':
            Mbst.clear()
        elif answer[i] == 'D':
            if(Mbst.destroy()):
                print("  System finished\n")
                signal = 0
        elif answer[i] == '^':
            i += 2
            tmp = StN(answer)
            target = Mbst.find_node(tmp)

            if target == Mbst.root:
                print("  [Error] Root has no parent\n")
            elif target == None:
                print("  [Error] Can't find target\n")
            else:
                p = Mbst.get_parent(Mbst.root, target)
                print("  Parent of {} is {}\n".format(tmp, p.data))

        i += 1

    if signal and Mbst.OnOff == 1:
        Mbst.print(Mbst.root)
    elif signal and Mbst.OnOff == 0:
        print("  Empty BST\n")




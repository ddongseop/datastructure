#class에 대한 개념 자체가 없었으나, 과제가 나온 주 주말에 밤을 새며 공부한 끝에 완성한 프로그램입니다.
#(https://blex.me/@baealex/파이썬으로-구현한-자료구조-연결-리스트)의 코드를 참고하였습니다.
#is_number 함수를 만들 때, (http://mwultong.blogspot.com/2007/01/python-isnumber-isnum-isnumeric.html)의 코드를 참고하였습니다.

start = 0 #LinkedList가 비어 있으면 0, 하나라도 값이 들어 있으면 1을 갖는 전역변수

class NODE: #NODE class 정의
    def __init__(self, data): #node를 생성하고 받은 data를 저장하는 스페셜 메서드
        self.data = data
        self.next = None

    def __str__(self): #node의 data 값을 출력하는 스페셜 메서드
        return str(self.data)

class LinkedList: #LinkedList class 정의
    def __init__(self, data): #첫번째 node를 추가하면서, linked list를 생성하는 스페셜 메서드 (create(my_list))
        global start
        new = NODE(data)
        self.head = new
        self.size = 1 #linked list에 있는 원소 수를 나타내는 변수
        self.current = 0 #current point를 나타내는 변수
        start = 1

    def __str__(self): #linked list의 모든 node의 data들을 출력하는 스페셜 메서드
        display = '  '
        tmp = self.head
        while True: 
            display += str(tmp) #각 node의 data 값을 하나씩 추가
            if tmp.next == None:
                break
            tmp = tmp.next
            display += ' '
        if (self.size): #data가 하나라도 존재하면
            tmp = self.head
            for i in range (0, self.current, 1):
                tmp = tmp.next
            display += ' (current point: {0})\n'.format(tmp.data) #current point의 값 출력
        
        return display

    def addFirst(self, data): #linked list의 가장 앞부분에 node를 추가하는 메서드
        new = NODE(data)
        
        new.next = self.head
        self.head = new
        self.size += 1

    def addTail(self, data): #linked list의 가장 뒷부분에 node를 추가하는 메서드
        new = NODE(data)
        tmp = self.head
        while True:
            if tmp.next == None:
                break
            tmp = tmp.next
        tmp.next = new
        self.size += 1
        self.current += 1

    def add(self, data): #current point에 node를 추가하는 메서드
        new = NODE(data)
        tmp = self.head

        for i in range (0, self.current, 1):
            tmp = tmp.next
        new.data = data
        new.next = tmp.next
        tmp.next = new

        self.current += 1
        self.size += 1

    def get_data(self): #current point의 data 값을 return하는 메서드
        tmp = self.head
        for i in range (0, self.current, 1):
            tmp = tmp.next
        return str(tmp.data)

    def traverse_first(self): #current point를 가장 앞으로 옮기는 메서드
        self.current = 0

    def traverse_last(self): #current point를 가장 뒤로 옮기는 메서드
        self.current = self.size -1

    def traverse_next(self): #current point를 한칸 뒤로 옮기는 메서드
        self.current += 1

    def traverse_prev(self): #current point를 한칸 앞으로 옮기는 메서드
        self.current += -1

    def delete(self): #current point의 node를 삭제하는 메서드
        if (self.size == 0): #원소가 하나도 없을 때
            return

        if (self.current == 0): #첫번째 원소를 삭제할 때
            target = self.head
            self.head = target.next
            del target

        else: #첫번째가 아닌 원소를 삭제할 때
            cur = self.head
            for i in range (0, self.current-1, 1):
                cur = cur.next
            target = cur.next
            cur.next = cur.next.next
            del target

        self.size += -1

        if (self.current >= self.size): #current point가 linked list에서 벗어났을 때
            print("  current initialization\n")
            self.current = 0

    def replace(self, data): #current point의 data를 다른 data로 replace하는 메서드
        tmp = self.head
        for i in range (0, self.current, 1):
            tmp = tmp.next
        tmp.data = data

    def data_count(self): #linked list의 data 개수를 세는 메서드
        return str(self.size)

    def is_member(self, data): #입력받은 data가 linked list에 있는지 확인하는 메서드
        tmp = self.head
        self.current = 0
        while (tmp):
            if (tmp.data == data):
                return self.current
            tmp = tmp.next
            self.current += 1
        self.current += -1
        return -1 #해당 원소를 찾지 못했을 때

    def clear(self): #linked list의 모든 원소를 삭제하는 메서드
        global start
        self.current = 0
        tmp = self.size
        for i in range (0, tmp, 1): #원소의 개수만큼 self.delete()를 실행
            self.delete()
        start = 0

    def is_empty(self): #linked list가 비어 있는지 확인하는 메서드
        if (self.head == None):
            return 1
        else:
            return 0

    def reverse(self): #linked list의 원소들을 역순으로 재배치하는 메서드
        first = self.head
        middle = None

        while(first):
            last = middle
            middle = first
            first = first.next
            middle.next = last #node의 방향을 변경

        self.head = middle #새로운 head 값으로 변경

    def split(self): #current point의 원소를 복제하는 메서드 (ex) a b c (current point: b) -> a b b c
        self.add(self.get_data())

    def capital(self): #current point의 원소가 대문자면 소문자로, 소문자면 대문자로 바꾸는 메서드
        tmp = self.head
        for i in range (0, self.current, 1):
            tmp = tmp.next
        cap = ord(tmp.data)
        if (cap >= 65 and cap <= 90): #current point의 원소가 대문자인 경우
            cap = cap + 32
        elif (cap >= 97 and cap <= 122): #current point의 원소가 소문자인 경우
            cap = cap -32
        tmp.data = chr(cap)

def is_number(factor): #factor가 숫자인지 확인하는 함수
    try:
        float(factor)
        return 1
    except ValueError:
        return 0

answer = [] #command를 받을 배열(문자열)

print("\n");
print("───────────────────────────────────────────────────\n")
print("\t      C O M M A N D   H E L P E R \n");
print("───────────────────────────────────────────────────\n")
print("  + : Insert factor                                                       \n")
print("      ex) +a +b +c +d                                                     \n")
print("  < : Move current point to first                                         \n")
print("  > : Move current point to last                                          \n")
print("  N : Move current point to next                                          \n")
print("  P : Move current point to prev                                          \n")
print("  n : (n: integer) Move current point to nth element			 \n")
print("  - : Delete current factor					         \n")
print("  # : Print the number of factors          		                 \n")
print(" ?@ : Check data @ is member of linked list or not		         \n")
print("  G : Get data of current point	                                         \n")
print("	=@ : Replace data of current point to @	                                 \n")
print("	 E : Check linked list is empty or not 		                         \n")
print("	 C : Delete all factors    	                                         \n")
print("  L : Print all factors							 \n")
print("* R : Reverse factors of linked list				     	 \n")
print("	   ex) a b c d -> d c b a						 \n")
print("* S : Duplicate data of current point			     	         \n")
print("	   ex) a b c (current point: b) -> a b b c 		   	         \n")
print("* A : Upper or lower the letter			     		         \n")
print("	   ex) a b c (current point: b) -> a B c 		   	         \n")
print("	   ex) a B c (current point: B) -> a b c 		   	         \n")
print("───────────────────────────────────────────────────\n")
print("  This program can handle only 30 commands				 \n")
print("  Make a space between commands					         \n")
print("  Programmed by 2019310181 Dongseop Lee					 \n")
print("───────────────────────────────────────────────────\n")

while True:
    answer = input("  >> ") #command 입력받음
    long = len(answer)

    i = 0
    
    while i < long: #command가 남지 않을 때까지 반복함

        if answer[i] == '+': #원소를 추가할 때
            if start == 0: #가장 첫 원소를 추가할 때
                mylist = LinkedList(answer[i+1])

            else:
                if mylist.current + 1 == mylist.size: #제일 끝에 원소를 추가할 때
                    mylist.addTail(answer[i+1])
                    i += 1
                else: #중간에 원소를 추가할 때
                    mylist.add(answer[i+1])
                    i += 1

        elif answer[i] == 'L': #원소들을 모두 출력해야 할 때
            break

        elif answer[i] == 'G': #current point의 원소를 출력하고 싶을 때
            if (start): 
                print("  {0}\n".format(mylist.get_data()))
            else: #원소가 하나도 없을 때
                print("  empty list\n")

        elif answer[i] == '<': #current point를 가장 앞으로 옮기고 싶을 때
            mylist.traverse_first()
            if long > 2:
                if answer[i+2] == '+': #가장 앞에 원소를 추가할 때
                    mylist.addFirst(answer[i+3])
                    i += 3

        elif answer[i] == '>': #current point를 가장 뒤로 옮기고 싶을 때
            mylist.traverse_last()

        elif answer[i] == 'N': #current point를 한칸 뒤로 옮기고 싶을 때
            mylist.traverse_next()

        elif answer[i] == 'P': #current point를 한칸 앞으로 옮기고 싶을 때
            mylist.traverse_prev()

        elif answer[i] == '-': #current point의 원소를 삭제하고 싶을 때
            mylist.delete()

        elif answer[i] == '=': #current point의 원소를 다른 원소로 replace 하고 싶을 때
            mylist.replace(answer[i+1])
            i += 1

        elif is_number(answer[i]): #입력받은 숫자번째로 current point를 변경하고 싶을 때
            mylist.current =  int(answer[i]) - 1

        elif answer[i] == '#': #원소의 개수를 출력하고 싶을 때
            print("  {0}\n".format(mylist.data_count()))

        elif answer[i] == '?': #해당 원소가 linked list 안에 있는지 확인하고 싶을 때
            mem = mylist.is_member(answer[i+1])

            if mem == -1: #해당 원소를 찾지 못했을 때
                print("  {0} is not member\n".format(answer[i+1]))

            else: #해당 원소를 찾았을 때
                print("  {0} is our member {1}\n".format(answer[i+1], mem+1))

            i += 1

        elif answer[i] == 'C': #linked list의 모든 원소들을 삭제하고 싶을 때
            mylist.clear()
            start = 0

        elif answer[i] == 'E': #linked list가 비어 있는지 확인하고 싶을 때
            if mylist.is_empty():
                print("  TRUE\n")

            else:
                print("  FALSE\n")

        elif answer[i] == 'R': #linked list 원소들의 순서를 거꾸로 뒤집고 싶을 때
            mylist.reverse()
 
        elif answer[i] == 'S': #current point의 원소를 복제하고 싶을 때
            mylist.split()

        elif answer[i] == 'A': #current point의 원소가 대문자면 소문자로, 소문자면 대문자로 바꾸고 싶을 때
            mylist.capital()

        elif answer[i] == ' ': #공백이 입력되었을 때
            i += 1
            continue

        i += 1

    if (start): #만약 원소가 하나라도 있으면
        print(mylist) #명령어를 처리할 때마다 linked list를 출력
    else: #원소가 하나도 없을 때
        print('  empty list\n')

             
            

    

    

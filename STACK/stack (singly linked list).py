class NODE: #NODE class 정의
    def __init__(self, data): #node를 생성하고 받은 data를 저장하는 스페셜 메서드
        self.data = data
        self.next = None

    def __str__(self): #node의 data 값을 출력하는 스페셜 메서드
        return str(self.data)

class STACK: #STACK class 정의
    def __init__(self, MAX): #첫번째 헤드 node를 생성하면서, stack을 생성하는 스페셜 메서드
        new = NODE(None)
        self.top = new.next #헤드 node의 다음이 top에 해당하게 된다
        self.size = 0 #stack의 크기를 저장하는 속성
        self.max = MAX #stack의 최대 크기를 저장하는 속성

    def __str__(self): #stack의 모든 node의 data들을 출력하는 스페셜 메서드
        tmp = STACK(self.max) #임시 stack을 생성
        display = '  '
        while (self.is_empty() != 1): #my_stack에서 pop해서 임시 stack으로 push
            tmp.push(self.pop())

        while (tmp.is_empty() != 1): #다시 임시 stack에서 pop해서 my_stack으로 push하면서 하나씩 출력
            self.push(tmp.pop())
            display += self.peek()
            display += ' '

        if (self.is_empty() != 1): #만약 stack이 비어있지 않으면 top의 data를 출력 
            display += '(top: {0})\n'.format(self.top.data)
        else:
            display += 'empty stack\n'

        return display

    def push(self, data): #stack의 top에 데이터를 push하는 메서드
        new = NODE(data)

        new.next = self.top
        self.top = new
        self.size += 1

    def pop(self): #stack의 top에서 데이터를 pop하는 메서드
        pop_data = self.top.data #뽑아낼 데이터를 따로 저장

        target = self.top
        self.top = self.top.next

        del target

        self.size += -1

        return pop_data

    def element_count(self): #stack의 element의 개수를 반환하는 메서드
        count = 0
        tmp = self.top
        while (tmp):
            tmp = tmp.next
            count += 1

        return count

    def is_empty(self): #stack이 비어있는지 확인하는 메서드
        if (self.size == 0):
            return 1
        else:
            return 0

    def is_full(self): #stack이 가득 차있는지 확인하는 메서드 
        if (self.size >= self.max):
            return 1
        else:
            return 0

    def peek(self): #stack의 top에 있는 데이터를 반환하는 메서드 
        return self.top.data

    def topp(self): #stack의 top의 위치를 반환하는 메서드
        return self.size

    def is_member(self, element): #특정 데이터가 stack의 멤버인지 확인하는 메서드
        tmp = STACK(self.max) #임시 stack을 생성
        TF = 0

        while (self.is_empty() != 1): #my_stack에서 pop해서 임시 stack으로 push
            tmp.push(self.pop())

        while (tmp.is_empty() != 1):#다시 임시 stack에서 pop해서 my_stack으로 push하면서 찾는 데이터가 있는지 확인
            self.push (tmp.pop())
            if (self.peek() == element):
                TF = 1
        return TF

    def replace(self, new_element): #top의 데이터를 pop하고, 받은 데이터를 push하는 메서드
        self.pop()
        self.push(new_element) #pop and push 

    def clear(self): #stack이 빌 때까지 pop하는 메서드 (stack의 모든 데이터를 삭제)
        tmp = self.element_count() #원소의 개수만큼
        for i in range (0, tmp, 1):
            self.pop() #pop하기
        print("  clear finished\n")

    def twice(self): #stack의 모든 element들을 두배로 불리는 메서드 (use 2 stacks)
        if (self.max < (self.size)*2): #max size의 한계로 인해 2배로 늘릴 수 없을 때
            print("  [Error] not enough memory\n")
            return

        tmp = STACK(self.max) #임시 stack을 생성

        while (self.is_empty() != 1): #my_stack에서 pop해서 임시 stack으로 push
            tmp.push(self.pop())

        while (tmp.is_empty() != 1): #다시 임시 stack에서 pop해서 my_stack으로 "두번씩" push
            twice = tmp.pop()
            self.push(twice)
            self.push(twice)

    def reverse(self): #stack의 element들을 invert하는 메서드 (use 2 stacks)
        if (self.is_empty() == 1): #stack이 비어있을 때
            print("  [Error] nothing to reverse\n")
            return

        tmp = STACK(self.max) #임시 stack을 생성
        while (self.is_empty() != 1): #my_stack에서 pop해서 임시 stack으로 push
            tmp.push(self.pop())

        return tmp #임시 stack을 return

    def maxpush(self, element): #stack이 가득 찰 때까지 받은 데이터를 push하는 메서드
        if (self.is_full() == 1): #이미 가득 차있을 때
            print("  [Error] already full\n")
            return

        count = self.max - self.size
        for i in range (0, count, 1): #가득 찰 때까지
            self.push(element) #받은 데이터를 push

def is_number(factor): #factor가 숫자인지 확인하는 함수
    try:
        float(factor)
        return 1
    except ValueError:
        return 0

print("\n");
print("───────────────────────────────────────────────────\n")
print("\t      C O M M A N D   H E L P E R                                       \n");
print("───────────────────────────────────────────────────\n")
print("  + : Push element(s)                                                     \n")
print("      ex) +a +b +c +d                                                     \n")
print("  - : Pop element                                                         \n")
print("  L : Print all elements                                                  \n")
print("  P : Peek data of top                                                    \n")
print("  F : Check stack is full or not                                          \n")
print("  # : Print the number of elements                			 \n")
print("  T : Print location and data of top				         \n")
print(" n- : (n: integer) Pop element n times          		                 \n")
print(" ?@ : Check data @ is member of stack or not         		         \n")
print(" =@ : Replace data of top to @	                                         \n")
print("  C : Delete all elements of stack                                        \n")
print("───────────────────────────────────────────────────\n")
print("\t      N  E  W   F U N C T I O N S					 \n")
print("───────────────────────────────────────────────────\n")
print("  t : Make stack be doubled					     	 \n")
print("	   ex) a b c (top: c) -> a a b b c c (top: c)				 \n")
print("  R : Reverse elements of stack			     	                 \n")
print("	   ex) a b c d (top: d) -> d c b a (top: a) 		   	         \n")
print(" X@ : Push @ until stack is full			     		         \n")
print("	   ex) a b c (top: c) (if max == 10)				         \n")
print("	       >> Xh                     				         \n")
print("	       a b c h h h h h h h (top: h) 				         \n")
print("───────────────────────────────────────────────────\n")
print("  The length of command must be shorter than 30				 \n")
print("  Make a space between commands					         \n")
print("  Programmed by 2019310181 Dongseop Lee					 \n")
print("───────────────────────────────────────────────────\n")

answer = [] #command를 받을 배열(문자열)
MAX = int(input("  decide max size of stack: ")) #stack의 max size 입력받기
my_stack = STACK(MAX) #create(my_stack)

while True:
    answer = input("  >> ") #command 입력받음
    long = len(answer) 

    i = 0

    while i < long: #command가 남지 않을 때까지 반복
        if answer[i] == '+': #push할 때
            if (my_stack.is_full()): #stack이 가득 차있으면
                print("  [Error] Stack is full\n")
            else: #stack이 가득 차있지 않으면
                my_stack.push(answer[i+1])
            i += 1
            
        elif answer[i] == '-': #pop할 때
            if (my_stack.is_empty()): #stack이 비어있으면
                print("  [Error] Nothing to pop\n")
            else: #stack이 비어있지 않으면
                print("  return {0}\n".format(my_stack.pop()))
                
        elif answer[i] == 'L': #stack을 출력할 때
            break
        
        elif answer[i] == 'P': #stack의 top에 있는 data를 보고싶을 때 
            if (my_stack.is_empty()): #stack이 비어있으면 
                print("  [Error] Nothing to peek\n")
            else: #stack이 비어있지 않으면
                print("  {0}\n".format(my_stack.peek()))
                
        elif answer[i] == 'F': #stack이 가득 차있는지 알고싶을 때
            if (my_stack.is_full()): #stack이 가득 차있으면 
                print("  TRUE\n") 
            else: #stack이 가득 차있지 않으면 
                print("  FALSE\n")
                
        elif answer[i] == '#': #stack의 원소의 개수를 알고싶을 때
            print("  element count: {0}\n".format(my_stack.element_count()))

        elif answer[i] == 'T': #stack의 top 위치와 data 값을 알고 싶을 때
            if (my_stack.is_empty()): #stack이 비어있을 때
                print("  [Error] nothing on top")
            else: #stack이 비어있지 않을 때
                print("  ( {0}, {1} )\n".format(my_stack.topp(), my_stack.peek()))

        elif is_number(answer[i]): #반복해서 pop을 하고 싶을 때
            for j in range (0, int(answer[i]), 1): #입력받은 숫자만큼 반복
                if (my_stack.is_empty()): #stack이 비어있을 때
                    print("  [Error] nothing to pop\n")
                else: #stack이 비어있지 않을 때
                    print("  return {0}\n".format(my_stack.pop()))
            i += 1

        elif answer[i] == '?': #특정 data가 stack의 원소인지 확인하고 싶을 때
            if (my_stack.is_member(answer[i+1])): #member가 맞으면
                print("  TRUE\n")
            else: #member가 아니면
                print("  FALSE\n")
            i += 1

        elif answer[i] == '=': #top의 data를 특정 data로 교체하고 싶을 때
            if (my_stack.is_empty()): #stack이 비어있으면
                print("  [Error] no element to replace\n")
            else: #stack이 비어있지 않으면
                my_stack.replace(answer[i+1])
            i += 1

        elif answer[i] == 'C': #stack을 비우고 싶을 때
            my_stack.clear()

        elif answer[i] == 't': #stack의 원소들을 각각 두배로 늘리고 싶을 때
            my_stack.twice()

        elif answer[i] == 'R': #stack을 invert하고 싶을 때
            my_stack = my_stack.reverse() #임시 stack을 my_stack으로 변경

        elif answer[i] == 'X': #stack이 가득 찰 때까지 특정 데이터를 push하고 싶을 때
            my_stack.maxpush(answer[i+1])
            i += 1
                         
        i+= 1

    print(my_stack) #command를 처리할 때마다 결과를 출력

            
        


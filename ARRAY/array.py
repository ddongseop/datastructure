current = -1 #current point를 나타내는 전역 변수
size = 0 #배열에 있는 원소 수를 나타내는 전역 변수
 
def insert(arr, data): #배열에 원소를 추가하는 함수
    global current
    global size
    if current+1 == size: #배열의 끝에 원소를 추가할 때
        arr.append(data)
    else: #배열의 끝이 아닌 곳에 원소를 추가할 때
        arr.insert(current+1, data)
    current += 1
    size += 1

def traverse_front(arr, count): #배열의 처음으로 current point를 이동하는 함수
    global current
    global size
    current = 0
    if count >= size: #N이 과도하게 입력되었을 때
        print("최대 이동 거리를 벗어났습니다\n")
        count = size-1
    if count: #<다음 N이 하나라도 왔을 때
        current = current + count

def traverse_rear(arr, count): #배열의 마지막으로 current point를 이동하는 함수
    global current
    global size
    current = size - 1; 
    if count >= size: #P가 과도하게 입력되었을 때
        print("최대 이동 거리를 벗어났습니다\n")
        count = size - 1;
    if count: #>다음 P가 하나라도 왔을 때
        current = current - count

def delete(arr): #current point의 원소를 삭제하는 함수
    global current
    global size
    if size <= 0: #더이상 지울 원소가 남아있지 않을 때
        print("지울 배열 요소가 더이상 없습니다\n")
        return
    size-=1
    for i in range(current, size, 1):
        arr[i] = arr[i+1]
    if current >= size: #current point가 가리키는 곳에 더이상 원소가 없을 때
        current = 0
        print("배열의 크기가 current point보다 작아져 current point를 0으로 초기화 합니다\n")
        
def get_data(arr): #current point의 원소를 return하는 함수
    return arr[current]
    
def replace(arr, new_data): #current point의 원소를 새로운 원소로 바꾸는 함수
    arr[current] = new_data
    
def empty(arr): #배열에 있는 원소들을 모두 삭제하는 함수
    global current 
    global size
    del arr[:]
    current = -1 #초기화
    size = 0 #초기화

def data_count(arr): #배열의 원소 수를 반환하는 함수
    global size
    return size
    
def move(arr, new_position): #current point의 원소를 다른 위치로 옮기는 함수
    global current
    global size
    if current == new_position: #현재 위치로 움직이려고 한 경우
        print("현재 위치입니다")
    elif (current > new_position): #현재 위치보다 앞으로 움직이려고 한 경우
        temp = arr[current]
        for i in range (current, new_position, -1):
            arr[i] = arr[i-1]
        arr[new_position] = temp
        current = new_position
    else: #현재 위치보다 뒤로 움직이려고 한 경우
        temp = arr[current]
        for i in range (current, new_position, 1):
            arr[i] = arr[i+1]
        arr[new_position] = temp
        current = new_position
        
def printt(arr): #배열에 있는 원소들을 모두 출력하는 함수
    print("  ",end='')
    for i in range(0, size, 1): #배열의 원소들을 출력
        print(arr[i], end=' ')
    if size: #배열에 원소가 하나라도 있으면 current point를 출력
        print("(current point: ", arr[current], ")\n")
    else:
        print("empty array\n")

def reverse(arr): #배열에 있는 원소들의 순서를 거꾸로 뒤집는 함수
    r = int(size/2)
    for i in range (0, r, 1):
        arr[i], arr[(size - 1) - i] = arr[(size - 1) - i], arr[i]

def split(arr): #current point에 있는 원소를 복제하는 함수 (ex) a b c (current point: b) -> a b b c
    global size
    global current
    if current+1 == size:
        arr.append(arr[current])
    else:
        arr.insert(current+1, arr[current])    
    size +=1
    current +=1

def capital(arr): #current point의 원소가 대문자이면 소문자로, 소문자이면 대문자로 바꾸는 함수
    cap = ord(arr[current])
    if (cap >= 65 and cap <= 90): #current point의 원소가 대문자인 경우
        cap = cap + 32;
    elif (cap >= 97 and cap <= 122): #current point의 원소가 소문자인 경우
        cap = cap - 32;
    arr[current] = chr(cap)
    
my_array = [] #원소들을 저장받을 배열(문자열): create(array)
answer = [] #command를 받을 배열(문자열)

print("\n");
print("─────────────────────────────────────\n")
print("\t      C O M M A N D   H E L P E R \n");
print("─────────────────────────────────────\n")
print("  + : Insert factor                                                       \n")
print("      ex) +a+b+c+d                                                        \n")
print("  < : Move current point to first                                         \n")
print("  > : Move current point to last                                          \n")
print("  <N : Move current point to first and move to next                       \n")
print("  >P : Move current point to last and move to prev                        \n")
print("  - : Delete current factor						 \n")
print("  @ : Get data of current point					         \n")
print("  =? : Replace data of current point to ?		                 \n")
print("  E : Delete all factors						         \n")
print("  M? : Move data of current point to index ?		                 \n")
print("	   ex) M2: Move data of current point to index 2	                 \n")
print("	   ex) Mn: Move data of current point to last	                    	 \n")
print("	   ex) MP: Move data of current point to prev   	                 \n")
print("	   ex) MN: Move data of current point to next   	                 \n")
print("  L : Print all factors							 \n")
print("* R : Reverse factors of my array				     	 \n")
print("	   ex) a b c d -> d c b a						 \n")
print("* S : Duplicate data of current point			     	         \n")
print("	   ex) a b c (current point: b) -> a b b c 		   	         \n")
print("* C : Upper or lower the letter			     		         \n")
print("	   ex) a b c (current point: b) -> a B c 		   	         \n")
print("	   ex) a B c (current point: B) -> a b c 		   	         \n")
print("─────────────────────────────────────\n")
print("  This program can handle only 30 factors				 \n")
print("  Don't make a space between commands					 \n")
print("  Programmed by 2019310181 Dongseop Lee					 \n")
print("─────────────────────────────────────\n")

while True:
    count = 0 #<NNN과 같은 상황에서 N이 몇번 나왔는지 세는 변수(매번 초기화)
    answer = input("  >> ") #command 입력받음
    
    if answer[0] == '+': #원소를 추가할 때
        l = int((len(answer)/2)+1)
        for i in range (1, l, 1):
            a = (2*i)-1
            insert(my_array, answer[a])
        printt(my_array)

    if answer[0] == '<': #current point를 맨 앞으로 이동할 때 (추가로 <N, <-, <M2, <Mn, <MN 가능)
        l = len(answer)
        b = 1
        if l>1:
            while True:
                if b > l-1: 
                    break #N이 없으면 count 중지
                elif answer[b] == 'N':
                    count += 1
                    b += 1
                else:
                    break
        traverse_front(my_array, count)
        b = 1
        if l>1:
            if answer[b] == '-':
                delete(my_array)
        if l>2:
            if answer[b] == 'M':
                if answer[b+1] == 'n':
                    np = size - 1
                elif answer[b+1] == 'P':
                    np = current - 1
                elif answer[b+1] == 'N':
                    np = current + 1
                else:
                    np = int(answer[b+1])
                move(my_array, np)
        printt(my_array)

    if answer[0] == '>': #current point를 맨 뒤로 이동할 때 (추가로 >P, >-, >M2, >Mn, >MP 가능)
        l = len(answer)
        c = 1
        if l>1:
            while True:
                if c > l-1:
                    break #P가 없으면 count 중지
                elif answer[c] == 'P':
                    count += 1
                    c += 1
                else:
                    break
        traverse_rear(my_array, count)
        c = 1
        if l>1:
            if answer[c] == '-':
                delete(my_array)
        if l>2:
            if answer[c] == 'M':
                if answer[c+1] == 'n':
                    np = size - 1
                elif answer[c+1] == 'P':
                    np = current - 1
                elif answer[c+1] == 'N':
                    np = current + 1
                else:
                    np = int(answer[c+1])
                move(my_array, np)
        printt(my_array)

    if answer[0] == '-': #current point의 원소를 삭제할 때
        delete(my_array)
        printt(my_array)

    if answer[0] == '@': #current point의 값을 출력하고 싶을 때
        print('  ', get_data(my_array), '\n')

    if answer[0] == '=': #current point의 원소를 다른 원소로 교체하고 싶을 때
        replace(my_array, answer[1])
        printt(my_array)

    if answer[0] == 'E': #배열의 원소들을 모두 삭제할 때
        empty(my_array)
        print("  empty array\n")

    if answer[0] == 'M': #current point의 원소를 다른 위치로 옮기고 싶을 때
        if answer[1] == 'n':
            np = size - 1
        elif answer[1] == 'P':
            np = current - 1
        elif answer[1] == 'N':
            np = current + 1
        else:
            np = int(answer[1])
        move(my_array, np)
        printt(my_array)

    if answer[0] == 'L': #배열의 원소들을 모두 출력하고 싶을 때
        printt(my_array)

    if answer[0] == 'R': #배열의 원소들의 순서를 뒤집고 싶을 때
        reverse(my_array)
        printt(my_array)

    if answer[0] == 'S': #current point의 원소를 복제하고 싶을 때
        split(my_array)
        printt(my_array)

    if answer[0] == 'C': #current point의 원소가 대문자면 소문자로, 소문자면 대문자로 바꾸고 싶을 때
        capital(my_array)
        printt(my_array)

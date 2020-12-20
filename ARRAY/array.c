#include <stdio.h>
#pragma warning (disable:4996)

int current = -1; //current point를 나타내는 전역 변수
int size = 0; //배열에 있는 원소 수를 나타내는 전역 변수
void insert(char arr[], char data); //배열에 원소를 추가하는 함수
void traverse_front(char arr[], int count); //배열의 처음으로 current point를 이동하는 함수
void traverse_rear(char arr[], int count); //배열의 마지막으로 current point를 이동하는 함수
void delete(char arr[]); //current point의 원소를 삭제하는 함수
char get_data(char arr[]); //current point의 원소를 return하는 함수
void replace(char arr[], char new_data); //current point의 원소를 새로운 원소로 바꾸는 함수
void empty(char arr[]); //배열에 있는 원소들을 모두 삭제하는 함수
int data_count(char arr[]); //배열의 원소 수를 반환하는 함수
void move(char arr[], int new_position); //current point의 원소를 다른 위치로 옮기는 함수
void print(char arr[]); //배열에 있는 원소들을 모두 출력하는 함수
void reverse(char arr[]); //배열에 있는 원소들의 순서를 거꾸로 뒤집는 함수
void split(char arr[]); //current point에 있는 원소를 복제하는 함수 (ex) a b c (current point: b) -> a b b c
void capital(char arr[]); //current point의 원소가 대문자이면 소문자로, 소문자이면 대문자로 바꾸는 함수

int main() {
	char my_array[30]; //원소들을 저장받을 배열(문자열): create(array)
	char answer[30]; //command를 받을 배열(문자열)
	int i;
	int count = 0; //<NNN과 같은 상황에서 N이 몇번 나왔는지 세는 변수

	printf("\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("\t      C O M M A N D   H E L P E R \n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  + : Insert factor                                     \n");
	printf("      ex) +a+b+c+d                                      \n");
	printf("  < : Move current point to first                       \n");
	printf("  > : Move current point to last                        \n");
	printf("  <N : Move current point to first and move to next     \n");
	printf("  >P : Move current point to last and move to prev      \n");
	printf("  - : Delete current factor								\n");
	printf("  @ : Get data of current point					        \n");
	printf("  =? : Replace data of current point to ?		        \n");
	printf("  E : Delete all factors						        \n");
	printf("  M? : Move data of current point to index ?		    \n");
	printf("	   ex) M2: Move data of current point to index 2	\n");
	printf("	   ex) Mn: Move data of current point to last		\n");
	printf("	   ex) MP: Move data of current point to prev   	\n");
	printf("	   ex) MN: Move data of current point to next   	\n");
	printf("  L : Print all factors							     	\n");
	printf("* R : Reverse factors of my array				     	\n");
	printf("	   ex) a b c d -> d c b a						   	\n");
	printf("* S : Duplicate data of current point			     	\n");
	printf("	   ex) a b c (current point: b) -> a b b c 		   	\n");
	printf("* C : Upper or lower the letter			     		    \n");
	printf("	   ex) a b c (current point: b) -> a B c 		   	\n");
	printf("	   ex) a B c (current point: B) -> a b c 		   	\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  This program can handle only 30 factors				\n");
	printf("  Don't make a space between commands					\n");
	printf("  Programmed by 2019310181 Dongseop Lee					\n");
	printf("─────────────────────────────────────────────────────────────\n");
	while (1) {
		printf("  >> ");
		count = 0; //매번 초기화
		scanf("%s", answer); //command 입력받음
		
		//원소를 추가할 때
		if (answer[0] == '+') {
			int a = 1;
			while (1) {
				insert(my_array, answer[a]);
				current++;
				size++;
				if (answer[a + 1] == '+') {
					a = a + 2;
				}
				else
					break;
			}
			print(my_array);
		} 
		//current point를 맨 앞으로 이동할 때 (추가로 <N, <-, <M2, <Mn, <MN 가능)
		if (answer[0] == '<') {
			int b = 1;
			while (1) {
				if (answer[b] == 'N') {
					count++;
					b++;
				}
				else
					break;
			}
			traverse_front(my_array, count);
			if (answer[b] == '-') {
				delete(my_array);
			}
			else if (answer[b] == 'M') {
				int np;
				if (answer[b+1] == 'n') {
					np = size - 1;
				}
				else if (answer[b+1] == 'P') {
					np = current - 1;
				}
				else if (answer[b+1] == 'N') {
					np = current + 1;
				}
				else {
					np = answer[b+1] - '0';
				}
				move(my_array, np);
			}
	
			print(my_array);
		}
		//current point를 맨 뒤로 이동할 때 (추가로 >P, >-, >M2, >Mn, >MP 가능)
		if (answer[0] == '>') {
			int c = 1;
			while (1) {
				if (answer[c] == 'P') {
					count++;
					c++;
				}
				else
					break;
			}
			traverse_rear(my_array, count);
			if (answer[c] == '-') {
				delete(my_array);
			}
			else if (answer[c] == 'M') {
				int np;
				if (answer[c+1] == 'n') {
					np = size - 1;
				}
				else if (answer[c+1] == 'P') {
					np = current - 1;
				}
				else if (answer[c+1] == 'N') {
					np = current + 1;
				}
				else {
					np = answer[c+1] - '0';
				}
				move(my_array, np);
			}
			print(my_array);
		}
		//current point의 원소를 삭제할 때
		if (answer[0] == '-') {
			delete(my_array);
			print(my_array);
		}
		//current point의 값을 출력하고 싶을 때
		if (answer[0] == '@') {
			printf("  %c\n", get_data(my_array));
		}
		//current point의 원소를 다른 원소로 교체하고 싶을 때
		if (answer[0] == '=') {
			replace(my_array, answer[1]);
			print(my_array);
		}
		//배열의 원소들을 모두 삭제할 때
		if (answer[0] == 'E') {
			empty(my_array);
			printf("  empty array\n");
		}
		//current point의 원소를 다른 위치로 옮기고 싶을 때
		if (answer[0] == 'M') {
			int np;
			if (answer[1] == 'n') {
				np = size - 1;
			}
			else if (answer[1] == 'P') {
				np = current - 1;
			}
			else if (answer[1] == 'N') {
				np = current + 1;
			}
			else {
				np = answer[1] - '0';
			}
			move(my_array, np);
			
			print(my_array);
		}
		//배열의 원소들을 모두 출력하고 싶을 때
		if (answer[0] == 'L') {
			print(my_array);
		}
		//배열의 원소들의 순서를 뒤집고 싶을 때
		if (answer[0] == 'R') {
			reverse(my_array);
			print(my_array);
		}
		//current point의 원소를 복제하고 싶을 때
		if (answer[0] == 'S') {
			split(my_array);
			print(my_array);
		}
		//current point의 원소가 대문자면 소문자로, 소문자면 대문자로 바꾸고 싶을 때
		if (answer[0] == 'C') {
			capital(my_array);
			print(my_array);
		}
	}//while
	
	return 0;
}
	void insert(char arr[], char data) {
		if (current + 1 == size) { //배열의 끝에 원소를 추가할 때
			arr[current + 1] = data;
		}
		else //배열의 끝이 아닌 곳에 원소를 추가할 때
			for (int i = size; i > current+1; i--) {
				arr[i] = arr[i - 1];
			}
			arr[current + 1] = data;
	}
	void traverse_front(char arr[], int count) {
		current = 0;
		if (count >= size) { //N이 과도하게 입력되었을 때
			printf("최대 이동 거리를 벗어났습니다\n");
			count = size - 1;
		}
		if (count) { //<다음 N이 하나라도 왔을 때
			current = current + count;
		}
	}
	void traverse_rear(char arr[], int count) {
		current = size - 1;
		if (count >= size) { //P가 과도하게 입력되었을 때
			printf("최대 이동 거리를 벗어났습니다\n");
			count = size - 1;
		}
		if (count) { //>다음 P가 하나라도 왔을 때
			current = current - count;
		}
	}
	void delete(char arr[]) {
		if (size <= 0) { //더이상 지울 원소가 남아있지 않을 때
			printf("지울 배열 요소가 더이상 없습니다\n");
			return;
		}
		size--;
		for (int i = current; i < size; i++) {
			arr[i] = arr[i + 1];
		}
		if (current >= size) {//current point가 가리키는 곳에 더이상 원소가 없을 때
			current = 0;
			printf("배열의 크기가 current point보다 작아져 current point를 0으로 초기화 합니다\n");
		}
	}
	char get_data(char arr[]) {
		return arr[current];
	}
	void replace(char arr[], char new_data) {
		arr[current] = new_data;
	}
	void empty(char arr[]) {
		for (int i = 0; i < size; i++) {
			arr[i] = '\0';
		}
		current = -1; //초기화
		size = 0; //초기화
	}
	int data_count(char arr[]) {
		return size;
	}
	void move(char arr[], int new_position) {
		char temp;
		if (current == new_position) {
			printf("현재 위치입니다\n"); //현재 위치로 움직이려고 한 경우
		}
		else if (current > new_position) { //현재 위치보다 앞으로 움직이려고 한 경우
			temp = arr[current];
			for (int i = current; i > new_position; i--) {
				arr[i] = arr[i - 1];
			}
			arr[new_position] = temp;
			current = new_position;
		}
		else { //현재 위치보다 뒤로 움직이려고 할 경우
			temp = arr[current];
			for (int i = current; i < new_position; i++) {
				arr[i] = arr[i + 1];
			}
			arr[new_position] = temp;
			current = new_position;
		}
	}
	void print(char arr[]) {
		printf("  ");
		for (int i = 0; i < size; i++) { //배열의 원소들을 출력
			printf("%c ", arr[i]);
		}
		if (size) { //배열에 원소가 하나라도 있으면 current point를 출력
			printf("(current point: %c)\n", arr[current]);
		}
		else
			printf("empty array\n");
	}
	void reverse(char arr[]) {
		int r = (size / 2);
		char temp;
		for (int i = 0; i < r; i++) {
			temp = arr[i];
			arr[i] = arr[(size - 1) - i];
			arr[(size - 1) - i] = temp;
		}
	}
	void split(char arr[]) {
		for (int i = current + 2; i < size + 1; i++) {
			arr[i] = arr[i - 1];
		}
		arr[current + 1] = arr[current];
		size++;
		current++;
	}
	void capital(char arr[]) {
		if (arr[current] >= 'A' && arr[current] <= 'Z') { //current point의 원소가 대문자인 경우
			arr[current] = arr[current] + 32;
		}
		else if (arr[current] >= 'a' && arr[current] <= 'z') { //current point의 원소가 소문자인 경우
			arr[current] = arr[current] - 32;
		}
	}
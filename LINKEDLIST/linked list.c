#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#pragma warning (disable:4996)

int current = -1; //current point를 나타내는 전역 변수
int size = 0; //linked list에 있는 원소 수를 나타내는 전역 변수

typedef struct node { //singly linked list의 node 구조체 정의
	char data;
	struct node* next;
}NODE;

NODE* init(char); //node를 생성하고 받은 데이터를 node에 저장하는 함수
NODE* addTail(NODE*, char); //linked list의 가장 뒷부분에 node를 추가하는 함수
void print(NODE*); //linked list의 모든 node의 data들을 출력하는 함수
char get_data(NODE*); //current point의 data 값을 return하는 함수
void traverse_first(); //current point를 가장 앞으로 옮기는 함수
void traverse_last(); //current point를 가장 뒤로 옮기는 함수
void traverse_next(); //current point를 한칸 뒤로 옮기는 함수
void traverse_prev(); //current point를 한칸 앞으로 옮기는 함수
NODE* delete(NODE*); //current point의 node를 삭제하는 함수
NODE* addFirst(NODE*, char); //linked list의 가장 앞부분에 node를 추가하는 함수
void add(NODE*, char); //current point에 node를 추가하는 함수
void replace(NODE*, char); //current point의 data를 다른 data로 replace하는 함수
int data_count(NODE*); //linked list의 data 개수를 세는 함수
int is_member(NODE*, char); //입력받은 data가 linked list에 있는지 확인하는 함수
NODE* clear(NODE*); //linked list의 모든 원소를 삭제하는 함수
int is_empty(NODE*); //linked list가 비어 있는지 확인하는 함수
NODE* reverse(NODE*); //linked list의 원소들을 역순으로 재배치하는 함수
NODE* split(NODE*); //current point의 원소를 복제하는 함수 (ex) a b c (current point: b) -> a b b c
void capital(NODE*); //current point의 원소가 대문자면 소문자로, 소문자면 대문자로 바꾸는 함수

int main() {
	NODE* head = NULL; // create(my_list)
	char answer[30]; //command를 받을 배열(문자열)
	int i;

	printf("\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("\t      C O M M A N D   H E L P E R \n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  + : Insert factor                                     \n");
	printf("      ex) +a +b +c +d                                   \n");
	printf("  < : Move current point to first                       \n");
	printf("  > : Move current point to last                        \n");
	printf("  N : Move current point to next						\n");
	printf("  P : Move current point to prev					    \n");
	printf("  n : (n: integer) Move current point to nth element	\n");
	printf("  - : Delete current factor								\n");
	printf("  # : Print the number of factors						\n");
	printf(" ?@ : Check data @ is member of linked list or not		\n");
	printf("  G : Get data of current point					        \n");
	printf(" =@ : Replace data of current point to @		        \n");
	printf("  E : Check linked list is empty or not					\n");
	printf("  C : Delete all factors						        \n");
	printf("  L : Print all factors							     	\n");
	printf("* R : Reverse factors of linked list			     	\n");
	printf("	   ex) a b c d -> d c b a						   	\n");
	printf("* S : Duplicate data of current point			     	\n");
	printf("	   ex) a b c (current point: b) -> a b b c 		   	\n");
	printf("* A : Upper or lower the letter			     		    \n");
	printf("	   ex) a b c (current point: b) -> a B c 		   	\n");
	printf("	   ex) a B c (current point: B) -> a b c 		   	\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  This program can handle only 30 commands				\n");
	printf("  Make a space between commands							\n");
	printf("  Programmed by 2019310181 Dongseop Lee					\n");
	printf("─────────────────────────────────────────────────────────────\n");

	while (1) {

		printf("  >> ");
		gets(answer); //command 입력받음

		for (int i = 0; answer[i] != '\0'; i++) { //command가 남지 않을 때까지 반복함

			if (answer[i] == '+') { //원소를 추가할 때
				if (current + 1 == size) { //제일 끝에 원소를 추가할 때
					head = addTail(head, answer[i + 1]);
					i++;
				}
				else { //중간에 원소를 추가할 때
					add(head, answer[i + 1]);
					i++;
				}
			}
			else if (answer[i] == 'L') { //원소들을 모두 출력해야 할 때
				continue;
			}
			else if (answer[i] == 'G') { //current point의 원소를 출력하고 싶을 때
				if (size) {
					printf("  %c\n", get_data(head));
				}
				else //원소가 하나도 없을 때
					printf("empty array\n");
				
			}
			else if (answer[i] == '<') { //current point를 가장 앞으로 옮기고 싶을 때
				traverse_first();
				if (answer[i + 2] == '+') { //가장 앞에 원소를 추가할 때
					head = addFirst(head, answer[i + 3]);
					i = i + 3;
				}
			}
			else if (answer[i] == '>') { //current point를 가장 뒤로 옮기고 싶을 때
				traverse_last();
			}
			else if (answer[i] == 'N') { //current point를 한칸 뒤로 옮기고 싶을 때
				traverse_next();
			}
			else if (answer[i] == 'P') { //current point를 한칸 앞으로 옮기고 싶을 때
				traverse_prev();
			}
			else if (answer[i] == '-') { //current point의 원소를 삭제하고 싶을 때
				head = delete(head);
			}
			else if (answer[i] == '=') { //current point의 원소를 다른 원소로 replace 하고 싶을 때
				replace(head, answer[i + 1]);
				i++;
			}
			else if (isdigit(answer[i])) { //입력받은 숫자번째로 current point를 변경하고 싶을 때
				current = answer[i] - '0' - 1;
			}
			else if (answer[i] == '#') { //원소의 개수를 출력하고 싶을 때
				printf("  %d\n", data_count(head));
			}
			else if (answer[i] == '?') { //해당 원소가 linked list 안에 있는지 확인하고 싶을 때
				int mem = is_member(head, answer[i + 1]);
				if (mem == -1) { //해당 원소를 찾지 못했을 때
					printf("  %c is not member\n", answer[i + 1]);
				}
				else { //해당 원소를 찾았을 때
					printf("  %c is our member %d\n", answer[i + 1], mem + 1);
				}
				i++;
			}
			else if (answer[i] == 'C') { //linked list의 모든 원소들을 삭제하고 싶을 때
				head = clear(head);
				current = -1;
			}
			else if (answer[i] == 'E') { //linked list가 비어 있는지 확인하고 싶을 때
				if (is_empty(head)) {
					printf("  TRUE\n");
				}
				else
					printf("  FALSE\n");
			}
			else if (answer[i] == 'R') { //linked list 원소들의 순서를 거꾸로 뒤집고 싶을 때
				head = reverse(head);
			}
			else if (answer[i] == 'S') { //current point의 원소를 복제하고 싶을 때
				head = split(head);
			}
			else if (answer[i] == 'A') { //current point의 원소가 대문자면 소문자로, 소문자면 대문자로 바꾸고 싶을 때
				capital(head);
			}
			else if (answer[i] == ' ') { //공백이 입력되었을 때
				continue;
			}
		}
		print(head); //명령어를 처리할 때마다 linked list를 출력
	}
	return 0;
}


NODE* init(char data) {
	NODE* new = (NODE*)malloc(sizeof(NODE));
	new->data = data;
	new->next = NULL;
	return new;
}

NODE* addTail(NODE* head, char data) {
	if (size == 0) { //첫 원소를 추가할 때
		head = init(data);
	}
	else { //linked list의 제일 뒷부분에 원소를 추가할 때
		NODE* tmp = head;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = init(data);
	}
	current++;
	size++;

	return head;
}

void print(NODE* head) {
	printf("  ");
	NODE* tmp = head;
	while (tmp) { //linked list의 원소들을 하나씩 출력
		printf("%c ", tmp->data);
		tmp = tmp->next;
	}
	if (size) { //linked list에 원소가 하나라도 있으면 current point를 출력
		tmp = head;
		for (int i = 0; i < current; i++) {
			tmp = tmp->next;
		}
		printf("(current point: %c)\n", tmp->data);
	}
	else
		printf("empty list\n");
}

char get_data(NODE* head) {
	NODE* tmp = head;

	for (int i = 0; i < current; i++) {
		tmp = tmp->next;
	}
	return tmp->data;
}

void traverse_first() {
	current = 0;
}
void traverse_last() {
	current = size - 1;
};
void traverse_next() {
	current++;
};
void traverse_prev() {
	current--;
};

NODE* delete(NODE* head) {

	if (!size) { //원소가 하나도 없을 때
		return;
	}

	NODE* target;
	if (current == 0) { //첫번째 원소를 삭제할 때
		target = head;
		head = head->next;
		free(target);
	}
	else { //첫번째가 아닌 원소를 삭제할 때
		NODE* cur = head;
		for (int i = 0; i < current - 1; i++) {
			cur = cur->next;
		}
		target = cur->next;
		cur->next = cur->next->next;
		free(target);
	}
	size--;

	if (current >= size) { //current point가 linked list에서 벗어났을 때
		printf("  current initialization\n");
		current = 0;
	}

	return head;
}

NODE* addFirst(NODE* head, char data) { //가장 앞에 node를 추가할 때
	NODE* new = (NODE*)malloc(sizeof(NODE));

	new->next = head;
	new->data = data;
	head = new;

	size++;
	return head;
}

void add(NODE* head, char data) { //중간에 node를 추가할 때
	NODE* new = (NODE*)malloc(sizeof(NODE));
	NODE* tmp = head;

	for (int i = 0; i < current; i++) {
		tmp = tmp->next;
	}
	new->data = data;
	new->next = tmp->next;
	tmp->next = new;

	current++;
	size++;
}

void replace(NODE* head, char data) {
	NODE* tmp = head;
	for (int i = 0; i < current; i++) {
		tmp = tmp->next;
	}
	tmp->data = data;
}

int data_count(NODE* head) {
	int count = 0;
	NODE* tmp = head;
	while (tmp) {
		tmp = tmp->next;
		count++;
	}

	return count;
}

int is_member(NODE* head, char data) {
	NODE* tmp = head;
	current = 0;
	while (tmp) {
		if (tmp->data == data) {
			return current;
		}
		tmp = tmp->next;
		current++;
	}
	current--;
	return -1; //해당 원소를 찾지 못했을 때
}

NODE* clear(NODE* head) {
	current = 0;
	int tmp = size;
	for (int i = 0; i < tmp; i++) { //원소의 개수만큼 delete()를 실행
		head = delete(head);
	}
	return head;
}

int is_empty(NODE* head) {
	if (head == NULL) {
		return 1;
	}
	else
		return 0;
}

NODE* reverse(NODE* head) {
	NODE *first, *middle, *last;
	first = head;
	middle = NULL;

	while (first) {
		last = middle;
		middle = first;
		first = first->next;
		middle->next = last; //node의 방향을 변경
	}

	return middle; //새로운 head를 return
}

NODE* split(NODE* head) {
	add(head, get_data(head));

	return head;
}

void capital(NODE* head) {
	NODE* tmp = head;
	for (int i = 0; i < current; i++) {
		tmp = tmp->next;
	}
	if (tmp->data >= 'A' && tmp->data <= 'Z') { //current point의 원소가 대문자인 경우
		tmp->data = tmp->data + 32;
	}
	else if (tmp->data >= 'a' && tmp->data <= 'z') { //current point의 원소가 소문자인 경우
		tmp->data = tmp->data - 32;
	}
}
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

typedef struct node { //doubly linked list의 node 구조체 정의
	char data;
	struct node* next;
	struct node* prev;
}NODE;

typedef struct deque { //deque의 정보를 담은 deque 구조체 정의 
	NODE* head; //head의 주소
	NODE* tail; //tail의 주소
	int size; //deque의 현재 크기
	int max; //deque의 최대 크기
}DQ;

void init(DQ*); //비어있는 deque를 생성하는 함수
void add_front(DQ*, char); //deque의 front(head)에 enqueue하는 함수
void add_rear(DQ*, char); //deque의 rear(tail)에 enqueue하는 함수
char delete_front(DQ*); //deque의 front(head)에서 dequeue하는 함수
char delete_rear(DQ*); //deque의 rear(tail)에서 dequeue하는 함수

int is_empty(DQ*); //deque가 비어있는지 확인하는 함수
int is_full(DQ*); //deque가 가득 찼는지 확인하는 함수

void print(DQ*); //delete_front한 data를 print한 뒤, 다시 add_rear하는 작업을 반복하며 deque의 모든 data를 출력하는 함수
char get_front(DQ*); //deque의 front(head)에 있는 data를 반환하는 함수
char get_rear(DQ*); //deque의 rear(tail)에 있는 data를 반환하는 함수

int data_count(DQ*); //deque에 들어있는 data의 개수를 반환하는 함수

NODE* head(DQ*); //deque의 head가 가리키는 주소를 반환하는 함수
NODE* tail(DQ*); //deque의 tail이 가리키는 주소를 반환하는 함수

int is_member(DQ*, char); //특정 data가 deque에 들어있는지 확인하고, 위치를 반환하는 함수

void replace_front(DQ*, char); //deque의 front(head)에 있는 값을 다른 data로 교체하는 함수
void replace_rear(DQ*, char); //deque의 rear(tail)에 있는 값을 다른 data로 교체하는 함수

void clear(DQ*); //deque의 모든 data를 delete하는 함수

void main() {
	printf("\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("\t      C O M M A N D   H E L P E R						\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  ) : Enqueue to front(head)							\n");
	printf("      ex) )a )b )c )d                                   \n");
	printf("  ( : Enqueue to rear(tail)                             \n");
	printf("      ex) (a (b (c (d                                   \n");
	printf("  - : Dequeue from front(head)							\n");
	printf("  _ : Dequeue from rear(tail)							\n");
	printf("  L : Print all elements							    \n");
	printf("  G : Peek data of head							        \n");
	printf("  g : Peek data of tail							        \n");
	printf("  F : Check deque is full or not				        \n");
	printf("  E : Check deque is empty or not				        \n");
	printf("  # : Print the number of elements						\n");
	printf("  H : Print address of head								\n");
	printf("  T : Print address of tail								\n");
	printf(" n- : (n: integer) Dequeue n times from front			\n");
	printf(" n_ : (n: integer) Dequeue n times from rear			\n");
	printf(" ?@ : Check data @ is member of deque or not			\n");
	printf(" +@ : Replace data of head to @							\n");
	printf(" =@ : Replace data of tail to @					        \n");
	printf("  C : Delete all elements of deque				        \n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  The length of command must be shorter than 30			\n");
	printf("  Make a space between commands							\n");
	printf("  Programmed by 2019310181 Dongseop Lee					\n");
	printf("─────────────────────────────────────────────────────────────\n");

	DQ my_deque; //create(my_deque)
	init(&my_deque); //비어있는 deque를 생성
	printf("  decide max size of deque: ");
	scanf("%d", &(my_deque.max)); //deque의 최대 크기 입력받기
	getchar(); //입력 버퍼 비우기

	char answer[30]; //command를 받을 배열(문자열)

	while (1) {
		printf("  >> ");
		gets(answer); //command 입력받음

		for (int i = 0; answer[i] != '\0'; i++) { //command가 남지 않을 때까지 반복함

			if (answer[i] == ')') { //add_front할 때
				add_front(&my_deque, answer[i + 1]);
				i++;
			}
			else if (answer[i] == '(') { //add_rear할 때
				add_rear(&my_deque, answer[i + 1]);
				i++;
			}
			else if (answer[i] == '-') { //delete_front할 때
				if (is_empty(&my_deque)) {
					printf("  [Error] Nothing to delete\n");
				}
				else {
					printf("  return %c\n", delete_front(&my_deque));
				}
			}
			else if (answer[i] == '_') { //delete_rear할 때
				if (is_empty(&my_deque)) {
					printf("  [Error] Nothing to delete\n");
				}
				else {
					printf("  return %c\n", delete_rear(&my_deque));
				}
			}
			else if (answer[i] == 'L') { //deque의 data들을 출력할 때
				continue;
			}
			else if (answer[i] == 'G') { //deque의 head가 가리키는 값을 보고싶을 때
				if (is_empty(&my_deque)) {
					printf("  [Error] Nothing to peek\n");
				}
				else
					printf("  {%c}\n", get_front(&my_deque));
			}
			else if (answer[i] == 'g') {
				if (is_empty(&my_deque)) { //deque의 tail이 가리키는 값을 보고싶을 때
					printf("  [Error] Nothing to peek\n");
				}
				else
					printf("  {%c}\n", get_rear(&my_deque));
			}
			else if (answer[i] == 'F') { //deque가 가득 차있는지 확인하고 싶을 때
				if (is_full(&my_deque)) {
					printf("  TRUE\n");
				}
				else {
					printf("  FALSE\n");
				}
			}
			else if (answer[i] == 'E') { //deque가 비어있는지 확인하고 싶을 때
				if (is_empty(&my_deque)) {
					printf("  TRUE\n");
				}
				else {
					printf("  FALSE\n");
				}
			}
			else if (answer[i] == '#') { //deque에 들어있는 data의 개수가 궁금할 때
				printf("  Number of data: %d\n", data_count(&my_deque));
			}
			else if (answer[i] == 'H') { //deque의 head가 가리키는 주소를 알고싶을 때
				if (my_deque.head == NULL) { //head가 가리키는 곳이 없으면
					printf("  [Error] Nothing on head\n");
				}
				else
					printf("  Adress of head: %p\n", head(&my_deque));
			}
			else if (answer[i] == 'T') { //deque의 tail이 가리키는 주소를 알고싶을 때
				if (my_deque.tail == NULL) { //tail이 가리키는 곳이 없으면
					printf("  [Error] Nothing on tail\n");
				}
				else {
					printf("  Adress of tail: %p\n", tail(&my_deque));
				}
			}
			else if ('0' <= answer[i] && answer[i] <= '9') { //입력받은 숫자만큼 반복해서 dequeue하고 싶을 때
				if (answer[i + 1] == '-') { //delete_front()
					for (int j = 0; j < answer[i] - '0'; j++) {
						if (is_empty(&my_deque)) {
							printf("  [Error] Nothing to dequeue\n");
						}
						else {
							printf("  return %c\n", delete_front(&my_deque));
						}
					}
					i++;
				}
				else if (answer[i + 1] == '_') { //delete_rear()
					for (int j = 0; j < answer[i] - '0'; j++) {
						if (is_empty(&my_deque)) {
							printf("  [Error] Nothing to dequeue\n");
						}
						else {
							printf("  return %c\n", delete_rear(&my_deque));
						}
					}
					i++;
				}
				else { //숫자 다음에 '-'나 '_'가 정상적으로 입력되지 않았을 때
					printf("  [Error] Check your command\n");
					continue;
				}
			}
			else if (answer[i] == '?') { //특정 data가 deque에 속해있는지 알고싶을 때
				int pos = is_member(&my_deque, answer[i + 1]); //is_member()함수로부터 위치 정보를 받아오기
				if (pos == -1) {
					printf("  -1 (Not in the deque)\n");
				}
				else {
					printf("  %d (Position of member)\n", pos);
				}
				i++;
			}
			else if (answer[i] == '+') { //front의 data를 특정 data로 교체하고 싶을 때
				if (is_empty(&my_deque)) {
					printf("  [Error] No element to replace\n");
				}
				else {
					replace_front(&my_deque, answer[i + 1]);
					i++;
				}
			}
			else if (answer[i] == '=') { //rear의 data를 특정 data로 교체하고 싶을 때
				if (is_empty(&my_deque)) {
					printf("  [Error] No element to replace\n");
				}
				else {
					replace_rear(&my_deque, answer[i + 1]);
					i++;
				}
			}
			else if (answer[i] == 'C') { //deque를 비우고 싶을 때
				clear(&my_deque);
			}
		}
		print(&my_deque); //입력받은 command가 모두 처리될때마다 print() 실행
	}
	return 0;
}

void init(DQ* md) {
	md->head = NULL;
	md->tail = NULL;
	md->size = 0;
}

void add_front(DQ* md, char data) {
	if (is_full(md)) {
		printf("  [Error] Deque is full\n");
		return;
	}

	NODE* new = (NODE*)malloc(sizeof(NODE));
	new->data = data;
	new->prev = NULL;
	new->next = NULL;

	if (is_empty(md)) { //처음 add하는 거라면
		md->tail = new;
		md->head = new;
	}
	else {
		new->next = md->head;
		md->head->prev = new;
		md->head = new;
	}
	md->size++;
}

void add_rear(DQ* md, char data) {
	if (is_full(md)) {
		printf("  [Error] Deque is full\n");
		return;
	}

	NODE* new = (NODE*)malloc(sizeof(NODE));
	new->data = data;
	new->prev = NULL;
	new->next = NULL;

	if (is_empty(md)) { //처음 add하는 거라면
		md->tail = new;
		md->head = new;
	}
	else {
		new->prev = md->tail;
		md->tail->next = new;
		md->tail = new;
	}
	md->size++;
}

char delete_front(DQ* md) {
	char dequeue_data = md->head->data; //뽑아낼 데이터를 따로 저장
	NODE* target = md->head;

	if (md->size == 1) { //마지막 data를 delete하는 거라면
		md->head = NULL;
		md->tail = NULL;
	}

	else {
		md->head->next->prev = md->head->prev;
		md->head = md->head->next;
	}

	free(target);
	md->size--;

	return dequeue_data;
}

char delete_rear(DQ* md) {
	char dequeue_data = md->tail->data; //뽑아낼 데이터를 따로 저장
	NODE* target = md->tail;

	if (md->size == 1) { //마지막 data를 delete하는 거라면
		md->head = NULL;
		md->tail = NULL;
	}

	else {
		md->tail->prev->next = md->tail->next;
		md->tail = md->tail->prev;
	}

	free(target);
	md->size--;

	return dequeue_data;
}

int is_empty(DQ* md) {
	if (md->size == 0) {
		return 1;
	}
	else
		return 0;
}

int is_full(DQ* md) {
	if (md->size == md->max) {
		return 1;
	}
	else
		return 0;
}

void print(DQ* md) {
	printf("  ");
	int sz = md->size;

	for (int i = 0; i < sz; i++) { //data의 수만큼 delete_front한 후 출력하고 다시 add_rear하는 과정을 반복
		char tmp = delete_front(md);
		printf("%c ", tmp);
		add_rear(md, tmp);
	}

	if (!is_empty(md)) { //만약 비어있는 deque가 아니라면 head와 tail의 data 출력
		printf("(head: %c & tail: %c)\n", md->head->data, md->tail->data);
	}
	else
		printf("empty deque\n");
}

char get_front(DQ* md) {
	return md->head->data;
}

char get_rear(DQ* md) {
	return md->tail->data;
}

int data_count(DQ* md) {
	return md->size;
}

NODE* head(DQ* md) {
	return md->head;
}

NODE* tail(DQ* md) {
	return md->tail;
}

int is_member(DQ* md, char data) {
	int count = 0; //현재 탐색 중인 위치를 기록할 변수
	int position = -1; //만약 찾는 data와 일치하는 data를 발견하면 현재 탐색 중인 위치를 대입할 변수

	int sz = md->size;

	for (int i = 0; i < sz; i++) { //data의 수만큼 delete_front한 후, 받은 data와 비교한 뒤, 다시 add_rear하는 과정을 반복
		char tmp = delete_front(md);
		count++;
		if (tmp == data) {
			position = count;
		}
		add_rear(md, tmp);
	}

	return position;
}

void replace_front(DQ* md, char data) {
	md->head->data = data;
}

void replace_rear(DQ* md, char data) {
	md->tail->data = data;
}

void clear(DQ* md) {
	int sz = md->size;
	for (int i = 0; i < sz; i++) { //data의 수만큼 delete_front (delete_rear도 가능)
		delete_front(md);
	}
	printf("  Clear Finished\n");
}
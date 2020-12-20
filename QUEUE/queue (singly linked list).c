#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

typedef struct node { //singly linked list의 node 구조체 정의
	char data;
	struct node* next;
}NODE;

typedef struct queue { //queue에 대한 정보를 담은 queue 구조체 정의 
	NODE* head; //head의 주소
	NODE* tail; //tail의 주소
	int size; //queue의 현재 크기
	int max; //queue의 최대 크기
}Q;

void init(Q*); //비어있는 queue를 생성하는 함수
void enqueue(Q*, char); //queue의 tail에 data를 enqueue하는 함수
char dequeue(Q*); //queue의 head에서 data를 dequeue하는 함수

int is_empty(Q*); //queue가 비어있는지 확인하는 함수
int is_full(Q*); //queue가 가득 차있는지 확인하는 함수 (linked list를 활용했기 때문에 tail == Max_Size의 방식으로 확인하는 것과 다르게 queue 구조체의 정보를 활용해 판단)

void print(Q*); //dequeue한 data를 print한 뒤, 다시 enqueue하는 작업을 반복하며 queue의 모든 data를 출력하는 함수
			   //+ head와 tail이 가리키는 data도 출력, 동적할당이므로 index를 나타내는 것보다 유용한 정보라고 판단
char peek(Q*); //queue의 head에 있는 data를 반환하는 함수

NODE* head(Q*); //queue의 head가 가리키는 주소를 반환하는 함수 (linked list를 활용했기 때문에 index가 아닌 주소를 반환)
NODE* tail(Q*); //queue의 tail 가리키는 주소를 반환하는 함수 (linked list를 활용했기 때문에 index가 아닌 주소를 반환)

int data_count(Q*); //queue에 들어있는 data의 개수를 반환하는 함수 (linked list를 활용했기 때문에 tail-head의 방식으로 계산하는 것이 아닌 queue 구조체의 size 데이터를 활용)
int is_member(Q*, char); //특정 data가 queue에 속해 있는지 확인하고, 몇번째 위치에 있는지 반환하는 함수
void replace(Q*, char); //tail의 data를 다른 data로 교체하는 함수
void clear(Q*); //queue의 모든 data를 dequeue하는 함수

void SizeChange(Q*, int); //queue의 최대 크기를 바꾸는 함수
void Twice(Q*); //queue의 data들을 하나씩 dequeue한 뒤, 두번씩 enqueue하면서 data를 두배로 불리는 함수
void MaxEnqueue(Q*, char); //queue가 full한 상태가 될 때까지 특정 data를 enqueue하는 함수

void main() {
	printf("\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("\t      C O M M A N D   H E L P E R						\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  + : Enqueue(s)		                                \n");
	printf("      ex) +a +b +c +d                                   \n");
	printf("  - : Dequeue											\n");
	printf("  L : Print all elements							    \n");
	printf("  P : Peek data of head							        \n");
	printf("  F : Check queue is full or not				        \n");
	printf("  E : Check queue is empty or not				        \n");
	printf("  # : Print the number of elements						\n");
	printf("  H : Print address of head								\n");
	printf("  T : Print address of tail								\n");
	printf(" n- : (n: integer) Dequeue n times						\n");
	printf(" ?@ : Check data @ is member of queue or not			\n");
	printf(" =@ : Replace data of tail to @					        \n");
	printf("  C : Delete all elements of queue				        \n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("\t      N  E  W   F U N C T I O N S						\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf(" $n : (n: integer) Change size of queue to n			\n");	
	printf("  D : Make queue be doubled					     	    \n");
	printf("	   ex) a b c -> a a b b c c						   	\n");
	printf(" X@ : Enqueue @ until queue is full		     		    \n");
	printf("	   ex) a b c (if max == 10)			   				\n");
	printf("	       >> Xh 		   								\n");
	printf("	       a b c h h h h h h h						   	\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  The length of command must be shorter than 30			\n");
	printf("  Make a space between commands							\n");
	printf("  Programmed by 2019310181 Dongseop Lee					\n");
	printf("─────────────────────────────────────────────────────────────\n");
	
	Q my_queue; //create(my_queue)
	init(&my_queue); //비어있는 queue를 생성

	printf("  decide max size of queue: ");
	scanf("%d", &(my_queue.max)); //queue의 최대 크기 입력받기
	getchar(); //입력 버퍼 비우기

	char answer[30]; //command를 받을 배열(문자열)
	
	while (1) {
		printf("  >> ");
		gets(answer); //command 입력받음

		for (int i = 0; answer[i] != '\0'; i++) { //command가 남지 않을 때까지 반복함

			if (answer[i] == '+') { //enqueue할 때
				enqueue(&my_queue, answer[i + 1]);
				i++;
			}
			else if (answer[i] == '-') { //dequeue할 때
				if (is_empty(&my_queue)) { //dequeue할 data가 없으면
					printf("  [Error] Nothing to dequeue\n");
				}
				else { //있으면 dequeue 실행
					printf("  return %c\n", dequeue(&my_queue));
				}
			}
			else if (answer[i] == 'L') { //queue를 출력할 때
				continue;
			}
			else if (answer[i] == 'P') { //queue의 head에 있는 data를 보고싶을 때
				if (is_empty(&my_queue)) { //peek할 data가 없으면
					printf("  [Error] Nothing to peek\n");
				}
				else //있으면 head가 가리키는 data 출력
					printf("  {%c}\n", peek(&my_queue));
			}
			else if (answer[i] == 'F') { //queue가 가득 차있는지 알고싶을 때
				if (is_full(&my_queue)) {
					printf("  TRUE\n");
				}
				else {
					printf("  FALSE\n");
				}
			}
			else if (answer[i] == 'E') { //queue가 비어있는지 알고싶을 때
				if (is_empty(&my_queue)) {
					printf("  TRUE\n");
				}
				else {
					printf("  FALSE\n");
				}
			}
			else if (answer[i] == '#') { //queue에 들어있는 data의 개수를 알고싶을 때
				printf("  Number of data: %d\n", data_count(&my_queue));
			}
			else if (answer[i] == 'H') { //queue의 head가 가리키는 주소를 알고싶을 때
				if (my_queue.head == NULL) { //head가 가리키는 곳이 없으면
					printf("  [Error] Nothing on head\n");
				}
				else
					printf("  Adress of head: %p\n", head(&my_queue));
			}
			else if (answer[i] == 'T') { //queue의 tail이 가리키는 주소를 알고싶을 때
				if (my_queue.tail == NULL) { //tail이 가리키는 곳이 없으면
					printf("  [Error] Nothing on tail\n");
				}
				else {
					printf("  Adress of tail: %p\n", tail(&my_queue));
				}
			}
			else if ('0' <= answer[i] && answer[i] <= '9') { //입력받은 숫자만큼 반복해서 dequeue하고 싶을 때
				if (answer[i + 1] == '-') {
					for (int j = 0; j < answer[i] - '0'; j++) { //입력받은 숫자만큼 반복해서 dequeue
						if (is_empty(&my_queue)) {
							printf("  [Error] Nothing to dequeue\n");
						}
						else {
							printf("  return %c\n", dequeue(&my_queue));
						}
					}
					i++;
				}
				else {
					printf("  [Error] Check your command\n"); //숫자 다음에 '-'가 정상적으로 입력되지 않았을 때
					continue;
				}
			}
			else if (answer[i] == '?') { //특정 data가 queue에 속해있는지 알고싶을 때
				int pos = is_member(&my_queue, answer[i + 1]); //is_member()함수로부터 위치 정보를 받아오기
				if (pos == -1) { 
					printf("  -1 (Not in the queue)\n");
				}
				else {
					printf("  %d (Position of member)\n", pos);
				}
				i++;
			}
			else if (answer[i] == '=') { //tail의 data를 특정 data로 교체하고 싶을 때
				if (is_empty(&my_queue)) { //tail에 data가 없을 때
					printf("  [Error] No element to replace\n");
				}
				else {
					replace(&my_queue, answer[i + 1]);
					i++;
				}
			}
			else if (answer[i] == 'C') { //queue의 모든 data들을 dequeue하고 싶을 때
				clear(&my_queue);
			}
			else if (answer[i] == '$') { //queue의 최대 크기를 바꾸고 싶을 때
				SizeChange(&my_queue, answer[i + 1] - '0');
				i++;
			}
			else if (answer[i] == 'D') { //queue의 모든 data들을 두배로 불리고 싶을 때
				Twice(&my_queue);
			}
			else if (answer[i] == 'X') { //queue가 full해질 때까지 특정 data를 enqueue하고 싶을 때
				MaxEnqueue(&my_queue, answer[i + 1]);
				i++;
			}
		}
		print(&my_queue); //입력받은 command가 모두 처리될때마다 print() 실행
	}
	return 0;
}

void init(Q* mq) { 
	mq->head = NULL;
	mq->tail = NULL;
	mq->size = 0;
}

void enqueue(Q* mq, char data) {
	if (is_full(mq)) { //만약 더이상 enqueue할 수 없으면
		printf("  [Error] Queue is full\n");
		return;
	}

	NODE* new = (NODE*)malloc(sizeof(NODE));
	new->data = data;
	new->next = NULL;

	if (is_empty(mq)) { //처음 enqueue하는 거면
		mq->tail = new;
		mq->head = new;
	}
	else {
		mq->tail->next = new;
		mq->tail = new;
	}

	mq->size++;
}

char dequeue(Q* mq) {
	char dequeue_data = mq->head->data; //뽑아낼 데이터를 따로 저장

	NODE* target = mq->head;
	mq->head = mq->head->next;

	free(target);

	mq->size--;

	if (mq->size == 0) { //마지막 data를 dequeue한 거면
		mq->tail = NULL;
	}

	return dequeue_data;
}

int is_empty(Q* mq) {
	if (mq->size == 0) {
		return 1;
	}
	else
		return 0;
}

int is_full(Q* mq) {
	if (mq->size == mq->max) {
		return 1;
	}
	else
		return 0;
}

void print(Q* mq) {
	printf("  ");
	int sz = mq->size;

	for (int i = 0; i < sz; i++) { //data의 수만큼 dequeue한 후 출력하고 다시 enqueue하는 과정을 반복
		char tmp = dequeue(mq);
		printf("%c ", tmp);
		enqueue(mq, tmp);
	}

	if (!is_empty(mq)) { //만약 비어있는 queue가 아니라면 head와 tail의 data 출력
		printf("(head: %c & tail: %c)\n", mq->head->data, mq->tail->data);
	}
	else
		printf("empty queue\n");
}

char peek(Q* mq) {
	return mq->head->data;
}

int data_count(Q* mq) {
	return mq->size;
}

NODE* head(Q* mq) {
	return mq->head; //head의 주소를 반환
}

NODE* tail(Q* mq) {
	return mq->tail; //tail의 주소를 반환
}

int is_member(Q* mq, char data) {
	int count = 0; //현재 탐색 중인 위치를 기록할 변수
	int position = -1; //만약 찾는 data와 일치하는 data를 발견하면 현재 탐색 중인 위치를 대입할 변수

	int sz = mq->size;

	for (int i = 0; i < sz; i++) { //data의 수만큼 dequeue한 후, 받은 data와 비교한 뒤, 다시 enqueue하는 과정을 반복
		char tmp = dequeue(mq);
		count++;
		if (tmp == data) {
			position = count;
		}
		enqueue(mq, tmp);
	}

	return position;
}

void replace(Q* mq, char data) {
	mq->tail->data = data;
}

void clear(Q* mq) {
	int sz = mq->size;
	for (int i = 0; i < sz; i++) { //data의 수만큼 dequeue
		dequeue(mq);
	}
	printf("  Clear Finished\n");
}

void SizeChange(Q* mq, int new_size) {
	if (mq->size > new_size) { //만약 현재 data의 수가 바꾸려고 하는 최대 크기보다 클 경우 (과도하게 최대 크기를 줄일 경우)
		printf("  [Error] Too many elements\n");
		return;
	}

	mq->max = new_size;
}

void Twice(Q* mq) {
	if (mq->max < (mq->size)*2) { //max size의 한계로 인해 data를 2배로 늘릴 수 없을 때
		printf("  [Error] Not enough memory\n");
		return;
	}

	int sz = mq->size;
	for (int i = 0; i < sz; i++) { //data를 하나씩 dequeue하며 다시 두번씩 enqueue해줌
		char tmp = dequeue(mq);
		enqueue(mq, tmp);
		enqueue(mq, tmp);
	}
}

void MaxEnqueue(Q* mq, char data) {
	if (is_full(mq)) { //이미 가득 차있으면
		printf("  [Error] Already full\n");
		return;
	}

	int count = mq->max - mq->size;
	for (int i = 0; i < count; i++) { //가득 찰 때까지
		enqueue(mq, data); //받은 data를 enqueue
	}
}
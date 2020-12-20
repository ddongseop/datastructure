#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#pragma warning (disable:4996)

typedef struct node { //singly linked list의 node 구조체 정의
	char data;
	struct node* next;
}NODE;

typedef struct stack { //list의 head(top)와 stack의 size 정보를 담은 stack 구조체 정의
	NODE* top;
	int size;
	int max; //stack의 최대 크기에 대한 정보도 저장
}STACK;

void init(STACK*); //비어 있는 stack을 생성하는 함수
void push(STACK*, char); //stack의 top에 데이터를 push하는 함수
char pop(STACK*); //stack의 top에서 데이터를 pop하는 함수
int element_count(STACK*); //stack의 element의 개수를 반환하는 함수
int is_empty(STACK*); //stack이 비어있는지 확인하는 함수
int is_full(STACK*); //stack이 가득 차있는지 확인하는 함수
char peek(STACK*); //stack의 top에 있는 데이터를 반환하는 함수
void print(STACK*); //stack의 원소들을 bottom부터 top 순서대로 출력하고, top의 위치를 출력하는 함수
int top(STACK*); //stack의 top의 위치를 반환하는 함수
int is_member(STACK*, char); //특정 데이터가 stack의 멤버인지 확인하는 함수
void replace(STACK*, char); //top의 데이터를 pop하고, 받은 데이터를 push하는 함수
void clear(STACK*); //stack이 빌 때까지 pop하는 함수 (stack의 모든 데이터를 삭제)

void twice(STACK*); //stack의 모든 element들을 두배로 불리는 함수 (use 2 stacks)
void reverse(STACK*); //stack의 element들을 invert하는 함수 (use 2 stacks)
void maxpush(STACK*, char); //stack이 가득 찰 때까지 받은 데이터를 push하는 함수

int main() {
	printf("\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("\t      C O M M A N D   H E L P E R						\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  + : Push element(s)                                   \n");
	printf("      ex) +a +b +c +d                                   \n");
	printf("  - : Pop element										\n");
	printf("  L : Print all elements							    \n");
	printf("  P : Peek data of top							        \n");
	printf("  F : Check stack is full or not				        \n");
	printf("  # : Print the number of elements						\n");
	printf("  T : Print location and data of top					\n");
	printf(" n- : (n: integer) Pop element n times					\n");
	printf(" ?@ : Check data @ is member of stack or not			\n");
	printf(" =@ : Replace data of top to @					        \n");
	printf("  C : Delete all elements of stack				        \n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("\t      N  E  W   F U N C T I O N S						\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  t : Make stack be doubled					     	    \n");
	printf("	   ex) a b c (top: c) -> a a b b c c (top: c)   	\n");
	printf("  R : Reverse elements of stack				     	    \n");
	printf("	   ex) a b c d (top: d) -> d c b a (top: a)		   	\n");
	printf(" X@ : Push @ until stack is full		     		    \n");
	printf("	   ex) a b c (top: c) (if max == 10)			   	\n");
	printf("	       >> Xh 		   								\n");
	printf("	       a b c h h h h h h h (top: h)				   	\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  The length of command must be shorter than 30			\n");
	printf("  Make a space between commands							\n");
	printf("  Programmed by 2019310181 Dongseop Lee					\n");
	printf("─────────────────────────────────────────────────────────────\n");

	STACK my_stack; // create(my_stack)
	init(&my_stack); // 비어 있는 stack 생성

	printf("  decide max size of stack: ");
	scanf("%d", &(my_stack.max)); //stack의 max size 입력받기
	getchar(); //입력 버퍼 비우기

	char answer[30]; //command를 받을 배열(문자열)

	while (1) {

		printf("  >> ");
		gets(answer); //command 입력받음

		for (int i = 0; answer[i] != '\0'; i++) { //command가 남지 않을 때까지 반복함
			if (answer[i] == '+'){ //push할 때
				if (is_full(&my_stack)) { //stack이 가득 차있으면
					printf("  [Error] Stack is full\n");
				}
				else //stack이 가득 차있지 않으면
					push(&my_stack, answer[i + 1]);
				i++;
			}
			else if (answer[i] == '-') { //pop할 때
				if (is_empty(&my_stack)) { //stack이 비어있으면
					printf("  [Error] nothing to pop\n");
				}
				else //stack이 비어있지 않으면
					printf("  return %c\n", pop(&my_stack));			
			}
			else if (answer[i] == 'L') { //stack을 출력할 때
				continue;
			}
			else if (answer[i] == 'P') { //stack의 top에 있는 data를 보고 싶을 때
				if (is_empty(&my_stack)) { //stack이 비어있으면
					printf("  [Error] nothing to peek\n");
				}
				else //stack이 비어있지 않으면
					printf("  %c\n", peek(&my_stack));
			}
			else if (answer[i] == 'F') { //stack이 가득 차있는지 확인하고 싶을 때
				if (is_full(&my_stack)) { //stack이 가득 차있으면
					printf("  TRUE\n");
				}
				else //stack이 가득 차있지 않으면
					printf("  FALSE\n");
			}
			else if (answer[i] == '#') { //stack의 원소의 개수를 알고 싶을 때
				printf("  element count: %d\n", element_count(&my_stack));
			}
			else if (answer[i] == 'T') { //stack의 top 위치와 data 값을 알고 싶을 때
				if (is_empty(&my_stack)) { //stack이 비어있을 때
					printf("  [Error] nothing on top\n");
				}
				else //stack이 비어있지 않을 때
					printf("  ( %d, %c )\n", top(&my_stack), peek(&my_stack));
			}
			else if (isdigit(answer[i])) { //반복해서 pop을 하고 싶을 때
				for (int j = 0; j < (answer[i] - '0'); j++) { //입력받은 숫자만큼 반복
					if (is_empty(&my_stack)) { //stack이 비어있을 때
						printf("  [Error] nothing to pop\n");
					}
					else //stack이 비어있지 않을 때
						printf("  return %c\n", pop(&my_stack));
				}
				i++;
			}
			else if (answer[i] == '?') { //특정 data가 stack의 원소인지 확인하고 싶을 때
				if (is_member(&my_stack, answer[i + 1])) { //member가 맞으면
					printf("  TRUE\n");
				}
				else //member가 아니면
					printf("  FALSE\n");
				i++;
			}
			else if (answer[i] == '=') { //top의 data를 특정 data로 교체하고 싶을 때
				if (is_empty(&my_stack)) { //stack이 비어있으면
					printf("  [Error] no element to replace\n");
				}
				else { //stack이 비어있지 않으면
					replace(&my_stack, answer[i + 1]);
				}
				i++;
			}
			else if (answer[i] == 'C') { //stack을 비우고 싶을 때
				clear(&my_stack);
			}
			else if (answer[i] == 't') { //stack의 원소들을 각각 두배로 늘리고 싶을 때
				twice(&my_stack);
			}
			else if (answer[i] == 'R') { //stack을 invert하고 싶을 때
				reverse(&my_stack);
			}
			else if (answer[i] == 'X') { //stack이 가득 찰 때까지 특정 데이터를 push하고 싶을 때
				maxpush(&my_stack, answer[i + 1]);
				i++;
			}
		}
		print(&my_stack); //command를 처리할 때마다 결과를 출력
	}
	return 0;
}

void init(STACK* mst) {
	mst->top = NULL;
	mst->size = 0;
}

void push(STACK* mst, char data) {
	
	NODE* new = (NODE*)malloc(sizeof(NODE));
	
	new->next = mst->top;
	new->data = data;
	mst->top = new;

	mst->size++;
}

char pop(STACK* mst) {

	char pop_data = mst->top->data; //뽑아낼 데이터를 따로 저장

	NODE* target = mst->top;
	mst->top = mst->top->next;

	free(target);

	mst->size--;

	return pop_data;
}

int element_count(STACK* mst) {
	int count = 0;
	NODE* tmp = mst->top;
	while (tmp) {
		tmp = tmp->next;
		count++;
	}

	return count;
}

int is_empty(STACK* mst) {
	if (mst->top == NULL) {
		return 1;
	}
	else
		return 0;
}

int is_full(STACK* mst) {
	if (mst->size >= mst->max) {
		return 1;
	}
	else
		return 0;
}

char peek(STACK* mst) {
	return mst->top->data;
}

void print(STACK* mst) {
	STACK tmp; //임시 stack을 생성
	init(&tmp);
	tmp.max = mst->max;

	printf("  ");

	while (!is_empty(mst)) { //my stack에서 pop해서 임시 stack에 push
		push(&tmp, pop(mst));
	}

	while (!is_empty(&tmp)) { //다시 임시 stack에서 pop해서 my stack에 push 하면서 하나씩 출력
		push(mst, pop(&tmp));
		printf("%c ", peek(mst));
	}

	if (!is_empty(mst)) { //stack이 비어있지 않으면 top의 data를 출력
		printf("(top: %c)\n", mst->top->data);
	}
	else 
		printf("empty stack\n");
}

int top(STACK* mst){
	return mst->size;
}

int is_member(STACK* mst, char element) {
	STACK tmp; //임시 stack을 생성
	init(&tmp);
	tmp.max = mst->max;
	int TF = 0;

	while (!is_empty(mst)) { //my stack에서 pop해서 임시 stack에 push
		push(&tmp, pop(mst));
	}

	while (!is_empty(&tmp)) { //다시 임시 stack에서 pop해서 my stack으로 push하면서 특정 데이터가 있는지 확인
		push(mst, pop(&tmp));
		if (peek(mst) == element) {
			TF = 1;
		}
	}

	return TF;
}

void replace(STACK* mst, char new_element) { //pop and push
	pop(mst);
	push(mst, new_element);
}

void clear(STACK* mst) {
	int tmp = element_count(mst); //원소의 개수만큼
	for (int i = 0; i < tmp; i++) {
		pop(mst); //pop하기
	}
	printf("  clear finished\n");
}

void twice(STACK* mst) {
	if (mst->max < (mst->size) * 2) { //max size의 한계로 인해 2배로 늘릴 수 없을 때
		printf("  [Error] not enough memory\n");
		return;
	}

	STACK tmp; //임시 stack을 생성
	init(&tmp);
	tmp.max = mst->max;

	char twice;

	while (!is_empty(mst)) { //my stack에서 pop해서 임시 stack에 push
		push(&tmp, pop(mst));
	}

	while (!is_empty(&tmp)) { //다시 임시 stack에서 pop해서 my stack에 "두번씩" push
		twice = pop(&tmp);
		push(mst, twice);
		push(mst, twice);
	}
}

void reverse(STACK* mst) {
	if (is_empty(mst)) { //stack이 비어있을 때
		printf("  [Error] nothing to reverse\n");
		return;
	}

	STACK tmp; //임시 stack을 생성
	init(&tmp);
	tmp.max = mst->max;

	while (!is_empty(mst)) { //my stack에서 pop해서 임시 stack에 push
		push(&tmp, pop(mst));
	}

	mst->top = tmp.top; //임시 stack을 my stack으로 변경
}

void maxpush(STACK* mst, char element) {
	if (is_full(mst)) { //이미 가득 차있으면
		printf("  [Error] already full\n");
		return;
	}

	int count = mst->max - mst->size;

	for (int i = 0; i < count; i++) { //가득 찰 때까지
		push(mst, element); //받은 data를 push
	}
}
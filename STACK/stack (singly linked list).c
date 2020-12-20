#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#pragma warning (disable:4996)

typedef struct node { //singly linked list�� node ����ü ����
	char data;
	struct node* next;
}NODE;

typedef struct stack { //list�� head(top)�� stack�� size ������ ���� stack ����ü ����
	NODE* top;
	int size;
	int max; //stack�� �ִ� ũ�⿡ ���� ������ ����
}STACK;

void init(STACK*); //��� �ִ� stack�� �����ϴ� �Լ�
void push(STACK*, char); //stack�� top�� �����͸� push�ϴ� �Լ�
char pop(STACK*); //stack�� top���� �����͸� pop�ϴ� �Լ�
int element_count(STACK*); //stack�� element�� ������ ��ȯ�ϴ� �Լ�
int is_empty(STACK*); //stack�� ����ִ��� Ȯ���ϴ� �Լ�
int is_full(STACK*); //stack�� ���� ���ִ��� Ȯ���ϴ� �Լ�
char peek(STACK*); //stack�� top�� �ִ� �����͸� ��ȯ�ϴ� �Լ�
void print(STACK*); //stack�� ���ҵ��� bottom���� top ������� ����ϰ�, top�� ��ġ�� ����ϴ� �Լ�
int top(STACK*); //stack�� top�� ��ġ�� ��ȯ�ϴ� �Լ�
int is_member(STACK*, char); //Ư�� �����Ͱ� stack�� ������� Ȯ���ϴ� �Լ�
void replace(STACK*, char); //top�� �����͸� pop�ϰ�, ���� �����͸� push�ϴ� �Լ�
void clear(STACK*); //stack�� �� ������ pop�ϴ� �Լ� (stack�� ��� �����͸� ����)

void twice(STACK*); //stack�� ��� element���� �ι�� �Ҹ��� �Լ� (use 2 stacks)
void reverse(STACK*); //stack�� element���� invert�ϴ� �Լ� (use 2 stacks)
void maxpush(STACK*, char); //stack�� ���� �� ������ ���� �����͸� push�ϴ� �Լ�

int main() {
	printf("\n");
	printf("��������������������������������������������������������������������������������������������������������������������������\n");
	printf("\t      C O M M A N D   H E L P E R						\n");
	printf("��������������������������������������������������������������������������������������������������������������������������\n");
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
	printf("��������������������������������������������������������������������������������������������������������������������������\n");
	printf("\t      N  E  W   F U N C T I O N S						\n");
	printf("��������������������������������������������������������������������������������������������������������������������������\n");
	printf("  t : Make stack be doubled					     	    \n");
	printf("	   ex) a b c (top: c) -> a a b b c c (top: c)   	\n");
	printf("  R : Reverse elements of stack				     	    \n");
	printf("	   ex) a b c d (top: d) -> d c b a (top: a)		   	\n");
	printf(" X@ : Push @ until stack is full		     		    \n");
	printf("	   ex) a b c (top: c) (if max == 10)			   	\n");
	printf("	       >> Xh 		   								\n");
	printf("	       a b c h h h h h h h (top: h)				   	\n");
	printf("��������������������������������������������������������������������������������������������������������������������������\n");
	printf("  The length of command must be shorter than 30			\n");
	printf("  Make a space between commands							\n");
	printf("  Programmed by 2019310181 Dongseop Lee					\n");
	printf("��������������������������������������������������������������������������������������������������������������������������\n");

	STACK my_stack; // create(my_stack)
	init(&my_stack); // ��� �ִ� stack ����

	printf("  decide max size of stack: ");
	scanf("%d", &(my_stack.max)); //stack�� max size �Է¹ޱ�
	getchar(); //�Է� ���� ����

	char answer[30]; //command�� ���� �迭(���ڿ�)

	while (1) {

		printf("  >> ");
		gets(answer); //command �Է¹���

		for (int i = 0; answer[i] != '\0'; i++) { //command�� ���� ���� ������ �ݺ���
			if (answer[i] == '+'){ //push�� ��
				if (is_full(&my_stack)) { //stack�� ���� ��������
					printf("  [Error] Stack is full\n");
				}
				else //stack�� ���� ������ ������
					push(&my_stack, answer[i + 1]);
				i++;
			}
			else if (answer[i] == '-') { //pop�� ��
				if (is_empty(&my_stack)) { //stack�� ���������
					printf("  [Error] nothing to pop\n");
				}
				else //stack�� ������� ������
					printf("  return %c\n", pop(&my_stack));			
			}
			else if (answer[i] == 'L') { //stack�� ����� ��
				continue;
			}
			else if (answer[i] == 'P') { //stack�� top�� �ִ� data�� ���� ���� ��
				if (is_empty(&my_stack)) { //stack�� ���������
					printf("  [Error] nothing to peek\n");
				}
				else //stack�� ������� ������
					printf("  %c\n", peek(&my_stack));
			}
			else if (answer[i] == 'F') { //stack�� ���� ���ִ��� Ȯ���ϰ� ���� ��
				if (is_full(&my_stack)) { //stack�� ���� ��������
					printf("  TRUE\n");
				}
				else //stack�� ���� ������ ������
					printf("  FALSE\n");
			}
			else if (answer[i] == '#') { //stack�� ������ ������ �˰� ���� ��
				printf("  element count: %d\n", element_count(&my_stack));
			}
			else if (answer[i] == 'T') { //stack�� top ��ġ�� data ���� �˰� ���� ��
				if (is_empty(&my_stack)) { //stack�� ������� ��
					printf("  [Error] nothing on top\n");
				}
				else //stack�� ������� ���� ��
					printf("  ( %d, %c )\n", top(&my_stack), peek(&my_stack));
			}
			else if (isdigit(answer[i])) { //�ݺ��ؼ� pop�� �ϰ� ���� ��
				for (int j = 0; j < (answer[i] - '0'); j++) { //�Է¹��� ���ڸ�ŭ �ݺ�
					if (is_empty(&my_stack)) { //stack�� ������� ��
						printf("  [Error] nothing to pop\n");
					}
					else //stack�� ������� ���� ��
						printf("  return %c\n", pop(&my_stack));
				}
				i++;
			}
			else if (answer[i] == '?') { //Ư�� data�� stack�� �������� Ȯ���ϰ� ���� ��
				if (is_member(&my_stack, answer[i + 1])) { //member�� ������
					printf("  TRUE\n");
				}
				else //member�� �ƴϸ�
					printf("  FALSE\n");
				i++;
			}
			else if (answer[i] == '=') { //top�� data�� Ư�� data�� ��ü�ϰ� ���� ��
				if (is_empty(&my_stack)) { //stack�� ���������
					printf("  [Error] no element to replace\n");
				}
				else { //stack�� ������� ������
					replace(&my_stack, answer[i + 1]);
				}
				i++;
			}
			else if (answer[i] == 'C') { //stack�� ���� ���� ��
				clear(&my_stack);
			}
			else if (answer[i] == 't') { //stack�� ���ҵ��� ���� �ι�� �ø��� ���� ��
				twice(&my_stack);
			}
			else if (answer[i] == 'R') { //stack�� invert�ϰ� ���� ��
				reverse(&my_stack);
			}
			else if (answer[i] == 'X') { //stack�� ���� �� ������ Ư�� �����͸� push�ϰ� ���� ��
				maxpush(&my_stack, answer[i + 1]);
				i++;
			}
		}
		print(&my_stack); //command�� ó���� ������ ����� ���
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

	char pop_data = mst->top->data; //�̾Ƴ� �����͸� ���� ����

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
	STACK tmp; //�ӽ� stack�� ����
	init(&tmp);
	tmp.max = mst->max;

	printf("  ");

	while (!is_empty(mst)) { //my stack���� pop�ؼ� �ӽ� stack�� push
		push(&tmp, pop(mst));
	}

	while (!is_empty(&tmp)) { //�ٽ� �ӽ� stack���� pop�ؼ� my stack�� push �ϸ鼭 �ϳ��� ���
		push(mst, pop(&tmp));
		printf("%c ", peek(mst));
	}

	if (!is_empty(mst)) { //stack�� ������� ������ top�� data�� ���
		printf("(top: %c)\n", mst->top->data);
	}
	else 
		printf("empty stack\n");
}

int top(STACK* mst){
	return mst->size;
}

int is_member(STACK* mst, char element) {
	STACK tmp; //�ӽ� stack�� ����
	init(&tmp);
	tmp.max = mst->max;
	int TF = 0;

	while (!is_empty(mst)) { //my stack���� pop�ؼ� �ӽ� stack�� push
		push(&tmp, pop(mst));
	}

	while (!is_empty(&tmp)) { //�ٽ� �ӽ� stack���� pop�ؼ� my stack���� push�ϸ鼭 Ư�� �����Ͱ� �ִ��� Ȯ��
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
	int tmp = element_count(mst); //������ ������ŭ
	for (int i = 0; i < tmp; i++) {
		pop(mst); //pop�ϱ�
	}
	printf("  clear finished\n");
}

void twice(STACK* mst) {
	if (mst->max < (mst->size) * 2) { //max size�� �Ѱ�� ���� 2��� �ø� �� ���� ��
		printf("  [Error] not enough memory\n");
		return;
	}

	STACK tmp; //�ӽ� stack�� ����
	init(&tmp);
	tmp.max = mst->max;

	char twice;

	while (!is_empty(mst)) { //my stack���� pop�ؼ� �ӽ� stack�� push
		push(&tmp, pop(mst));
	}

	while (!is_empty(&tmp)) { //�ٽ� �ӽ� stack���� pop�ؼ� my stack�� "�ι���" push
		twice = pop(&tmp);
		push(mst, twice);
		push(mst, twice);
	}
}

void reverse(STACK* mst) {
	if (is_empty(mst)) { //stack�� ������� ��
		printf("  [Error] nothing to reverse\n");
		return;
	}

	STACK tmp; //�ӽ� stack�� ����
	init(&tmp);
	tmp.max = mst->max;

	while (!is_empty(mst)) { //my stack���� pop�ؼ� �ӽ� stack�� push
		push(&tmp, pop(mst));
	}

	mst->top = tmp.top; //�ӽ� stack�� my stack���� ����
}

void maxpush(STACK* mst, char element) {
	if (is_full(mst)) { //�̹� ���� ��������
		printf("  [Error] already full\n");
		return;
	}

	int count = mst->max - mst->size;

	for (int i = 0; i < count; i++) { //���� �� ������
		push(mst, element); //���� data�� push
	}
}
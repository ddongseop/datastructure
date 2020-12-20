#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

typedef struct node { //doubly linked list�� node ����ü ����
	char data;
	struct node* next;
	struct node* prev;
}NODE;

typedef struct deque { //deque�� ������ ���� deque ����ü ���� 
	NODE* head; //head�� �ּ�
	NODE* tail; //tail�� �ּ�
	int size; //deque�� ���� ũ��
	int max; //deque�� �ִ� ũ��
}DQ;

void init(DQ*); //����ִ� deque�� �����ϴ� �Լ�
void add_front(DQ*, char); //deque�� front(head)�� enqueue�ϴ� �Լ�
void add_rear(DQ*, char); //deque�� rear(tail)�� enqueue�ϴ� �Լ�
char delete_front(DQ*); //deque�� front(head)���� dequeue�ϴ� �Լ�
char delete_rear(DQ*); //deque�� rear(tail)���� dequeue�ϴ� �Լ�

int is_empty(DQ*); //deque�� ����ִ��� Ȯ���ϴ� �Լ�
int is_full(DQ*); //deque�� ���� á���� Ȯ���ϴ� �Լ�

void print(DQ*); //delete_front�� data�� print�� ��, �ٽ� add_rear�ϴ� �۾��� �ݺ��ϸ� deque�� ��� data�� ����ϴ� �Լ�
char get_front(DQ*); //deque�� front(head)�� �ִ� data�� ��ȯ�ϴ� �Լ�
char get_rear(DQ*); //deque�� rear(tail)�� �ִ� data�� ��ȯ�ϴ� �Լ�

int data_count(DQ*); //deque�� ����ִ� data�� ������ ��ȯ�ϴ� �Լ�

NODE* head(DQ*); //deque�� head�� ����Ű�� �ּҸ� ��ȯ�ϴ� �Լ�
NODE* tail(DQ*); //deque�� tail�� ����Ű�� �ּҸ� ��ȯ�ϴ� �Լ�

int is_member(DQ*, char); //Ư�� data�� deque�� ����ִ��� Ȯ���ϰ�, ��ġ�� ��ȯ�ϴ� �Լ�

void replace_front(DQ*, char); //deque�� front(head)�� �ִ� ���� �ٸ� data�� ��ü�ϴ� �Լ�
void replace_rear(DQ*, char); //deque�� rear(tail)�� �ִ� ���� �ٸ� data�� ��ü�ϴ� �Լ�

void clear(DQ*); //deque�� ��� data�� delete�ϴ� �Լ�

void main() {
	printf("\n");
	printf("��������������������������������������������������������������������������������������������������������������������������\n");
	printf("\t      C O M M A N D   H E L P E R						\n");
	printf("��������������������������������������������������������������������������������������������������������������������������\n");
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
	printf("��������������������������������������������������������������������������������������������������������������������������\n");
	printf("  The length of command must be shorter than 30			\n");
	printf("  Make a space between commands							\n");
	printf("  Programmed by 2019310181 Dongseop Lee					\n");
	printf("��������������������������������������������������������������������������������������������������������������������������\n");

	DQ my_deque; //create(my_deque)
	init(&my_deque); //����ִ� deque�� ����
	printf("  decide max size of deque: ");
	scanf("%d", &(my_deque.max)); //deque�� �ִ� ũ�� �Է¹ޱ�
	getchar(); //�Է� ���� ����

	char answer[30]; //command�� ���� �迭(���ڿ�)

	while (1) {
		printf("  >> ");
		gets(answer); //command �Է¹���

		for (int i = 0; answer[i] != '\0'; i++) { //command�� ���� ���� ������ �ݺ���

			if (answer[i] == ')') { //add_front�� ��
				add_front(&my_deque, answer[i + 1]);
				i++;
			}
			else if (answer[i] == '(') { //add_rear�� ��
				add_rear(&my_deque, answer[i + 1]);
				i++;
			}
			else if (answer[i] == '-') { //delete_front�� ��
				if (is_empty(&my_deque)) {
					printf("  [Error] Nothing to delete\n");
				}
				else {
					printf("  return %c\n", delete_front(&my_deque));
				}
			}
			else if (answer[i] == '_') { //delete_rear�� ��
				if (is_empty(&my_deque)) {
					printf("  [Error] Nothing to delete\n");
				}
				else {
					printf("  return %c\n", delete_rear(&my_deque));
				}
			}
			else if (answer[i] == 'L') { //deque�� data���� ����� ��
				continue;
			}
			else if (answer[i] == 'G') { //deque�� head�� ����Ű�� ���� ������� ��
				if (is_empty(&my_deque)) {
					printf("  [Error] Nothing to peek\n");
				}
				else
					printf("  {%c}\n", get_front(&my_deque));
			}
			else if (answer[i] == 'g') {
				if (is_empty(&my_deque)) { //deque�� tail�� ����Ű�� ���� ������� ��
					printf("  [Error] Nothing to peek\n");
				}
				else
					printf("  {%c}\n", get_rear(&my_deque));
			}
			else if (answer[i] == 'F') { //deque�� ���� ���ִ��� Ȯ���ϰ� ���� ��
				if (is_full(&my_deque)) {
					printf("  TRUE\n");
				}
				else {
					printf("  FALSE\n");
				}
			}
			else if (answer[i] == 'E') { //deque�� ����ִ��� Ȯ���ϰ� ���� ��
				if (is_empty(&my_deque)) {
					printf("  TRUE\n");
				}
				else {
					printf("  FALSE\n");
				}
			}
			else if (answer[i] == '#') { //deque�� ����ִ� data�� ������ �ñ��� ��
				printf("  Number of data: %d\n", data_count(&my_deque));
			}
			else if (answer[i] == 'H') { //deque�� head�� ����Ű�� �ּҸ� �˰���� ��
				if (my_deque.head == NULL) { //head�� ����Ű�� ���� ������
					printf("  [Error] Nothing on head\n");
				}
				else
					printf("  Adress of head: %p\n", head(&my_deque));
			}
			else if (answer[i] == 'T') { //deque�� tail�� ����Ű�� �ּҸ� �˰���� ��
				if (my_deque.tail == NULL) { //tail�� ����Ű�� ���� ������
					printf("  [Error] Nothing on tail\n");
				}
				else {
					printf("  Adress of tail: %p\n", tail(&my_deque));
				}
			}
			else if ('0' <= answer[i] && answer[i] <= '9') { //�Է¹��� ���ڸ�ŭ �ݺ��ؼ� dequeue�ϰ� ���� ��
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
				else { //���� ������ '-'�� '_'�� ���������� �Էµ��� �ʾ��� ��
					printf("  [Error] Check your command\n");
					continue;
				}
			}
			else if (answer[i] == '?') { //Ư�� data�� deque�� �����ִ��� �˰���� ��
				int pos = is_member(&my_deque, answer[i + 1]); //is_member()�Լ��κ��� ��ġ ������ �޾ƿ���
				if (pos == -1) {
					printf("  -1 (Not in the deque)\n");
				}
				else {
					printf("  %d (Position of member)\n", pos);
				}
				i++;
			}
			else if (answer[i] == '+') { //front�� data�� Ư�� data�� ��ü�ϰ� ���� ��
				if (is_empty(&my_deque)) {
					printf("  [Error] No element to replace\n");
				}
				else {
					replace_front(&my_deque, answer[i + 1]);
					i++;
				}
			}
			else if (answer[i] == '=') { //rear�� data�� Ư�� data�� ��ü�ϰ� ���� ��
				if (is_empty(&my_deque)) {
					printf("  [Error] No element to replace\n");
				}
				else {
					replace_rear(&my_deque, answer[i + 1]);
					i++;
				}
			}
			else if (answer[i] == 'C') { //deque�� ���� ���� ��
				clear(&my_deque);
			}
		}
		print(&my_deque); //�Է¹��� command�� ��� ó���ɶ����� print() ����
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

	if (is_empty(md)) { //ó�� add�ϴ� �Ŷ��
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

	if (is_empty(md)) { //ó�� add�ϴ� �Ŷ��
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
	char dequeue_data = md->head->data; //�̾Ƴ� �����͸� ���� ����
	NODE* target = md->head;

	if (md->size == 1) { //������ data�� delete�ϴ� �Ŷ��
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
	char dequeue_data = md->tail->data; //�̾Ƴ� �����͸� ���� ����
	NODE* target = md->tail;

	if (md->size == 1) { //������ data�� delete�ϴ� �Ŷ��
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

	for (int i = 0; i < sz; i++) { //data�� ����ŭ delete_front�� �� ����ϰ� �ٽ� add_rear�ϴ� ������ �ݺ�
		char tmp = delete_front(md);
		printf("%c ", tmp);
		add_rear(md, tmp);
	}

	if (!is_empty(md)) { //���� ����ִ� deque�� �ƴ϶�� head�� tail�� data ���
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
	int count = 0; //���� Ž�� ���� ��ġ�� ����� ����
	int position = -1; //���� ã�� data�� ��ġ�ϴ� data�� �߰��ϸ� ���� Ž�� ���� ��ġ�� ������ ����

	int sz = md->size;

	for (int i = 0; i < sz; i++) { //data�� ����ŭ delete_front�� ��, ���� data�� ���� ��, �ٽ� add_rear�ϴ� ������ �ݺ�
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
	for (int i = 0; i < sz; i++) { //data�� ����ŭ delete_front (delete_rear�� ����)
		delete_front(md);
	}
	printf("  Clear Finished\n");
}
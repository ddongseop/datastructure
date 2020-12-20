#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#pragma warning (disable:4996)

int current = -1; //current point�� ��Ÿ���� ���� ����
int size = 0; //linked list�� �ִ� ���� ���� ��Ÿ���� ���� ����

typedef struct node { //singly linked list�� node ����ü ����
	char data;
	struct node* next;
}NODE;

NODE* init(char); //node�� �����ϰ� ���� �����͸� node�� �����ϴ� �Լ�
NODE* addTail(NODE*, char); //linked list�� ���� �޺κп� node�� �߰��ϴ� �Լ�
void print(NODE*); //linked list�� ��� node�� data���� ����ϴ� �Լ�
char get_data(NODE*); //current point�� data ���� return�ϴ� �Լ�
void traverse_first(); //current point�� ���� ������ �ű�� �Լ�
void traverse_last(); //current point�� ���� �ڷ� �ű�� �Լ�
void traverse_next(); //current point�� ��ĭ �ڷ� �ű�� �Լ�
void traverse_prev(); //current point�� ��ĭ ������ �ű�� �Լ�
NODE* delete(NODE*); //current point�� node�� �����ϴ� �Լ�
NODE* addFirst(NODE*, char); //linked list�� ���� �պκп� node�� �߰��ϴ� �Լ�
void add(NODE*, char); //current point�� node�� �߰��ϴ� �Լ�
void replace(NODE*, char); //current point�� data�� �ٸ� data�� replace�ϴ� �Լ�
int data_count(NODE*); //linked list�� data ������ ���� �Լ�
int is_member(NODE*, char); //�Է¹��� data�� linked list�� �ִ��� Ȯ���ϴ� �Լ�
NODE* clear(NODE*); //linked list�� ��� ���Ҹ� �����ϴ� �Լ�
int is_empty(NODE*); //linked list�� ��� �ִ��� Ȯ���ϴ� �Լ�
NODE* reverse(NODE*); //linked list�� ���ҵ��� �������� ���ġ�ϴ� �Լ�
NODE* split(NODE*); //current point�� ���Ҹ� �����ϴ� �Լ� (ex) a b c (current point: b) -> a b b c
void capital(NODE*); //current point�� ���Ұ� �빮�ڸ� �ҹ��ڷ�, �ҹ��ڸ� �빮�ڷ� �ٲٴ� �Լ�

int main() {
	NODE* head = NULL; // create(my_list)
	char answer[30]; //command�� ���� �迭(���ڿ�)
	int i;

	printf("\n");
	printf("��������������������������������������������������������������������������������������������������������������������������\n");
	printf("\t      C O M M A N D   H E L P E R \n");
	printf("��������������������������������������������������������������������������������������������������������������������������\n");
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
	printf("��������������������������������������������������������������������������������������������������������������������������\n");
	printf("  This program can handle only 30 commands				\n");
	printf("  Make a space between commands							\n");
	printf("  Programmed by 2019310181 Dongseop Lee					\n");
	printf("��������������������������������������������������������������������������������������������������������������������������\n");

	while (1) {

		printf("  >> ");
		gets(answer); //command �Է¹���

		for (int i = 0; answer[i] != '\0'; i++) { //command�� ���� ���� ������ �ݺ���

			if (answer[i] == '+') { //���Ҹ� �߰��� ��
				if (current + 1 == size) { //���� ���� ���Ҹ� �߰��� ��
					head = addTail(head, answer[i + 1]);
					i++;
				}
				else { //�߰��� ���Ҹ� �߰��� ��
					add(head, answer[i + 1]);
					i++;
				}
			}
			else if (answer[i] == 'L') { //���ҵ��� ��� ����ؾ� �� ��
				continue;
			}
			else if (answer[i] == 'G') { //current point�� ���Ҹ� ����ϰ� ���� ��
				if (size) {
					printf("  %c\n", get_data(head));
				}
				else //���Ұ� �ϳ��� ���� ��
					printf("empty array\n");
				
			}
			else if (answer[i] == '<') { //current point�� ���� ������ �ű�� ���� ��
				traverse_first();
				if (answer[i + 2] == '+') { //���� �տ� ���Ҹ� �߰��� ��
					head = addFirst(head, answer[i + 3]);
					i = i + 3;
				}
			}
			else if (answer[i] == '>') { //current point�� ���� �ڷ� �ű�� ���� ��
				traverse_last();
			}
			else if (answer[i] == 'N') { //current point�� ��ĭ �ڷ� �ű�� ���� ��
				traverse_next();
			}
			else if (answer[i] == 'P') { //current point�� ��ĭ ������ �ű�� ���� ��
				traverse_prev();
			}
			else if (answer[i] == '-') { //current point�� ���Ҹ� �����ϰ� ���� ��
				head = delete(head);
			}
			else if (answer[i] == '=') { //current point�� ���Ҹ� �ٸ� ���ҷ� replace �ϰ� ���� ��
				replace(head, answer[i + 1]);
				i++;
			}
			else if (isdigit(answer[i])) { //�Է¹��� ���ڹ�°�� current point�� �����ϰ� ���� ��
				current = answer[i] - '0' - 1;
			}
			else if (answer[i] == '#') { //������ ������ ����ϰ� ���� ��
				printf("  %d\n", data_count(head));
			}
			else if (answer[i] == '?') { //�ش� ���Ұ� linked list �ȿ� �ִ��� Ȯ���ϰ� ���� ��
				int mem = is_member(head, answer[i + 1]);
				if (mem == -1) { //�ش� ���Ҹ� ã�� ������ ��
					printf("  %c is not member\n", answer[i + 1]);
				}
				else { //�ش� ���Ҹ� ã���� ��
					printf("  %c is our member %d\n", answer[i + 1], mem + 1);
				}
				i++;
			}
			else if (answer[i] == 'C') { //linked list�� ��� ���ҵ��� �����ϰ� ���� ��
				head = clear(head);
				current = -1;
			}
			else if (answer[i] == 'E') { //linked list�� ��� �ִ��� Ȯ���ϰ� ���� ��
				if (is_empty(head)) {
					printf("  TRUE\n");
				}
				else
					printf("  FALSE\n");
			}
			else if (answer[i] == 'R') { //linked list ���ҵ��� ������ �Ųٷ� ������ ���� ��
				head = reverse(head);
			}
			else if (answer[i] == 'S') { //current point�� ���Ҹ� �����ϰ� ���� ��
				head = split(head);
			}
			else if (answer[i] == 'A') { //current point�� ���Ұ� �빮�ڸ� �ҹ��ڷ�, �ҹ��ڸ� �빮�ڷ� �ٲٰ� ���� ��
				capital(head);
			}
			else if (answer[i] == ' ') { //������ �ԷµǾ��� ��
				continue;
			}
		}
		print(head); //��ɾ ó���� ������ linked list�� ���
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
	if (size == 0) { //ù ���Ҹ� �߰��� ��
		head = init(data);
	}
	else { //linked list�� ���� �޺κп� ���Ҹ� �߰��� ��
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
	while (tmp) { //linked list�� ���ҵ��� �ϳ��� ���
		printf("%c ", tmp->data);
		tmp = tmp->next;
	}
	if (size) { //linked list�� ���Ұ� �ϳ��� ������ current point�� ���
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

	if (!size) { //���Ұ� �ϳ��� ���� ��
		return;
	}

	NODE* target;
	if (current == 0) { //ù��° ���Ҹ� ������ ��
		target = head;
		head = head->next;
		free(target);
	}
	else { //ù��°�� �ƴ� ���Ҹ� ������ ��
		NODE* cur = head;
		for (int i = 0; i < current - 1; i++) {
			cur = cur->next;
		}
		target = cur->next;
		cur->next = cur->next->next;
		free(target);
	}
	size--;

	if (current >= size) { //current point�� linked list���� ����� ��
		printf("  current initialization\n");
		current = 0;
	}

	return head;
}

NODE* addFirst(NODE* head, char data) { //���� �տ� node�� �߰��� ��
	NODE* new = (NODE*)malloc(sizeof(NODE));

	new->next = head;
	new->data = data;
	head = new;

	size++;
	return head;
}

void add(NODE* head, char data) { //�߰��� node�� �߰��� ��
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
	return -1; //�ش� ���Ҹ� ã�� ������ ��
}

NODE* clear(NODE* head) {
	current = 0;
	int tmp = size;
	for (int i = 0; i < tmp; i++) { //������ ������ŭ delete()�� ����
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
		middle->next = last; //node�� ������ ����
	}

	return middle; //���ο� head�� return
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
	if (tmp->data >= 'A' && tmp->data <= 'Z') { //current point�� ���Ұ� �빮���� ���
		tmp->data = tmp->data + 32;
	}
	else if (tmp->data >= 'a' && tmp->data <= 'z') { //current point�� ���Ұ� �ҹ����� ���
		tmp->data = tmp->data - 32;
	}
}
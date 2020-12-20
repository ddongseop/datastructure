#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

typedef struct node { //singly linked list�� node ����ü ����
	char data;
	struct node* next;
}NODE;

typedef struct queue { //queue�� ���� ������ ���� queue ����ü ���� 
	NODE* head; //head�� �ּ�
	NODE* tail; //tail�� �ּ�
	int size; //queue�� ���� ũ��
	int max; //queue�� �ִ� ũ��
}Q;

void init(Q*); //����ִ� queue�� �����ϴ� �Լ�
void enqueue(Q*, char); //queue�� tail�� data�� enqueue�ϴ� �Լ�
char dequeue(Q*); //queue�� head���� data�� dequeue�ϴ� �Լ�

int is_empty(Q*); //queue�� ����ִ��� Ȯ���ϴ� �Լ�
int is_full(Q*); //queue�� ���� ���ִ��� Ȯ���ϴ� �Լ� (linked list�� Ȱ���߱� ������ tail == Max_Size�� ������� Ȯ���ϴ� �Ͱ� �ٸ��� queue ����ü�� ������ Ȱ���� �Ǵ�)

void print(Q*); //dequeue�� data�� print�� ��, �ٽ� enqueue�ϴ� �۾��� �ݺ��ϸ� queue�� ��� data�� ����ϴ� �Լ�
			   //+ head�� tail�� ����Ű�� data�� ���, �����Ҵ��̹Ƿ� index�� ��Ÿ���� �ͺ��� ������ ������� �Ǵ�
char peek(Q*); //queue�� head�� �ִ� data�� ��ȯ�ϴ� �Լ�

NODE* head(Q*); //queue�� head�� ����Ű�� �ּҸ� ��ȯ�ϴ� �Լ� (linked list�� Ȱ���߱� ������ index�� �ƴ� �ּҸ� ��ȯ)
NODE* tail(Q*); //queue�� tail ����Ű�� �ּҸ� ��ȯ�ϴ� �Լ� (linked list�� Ȱ���߱� ������ index�� �ƴ� �ּҸ� ��ȯ)

int data_count(Q*); //queue�� ����ִ� data�� ������ ��ȯ�ϴ� �Լ� (linked list�� Ȱ���߱� ������ tail-head�� ������� ����ϴ� ���� �ƴ� queue ����ü�� size �����͸� Ȱ��)
int is_member(Q*, char); //Ư�� data�� queue�� ���� �ִ��� Ȯ���ϰ�, ���° ��ġ�� �ִ��� ��ȯ�ϴ� �Լ�
void replace(Q*, char); //tail�� data�� �ٸ� data�� ��ü�ϴ� �Լ�
void clear(Q*); //queue�� ��� data�� dequeue�ϴ� �Լ�

void SizeChange(Q*, int); //queue�� �ִ� ũ�⸦ �ٲٴ� �Լ�
void Twice(Q*); //queue�� data���� �ϳ��� dequeue�� ��, �ι��� enqueue�ϸ鼭 data�� �ι�� �Ҹ��� �Լ�
void MaxEnqueue(Q*, char); //queue�� full�� ���°� �� ������ Ư�� data�� enqueue�ϴ� �Լ�

void main() {
	printf("\n");
	printf("��������������������������������������������������������������������������������������������������������������������������\n");
	printf("\t      C O M M A N D   H E L P E R						\n");
	printf("��������������������������������������������������������������������������������������������������������������������������\n");
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
	printf("��������������������������������������������������������������������������������������������������������������������������\n");
	printf("\t      N  E  W   F U N C T I O N S						\n");
	printf("��������������������������������������������������������������������������������������������������������������������������\n");
	printf(" $n : (n: integer) Change size of queue to n			\n");	
	printf("  D : Make queue be doubled					     	    \n");
	printf("	   ex) a b c -> a a b b c c						   	\n");
	printf(" X@ : Enqueue @ until queue is full		     		    \n");
	printf("	   ex) a b c (if max == 10)			   				\n");
	printf("	       >> Xh 		   								\n");
	printf("	       a b c h h h h h h h						   	\n");
	printf("��������������������������������������������������������������������������������������������������������������������������\n");
	printf("  The length of command must be shorter than 30			\n");
	printf("  Make a space between commands							\n");
	printf("  Programmed by 2019310181 Dongseop Lee					\n");
	printf("��������������������������������������������������������������������������������������������������������������������������\n");
	
	Q my_queue; //create(my_queue)
	init(&my_queue); //����ִ� queue�� ����

	printf("  decide max size of queue: ");
	scanf("%d", &(my_queue.max)); //queue�� �ִ� ũ�� �Է¹ޱ�
	getchar(); //�Է� ���� ����

	char answer[30]; //command�� ���� �迭(���ڿ�)
	
	while (1) {
		printf("  >> ");
		gets(answer); //command �Է¹���

		for (int i = 0; answer[i] != '\0'; i++) { //command�� ���� ���� ������ �ݺ���

			if (answer[i] == '+') { //enqueue�� ��
				enqueue(&my_queue, answer[i + 1]);
				i++;
			}
			else if (answer[i] == '-') { //dequeue�� ��
				if (is_empty(&my_queue)) { //dequeue�� data�� ������
					printf("  [Error] Nothing to dequeue\n");
				}
				else { //������ dequeue ����
					printf("  return %c\n", dequeue(&my_queue));
				}
			}
			else if (answer[i] == 'L') { //queue�� ����� ��
				continue;
			}
			else if (answer[i] == 'P') { //queue�� head�� �ִ� data�� ������� ��
				if (is_empty(&my_queue)) { //peek�� data�� ������
					printf("  [Error] Nothing to peek\n");
				}
				else //������ head�� ����Ű�� data ���
					printf("  {%c}\n", peek(&my_queue));
			}
			else if (answer[i] == 'F') { //queue�� ���� ���ִ��� �˰���� ��
				if (is_full(&my_queue)) {
					printf("  TRUE\n");
				}
				else {
					printf("  FALSE\n");
				}
			}
			else if (answer[i] == 'E') { //queue�� ����ִ��� �˰���� ��
				if (is_empty(&my_queue)) {
					printf("  TRUE\n");
				}
				else {
					printf("  FALSE\n");
				}
			}
			else if (answer[i] == '#') { //queue�� ����ִ� data�� ������ �˰���� ��
				printf("  Number of data: %d\n", data_count(&my_queue));
			}
			else if (answer[i] == 'H') { //queue�� head�� ����Ű�� �ּҸ� �˰���� ��
				if (my_queue.head == NULL) { //head�� ����Ű�� ���� ������
					printf("  [Error] Nothing on head\n");
				}
				else
					printf("  Adress of head: %p\n", head(&my_queue));
			}
			else if (answer[i] == 'T') { //queue�� tail�� ����Ű�� �ּҸ� �˰���� ��
				if (my_queue.tail == NULL) { //tail�� ����Ű�� ���� ������
					printf("  [Error] Nothing on tail\n");
				}
				else {
					printf("  Adress of tail: %p\n", tail(&my_queue));
				}
			}
			else if ('0' <= answer[i] && answer[i] <= '9') { //�Է¹��� ���ڸ�ŭ �ݺ��ؼ� dequeue�ϰ� ���� ��
				if (answer[i + 1] == '-') {
					for (int j = 0; j < answer[i] - '0'; j++) { //�Է¹��� ���ڸ�ŭ �ݺ��ؼ� dequeue
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
					printf("  [Error] Check your command\n"); //���� ������ '-'�� ���������� �Էµ��� �ʾ��� ��
					continue;
				}
			}
			else if (answer[i] == '?') { //Ư�� data�� queue�� �����ִ��� �˰���� ��
				int pos = is_member(&my_queue, answer[i + 1]); //is_member()�Լ��κ��� ��ġ ������ �޾ƿ���
				if (pos == -1) { 
					printf("  -1 (Not in the queue)\n");
				}
				else {
					printf("  %d (Position of member)\n", pos);
				}
				i++;
			}
			else if (answer[i] == '=') { //tail�� data�� Ư�� data�� ��ü�ϰ� ���� ��
				if (is_empty(&my_queue)) { //tail�� data�� ���� ��
					printf("  [Error] No element to replace\n");
				}
				else {
					replace(&my_queue, answer[i + 1]);
					i++;
				}
			}
			else if (answer[i] == 'C') { //queue�� ��� data���� dequeue�ϰ� ���� ��
				clear(&my_queue);
			}
			else if (answer[i] == '$') { //queue�� �ִ� ũ�⸦ �ٲٰ� ���� ��
				SizeChange(&my_queue, answer[i + 1] - '0');
				i++;
			}
			else if (answer[i] == 'D') { //queue�� ��� data���� �ι�� �Ҹ��� ���� ��
				Twice(&my_queue);
			}
			else if (answer[i] == 'X') { //queue�� full���� ������ Ư�� data�� enqueue�ϰ� ���� ��
				MaxEnqueue(&my_queue, answer[i + 1]);
				i++;
			}
		}
		print(&my_queue); //�Է¹��� command�� ��� ó���ɶ����� print() ����
	}
	return 0;
}

void init(Q* mq) { 
	mq->head = NULL;
	mq->tail = NULL;
	mq->size = 0;
}

void enqueue(Q* mq, char data) {
	if (is_full(mq)) { //���� ���̻� enqueue�� �� ������
		printf("  [Error] Queue is full\n");
		return;
	}

	NODE* new = (NODE*)malloc(sizeof(NODE));
	new->data = data;
	new->next = NULL;

	if (is_empty(mq)) { //ó�� enqueue�ϴ� �Ÿ�
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
	char dequeue_data = mq->head->data; //�̾Ƴ� �����͸� ���� ����

	NODE* target = mq->head;
	mq->head = mq->head->next;

	free(target);

	mq->size--;

	if (mq->size == 0) { //������ data�� dequeue�� �Ÿ�
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

	for (int i = 0; i < sz; i++) { //data�� ����ŭ dequeue�� �� ����ϰ� �ٽ� enqueue�ϴ� ������ �ݺ�
		char tmp = dequeue(mq);
		printf("%c ", tmp);
		enqueue(mq, tmp);
	}

	if (!is_empty(mq)) { //���� ����ִ� queue�� �ƴ϶�� head�� tail�� data ���
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
	return mq->head; //head�� �ּҸ� ��ȯ
}

NODE* tail(Q* mq) {
	return mq->tail; //tail�� �ּҸ� ��ȯ
}

int is_member(Q* mq, char data) {
	int count = 0; //���� Ž�� ���� ��ġ�� ����� ����
	int position = -1; //���� ã�� data�� ��ġ�ϴ� data�� �߰��ϸ� ���� Ž�� ���� ��ġ�� ������ ����

	int sz = mq->size;

	for (int i = 0; i < sz; i++) { //data�� ����ŭ dequeue�� ��, ���� data�� ���� ��, �ٽ� enqueue�ϴ� ������ �ݺ�
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
	for (int i = 0; i < sz; i++) { //data�� ����ŭ dequeue
		dequeue(mq);
	}
	printf("  Clear Finished\n");
}

void SizeChange(Q* mq, int new_size) {
	if (mq->size > new_size) { //���� ���� data�� ���� �ٲٷ��� �ϴ� �ִ� ũ�⺸�� Ŭ ��� (�����ϰ� �ִ� ũ�⸦ ���� ���)
		printf("  [Error] Too many elements\n");
		return;
	}

	mq->max = new_size;
}

void Twice(Q* mq) {
	if (mq->max < (mq->size)*2) { //max size�� �Ѱ�� ���� data�� 2��� �ø� �� ���� ��
		printf("  [Error] Not enough memory\n");
		return;
	}

	int sz = mq->size;
	for (int i = 0; i < sz; i++) { //data�� �ϳ��� dequeue�ϸ� �ٽ� �ι��� enqueue����
		char tmp = dequeue(mq);
		enqueue(mq, tmp);
		enqueue(mq, tmp);
	}
}

void MaxEnqueue(Q* mq, char data) {
	if (is_full(mq)) { //�̹� ���� ��������
		printf("  [Error] Already full\n");
		return;
	}

	int count = mq->max - mq->size;
	for (int i = 0; i < count; i++) { //���� �� ������
		enqueue(mq, data); //���� data�� enqueue
	}
}
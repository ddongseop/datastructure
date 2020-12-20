#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

typedef struct heap {
	int array[200];
	int type; //max heap -> 1, min heap -> 0
	int size;
}HEAP;

typedef struct node {
	int data;
	struct node* left;
	struct node* right;
}NODE;

typedef struct bst {
	NODE* root;
	int OnOff;
}BST;

int signal = 1; //시스템 종료와 관련된 변수
int StN(char[], int*); //String to Number

void heap_insert(HEAP*, int);
int heap_delete(HEAP*);
void heap_init(HEAP*);
void heap_print(HEAP*, int);
void heap_peek(HEAP*);
int heap_count(HEAP*);
void heap_clear(HEAP*);
int heap_destroy(HEAP*);

void bst_create(BST*, int);
void bst_insert_node(BST*, int);
void bst_print(BST*, NODE*);
int bst_delete_node(BST*, int);
NODE* bst_find_node(BST*, int);
NODE* bst_get_parent(BST*, NODE*, NODE*);

void HEAP_to_BST(HEAP*); //1.HEAP을 BST로 변환한다
						 //2.HEAP과 BST를 Destroy하고 system을 종료할지, 변환한 BST를 다시 HEAP으로 변환할지 고른다
						 //3.만약 BST를 다시 HEAP으로 변환한다면, MAX HEAP으로 변환할지 MIN HEAP으로 변환할지 고르게 한다

int main() {
	printf("\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("\t      C O M M A N D   H E L P E R									\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  +@   : Insert Element @ to HEAP									\n");
	printf("         (you can insert consecutively)								\n");
	printf("  -    : Delete Root Element of HEAP								\n");
	printf("  P    : Print HEAP                                                 \n");
	printf("  R    : Peek Root of HEAP (Minimum or Maximum)						\n");
	printf("  #    : Count Node of HEAP											\n");
	printf("  C    : Clear HEAP                                                 \n");
	printf("  D    : Destroy HEAP												\n");
	printf("  T    : HEAP to BST												\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  The length of command must be shorter than 30						\n");
	printf("  Make a space between commands										\n");
	printf("  Programmed by 2019310181 Dongseop Lee								\n");
	printf("─────────────────────────────────────────────────────────────\n");

	char answer[30];
	int TP;
	HEAP* myHeap = (HEAP*)malloc(sizeof(HEAP));
	heap_init(myHeap);

	while (1) {
		printf("  Choose type of HEAP: 1.MAX HEAP  2.MIN HEAP\n");
		printf("  >> ");
		scanf("%d", &TP);
		getchar();

		if (TP == 1) {
			myHeap->type = 1;
			break;
		}
		else if (TP == 2) {
			myHeap->type = 0;
			break;
		}
		else {
			printf("  [Error] Input just number 1 or 2\n");
		}
	}

	while (signal) {
		printf("  >> ");
		gets(answer);

		for (int i = 0; answer[i] != '\0'; i++) {
			if (answer[i] == '+') {
				i++;
				heap_insert(myHeap, StN(answer, &i));
				i--;
			}
			else if (answer[i] == '-') {
				int tmp = heap_delete(myHeap);
				if (tmp != -1) {
					printf("  Deleted : %d\n", tmp);
				}
			}
			else if (answer[i] == 'P') {
				continue;
			}
			else if (answer[i] == 'R') {
				heap_peek(myHeap);
			}
			else if (answer[i] == '#') {
				printf("  Count of node : %d\n", heap_count(myHeap));
			}
			else if (answer[i] == 'C') {
				heap_clear(myHeap);
			}
			else if (answer[i] == 'D') {
				if (heap_destroy(myHeap)) {
					printf("  System finshed\n");
					signal = 0;
				}
			}
			else if (answer[i] == 'T') {
				HEAP_to_BST(myHeap);
			}
		}//for
		if (signal && myHeap->size >= 1) {
			heap_print(myHeap, 1);
		}
		else if (signal && myHeap->size == 0) {
			printf("  Empty HEAP\n");
		}
	}//while	


	return 0;
}

void heap_init(HEAP* myHeap) {
	for (int i = 0; i < 200; i++) {
		myHeap->array[i] = 0;
	}
	myHeap->size = 0;
}

void heap_insert(HEAP* myHeap, int data) {
	int i;
	i = ++(myHeap->size);

	if (myHeap->type) { //maxheap
		while ((i != 1) && data > myHeap->array[i/2]) {
			myHeap->array[i] = myHeap->array[i/2];
			i /= 2;
		}
		myHeap->array[i] = data;
	}
	else {
		while ((i != 1) && data < myHeap->array[i/2]) {
			myHeap->array[i] = myHeap->array[i/2];
			i /= 2;
		}
		myHeap->array[i] = data;
	}
}

int heap_delete(HEAP* myHeap) {
	if (myHeap->size == 0) {
		printf("  [Error] Nothing to delete\n");
		return -1;
	}

	int parent, child;
	int item, tmp;

	item = myHeap->array[1];
	tmp = myHeap->array[(myHeap->size)--];

	parent = 1;
	child = 2;

	if (myHeap->type) {
		while (child <= myHeap->size) {
			if (child < myHeap->size && myHeap->array[child] < myHeap->array[child + 1]) {
				child++;
			}
			if (tmp >= myHeap->array[child]) {
				break;
			}
			myHeap->array[parent] = myHeap->array[child];
			parent = child;
			child *= 2;
		}
		myHeap->array[parent] = tmp;
		return item;
	}
	else {
		while (child <= myHeap->size) {
			if (child < myHeap->size && myHeap->array[child] > myHeap->array[child + 1]) {
				child++;
			}
			if (tmp <= myHeap->array[child]) {
				break;
			}
			myHeap->array[parent] = myHeap->array[child];
			parent = child;
			child *= 2;
		}
		myHeap->array[parent] = tmp;
		return item;
	}
}

int StN(char answer[], int* i) {

	int number = 0;

	while ('0' <= answer[*i] && answer[*i] <= '9') {
		number = number * 10;
		number += (answer[*i] - '0');

		(*i)++;
	}

	return number;
}

void heap_print(HEAP* myHeap, int i) {
	if (i > myHeap->size)
		return;
	
	if (i == 1)
		printf("  (");

	printf("%d", myHeap->array[i]);


	if ((2 * i) <= myHeap->size || (2 * i + 1) <= myHeap->size) {
		printf("(");
		heap_print(myHeap, (2 * i));
		printf(",");
		heap_print(myHeap, (2 * i + 1));
		printf(")");
	}

	if (i == 1)
		printf(")\n");
}

void heap_peek(HEAP* myHeap) {
	if (myHeap->size == 0) {
		printf("  [Error] HEAP is empty\n");
		return;
	}
	if (myHeap->type) {
		printf("  Maximum of HEAP : %d\n", myHeap->array[1]);
	}
	else
		printf("  Minimum of HEAP : %d\n", myHeap->array[1]);
}

int heap_count(HEAP* myHeap) {
	return myHeap->size;
}

void heap_clear(HEAP* myHeap) {
	if (myHeap->size == 0) {
		printf("  [Error] Already Empty\n");
		return;
	}

	int tmp = myHeap->size;

	for (int i = 0; i < tmp; i++) {
		heap_delete(myHeap);
	}

	printf("  Clear finished\n");
}

int heap_destroy(HEAP* myHeap) {
	if (myHeap->size != 0) {
		printf("  [Error] Please clear HEAP first\n");
		return 0;
	}

	free(myHeap);
	return 1;
}

void bst_create(BST* Mbst, int data) {
	NODE* new = (NODE*)malloc(sizeof(NODE));

	new->data = data;
	new->left = NULL;
	new->right = NULL;

	Mbst->root = new;
	Mbst->OnOff = 1;
}

void bst_insert_node(BST* Mbst, int data) {
	NODE* tmp = Mbst->root;
	NODE* p_tmp = NULL;

	while (tmp != NULL) {
		if (tmp->data == data) {
			printf("  [Error] Data already exists\n");
			return;
		}
		p_tmp = tmp;

		if (data > tmp->data) {
			tmp = tmp->right;
		}
		else {
			tmp = tmp->left;
		}
	}

	NODE* new = (NODE*)malloc(sizeof(NODE));

	new->data = data;
	new->left = NULL;
	new->right = NULL;

	if (data > p_tmp->data) {
		p_tmp->right = new;
	}
	else {
		p_tmp->left = new;
	}
}

void bst_print(BST* Mbst, NODE* tmp) {
	if (tmp == NULL) {
		return;
	}

	if (Mbst->root == tmp) {
		printf("  (");
	}

	printf("%d", tmp->data);

	if (tmp->left != NULL || tmp->right != NULL) {
		printf("(");
		bst_print(Mbst, tmp->left);
		printf(",");
		bst_print(Mbst, tmp->right);
		printf(")");
	}

	if (Mbst->root == tmp) {
		printf(")\n");
	}
}

int bst_delete_node(BST* Mbst, int data) {
	if (Mbst->OnOff == 0) {
		printf("  [Error] Nothing to delete\n");
		return -1;
	}

	NODE* target = bst_find_node(Mbst, data);
	if (target == NULL) {
		printf("  [Error] Can't find target\n");
		return -1;
	}

	int item;

	if (target->left == NULL && target->right == NULL) {
		if (target == Mbst->root) {
			item = target->data;
			free(target);
			Mbst->root = NULL;
			Mbst->OnOff = 0;
		}
		else {
			NODE* p_target = bst_get_parent(Mbst, Mbst->root, target);

			if (p_target->right == target) {
				p_target->right = target->left;
				item = target->data;
				free(target);
			}
			else {
				p_target->left = target->left;
				item = target->data;
				free(target);
			}
		}
	}
	else if (target->left != NULL && target->right == NULL) {
		if (target == Mbst->root) {
			Mbst->root = target->left;
			item = target->data;
			free(target);
		}
		else {
			NODE* p_target = bst_get_parent(Mbst, Mbst->root, target);

			if (p_target->right == target) {
				p_target->right = target->left;
				item = target->data;
				free(target);
			}
			else {
				p_target->left = target->left;
				item = target->data;
				free(target);
			}
		}

	}
	else if (target->left == NULL && target->right != NULL) {
		if (target == Mbst->root) {
			Mbst->root = target->right;
			item = target->data;
			free(target);
		}
		else {
			NODE* p_target = bst_get_parent(Mbst, Mbst->root, target);

			if (p_target->right == target) {
				p_target->right = target->right;
				item = target->data;
				free(target);
			}
			else {
				p_target->left = target->right;
				item = target->data;
				free(target);
			}
		}

	}
	else { //left most 값을 후계자 노드로 지정
		NODE* heir = target->left;

		while (heir->right != NULL) {
			heir = heir->right;
		}

		item = target->data;
		int heir_data = heir->data;

		bst_delete_node(Mbst, heir->data);
		target->data = heir_data;
	}

	return item;
}

NODE* bst_find_node(BST* Mbst, int data) {
	NODE* tmp = Mbst->root;

	while (tmp != NULL) {
		if (data == tmp->data) {
			return tmp;
		}
		else if (data > tmp->data) {
			tmp = tmp->right;
		}
		else {
			tmp = tmp->left;
		}
	}

	return tmp;
}

NODE* bst_get_parent(BST* Mbst, NODE* search, NODE* target) { //target이 NULL이 아니라는 것을 알고 사용

	if (search == NULL) {
		return NULL;
	}

	if (search->left == target || search->right == target) {
		return search;
	}

	NODE* adress;

	adress = bst_get_parent(Mbst, search->left, target);
	if (adress) {
		return adress;
	}

	adress = bst_get_parent(Mbst, search->right, target);
	if (adress) {
		return adress;
	}

	return NULL;
}

void HEAP_to_BST(HEAP* myHeap) {
	if (myHeap->size == 0) {
		printf("  [Error] HEAP is empty\n");
		return;
	}

	printf("  <HEAP>\n");
	heap_print(myHeap, 1);

	BST* Mbst = (BST*)malloc(sizeof(BST));
	Mbst->root = NULL;
	Mbst->OnOff = 0;

	int tmp = heap_delete(myHeap);
	bst_create(Mbst, tmp);

	while (myHeap->size != 0) {
		tmp = heap_delete(myHeap);
		bst_insert_node(Mbst, tmp);
	}
	printf("  Transform Finished (HEAP to BST)\n");

	printf("  <BST>\n");
	bst_print(Mbst, Mbst->root);

	while (1) {
		printf("  1. Destroy BST and HEAP to exit\n");
		printf("  2. BST to HEAP (Destroy BST)\n");		
		printf("  >> ");
		scanf("%d", &tmp);
		getchar();

		if (tmp == 1) {
			while (1) {
				if (Mbst->root == NULL) {
					break;
				}
				bst_delete_node(Mbst, Mbst->root->data);
			}
			free(Mbst);
			free(myHeap);
			signal = 0;

			break;
		}
		else if (tmp == 2) {
			int TP;
			while (1) {
				printf("  Choose type of HEAP: 1.MAX HEAP  2.MIN HEAP\n");
				printf("  >> ");
				scanf("%d", &TP);
				getchar();

				if (TP == 1) {
					myHeap->type = 1;
					break;
				}
				else if (TP == 2) {
					myHeap->type = 0;
					break;
				}
				else {
					printf("  [Error] Input just number 1 or 2\n");
				}
			}
			int tmp2;

			while (1) {
				if (Mbst->root == NULL) {
					break;
				}
				tmp2 = bst_delete_node(Mbst, Mbst->root->data);
				heap_insert(myHeap, tmp2);
			}

			printf("  Transform Finished (BST to HEAP)\n");
			free(Mbst);

			break;
			
		}
		else {
			printf("  [Error] Input just number 1 or 2\n");
		}
	}
}

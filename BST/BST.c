#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

typedef struct node {
	int data;
	struct node* left;
	struct node* right;
}NODE;

typedef struct bst {
	NODE* root;
	int OnOff; //create를 할건지 insert를 할건지 구분해주는 변수
}BST;

void create(BST*, int);
int StN(char[], int*); //String(char[]) to Number(int)
void insert_node(BST*, int);
void print(BST*, NODE*);
NODE* get_parent(BST*, NODE*, NODE*);
void inorder_traversal(BST*, NODE*);
void right_root_left_traversal(BST*, NODE*);
int get_min(BST*);
int get_max(BST*);
NODE* find_node(BST*, int);
void find_path(BST*, NODE*);
int delete_node(BST*, int);
int height_of_node(BST*, NODE*);
void height(BST*, NODE*, int*);
int get_right_child(BST*, int);
int get_left_child(BST*, int);
int count_node(NODE*);
void clear(BST*);
int destroy(BST*);

int main() {
	printf("\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("\t      C O M M A N D   H E L P E R									\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  +@   : Create BST (at first), Insert Node with Data @				\n");
	printf("         (you can insert consecutively)								\n");
	printf("  P    : Print all Data of BST										\n");
	printf("  I    : Inorder Traversal (From a small number)					\n");
	printf("  R    : Right Root Left Traversal (From a large number)			\n");
	printf("  N    : Get Minimum												\n");
	printf("  M    : Get Maximum												\n");
	printf("  F@   : Find Node with Data @ and Search Path						\n");
	printf("  -@   : Delete Node wiht Data @									\n");
	printf("  H    : Get Height of BST											\n");
	printf("  H(@) : Get Height of Node wih Data @								\n");
	printf("  G(@) : Get Right Child of Node with Data @ 						\n");
	printf("  L(@) : Get Left Child of Node with Data @							\n");
	printf("  #    : Count Node                                                 \n");
	printf("  ^(@) : Get Parent of Node with Data @								\n");
	printf("  C    : Clear BST                                                  \n");
	printf("  D    : Destroy BST												\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  The length of command must be shorter than 30						\n");
	printf("  Make a space between commands										\n");
	printf("  Programmed by 2019310181 Dongseop Lee								\n");
	printf("─────────────────────────────────────────────────────────────\n");

	int signal = 1;
	char answer[30];
	BST* Mbst = (BST*)malloc(sizeof(BST));
	Mbst->root = NULL;
	Mbst->OnOff = 0; 

	while (signal) {
		printf("  >> ");
		gets(answer);

		for (int i = 0; answer[i] != '\0'; i++) {
			if (answer[i] == '+' && Mbst->OnOff == 0) {
				i++;
				create(Mbst, StN(answer, &i));
				i--;
			}
			else if (answer[i] == '+' && Mbst->OnOff == 1) {
				i++;
				insert_node(Mbst, StN(answer, &i));
				i--;
			}
			else if (answer[i] == 'P') {
				continue;
			}
			else if (answer[i] == 'I') {
				inorder_traversal(Mbst, Mbst->root);
			}
			else if (answer[i] == 'R') {
				right_root_left_traversal(Mbst, Mbst->root);
			}
			else if (answer[i] == 'N') {
				printf("  Minimum : %d\n", get_min(Mbst));
			}
			else if (answer[i] == 'X') {
				printf("  Maximum : %d\n", get_max(Mbst));
			}
			else if (answer[i] == 'F') {
				i++;
				NODE* tmp = find_node(Mbst, StN(answer, &i));
				i--;

				if (tmp == NULL) {
					printf("  [Error] Not Exist!\n");
				}
				else {
					find_path(Mbst, tmp);
				}
			}
			else if (answer[i] == '-') {
				i++;
				int tmp = delete_node(Mbst, StN(answer, &i));
				if (tmp != -1) {
					printf("  Deleted : %d\n", tmp);
				}
				i--;
			}
			else if (answer[i] == 'H') {
				if (answer[i + 1] == '(') { //H(@)
					i += 2;
					int tmp = StN(answer, &i);

					NODE* target = find_node(Mbst, tmp);
					if (target == NULL) {
						printf("  [Error] Can't find target\n");
						continue;
					}

					printf("  Height of %d is %d\n", tmp, height_of_node(Mbst, target));
				}
				else { //그냥 H
					if (Mbst->OnOff == 0) {
						printf("  [Error] Empty BST\n");
						continue;
					}
					int Height;
					height(Mbst, Mbst->root, &Height);
					printf("  Height of BST is %d\n", Height);
				}
			}
			else if (answer[i] == 'G') {
				i += 2;
				int tmp = StN(answer, &i);
				int rc = get_right_child(Mbst, tmp);

				if (rc == -1) {
					continue;
				}
				else if (rc == -2) {
					printf("  Right child of %d is NULL\n", tmp);
				}
				else
					printf("  Right child of %d is %d\n", tmp, rc);
			}
			else if (answer[i] == 'L') {
				i += 2;
				int tmp = StN(answer, &i);
				int lc = get_left_child(Mbst, tmp);

				if (lc == -1) {
					continue;
				}
				else if (lc == -2) {
					printf("  Left child of %d is NULL\n", tmp);
				}
				else
					printf("  Left child of %d is %d\n", tmp, lc);
			}
			else if (answer[i] == '#') {
				printf("  Count of node : %d\n", count_node(Mbst->root));
			}
			else if (answer[i] == 'C') {
				clear(Mbst);
			}
			else if (answer[i] == 'D') {
			if (destroy(Mbst)) {
				printf("  System finshed\n");
				signal = 0;
				}
			}
			else if (answer[i] == '^') {
				i += 2;
				int tmp = StN(answer, &i);
				NODE* target = find_node(Mbst, tmp);

				if (target == Mbst->root) {
					printf("  [Error] Root has no parent\n");
				}
				else if (target == NULL) {
					printf("  [Error] Can't find target\n");
				}
				else {
					NODE* p = get_parent(Mbst, Mbst->root, target);
					printf("  Parent of %d is %d\n", tmp, p->data);
				}
			}
		}
		if (signal && Mbst->OnOff == 1) {
			print(Mbst, Mbst->root);
		}
		else if (signal && Mbst->OnOff == 0) {
			printf("  Empty BST\n");
		}
	}

	return 0;
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

void create(BST* Mbst, int data) {
	NODE* new = (NODE*)malloc(sizeof(NODE));

	new->data = data;
	new->left = NULL;
	new->right = NULL;

	Mbst->root = new;
	Mbst->OnOff = 1;
}

void print(BST* Mbst, NODE* tmp) {
	if (tmp == NULL) {
		return;
	}
	
	if (Mbst->root == tmp) {
		printf("  (");
	}

	printf("%d", tmp->data);

	if (tmp->left != NULL || tmp->right !=NULL) {
		printf("(");
		print(Mbst, tmp->left);
		printf(",");
		print(Mbst, tmp->right);
		printf(")");
	}

	if (Mbst->root == tmp) {
		printf(")\n");
	}
}

void insert_node(BST* Mbst, int data) {
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


NODE* get_parent(BST* Mbst, NODE* search, NODE* target) { //target이 NULL이 아니라는 것을 알고 사용

	if (search == NULL) {
		return NULL;
	}

	if (search->left == target || search->right == target) {
		return search;
	}

	NODE* adress;

	adress = get_parent(Mbst, search->left, target);
	if (adress) {
		return adress;
	}

	adress = get_parent(Mbst, search->right, target);
	if (adress) {
		return adress;
	}

	return NULL;
}


void inorder_traversal(BST* Mbst, NODE* traverse) {
	if (traverse == NULL) {
		return;
	}
	
	if (Mbst->root == traverse) {
		printf("  ");
	}

	inorder_traversal(Mbst, traverse->left);

	printf("%d ", traverse->data);

	inorder_traversal(Mbst, traverse->right);

	if (Mbst->root == traverse) {
		printf("\n");
	}
}

void right_root_left_traversal(BST* Mbst, NODE* traverse) {
	if (traverse == NULL) {
		return;
	}

	if (Mbst->root == traverse) {
		printf("  ");
	}

	right_root_left_traversal(Mbst, traverse->right);

	printf("%d ", traverse->data);

	right_root_left_traversal(Mbst, traverse->left);

	if (Mbst->root == traverse) {
		printf("\n");
	}
}

int get_min(BST* Mbst) {
	NODE* tmp = Mbst->root;

	while (tmp->left != NULL) {
		tmp = tmp->left;
	}

	return tmp->data;
}

int get_max(BST* Mbst) {
	NODE* tmp = Mbst->root;

	while (tmp->right != NULL) {
		tmp = tmp->right;
	}

	return tmp->data;
}

NODE* find_node(BST* Mbst, int data) {
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

void find_path(BST* Mbst, NODE* target) {
	printf("  Root");

	NODE* tmp = Mbst->root;

	while (tmp->data != target->data) {
		if (target->data > tmp->data) {
			printf(" > Right");
			tmp = tmp->right;
		}
		else {
			printf(" > Left");
			tmp = tmp->left;
		}
	}

	printf("\n");
}

int delete_node(BST* Mbst, int data) {
	if (Mbst->OnOff == 0) { //BST empty
		printf("  [Error] Nothing to delete\n");
		return -1;
	}

	NODE* target = find_node(Mbst, data);
	if (target == NULL) {
		printf("  [Error] Can't find target\n");
		return -1;
	}
	
	int item;

	if (target->left == NULL && target->right == NULL) { //자식노드가 아예 없을 때
		if (target == Mbst->root) {
			item = target->data;
			free(target);
			Mbst->root = NULL;
			Mbst->OnOff = 0;
		}
		else {
			NODE* p_target = get_parent(Mbst, Mbst->root, target);

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
	else if (target->left != NULL && target->right == NULL) { //왼쪽에만 자식이 있을 때
		if (target == Mbst->root) {
			Mbst->root = target->left;
			item = target->data;
			free(target);
		}
		else {
			NODE* p_target = get_parent(Mbst, Mbst->root, target);

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
	else if (target->left == NULL && target->right != NULL) { //오른쪽에만 자식이 있을 때
		if (target == Mbst->root) {
			Mbst->root = target->right;
			item = target->data;
			free(target);
		}
		else {
			NODE* p_target = get_parent(Mbst, Mbst->root, target);

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
	else { //자식 노드가 2개일 때, (*) left most 값을 후계자 노드로 지정
		NODE* heir = target->left;

		while (heir->right != NULL) {
			heir = heir->right;
		}

		item = target->data;
		int heir_data = heir->data;

		delete_node(Mbst, heir->data);
		target->data = heir_data;
	}

	return item;
}

int height_of_node(BST* Mbst, NODE* target) {

	int height = 0;

	while (target != Mbst->root) {
		target = get_parent(Mbst, Mbst->root, target);
		height++;
	}

	return height;
}

void height(BST* Mbst, NODE* tmp, int* Height) {
	if (tmp == NULL) {
		return;
	}

	height(Mbst, tmp->left, Height);
	height(Mbst, tmp->right, Height);

	if (height_of_node(Mbst, tmp) > *Height) {
		*Height = height_of_node(Mbst, tmp);
	}
}

int get_right_child(BST* Mbst, int data) {
	NODE* target = find_node(Mbst, data);
	if (target == NULL) {
		printf("  [Error] Can't find target\n");
		return -1;
	}
	if (target->right == NULL) {
		return -2;
	}
	return target->right->data;
}

int get_left_child(BST* Mbst, int data) {
	NODE* target = find_node(Mbst, data);
	if (target == NULL) {
		printf("  [Error] Can't find target\n");
		return -1;
	}
	if (target->left == NULL) {
		return -2;
	}
	return target->left->data;
}

int count_node(NODE* tmp) {
	if (tmp == NULL) {
		return 0;
	}

	return count_node(tmp->left) + count_node(tmp->right) + 1;
}

void clear(BST* Mbst) {
	if (Mbst->root == NULL) {
		printf("  [Error] Already Empty\n");
		return;
	}

	while (1) {
		if (Mbst->root == NULL) {
			printf("  Clear finished\n");
			break;
		}

		delete_node(Mbst, Mbst->root->data);
	}
}

int destroy(BST* Mbst) {
	if (Mbst->root != NULL) {
		printf("  [Error] Please clear BST first\n");
		return 0;
	}

	free(Mbst);
	return 1;
}
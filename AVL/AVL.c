#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

typedef struct node {
	int data;
	struct node* left;
	struct node* right;
}NODE;

typedef struct avl {
	NODE* root;
	int OnOff; //create를 할건지 insert를 할건지 구분해주는 변수
}AVL;

void create(AVL*, int);
int StN(char[], int*); //String(char[]) to Number(int)
void insert_node(AVL*, int);
void print(AVL*, NODE*);
NODE* get_parent(NODE*, NODE*);
void inorder_traversal(AVL*, NODE*);
void right_root_left_traversal(AVL*, NODE*);
int get_min(AVL*);
int get_max(AVL*);
NODE* find_node(AVL*, int);
void find_path(AVL*, NODE*);
int delete_node(AVL*, int);
int height_of_node(NODE*, NODE*);
void height(NODE*, NODE*, int*);
int get_right_child(AVL*, int);
int get_left_child(AVL*, int);
int count_node(NODE*);
void clear(AVL*);
int destroy(AVL*);

NODE* right_rotate(NODE*);
NODE* left_rotate(NODE*);
NODE* RL_rotate(NODE*);
NODE* LR_rotate(NODE*);
int balance_factor(NODE*);
NODE* rebalance(NODE**);


int main() {
	printf("\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("\t      C O M M A N D   H E L P E R									\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  +@   : Create AVL (at first), Insert Node with Data @				\n");
	printf("         (you can insert consecutively)								\n");
	printf("  P    : Print all Data of AVL										\n");
	printf("  B@   : Get Balance Factor of @                                    \n");
	printf("  I    : Inorder Traversal (From a small number)					\n");
	printf("  R    : Right Root Left Traversal (From a large number)			\n");
	printf("  N    : Get Minimum												\n");
	printf("  X    : Get Maximum												\n");
	printf("  F@   : Find Node with Data @ and Search Path						\n");
	printf("  D@   : Delete Node with Data @									\n");
	printf("  H    : Get Height of AVL (Start from 0)							\n");
	printf("  H(@) : Get Height of Node with Data @								\n");
	printf("  G(@) : Get Right Child of Node with Data @ 						\n");
	printf("  L(@) : Get Left Child of Node with Data @							\n");
	printf("  #    : Count Node                                                 \n");
	printf("  ^(@) : Get Parent of Node with Data @								\n");
	printf("  C    : Clear AVL                                                  \n");
	printf("  Q    : Destroy AVL												\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  The length of command must be shorter than 30						\n");
	printf("  Make a space between commands										\n");
	printf("  Programmed by 2019310181 Dongseop Lee								\n");
	printf("─────────────────────────────────────────────────────────────\n");

	int signal = 1;
	char answer[30];
	AVL* Mavl = (AVL*)malloc(sizeof(AVL));
	Mavl->root = NULL;
	Mavl->OnOff = 0;

	while (signal) {
		printf("  >> ");
		gets(answer);

		for (int i = 0; answer[i] != '\0'; i++) {
			if (answer[i] == '+' && Mavl->OnOff == 0) {
				i++;
				create(Mavl, StN(answer, &i));
				i--;
			}
			else if (answer[i] == '+' && Mavl->OnOff == 1) {
				i++;
				insert_node(Mavl, StN(answer, &i));
				i--;
			}
			else if (answer[i] == 'D') {
				i++;
				int tmp = delete_node(Mavl, StN(answer, &i));
				if (tmp != -1) {
					printf("  Deleted : %d\n", tmp);
				}
				i--;
			}
			else if (answer[i] == 'P') {
				continue;
			}
			else if (answer[i] == 'B') {
				i++;
				int num = StN(answer, &i);
				i--;
				int tmp = find_node(Mavl, num);
				if (tmp == NULL) {
					printf("  [Error] Can't find target\n");
					continue;
				}
				printf("  Balance Factor of %d is %d\n", num, balance_factor(tmp));
			}
			else if (answer[i] == 'I') {
				inorder_traversal(Mavl, Mavl->root);
			}
			else if (answer[i] == 'R') {
				right_root_left_traversal(Mavl, Mavl->root);
			}
			else if (answer[i] == 'N') {
				if (Mavl->OnOff) {
					printf("  Minimum : %d\n", get_min(Mavl));
				}
				else
					printf("  [Error] Empty AVL\n");
			}
			else if (answer[i] == 'X') {
				if (Mavl->OnOff) {
					printf("  Maximum : %d\n", get_max(Mavl));
				}
				else
					printf("  [Error] Empty AVL\n");
			}
			else if (answer[i] == 'F') {
				i++;
				NODE* tmp = find_node(Mavl, StN(answer, &i));
				i--;

				if (tmp == NULL) {
					printf("  [Error] Not Exist!\n");
				}
				else {
					find_path(Mavl, tmp);
				}
			}
			else if (answer[i] == 'H') {
				if (answer[i + 1] == '(') { //H(@)
					i += 2;
					int tmp = StN(answer, &i);

					NODE* target = find_node(Mavl, tmp);
					if (target == NULL) {
						printf("  [Error] Can't find target\n");
						continue;
					}

					printf("  Height of %d is %d\n", tmp, height_of_node(Mavl->root, target));
				}
				else { //그냥 H
					if (Mavl->OnOff == 0) {
						printf("  [Error] Empty AVL\n");
						continue;
					}
					int Height;
					height(Mavl->root, Mavl->root, &Height);
					printf("  Height of AVL is %d\n", Height);
				}
			}
			else if (answer[i] == 'G') {
				i += 2;
				int tmp = StN(answer, &i);
				int rc = get_right_child(Mavl, tmp);

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
				int lc = get_left_child(Mavl, tmp);

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
				printf("  Count of node : %d\n", count_node(Mavl->root));
			}
			else if (answer[i] == 'C') {
				clear(Mavl);
			}
			else if (answer[i] == 'Q') {
				if (destroy(Mavl)) {
					printf("  System finshed\n");
					signal = 0;
				}
			}
			else if (answer[i] == '^') {
				i += 2;
				int tmp = StN(answer, &i);
				NODE* target = find_node(Mavl, tmp);

				if (target == Mavl->root) {
					printf("  [Error] Root has no parent\n");
				}
				else if (target == NULL) {
					printf("  [Error] Can't find target\n");
				}
				else {
					NODE* p = get_parent(Mavl->root, target);
					printf("  Parent of %d is %d\n", tmp, p->data);
				}
			}
		}
		if (signal && Mavl->OnOff == 1) {
			print(Mavl, Mavl->root);
		}
		else if (signal && Mavl->OnOff == 0) {
			printf("  Empty AVL\n");
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

void create(AVL* Mavl, int data) {
	NODE* new = (NODE*)malloc(sizeof(NODE));

	new->data = data;
	new->left = NULL;
	new->right = NULL;

	Mavl->root = new;
	Mavl->OnOff = 1;
}

void print(AVL* Mavl, NODE* tmp) {
	if (tmp == NULL) {
		return;
	}

	if (Mavl->root == tmp) {
		printf("  (");
	}

	printf("%d", tmp->data);

	if (tmp->left != NULL || tmp->right != NULL) {
		printf("(");
		print(Mavl, tmp->left);
		printf(",");
		print(Mavl, tmp->right);
		printf(")");
	}

	if (Mavl->root == tmp) {
		printf(")\n");
	}
}

void insert_node(AVL* Mavl, int data) {
	NODE* tmp = Mavl->root;
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

	Mavl->root = rebalance(&Mavl->root);
}


NODE* get_parent(NODE* search, NODE* target) { //target이 NULL이 아니라는 것을 알고 사용

	if (search == NULL) {
		return NULL;
	}

	if (search->left == target || search->right == target) {
		return search;
	}

	NODE* adress;

	adress = get_parent(search->left, target);
	if (adress) {
		return adress;
	}

	adress = get_parent(search->right, target);
	if (adress) {
		return adress;
	}

	return NULL;
}


void inorder_traversal(AVL* Mavl, NODE* traverse) {
	if (traverse == NULL) {
		return;
	}

	if (Mavl->root == traverse) {
		printf("  ");
	}

	inorder_traversal(Mavl, traverse->left);

	printf("%d ", traverse->data);

	inorder_traversal(Mavl, traverse->right);

	if (Mavl->root == traverse) {
		printf("\n");
	}
}

void right_root_left_traversal(AVL* Mavl, NODE* traverse) {
	if (traverse == NULL) {
		return;
	}

	if (Mavl->root == traverse) {
		printf("  ");
	}

	right_root_left_traversal(Mavl, traverse->right);

	printf("%d ", traverse->data);

	right_root_left_traversal(Mavl, traverse->left);

	if (Mavl->root == traverse) {
		printf("\n");
	}
}

int get_min(AVL* Mavl) {
	NODE* tmp = Mavl->root;

	while (tmp->left != NULL) {
		tmp = tmp->left;
	}

	return tmp->data;
}

int get_max(AVL* Mavl) {
	NODE* tmp = Mavl->root;

	while (tmp->right != NULL) {
		tmp = tmp->right;
	}

	return tmp->data;
}

NODE* find_node(AVL* Mavl, int data) {
	NODE* tmp = Mavl->root;

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

void find_path(AVL* Mavl, NODE* target) {
	printf("  Root");

	NODE* tmp = Mavl->root;

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

int delete_node(AVL* Mavl, int data) {
	if (Mavl->OnOff == 0) { //AVL empty
		printf("  [Error] Nothing to delete\n");
		return -1;
	}

	NODE* target = find_node(Mavl, data);
	if (target == NULL) {
		printf("  [Error] Can't find target\n");
		return -1;
	}

	int item;

	if (target->left == NULL && target->right == NULL) { //자식노드가 아예 없을 때
		if (target == Mavl->root) {
			item = target->data;
			free(target);
			Mavl->root = NULL;
			Mavl->OnOff = 0;
		}
		else {
			NODE* p_target = get_parent(Mavl->root, target);

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
		if (target == Mavl->root) {
			Mavl->root = target->left;
			item = target->data;
			free(target);
		}
		else {
			NODE* p_target = get_parent(Mavl->root, target);

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
		if (target == Mavl->root) {
			Mavl->root = target->right;
			item = target->data;
			free(target);
		}
		else {
			NODE* p_target = get_parent(Mavl->root, target);

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
	else { //자식 노드가 2개일 때, (*) balance factor에 따라 left most / right most 값을 후계자 노드로 지정
		NODE* heir = target;
		
		if (balance_factor(target) >= 0) { //left most
			heir = target->left;

			while (heir->right != NULL) {
				heir = heir->right;
			}
		}
		else { //right most
			heir = target->right;

			while (heir->left != NULL) {
				heir = heir->left;
			}
		}

		item = target->data;
		int heir_data = heir->data;

		delete_node(Mavl, heir->data);
		target->data = heir_data;
	}

	Mavl->root = rebalance(&Mavl->root);
	return item;
}

int height_of_node(NODE* root, NODE* target) {

	int height = 0;

	while (target != root) {
		target = get_parent(root, target);
		height++;
	}

	return height;
}

void height(NODE* root, NODE* tmp, int* Height) {
	
	if (tmp == NULL) {
		return;
	}

	height(root, tmp->left, Height);
	height(root, tmp->right, Height);

	if (height_of_node(root, tmp) > *Height) {
		*Height = height_of_node(root, tmp);
	}
}

int get_right_child(AVL* Mavl, int data) {
	NODE* target = find_node(Mavl, data);
	if (target == NULL) {
		printf("  [Error] Can't find target\n");
		return -1;
	}
	if (target->right == NULL) {
		return -2;
	}
	return target->right->data;
}

int get_left_child(AVL* Mavl, int data) {
	NODE* target = find_node(Mavl, data);
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

void clear(AVL* Mavl) {
	if (Mavl->root == NULL) {
		printf("  [Error] Already Empty\n");
		return;
	}

	while (1) {
		if (Mavl->root == NULL) {
			printf("  Clear finished\n");
			break;
		}

		delete_node(Mavl, Mavl->root->data);
	}
}

int destroy(AVL* Mavl) {
	if (Mavl->root != NULL) {
		printf("  [Error] Please clear AVL first\n");
		return 0;
	}

	free(Mavl);
	return 1;
}

NODE* right_rotate(NODE* root) {
	NODE* parent = root;
	NODE* child = parent->left;

	parent->left = child->right;
	child->right = parent;

	return child;
}

NODE* left_rotate(NODE* root) {
	NODE* parent = root;
	NODE* child = parent->right;

	parent->right = child->left;
	child->left = parent;

	return child;
}

NODE* LR_rotate(NODE* root) {
	NODE* parent = root;
	NODE* child = parent->left;

	parent->left = left_rotate(child);

	return right_rotate(parent);
}

NODE* RL_rotate(NODE* root) {
	NODE* parent = root;
	NODE* child = parent->right;

	parent->right = right_rotate(child);

	return left_rotate(parent);
}

int balance_factor(NODE* root) {
	int left_height = -1;
	int right_height = -1;

	height(root->left, root->left, &left_height);
	height(root->right, root->right, &right_height);

	return left_height - right_height;
}

NODE* rebalance(NODE** root) {
	if (*root == NULL) {
		return NULL;
	}
	(*root)->left = rebalance(&(*root)->left);
	(*root)->right = rebalance(&(*root)->right);

	int bf = balance_factor(*root);

	if (-1 <= bf && bf <= 1) {
		return *root;
	}

	if (bf >= 2) {
		if (balance_factor((*root)->left) >= 1) {
			*root = right_rotate(*root);
			printf("  Right Rotate is Done\n");
		}
		else {
			*root = LR_rotate(*root);
			printf("  LR Rotate is Done\n");
		}
	}

	if (bf <= -2) {
		if (balance_factor((*root)->right) <= -1) {
			*root = left_rotate(*root);
			printf("  Left Rotate is Done\n");
		}
		else {
			*root = RL_rotate(*root);
			printf("  RL Rotate is Done\n");
		}
	}

	return *root;
}




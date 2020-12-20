#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

typedef struct tnode {
	char data;
	struct tnode* left;
	struct tnode* right;
}TNODE;

typedef struct trees {
	TNODE* root[10];
	int current;
	int count;
	int type;
}TREEs;

void init(TREEs*);
void create(TREEs*, char);
void insert_node(TREEs*, TNODE*, char);
TNODE* search(TNODE*, char);
void moveIndex(TREEs*, int);
void print(TNODE*, TNODE*);
TNODE* get_parent(TNODE*, TNODE*);
void get_sibling(TREEs*, TNODE*);
void get_child(TNODE*);
int level_of_node(TREEs*, TNODE*);
int level_of_tree(TREEs*, TNODE*, int*);
int delete_node(TREEs*, TNODE*);
void get_ancestors(TREEs*, TNODE*);
void get_descendants(TNODE*);
int degree_of_node(TNODE*);
void degree_of_tree(TNODE*, int*);
int count_node(TNODE*);
void insert_sibling(TREEs*, TNODE*, char);
void join_trees(TREEs*, char, int, int);
TNODE* copy(TNODE*);
void clear(TNODE*);

int main() {
	printf("\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("\t      C O M M A N D   H E L P E R									\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  +^@      : Create new tree with root @							\n");
	printf("             (you can create up to 10)								\n");
	printf("  +A(B)    : Insert B as child of A									\n");
	printf("             (+A(B,C,D) available)									\n");
	printf("  S(@)     : Get sibling of @										\n");
	printf("  T        : Print current tree										\n");
	printf("  M@       : Move to tree index of @								\n");
	printf("  P(@)     : Get parent of @										\n");
	printf("  C(@)     : Get child of @											\n");
	printf("  L(@)     : Get level of @											\n");
	printf("  L        : Get level of tree										\n");
	printf("  -@       : Delete node which has data @							\n");
	printf("             (You can only delete leaf node)						\n");
	printf("  A(@)     : Get ancestors of @										\n");
	printf("  D(@)     : Get descendants of @									\n");
	printf("  G(@)     : Get degree of @										\n");
	printf("  G        : Get degree of tree										\n");
	printf("  #        : Count number of node of tree							\n");
	printf("  =+A(B)   : Insert B as sibling of A								\n");
	printf("             (=+A(B,C) available)									\n");
	printf("  J(@,a,b) : Make new tree with root @ and join						\n");
	printf("             two trees 'Index' of 'a' and 'b'	 					\n");
	printf("  K        : Clear all tree                                         \n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  The length of command must be shorter than 30						\n");
	printf("  Make a space between commands										\n");
	printf("  Programmed by 2019310181 Dongseop Lee								\n");
	printf("─────────────────────────────────────────────────────────────\n");
	
	char answer[30];
	TREEs* Mtree = (TREEs*)malloc(sizeof(TREEs));
	init(Mtree);

	int type;
	printf("  1.general tree  2.binary tree\n");
	printf("  >> ");
	scanf("%d", &type);
	getchar();

	if (type == 1) {
		Mtree->type = 1;
	}
	else
		Mtree->type = 0;

	while (1) {
		printf("  >> ");
		gets(answer);

		for (int i = 0; answer[i] != '\0'; i++) {
			if (answer[i] == '+') {
				if (answer[i + 1] == '^') {
					if (Mtree->count >= 10) {
						printf("  [Error] You can't create Tree more\n");
					}
					else {
						create(Mtree, answer[i + 2]);
					}
					i += 2;
				}
				else if (answer[i + 2] == '(') {
					TNODE* target = search(Mtree->root[Mtree->current], answer[i + 1]);

					if (target == NULL) {
						printf("  [Error] Can't find %c\n", answer[i + 1]);
						while (answer[i] != ')')
							i++;
						continue;
					}
					for (int j = i + 3; answer[j] != ')'; j++) {
						if (answer[j] == ',') {
							continue;
						}
						if (search(Mtree->root[Mtree->current], answer[j]) != NULL) {
							printf("  [Error] %c already exist\n", answer[j]);
							continue;
						}
						insert_node(Mtree, target, answer[j]);
					}
					while (answer[i] != ')')
						i++;
				}
			}
			else if (answer[i + 1] != '^' && Mtree->count == 0) {
				printf("  [Error] Threre is nothing\n");
				break;
			}
			else if (answer[i] == 'T') {
				continue;
			}
			else if (answer[i] == 'M') {
				moveIndex(Mtree, answer[i + 1] - '0');
				i++;
			}
			else if (answer[i] == 'P') {
				TNODE* target = search(Mtree->root[Mtree->current], answer[i + 2]);

				if (target == NULL) {
					printf("  [Error] Can't find %c\n", answer[i + 2]);

					i += 3;
					continue;
				}

				TNODE* parent;
				parent = get_parent(Mtree->root[Mtree->current], target);
				
				if (parent == NULL) {
					printf("  [Error] This node is root\n");
				}
				else
					printf("  Parent of %c is %c\n", answer[i + 2], parent->data);
				i += 3;
			}
			else if (answer[i] == 'S') {
				TNODE* target = search(Mtree->root[Mtree->current], answer[i + 2]);

				if (target == NULL) {
					printf("  [Error] Can't find %c\n", answer[i + 2]);

					i += 3;
					continue;
				}
				get_sibling(Mtree, target);

				i += 3;
			}
			else if (answer[i] == 'C') {
				TNODE* target = search(Mtree->root[Mtree->current], answer[i + 2]);

				if (target == NULL) {
					printf("  [Error] Can't find %c\n", answer[i + 2]);

					i += 3;
					continue;
				}

				get_child(target);

				i += 3;
			}
			else if (answer[i] == 'L') {
				if (answer[i + 1] == '(') {
					TNODE* target = search(Mtree->root[Mtree->current], answer[i + 2]);

					if (target == NULL) {
						printf("  [Error] Can't find %c\n", answer[i + 2]);

						i += 3;
						continue;
					}

					printf("  Level of %c is %d\n", answer[i + 2], level_of_node(Mtree, target));
					i += 3;
				}
				else {
					int level = 0;
					level_of_tree(Mtree, Mtree->root[Mtree->current], &level);
					printf("  Level of tree is %d\n", level);
				}
			}
			else if (answer[i] == '-') {
				TNODE* target = search(Mtree->root[Mtree->current], answer[i + 1]);

				if (target == NULL) {
					printf("  [Error] Can't find %c\n", answer[i + 1]);

					i++;
					continue;
				}
				int signal = delete_node(Mtree, target);

				if (signal) { //tree 자체가 삭제 됐을 경우
					printf("  Current tree is deleted, Index is modified\n");
					int j;
					for (j = Mtree->current; Mtree->root[j + 1] != NULL; j++) {
						Mtree->root[j] = Mtree->root[j + 1];
					}
					Mtree->root[j] = NULL;
					Mtree->count--;

					if (Mtree->count != 0) {
						int index;
						printf("  Select Index of Tree : ");
						scanf("%d", &index);
						getchar();
						moveIndex(Mtree, index);
					}
					else
						printf("  There is no Tree to select\n");
				}
				i++;
			}
			else if (answer[i] == 'A') {
				TNODE* target = search(Mtree->root[Mtree->current], answer[i + 2]);

				if (target == NULL) {
					printf("  [Error] Can't find %c\n", answer[i + 2]);

					i += 3;
					continue;
				}

				get_ancestors(Mtree, target);
				i += 3;
			}
			else if (answer[i] == 'D') {
				TNODE* target = search(Mtree->root[Mtree->current], answer[i + 2]);

				if (target == NULL) {
					printf("  [Error] Can't find %c\n", answer[i + 2]);

					i += 3;
					continue;
				}

				get_descendants(target);
				i += 3;

			}
			else if (answer[i] == 'G') {
				if (answer[i + 1] == '(') {
					TNODE* target = search(Mtree->root[Mtree->current], answer[i + 2]);

					if (target == NULL) {
						printf("  [Error] Can't find %c\n", answer[i + 2]);

						i++;
						continue;
					}

					printf("  Degree of %c is %d\n", answer[i + 2], degree_of_node(target));

					while (answer[i] != ')')
						i++;
				}
				else {
					int degree = 0;

					degree_of_tree(Mtree->root[Mtree->current], &degree);

					printf("  Degree of tree is %d\n", degree);
				}
			}
			else if (answer[i] == '#') {
				printf("  %d\n", count_node(Mtree->root[Mtree->current]));
			}
			else if (answer[i] == '=') {
				if (answer[i + 1] == '+' && answer[i + 3] == '(') {
					TNODE* target = search(Mtree->root[Mtree->current], answer[i + 2]);

					if (target == NULL) {
						printf("  [Error] Can't find %c\n", answer[i + 2]);

						while (answer[i] != ')')
							i++;
						continue;
					}

					for (int j = i + 4; answer[j] != ')'; j++) {
						if (answer[j] == ',') {
							continue;
						}
						if (search(Mtree->root[Mtree->current], answer[j]) != NULL) {
							printf("  [Error] %c already exist\n", answer[j]);
							continue;
						}
						insert_sibling(Mtree, target, answer[j]);
					}
					while (answer[i] != ')')
						i++;
				}
				else {
					printf("  [Error] Check your command\n");
					while (answer[i] != ')')
						i++;
				}
			}
			else if (answer[i] == 'J') {
				if (answer[i + 1] == '(') {
					join_trees(Mtree, answer[i + 2], answer[i + 4] - '0', answer[i + 6] - '0');
					while (answer[i] != ')')
						i++;
				}
				else {
					printf("  [Error] Check your command\n");
					while (answer[i] != ')')
						i++;
				}
			}
			else if (answer[i] == 'K') {
				Mtree->current = Mtree->count - 1;
				for (int j = 0; j < Mtree->count; j++) {
					clear(Mtree->root[Mtree->current]);
					Mtree->current--;
				}
				Mtree->count = 0;
				printf("  Clear finished\n");
			}
		}
		if (Mtree->count > 0) {
			print(Mtree->root[Mtree->current], Mtree->root[Mtree->current]);
			printf("  Index of current root : %d / %d\n", Mtree->current, Mtree->count - 1);
		}
		else
			printf("  Nothing to print\n");
	}	
	return 0;
}

void init(TREEs* Mtree) {
	for (int i = 0; i < 10; i++) {
		Mtree->root[i] = NULL;
	}
	Mtree->current = -1;
	Mtree->count = 0;
}

void create(TREEs* Mtree, char data) {
	TNODE* new = (TNODE*)malloc(sizeof(TNODE));
	new->data = data;
	new->left = NULL;
	new->right = NULL;

	Mtree->root[Mtree->count] = new;
	Mtree->current = Mtree->count;
	Mtree->count++;
}

void insert_node(TREEs* Mtree, TNODE* target, char data) {
	TNODE* new = (TNODE*)malloc(sizeof(TNODE));
	new->data = data;
	new->left = NULL;
	new->right = NULL;

	if (target->left == NULL) {
		target->left = new;
	}
	else {
		TNODE* tmp = target->left;
		if (!Mtree->type) {
			if (tmp->right != NULL) {
				printf("  [Error] Binary tree can't have three child\n");
				return;
			}
		}
		while (tmp->right) {
			tmp = tmp->right;
		}
		tmp->right = new;
	}
}

TNODE* search(TNODE* tmp1, char data) {
	if (tmp1 == NULL) {
		return NULL;
	}
	if (tmp1->data == data) {
		return tmp1;
	}

	TNODE* tmp2;

	tmp2 = search(tmp1->left, data);
	if (tmp2) {
		return tmp2;
	}

	tmp2 = search(tmp1->right, data);
	if (tmp2) {
		return tmp2;
	}

	return NULL;
}

void print(TNODE* root, TNODE* tmp1) {
	TNODE* tmp2 = tmp1->left;

	if (root == tmp1) {
		printf("  (%c", root->data);
	}
	if (root->left == NULL) {
		printf(")\n");
		return;
	}

	printf("(");

	while (tmp2) {
		printf("%c", tmp2->data);

		if (tmp2->left != NULL) {
			print(root, tmp2);
		}
		if (tmp2->right != NULL) {
			printf(",");
		}
		tmp2 = tmp2->right;
	}

	printf(")");

	if (root == tmp1) {
		printf(")\n");
	}
}

void moveIndex(TREEs* Mtree, int index) {
	if (Mtree->root[index] == NULL) {
		printf("  [Error] Tree did not created\n");
		printf("  Index initialized to 0\n");
		Mtree->current = 0;
		return;
	}
	Mtree->current = index;
}

TNODE* get_parent(TNODE* root, TNODE* target) {
	if (root == target) {
		return NULL;
	}

	TNODE* search = root->left;
	TNODE* answer = root;

	while (search) {
		TNODE* tmp = search;

		while (search) {
			if (search == target) {
				return answer;
			}

			if (search != tmp && search->left != NULL) {
				TNODE* answer2 = get_parent(search, target);
				if (answer2)
					return answer2;
			}

			search = search->right;
		}
		
		answer = tmp;
		search = tmp->left;
	}
	return NULL;
}

void get_sibling(TREEs* Mtree, TNODE* target) {
	if (Mtree->root[Mtree->current] == target) {
		printf("  [Error] Root has no sibling\n");
		return;
	}

	TNODE* search = get_parent(Mtree->root[Mtree->current], target)->left;

	printf("  {");

	while (search) {
		if (search != target) {
			printf("%c", search->data);
		}
		if (search->right != target && search->right != NULL) {
			printf(",");
		}
		search = search->right;
	}

	printf("}\n");
}

void get_child(TNODE* target) {
	if (target->left == NULL) {
		printf("  [Error] No child (leaf node)\n");
		return;
	}

	TNODE* tmp = target->left;

	printf("  {");

	while (tmp->right) {
		printf("%c,", tmp->data);
		tmp = tmp->right;
	}

	printf("%c}\n", tmp->data);
}

int level_of_node(TREEs* Mtree, TNODE* target) {
	int level = 0;

	TNODE* tmp = target;

	while (1) {

		if (Mtree->root[Mtree->current] == tmp) {
			return level;
		}
		else {
			tmp = get_parent(Mtree->root[Mtree->current], tmp);
			level++;
		}
	}
}

int level_of_tree(TREEs* Mtree, TNODE* search, int* level) {
	
	if (search == NULL) {
		return;
	}

	level_of_tree(Mtree, search->left, level);
	level_of_tree(Mtree, search->right, level);

	if (level_of_node(Mtree, search) > *level){
		*level = level_of_node(Mtree, search);
	}
}

int delete_node(TREEs* Mtree, TNODE* target) {
	if (target->left != NULL) {
		printf("  [Error] Target is parent node\n");
		return 0;
	}

	if (Mtree->root[Mtree->current] == target) {
		Mtree->root[Mtree->current] = NULL;
		
		printf("  Delete finished : %c\n", target->data);
		free(target);

		return 1;
	}
	else {
		TNODE* tmp = get_parent(Mtree->root[Mtree->current], target);

		if (tmp->left == target) {
			tmp->left = tmp->left->right;
			
			printf("  Delete finished : %c\n", target->data);
			free(target);
		}
		else {
			tmp = tmp->left;
			while (tmp->right != target) {
				tmp = tmp->right;
			}
			tmp->right = tmp->right->right;

			printf("  Delete finished : %c\n", target->data);
			free(target);
		}
	}
	return 0;
}

void get_ancestors(TREEs* Mtree, TNODE* target) {

	if (target == Mtree->root[Mtree->current]) {
		printf("  [Error] Root has no ancestor\n");
		return;
	}

	TNODE* tmp = target;
	printf("  ");

	while (1) {
		tmp = get_parent(Mtree->root[Mtree->current], tmp);

		printf("%c ", tmp->data);

		if (tmp == Mtree->root[Mtree->current]) {
			break;
		}
	}

	printf("\n");

}

void get_descendants(TNODE* target) {

	if (target->left == NULL) {
		printf("  [Error] No child (leaf node)\n");
		return;
	}

	TNODE* tmp = target->left;

	printf("  (");

	while (tmp) {
		printf("%c", tmp->data);

		if (tmp->left != NULL) {
			print(target, tmp);
		}
		if (tmp->right != NULL) {
			printf(",");
		}
		tmp = tmp->right;
	}

	printf(")\n");
}

int degree_of_node(TNODE* target) {
	int degree = 0;
	
	TNODE* search = target->left;

	while (search != NULL) {
		degree++;
		search = search->right;
	}

	return degree;
}

void degree_of_tree(TNODE* search, int* degree) {
	if (search == NULL) {
		return;
	}
	degree_of_tree(search->left, degree);
	degree_of_tree(search->right, degree);

	if (degree_of_node(search) > *degree) {
		*degree = degree_of_node(search);
	}
}

int count_node(TNODE* search) {
	if (search == NULL) {
		return 0;
	}

	return count_node(search->left) + count_node(search->right) + 1;
}

void insert_sibling(TREEs* Mtree, TNODE* target, char data) {
	TNODE* new = (TNODE*)malloc(sizeof(TNODE));
	new->data = data;
	new->left = NULL;
	new->right = NULL;

	if (!Mtree->type) {
		if (target->right != NULL) {
			printf("  [Error] Binary tree can't have three child\n");
			return;
		}
	}
	TNODE* tmp = target;
	while (tmp->right) {
		tmp = tmp->right;
	}
	tmp->right = new;
}

void join_trees(TREEs* Mtree, char data, int index1, int index2) {
	if (Mtree->root[index1] == NULL || Mtree->root[index2] == NULL) {
		printf("  [Error] Please check index\n");
	}

	create(Mtree, data);
	TNODE* left = copy(Mtree->root[index1]);
	TNODE* right = copy(Mtree->root[index2]);

	Mtree->root[Mtree->current]->left = left;
	left->right = right;
}

TNODE* copy(TNODE* search) {
	if (search == NULL) {
		return NULL;
	}
	else {
		TNODE* new = (TNODE*)malloc(sizeof(TNODE));
		new->data = search->data;
		new->left = NULL;
		new->right = NULL;

		new->left = copy(search->left);
		new->right = copy(search->right);

		return new;
	}
}

/*
void join_trees(TREEs* Mtree, char data, int index1, int index2) {
	if (Mtree->root[index1] == NULL || Mtree->root[index2] == NULL) {
		printf("  [Error] Please check index\n");
	}

	create(Mtree, data);

	Mtree->root[Mtree->current]->left = Mtree->root[index1];
	Mtree->root[Mtree->current]->left->right = Mtree->root[index2];
}
*/

void clear(TNODE* search) {
	if (search == NULL) {
		return;
	}
	clear(search->left);
	clear(search->right);

	free(search);
}
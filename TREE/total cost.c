#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

typedef struct tnode {
	int cost;
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
void create(TREEs*, int);
void insert_node(TREEs*, TNODE*, int);
TNODE* search(TNODE*, int);
void moveIndex(TREEs*, int);
void print(TNODE*, TNODE*);
int delete_node(TREEs*, TNODE*);
void clear(TNODE*);
TNODE* get_parent(TNODE*, TNODE*);
void total_cost(TNODE*, TNODE*, int*);

int main() {

	printf("\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("\t      C O M M A N D   H E L P E R									\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  *** You Can Insert Number ONLY in ( 0 ~ 99 ) ***					\n");
	printf("\n");
	printf("  +^@      : Create new tree with root @							\n");
	printf("             (you can create up to 10)								\n");
	printf("  +A(B)    : Insert B as child of A									\n");
	printf("             (+A(B,C,D) unavailable, just insert one by one)		\n");
	printf("  T        : Print current tree										\n");
	printf("  M@       : Move to tree index of @								\n");
	printf("  -@       : Delete node which has data @							\n");
	printf("             (You can only delete leaf node)						\n");
	printf("  K        : Clear all tree                                         \n");
	printf("  &@       : Calculate total                                        \n");
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
						break;
					}
					else if ('0' <= answer[i + 3] && answer[i + 3] <= '9'){ //두자리 수인 경우
						create(Mtree, (answer[i + 2] - '0') * 10 + answer[i + 3] - '0');
						i += 3;
					}
					else { //한자리 수인 경우
						create(Mtree, answer[i + 2] - '0');
						i += 2;
					}
					
				}
				else if (answer[i + 2] == '(') { //한자리 수 node의 child로 insert 하는 경우, 하나씩밖에 추가 못함
					TNODE* target = search(Mtree->root[Mtree->current], answer[i + 1] - '0');

					if (target == NULL) {
						printf("  [Error] Can't find %d\n", answer[i + 1] - '0');
						while (answer[i] != ')')
							i++;
						continue;
					}

					if ('0' <= answer[i + 4] && answer[i + 4] <= '9') { //insert 하는 데이터가 두자리 수인 경우
						if (search(Mtree->root[Mtree->current], (answer[i + 3] - '0') * 10 + answer[i + 4] - '0') != NULL) {
							printf("  [Error] %d already exist\n", (answer[i + 3] - '0') * 10 + answer[i + 4] - '0');
							continue;
						}
						insert_node(Mtree, target, (answer[i + 3] - '0') * 10 + answer[i + 4] - '0');
					}
					else { //insert 하는 데이터가 한자리 수인 경우
						if (search(Mtree->root[Mtree->current], (answer[i + 3] - '0') != NULL)) {
							printf("  [Error] %d already exist\n", (answer[i + 3] - '0'));
							continue;
						}
						insert_node(Mtree, target, (answer[i + 3] - '0'));
					}
					while (answer[i] != ')')
						i++;
				}
				else if (answer[i + 3] == '(') { //두자리 수 node의 child로 insert 하는 경우
					TNODE* target = search(Mtree->root[Mtree->current], (answer[i + 1] - '0') * 10 + answer[i + 2] - '0');

					if (target == NULL) {
						printf("  [Error] Can't find %d\n", (answer[i + 1] - '0') * 10 + answer[i + 2] - '0');
						while (answer[i] != ')')
							i++;
						continue;
					}
					if ('0' <= answer[i + 5] && answer[i + 5] <= '9') { //insert하는 데이터가 두자리 수인 경우
						if (search(Mtree->root[Mtree->current], (answer[i + 4] - '0') * 10 + answer[i + 5] - '0') != NULL) {
							printf("  [Error] %d already exist\n", (answer[i + 4] - '0') * 10 + answer[i + 5] - '0');
							continue;
						}
						insert_node(Mtree, target, (answer[i + 4] - '0') * 10 + answer[i + 5] - '0');
					}
					else { //insert하는 데이터가 한자리 수인 경우
						if (search(Mtree->root[Mtree->current], (answer[i + 4] - '0') != NULL)) {
							printf("  [Error] %d already exist\n", (answer[i + 4] - '0'));
							continue;
						}
						insert_node(Mtree, target, (answer[i + 4] - '0'));
					}
					while (answer[i] != ')')
						i++;
				}
				else {
					printf("  [Error] Check your command\n");
					break;
				}
			}
			else if (answer[i + 1] != '^' && Mtree->count == 0) {
				printf("  [Error] There is nothing\n");
				break;
			}
			else if (answer[i] == 'T') {
				continue;
			}
			else if (answer[i] == 'M') {
				moveIndex(Mtree, answer[i + 1] - '0');
				i++;
			}

			else if (answer[i] == '-') {
				if ('0' <= answer[i + 2] && answer[i + 2] <= '9') { //지우려는 수가 두자리 수인 경우
					TNODE* target = search(Mtree->root[Mtree->current], (answer[i + 1] - '0') * 10 + answer[i + 2] - '0');

					if (target == NULL) {
						printf("  [Error] Can't find %d\n", (answer[i + 1] - '0') * 10 + answer[i + 2] - '0');

						i += 2;
						continue;
					}
					int signal = delete_node(Mtree, target);

					if (signal) {
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

					i += 2;				
				}
				else { //지우려는 수가 한자리 수인 경우
					TNODE* target = search(Mtree->root[Mtree->current], answer[i + 1] - '0');

					if (target == NULL) {
						printf("  [Error] Can't find %d\n", answer[i + 1] - '0');

						i++;
						continue;
					}
					int signal = delete_node(Mtree, target);

					if (signal) {
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

			else if (answer[i] == '&') {
				if ('0' <= answer[i + 2] && answer[i + 2] <= '9') { //두자리 수 node의 path를 계산하여 total 값을 계산할 경우
					TNODE* target = search(Mtree->root[Mtree->current], (answer[i + 1] - '0')*10 + answer[i+2] - '0');

					if (target == NULL) {
						printf("  [Error] Can't find %d\n", (answer[i + 1] - '0') * 10 + answer[i + 2] - '0');

						i += 2;
						continue;
					}

					int total = 0;
					total_cost(Mtree->root[Mtree->current], target, &total);

					printf("  Total cost <from %d to root> is %d\n", (answer[i + 1] - '0') * 10 + answer[i + 2] - '0', total);
					i += 2;
				}
				else { //한자리 수 node의 path를 계산하여 total 값을 계산할 경우
					TNODE* target = search(Mtree->root[Mtree->current], answer[i + 1] - '0');

					if (target == NULL) {
						printf("  [Error] Can't find %d\n", answer[i + 1] - '0');

						i += 1;
						continue;
					}

					int total = 0;
					total_cost(Mtree->root[Mtree->current], target, &total);

					printf("  Total cost <from %d to root> is %d\n", answer[i + 1] - '0', total);
					i += 1;
				}
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

void create(TREEs* Mtree, int data) {
	TNODE* new = (TNODE*)malloc(sizeof(TNODE));
	new->cost = data;
	new->left = NULL;
	new->right = NULL;

	Mtree->root[Mtree->count] = new;
	Mtree->current = Mtree->count;
	Mtree->count++;
}

void insert_node(TREEs* Mtree, TNODE* target, int data) {
	TNODE* new = (TNODE*)malloc(sizeof(TNODE));
	new->cost = data;
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

TNODE* search(TNODE* tmp1, int data) {
	if (tmp1 == NULL) {
		return NULL;
	}
	if (tmp1->cost == data) {
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
		printf("  (%d", root->cost);
	}
	if (root->left == NULL) {
		printf(")\n");
		return;
	}

	printf("(");

	while (tmp2) {
		printf("%d", tmp2->cost);

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

int delete_node(TREEs* Mtree, TNODE* target) {
	if (target->left != NULL) {
		printf("  [Error] Target is parent node\n");
		return 0;
	}

	if (Mtree->root[Mtree->current] == target) {
		Mtree->root[Mtree->current] = NULL;

		printf("  Delete finished : %d\n", target->cost);
		free(target);

		return 1;
	}
	else {
		TNODE* tmp = get_parent(Mtree->root[Mtree->current], target);

		if (tmp->left == target) {
			tmp->left = tmp->left->right;

			printf("  Delete finished : %d\n", target->cost);
			free(target);
		}
		else {
			tmp = tmp->left;
			while (tmp->right != target) {
				tmp = tmp->right;
			}
			tmp->right = tmp->right->right;

			printf("  Delete finished : %d\n", target->cost);
			free(target);
		}
	}
	return 0;
}

void clear(TNODE* search) {
	if (search == NULL) {
		return;
	}
	clear(search->left);
	clear(search->right);

	free(search);
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

void total_cost(TNODE* root, TNODE* target, int* total) {

	*total += target->cost;

	if (root == target)
		return;

	target = get_parent(root, target);

	total_cost(root, target, total);
}


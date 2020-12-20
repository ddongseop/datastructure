#include <stdio.h>
#include <stdlib.h> 
#pragma warning (disable:4996)

typedef struct two34node{
	int left;
	int mid;
	int right;
	struct two34node* left_child;
	struct two34node* left_mid_child;
	struct two34node* right_mid_child;
	struct two34node* right_child;
}NODE;

typedef struct two34tree {
	NODE* root;
	int OnOff;
}T34;

int StN(char[], int*); //String(char[]) to Number(int)
void create(T34*, int);
void node_initialize(NODE*);
int node_data_count(NODE*);
void maxroot_split(NODE*);
void maxchild_1parent_split(NODE*, NODE*);
void maxchild_2parent_split(NODE*, NODE*);
void insert_to_leaf(NODE*, int);
int compare(int, NODE*);
NODE* search_position(int, NODE*);
void insert_to_234(NODE*, int);
void print(T34*, NODE*);
void inorder_traversal(T34*, NODE*);
void reverse_traversal(T34*, NODE*);
int get_min(NODE*);
int get_max(NODE*);
void find_path(T34*, int);
NODE* search_position(int, NODE*);
int height_of_node(NODE*, NODE*);
void height(NODE*, NODE*, int*);
NODE* get_parent(NODE*, NODE*);
int get_right_child(T34*, int);
int get_left_child(T34*, int);
void count_node(NODE*, int*);
int get_mid_child(T34*, int, int);
void clear(T34*);
int destroy(T34*);

void case1_delete_leaf_2data(NODE*, int);
NODE* get_immediate_sibling_node(T34*, NODE*);
void delete_underflow_2moresibling_transfer_withright(T34*, NODE*);
void delete_underflow_2moresibling_transfer_withleft(T34*, NODE*);
void delete_underflow_1sibling_merge_withrightleft_p3(T34*, NODE*);
void delete_underflow_1sibling_merge_withrightleft_p2(T34*, NODE*);
NODE* delete_underflow_1sibling_merge_withrightleft_p1(T34*, NODE*);
void handle_underflow_in_root(T34*, NODE*);
void delete(T34*, int);
//http://www.mathcs.emory.edu/~cheung/Courses/323/Syllabus/Trees/2,4-delete.html
//의 그림들을 참고하여 제작한 delete 함수입니다
//handle_underflow_in_root 함수나, leaf node가 아닌 노드들을 삭제하는 경우에 대한 테스트를 충분히 진행하지 못해 오류가 발생할 수도 있습니다.
//혹시 실행 중 오류가 발생하는 케이스가 있다면 알려주시면 감사하겠습니다 (제가 확인한 케이스들에 대해서는 오류를 찾지 못했습니다)


int main() {
	printf("\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("\t      C O M M A N D   H E L P E R									\n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  +@    : Create 234 (at first), Insert Node with Data @			 \n");
	printf("          (you can insert consecutively)							 \n");
	printf("  P     : Print all Data of 234										 \n");
	printf("  I     : Inorder Traversal (From a small number)					 \n");
	printf("  R     : Right Root Left Traversal (From a large number)			 \n");
	printf("  N     : Get Minimum												 \n");
	printf("  X     : Get Maximum												 \n");
	printf("  F@    : Find Node with Data @ and Search Path						 \n");
	printf("  D@    : Delete Node with Data @									 \n");
	printf("  H     : Get Height of 234 (Start from 0)							 \n");
	printf("  G(@)  : Get Right Child of Node with Data @ 						 \n");
	printf("  L(@)  : Get Left Child of Node with Data @						 \n");
	printf("  #     : Count Node                                                 \n");
	printf("  M(a,b): Get Mid Child of Node with Data 'a' and 'b'				 \n");
	printf("  C     : Clear 234                                                  \n");
	printf("  Q     : Destroy 234												 \n");
	printf("─────────────────────────────────────────────────────────────\n");
	printf("  The length of command must be shorter than 30						 \n");
	printf("  Make a space between commands										 \n");
	printf("  Programmed by 2019310181 Dongseop Lee								 \n");
	printf("─────────────────────────────────────────────────────────────\n");

	int signal = 1;
	char answer[30];
	T34* M234 = (T34*)malloc(sizeof(T34));
	M234->root = NULL;
	M234->OnOff = 0;

	while (signal) {
		printf("  >> ");
		gets(answer);

		for (int i = 0; answer[i] != '\0'; i++) {
			if (answer[i] == '+' && M234->OnOff == 0) {
				i++;
				create(M234, StN(answer, &i));
				i--;
			}
			else if (answer[i] == '+' && M234->OnOff == 1) {
				i++;
				insert_to_234(M234->root, StN(answer, &i));
				i--;
			}
			else if (answer[i] == 'P') {
				continue;
			}
			else if (answer[i] == 'I') {
				inorder_traversal(M234, M234->root);
			}
			else if (answer[i] == 'R') {
				reverse_traversal(M234, M234->root);
			}
			else if (answer[i] == 'N') {
				if (M234->OnOff) {
					printf("  Minimum : %d\n", get_min(M234->root));
				}
				else
					printf("  [Error] Empty 234\n");
			}
			else if (answer[i] == 'X') {
				if (M234->OnOff) {
					printf("  Maximum : %d\n", get_max(M234->root));
				}
				else
					printf("  [Error] Empty 234\n");
			}
			else if (answer[i] == 'F') {
				if (M234->OnOff == 0) {
					printf("  [Error] Empty 234\n");
					continue;
				}
				i++;
				int tgt = StN(answer, &i);
				NODE* tmp = search_position(tgt, M234->root);
				i--;

				if (tmp == NULL) {
					printf("  [Error] Not Exist!\n");
				}
				else {
					find_path(M234, tgt);
				}
			}
			else if (answer[i] == 'H') {
				if (M234->OnOff == 0) {
					printf("  [Error] Empty 234\n");
					continue;
				}
				int Height;
				height(M234->root, M234->root, &Height);
				printf("  Height of 234 is %d\n", Height);
			}
			else if (answer[i] == 'G') {
				if (M234->OnOff == 0) {
					printf("  [Error] Empty 234\n");
					continue;
				}
				i += 2;
				int tmp = StN(answer, &i);
				int rc = get_right_child(M234, tmp);

				if (rc == -1) {
					printf("  [Error] Can't find target\n");
					continue;
				}
				else if (rc == -2) {
					printf("  Right child of %d is NULL\n", tmp);
				}
				else
					printf("  Right child of %d is %d\n", tmp, rc);
			}
			else if (answer[i] == 'L') {
				if (M234->OnOff == 0) {
					printf("  [Error] Empty 234\n");
					continue;
				}
				i += 2;
				int tmp = StN(answer, &i);
				int lc = get_left_child(M234, tmp);

				if (lc == -1) {
					printf("  [Error] Can't find target\n");
					continue;
				}
				else if (lc == -2) {
					printf("  Left child of %d is NULL\n", tmp);
				}
				else
					printf("  Left child of %d is %d\n", tmp, lc);
			}
			else if (answer[i] == '#') {
				int count = 0;
				count_node(M234->root, &count);
				printf("  Count of 234 is %d\n", count);
			}
			else if (answer[i] == 'M') {
				if (M234->OnOff == 0) {
					printf("  [Error] Empty 234\n");
					continue;
				}
				i += 2;
				int left = StN(answer, &i);
				i++;
				int right = StN(answer, &i);

				int mc = get_mid_child(M234, left, right);
				if (mc == -1) {
					continue;
				}
				else
					printf("  Mid child of %d and %d is %d\n", left, right, mc);
			}
			else if (answer[i] == 'D') {
				i++;
				delete(M234, StN(answer, &i));
				i--;
			}
			else if (answer[i] == 'C') {
				clear(M234);
			}
			else if (answer[i] == 'Q') {
			if (destroy(M234)) {
				printf("  System finshed\n");
				signal = 0;
			}
			}
		}
		
		if (signal && M234->OnOff == 1) {
			print(M234, M234->root);
		}
		else if (signal && M234->OnOff == 0) {
			printf("  Empty 234\n");
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

void create(T34* M234, int data) {
	NODE* new = (NODE*)malloc(sizeof(NODE));

	node_initialize(new);
	new->left = data;

	M234->root = new;
	M234->OnOff = 1;
}

void node_initialize(NODE* target) {
	target->left = -1;
	target->mid = -1;
	target->right = -1;
	target->left_child = NULL;
	target->right_child = NULL;
	target->left_mid_child = NULL;
	target->right_mid_child = NULL;
}

int node_data_count(NODE* target) {
	if (target->left == -1) { //아예 아무 데이터도 없는 노드
		return 0;
	}
	else if (target->mid == -1) { //데이터가 하나인 노드
		return 1;
	}
	else if (target->right == -1) { //데이터가 두개인 노드
		return 2;
	}
	else { //데이터가 세개인 노드
		return 3;
	}
}

void maxroot_split(NODE* target) { //루트가 꽉 차있을 경우 루트 분할
	NODE* tmp1;
	NODE* tmp2;

	tmp1 = (NODE*)malloc(sizeof(NODE));
	tmp2 = (NODE*)malloc(sizeof(NODE));

	node_initialize(tmp1);
	node_initialize(tmp2);

	tmp1->left_child = target->left_child;
	tmp1->left_mid_child = target->left_mid_child;

	tmp2->left_child = target->right_mid_child;
	tmp2->left_mid_child = target->right_child;

	target->left_child = tmp1;
	target->left_mid_child = tmp2;

	tmp1->left = target->left;
	tmp2->left = target->right;

	target->left = target->mid;
	target->mid = -1;
	target->right = -1;

	target->right_mid_child = NULL;
	target->right_child = NULL;
}

void maxchild_1parent_split(NODE* parent, NODE* child){//데이터가 하나인 노드의 자식에 꽉 차있는 노드가 있을 때 분할
	NODE* tmp1;
	NODE* tmp2;

	tmp1 = (NODE*)malloc(sizeof(NODE));
	node_initialize(tmp1);

	if (parent->left_child == child) { //왼쪽 노드가 max일 때
		tmp2 = parent->left_mid_child;
		parent->left_mid_child = tmp1;
		parent->mid = parent->left;
		parent->left = child->mid;
		parent->right_mid_child = tmp2;
	}
	else if (parent->left_mid_child == child) { //왼쪽 중간 노드가 max일 때
		parent->right_mid_child = tmp1;
		parent->mid = child->mid;
	}
	tmp1->left = child->right;
	tmp1->left_child = child->right_mid_child;
	tmp1->left_mid_child = child->right_child;
	child->right_mid_child = NULL;
	child->right_child = NULL;
	child->mid = -1;
	child->right = -1;
	parent->right_child = NULL;
}

void maxchild_2parent_split(NODE* parent, NODE* child) {
	NODE* tmp;
	tmp = (NODE*)malloc(sizeof(NODE));
	node_initialize(tmp);

	if (parent->left_child == child) { //왼쪽 노드가 max일 때
		parent->right_child = parent->right_mid_child;
		parent->right_mid_child = parent->left_mid_child;
		parent->left_mid_child = tmp;
		parent->right = parent->mid;
		parent->mid = parent->left;
		parent->left = child->mid;
		tmp->left = child->right;
		tmp->left_child = child->right_mid_child;
		tmp->left_mid_child = child->right_child;

		child->right_mid_child = NULL;
		child->right_child = NULL;
		child->mid = -1;
		child->right = -1;
	}
	else if (parent->left_mid_child == child) { //왼쪽 중간 노드가 max일 때
		parent->right_child = parent->right_mid_child;
		parent->right_mid_child = tmp;
		parent->right = parent->mid;
		parent->mid = child->mid;
		tmp->left = child->right;
		tmp->left_child = child->right_mid_child;
		tmp->left_mid_child = child->right_child;

		child->right_mid_child = NULL;
		child->right_child = NULL;
		child->mid = -1;
		child->right = -1;
	}
	else if (parent->right_mid_child == child) {
		parent->right_child = tmp;
		parent->right = child->mid;
		tmp->left = child->right;
		tmp->left_child = child->right_mid_child;
		tmp->left_mid_child = child->right_child;

		child->right_mid_child = NULL;
		child->right_child = NULL;
		child->mid = -1;
		child->right = -1;
	}
}

void insert_to_leaf(NODE* target, int data) {
	if (target->mid == -1) {
		if (data > target->left) {
			target->mid = data;
		}
		else {
			target->mid = target->left;
			target->left = data;
		}
	}
	else if (target->right == -1) {
		if (data > target->mid) {
			target->right = data;
		}
		else if (data > target->left) {
			target->right = target->mid;
			target->mid = data;
		}
		else if (data < target->left) {
			target->right = target->mid;
			target->mid = target->left;
			target->left = data;
		}
	}
}

int compare(int data, NODE* target) {
	if (data == target->left || data == target->mid || data == target->right) {
		return 0; // 이미 있는 데이터인 경우
	}
	else if (target->left_child == NULL) {
		return -1; //leaf인 경우
	}
	else if (data < target->left) {
		return 1; //left_child인 경우
	}
	else if (data > target->left && data < target->mid || target->mid == -1) {
		return 2; //left_mid_child인 경우
	}
	else if (data > target->mid && data < target->right || target->right == -1) {
		return 3; //right_mid_child인 경우
	}
	else if (data > target->right) {
		return 4; //right_child인 경우
	}
	else
		return -2;
}

NODE* search_position(int data, NODE* root) {
	NODE* tmp = root;
	while (1) {
		switch (compare(data, tmp)) {
			case 0:
				return tmp;
			case -1:
				return NULL;
			case 1:
				tmp = tmp->left_child;
				break;
			case 2:
				tmp = tmp->left_mid_child;
				break;
			case 3:
				tmp = tmp->right_mid_child;
				break;
			case 4:
				tmp = tmp->right_child;
				break;
		}
	}
}

void find_path(T34* M234, int data) {
	printf("  Root");

	NODE* tmp = M234->root;

	while (tmp->left != data && tmp->mid != data && tmp->right != data) {
		if (tmp->right != -1 && data > tmp->right) {
			printf(" > Right");
			tmp = tmp->right_child;
		}
		else if (tmp->mid != -1 && data > tmp->mid) {
			printf(" > MidRight");
			tmp = tmp->right_mid_child;
		}
		else if (tmp->left != -1 && data > tmp->left) {
			printf(" > MidLeft");
			tmp = tmp->left_mid_child;
		}
		else { 
			printf(" > Left");
			tmp = tmp->left_child;
		}
	}

	printf("\n");
}

void insert_to_234(NODE* root, int data) {
	NODE* parent;
	NODE* child;

	if (node_data_count(root) == 3) {
		maxroot_split(root);
	}
	child = root;
	parent = NULL;

	while (1) {
		if (node_data_count(child) == 3) {
			if (node_data_count(parent) == 1) {
				maxchild_1parent_split(parent, child);
			}
			else {
				maxchild_2parent_split(parent, child);
			}
			child = parent;
		}
		parent = child;
		switch (compare(data, child)) {
			case 0:
				printf("  [Error] Already Exist\n");
				return;
			case -1:
				insert_to_leaf(child, data);
				return;
			case 1:
				child = child->left_child;
				break;
			case 2:
				child = child->left_mid_child;
				break;
			case 3:
				child = child->right_mid_child;
				break;
			case 4:
				child = child->right_child;
				break;
		}
	}
}

void print(T34* M234, NODE* tmp) {
	if (tmp == NULL) {
		return;
	}

	if (M234->root == tmp) {
		printf("  (");
	}
	if (node_data_count(tmp) > 1) {
		printf("(");
	}

	if (node_data_count(tmp) == 1) {
		printf("%d", tmp->left);
	}
	else if (node_data_count(tmp) == 2) {
		printf("%d", tmp->left);
		printf(",");
		printf("%d", tmp->mid);
	}
	else if (node_data_count(tmp) == 3) {
		printf("%d", tmp->left);
		printf(",");
		printf("%d", tmp->mid);
		printf(",");
		printf("%d", tmp->right);
	}

	if (node_data_count(tmp) > 1) {
		printf(")");
	}

	if (tmp->left_child != NULL || tmp->left_mid_child != NULL || tmp->right_mid_child != NULL || tmp->right_child != NULL) {
		printf("((");
		print(M234, tmp->left_child);
		printf(")(");
		print(M234, tmp->left_mid_child);
		printf(")(");
		print(M234, tmp->right_mid_child);
		printf(")(");
		print(M234, tmp->right_child);
		printf("))");
	}

	if (M234->root == tmp) {
		printf(")\n");
	}
}

void inorder_traversal(T34* M234, NODE* tmp) {
	if (tmp == NULL) {
		return;
	}
	if (M234->root == tmp) {
		printf("  ");
	}

	inorder_traversal(M234, tmp->left_child);
	if (tmp->left != -1) {
		printf("%d ", tmp->left);
	}
	inorder_traversal(M234, tmp->left_mid_child);
	if (tmp->mid != -1) {
		printf("%d ", tmp->mid);
	}
	inorder_traversal(M234, tmp->right_mid_child);
	if (tmp->right != -1) {
		printf("%d ", tmp->right);
	}
	inorder_traversal(M234, tmp->right_child);

	if (M234->root == tmp) {
		printf("\n");
	}
}

void reverse_traversal(T34* M234, NODE* tmp) {
	if (tmp == NULL) {
		return;
	}
	if (M234->root == tmp) {
		printf("  ");
	}

	reverse_traversal(M234, tmp->right_child);
	if (tmp->right != -1) {
		printf("%d ", tmp->right);
	}
	reverse_traversal(M234, tmp->right_mid_child);
	if (tmp->mid != -1) {
		printf("%d ", tmp->mid);	
	}
	reverse_traversal(M234, tmp->left_mid_child);
	if (tmp->left != -1) {
		printf("%d ", tmp->left);
	}
	reverse_traversal(M234, tmp->left_child);
	
	if (M234->root == tmp) {
		printf("\n");
	}
}

int get_min(NODE* root) {
	NODE* tmp = root;

	while (tmp->left_child != NULL) {
		tmp = tmp->left_child;
	}

	return tmp->left;
}

int get_max(NODE* root) {
	NODE* tmp = root;

	while (1) {
		if (tmp->left_child == NULL) {
			break;
		}
		else if (node_data_count(tmp) == 1) {
			tmp = tmp->left_mid_child;
		}
		else if (node_data_count(tmp) == 2) {
			tmp = tmp->right_mid_child;
		}
		else {
			tmp = tmp->right_child;
		}
	}

	if (node_data_count(tmp) == 1) {
		return tmp->left;
	}
	else if (node_data_count(tmp) == 2) {
		return tmp->mid;
	}
	else {
		return tmp->right;
	}
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

	height(root, tmp->left_child, Height);
	height(root, tmp->left_mid_child, Height);
	height(root, tmp->right_mid_child, Height);
	height(root, tmp->right_child, Height);

	if (height_of_node(root, tmp) > *Height) {
		*Height = height_of_node(root, tmp);
	}
}

NODE* get_parent(NODE* search, NODE* target) { //target이 NULL이 아니라는 것을 알고 사용

	if (search == NULL) {
		return NULL;
	}

	if (search->left_child == target || search->right_child == target || search->left_mid_child == target || search->right_mid_child == target) {
		return search;
	}

	NODE* adress;

	adress = get_parent(search->left_child, target);
	if (adress) {
		return adress;
	}

	adress = get_parent(search->left_mid_child, target);
	if (adress) {
		return adress;
	}

	adress = get_parent(search->right_mid_child, target);
	if (adress) {
		return adress;
	}

	adress = get_parent(search->right_child, target);
	if (adress) {
		return adress;
	}

	return NULL;
}

int get_right_child(T34* M234, int data) {
	NODE* target = search_position(data, M234->root);
	if (target == NULL) {
		return -1;
	}

	if (target->left == data) {
		if (target->left_mid_child == NULL) {
			return -2;
		}
		return target->left_mid_child->left;
	}
	else if (target->mid == data) {
		if (target->right_mid_child == NULL) {
			return -2;
		}
		return target->right_mid_child->left;
	}
	else {
		if (target->right_child == NULL) {
			return -2;
		}
		return target->right_child->left;
	}
}

int get_left_child(T34* M234, int data) {
	NODE* target = search_position(data, M234->root);
	if (target == NULL) {
		return -1;
	}

	if (target->left == data) {
		if (target->left_child == NULL) {
			return -2;
		}
		if (node_data_count(target->left_child) == 3) {
			return target->left_child->right;
		}
		else if (node_data_count(target->left_child) == 2) {
			return target->left_child->mid;
		}
		else {
			return target->left_child->left;
		}
	}
	else if (target->mid == data) {
		if (target->left_mid_child == NULL) {
			return -2;
		}
		if (node_data_count(target->left_mid_child) == 3) {
			return target->left_mid_child->right;
		}
		else if (node_data_count(target->left_mid_child) == 2) {
			return target->left_mid_child->mid;
		}
		else {
			return target->left_mid_child->left;
		}
	}
	else {
		if (target->right_mid_child == NULL) {
			return -2;
		}
		if (node_data_count(target->right_mid_child) == 3) {
			return target->right_mid_child->right;
		}
		else if (node_data_count(target->right_mid_child) == 2) {
			return target->right_mid_child->mid;
		}
		else {
			return target->right_mid_child->left;
		}
	}
}

void count_node(NODE* tmp, int* count) {
	if (tmp == NULL) {
		return 0;
	}
	*count += node_data_count(tmp);

	count_node(tmp->left_child, count);
	count_node(tmp->left_mid_child, count);
	count_node(tmp->right_mid_child, count);
	count_node(tmp->right_child, count);
}

int get_mid_child(T34* M234, int left, int right) {
	if (get_right_child(M234, left) == -1 || get_left_child(M234, right) == -1) {
		printf("  [Error] Can't find target\n");
		return -1;
	}
	if (get_right_child(M234, left) == -2) {
		printf("  Right child of %d is NULL\n", left);
		return -1;
	}
	if (get_left_child(M234, right) == -2) {
		printf("  Left child of %d is NULL\n", right);
		return -1;
	}
	if (right <= left) {
		printf("  Please recheck your range\n");
		return -1;
	}
	if (get_right_child(M234, left) != get_left_child(M234, right)) {
		printf("  Data of middle doesn't match\n");
		return -1;
	}
	if (get_right_child(M234, left) == get_left_child(M234, right)) {
		return get_right_child(M234, left);
	}
	else
		return -1;
}

void case1_delete_leaf_2data(NODE* target, int data) {
	if (target->left == data && node_data_count(target) == 2){
		target->left = target->mid;
		target->mid = -1;
		return;
	}
	else if (target->left == data && node_data_count(target) == 3) {
		target->left = target->mid;
		target->mid = target->right;
		target->right = -1;
		return;
	}
	else if (target->mid == data && node_data_count(target) == 2) {
		target->mid = -1;
		return;
	}
	else if (target->mid == data && node_data_count(target) == 3) {
		target->mid = target->right;
		target->right = -1;
		return;
	}
	else if (target->right == data && node_data_count(target) == 3) {
		target->right = -1;
		return;
	}
}

NODE* get_immediate_sibling_node(T34* M234, NODE* target) { //right sibling을 기준으로, 가장 오른쪽의 자식인 경우 left sibling으로
	NODE* p_target = get_parent(M234->root, target);

	if (p_target->left_child == target) {
		return p_target->left_mid_child;
	}
	else if (p_target->left_mid_child == target && node_data_count(p_target) == 1) {
		return p_target->left_child;
	}
	else if (p_target->left_mid_child == target && node_data_count(p_target) > 1) {
		return p_target->right_mid_child;
	}
	else if (p_target->right_mid_child == target && node_data_count(p_target) == 2) {
		return p_target->left_mid_child;
	}
	else if (p_target->right_mid_child == target && node_data_count(p_target) > 2) {
		return p_target->right_child;
	}
	else if (p_target->right_child == target) {
		return p_target->right_mid_child;
	}
	else {
		printf("  [Error] Can't find immediate sibling node\n");
		return NULL;
	}
}

void delete_underflow_2moresibling_transfer_withright(T34* M234, NODE* target) {
	NODE* parent = get_parent(M234->root, target);
	NODE* sibling = get_immediate_sibling_node(M234, target);

	if (node_data_count(parent) == 1 && node_data_count(sibling) == 2) {
		int parent_key = parent->left;
		target->left = parent_key;
		parent->left = sibling->left;
		sibling->left = sibling->mid;
		sibling->mid = -1;
		target->left_mid_child = sibling->left_child;
		sibling->left_child = sibling->left_mid_child;
		sibling->left_mid_child = sibling->right_mid_child;
		sibling->right_mid_child = NULL;
	}
	else if (node_data_count(parent) == 1 && node_data_count(sibling) == 3) {
		int parent_key = parent->left;
		target->left = parent_key;
		parent->left = sibling->left;
		sibling->left = sibling->mid;
		sibling->mid = sibling->right;
		sibling->right = -1;
		target->left_mid_child = sibling->left_child;
		sibling->left_child = sibling->left_mid_child;
		sibling->left_mid_child = sibling->right_mid_child;
		sibling->right_mid_child = sibling->right_child;
		sibling->right_child = NULL;
	}
	else if (node_data_count(parent) == 2 && node_data_count(sibling) == 2 && parent->left_child == target) {
		int parent_key = parent->left;
		target->left = parent_key;
		parent->left = sibling->left;
		sibling->left = sibling->mid;
		sibling->mid = -1;
		target->left_mid_child = sibling->left_child;
		sibling->left_child = sibling->left_mid_child;
		sibling->left_mid_child = sibling->right_mid_child;
		sibling->right_mid_child = NULL;
	}
	else if (node_data_count(parent) == 2 && node_data_count(sibling) == 3 && parent->left_child == target) {
		int parent_key = parent->left;
		target->left = parent_key;
		parent->left = sibling->left;
		sibling->left = sibling->mid;
		sibling->mid = sibling->right;
		sibling->right = -1;
		target->left_mid_child = sibling->left_child;
		sibling->left_child = sibling->left_mid_child;
		sibling->left_mid_child = sibling->right_mid_child;
		sibling->right_mid_child = sibling->right_child;
		sibling->right_child = NULL;
	}
	else if (node_data_count(parent) == 2 && node_data_count(sibling) == 2 && parent->left_mid_child == target) {
		int parent_key = parent->mid;
		target->left = parent_key;
		parent->mid = sibling->left;
		sibling->left = sibling->mid;
		sibling->mid = -1;
		target->left_mid_child = sibling->left_child;
		sibling->left_child = sibling->left_mid_child;
		sibling->left_mid_child = sibling->right_mid_child;
		sibling->right_mid_child = NULL;
	}
	else if (node_data_count(parent) == 2 && node_data_count(sibling) == 3 && parent->left_mid_child == target) {
		int parent_key = parent->mid;
		target->left = parent_key;
		parent->mid = sibling->left;
		sibling->left = sibling->mid;
		sibling->mid = sibling->right;
		sibling->right = -1;
		target->left_mid_child = sibling->left_child;
		sibling->left_child = sibling->left_mid_child;
		sibling->left_mid_child = sibling->right_mid_child;
		sibling->right_mid_child = sibling->right_child;
		sibling->right_child = NULL;
	}
	else if (node_data_count(parent) == 3 && node_data_count(sibling) == 2 && parent->left_child == target) {
		int parent_key = parent->left;
		target->left = parent_key;
		parent->left = sibling->left;
		sibling->left = sibling->mid;
		sibling->mid = -1;
		target->left_mid_child = sibling->left_child;
		sibling->left_child = sibling->left_mid_child;
		sibling->left_mid_child = sibling->right_mid_child;
		sibling->right_mid_child = NULL;
	}
	else if (node_data_count(parent) == 3 && node_data_count(sibling) == 3 && parent->left_child == target) {
		int parent_key = parent->left;
		target->left = parent_key;
		parent->left = sibling->left;
		sibling->left = sibling->mid;
		sibling->mid = sibling->right;
		sibling->right = -1;
		target->left_mid_child = sibling->left_child;
		sibling->left_child = sibling->left_mid_child;
		sibling->left_mid_child = sibling->right_mid_child;
		sibling->right_mid_child = sibling->right_child;
		sibling->right_child = NULL;
	}
	else if (node_data_count(parent) == 3 && node_data_count(sibling) == 2 && parent->left_mid_child == target) {
		int parent_key = parent->mid;
		target->left = parent_key;
		parent->mid = sibling->left;
		sibling->left = sibling->mid;
		sibling->mid = -1;
		target->left_mid_child = sibling->left_child;
		sibling->left_child = sibling->left_mid_child;
		sibling->left_mid_child = sibling->right_mid_child;
		sibling->right_mid_child = NULL;
	}
	else if (node_data_count(parent) == 3 && node_data_count(sibling) == 3 && parent->left_mid_child == target) {
		int parent_key = parent->mid;
		target->left = parent_key;
		parent->mid = sibling->left;
		sibling->left = sibling->mid;
		sibling->mid = sibling->right;
		sibling->right = -1;
		target->left_mid_child = sibling->left_child;
		sibling->left_child = sibling->left_mid_child;
		sibling->left_mid_child = sibling->right_mid_child;
		sibling->right_mid_child = sibling->right_child;
		sibling->right_child = NULL;
	}
	else if (node_data_count(parent) == 3 && node_data_count(sibling) == 2 && parent->right_mid_child == target) {
		int parent_key = parent->right;
		target->left = parent_key;
		parent->right = sibling->left;
		sibling->left = sibling->mid;
		sibling->mid = -1;
		target->left_mid_child = sibling->left_child;
		sibling->left_child = sibling->left_mid_child;
		sibling->left_mid_child = sibling->right_mid_child;
		sibling->right_mid_child = NULL;
	}
	else if (node_data_count(parent) == 3 && node_data_count(sibling) == 2 && parent->right_mid_child == target) {
		int parent_key = parent->right;
		target->left = parent_key;
		parent->right = sibling->left;
		sibling->left = sibling->mid;
		sibling->mid = sibling->right;
		sibling->right = -1;
		target->left_mid_child = sibling->left_child;
		sibling->left_child = sibling->left_mid_child;
		sibling->left_mid_child = sibling->right_mid_child;
		sibling->right_mid_child = sibling->right_child;
		sibling->right_child = NULL;
	}
	else {
		printf("  [Error] Can't handle this case\n"); //case를 다 잡았다고 생각합니다만, 만약의 오류로 시스템이 죽는 것을 방지 (밑의 동일한 Error들도 같은 이유로 넣었습니다)
	}
	return;

}

void delete_underflow_2moresibling_transfer_withleft(T34* M234, NODE* target) {
	NODE* parent = get_parent(M234->root, target);
	NODE* sibling = get_immediate_sibling_node(M234, target);

	if (node_data_count(parent) == 1 && node_data_count(sibling) == 2) {
		int parent_key = parent->left;
		target->left = parent_key;
		parent->left = sibling->mid;
		sibling->mid = -1;
		target->left_mid_child = sibling->right_mid_child;
		sibling->right_mid_child = NULL;

	}
	else if (node_data_count(parent) == 1 && node_data_count(sibling) == 3) {
		int parent_key = parent->left;
		target->left = parent_key;
		parent->left = sibling->right;
		sibling->right = -1;
		target->left_mid_child = sibling->right_child;
		sibling->right_child = NULL;
	}
	else if (node_data_count(parent) == 2 && node_data_count(sibling) == 2) {
		int parent_key = parent->mid;
		target->left = parent_key;
		parent->mid = sibling->mid;
		sibling->mid = -1;
		target->left_mid_child = sibling->right_mid_child;
		sibling->right_mid_child = NULL;
	}
	else if (node_data_count(parent) == 2 && node_data_count(sibling) == 3) {
		int parent_key = parent->mid;
		target->left = parent_key;
		parent->mid = sibling->right;
		sibling->right  = -1;
		target->left_mid_child = sibling->right_child;
		sibling->right_child = NULL;
	}
	else if (node_data_count(parent) == 3 && node_data_count(sibling) == 2) {
		int parent_key = parent->right;
		target->left = parent_key;
		parent->right = sibling->mid;
		sibling->mid = -1;
		target->left_mid_child = sibling->right_mid_child;
		sibling->right_mid_child = NULL;
	}
	else if (node_data_count(parent) == 3 && node_data_count(sibling) == 3) {
		int parent_key = parent->right;
		target->left = parent_key;
		parent->right = sibling->right;
		sibling->right = -1;
		target->left_mid_child = sibling->right_child;
		sibling->right_child = NULL;
	}
	else {
		printf("  [Error] Can't handle this case\n");
	}
	return;
}

//parent 개수, left/right, target의 상대적 위치에 따라 케이스 분류
void delete_underflow_1sibling_merge_withrightleft_p3(T34* M234, NODE* target) {
	NODE* parent = get_parent(M234->root, target);
	NODE* sibling = get_immediate_sibling_node(M234, target);

	target->left = -1;
	if (parent->left_child == target) {
		sibling->right_mid_child = sibling->left_mid_child;
		sibling->mid = sibling->left;
		sibling->left_mid_child = sibling->left_child;
		sibling->left = parent->left;
		sibling->left_child = target->left_child;
		parent->left = parent->mid;
		parent->mid = parent->right;
		parent->right = -1;
		parent->left_child = parent->left_mid_child;
		parent->left_mid_child = parent->right_mid_child;
		parent->right_mid_child = parent->right_child;
		parent->right_child = NULL;
	}
	else if (parent->left_mid_child == target) {
		sibling->right_mid_child = sibling->left_mid_child;
		sibling->mid = sibling->left;
		sibling->left_mid_child = sibling->left_child;
		sibling->left = parent->mid;
		sibling->left_child = target->left_child;
		parent->mid = parent->right;
		parent->right = -1;
		parent->left_mid_child = parent->right_mid_child;
		parent->right_mid_child = parent->right_child;
		parent->right_child = NULL;
	}
	else if (parent->right_mid_child == target) {
		sibling->right_mid_child = sibling->left_mid_child;
		sibling->mid = sibling->left;
		sibling->left_mid_child = sibling->left_child;
		sibling->left = parent->right;
		sibling->left_child = target->left_child;
		parent->right = -1;
		parent->right_mid_child = parent->right_child;
		parent->right_child = NULL;
	}
	else if (parent->right_child == target) {
		sibling->mid = parent->right;
		sibling->right_mid_child = target->left_child;
		parent->right = -1;
		parent->right_child = NULL;
	}
	else {
		printf("  [Error] Can't handle this case\n");
		return;
	}
	free(target);
	return;
}

void delete_underflow_1sibling_merge_withrightleft_p2(T34* M234, NODE* target) {
	NODE* parent = get_parent(M234->root, target);
	NODE* sibling = get_immediate_sibling_node(M234, target);

	target->left = -1;
	if (parent->left_child == target) {
		sibling->right_mid_child = sibling->left_mid_child;
		sibling->mid = sibling->left;
		sibling->left_mid_child = sibling->left_child;
		sibling->left = parent->left;
		sibling->left_child = target->left_child;
		parent->left = parent->mid;
		parent->mid = -1;
		parent->left_child = parent->left_mid_child;
		parent->left_mid_child = parent->right_mid_child;
		parent->right_mid_child = NULL;
	}
	else if (parent->left_mid_child == target) {
		sibling->right_mid_child = sibling->left_mid_child;
		sibling->mid = sibling->left;
		sibling->left_mid_child = sibling->left_child;
		sibling->left = parent->mid;
		sibling->left_child = target->left_child;
		parent->mid  = -1;
		parent->left_mid_child = parent->right_mid_child;
		parent->right_mid_child =  NULL;
	}
	else if (parent->right_mid_child == target) {
		sibling->mid = parent->mid;
		sibling->right_mid_child = target->left_child;
		parent->mid = -1;
		parent->right_mid_child = NULL;
	}
	else {
		printf("  [Error] Can't handle this case\n");
		return;
	}
	free(target);
	return;
}

NODE* delete_underflow_1sibling_merge_withrightleft_p1(T34* M234, NODE* target) {
	NODE* parent = get_parent(M234->root, target);
	NODE* sibling = get_immediate_sibling_node(M234, target);

	target->left = -1;
	if (parent->left_child == target) {
		sibling->right_mid_child = sibling->left_mid_child;
		sibling->mid = sibling->left;
		sibling->left_mid_child = sibling->left_child;
		sibling->left = parent->left;
		sibling->left_child = target->left_child;
		parent->left = -1;
		parent->left_child = parent->left_mid_child;
		parent->left_mid_child = NULL;
	}
	else if (parent->left_mid_child == target) {
		sibling->mid = parent->mid;
		sibling->right_mid_child = target->left_child;
		parent->left = -1;
		parent->left_mid_child = NULL;
	}
	else {
		printf("  [Error] Can't handle this case\n");
		return NULL;
	}
	free(target);
	return parent;
}

void handle_underflow_in_root(T34* M234, NODE* target) {
	if (target == M234->root) {
		M234->root = target->left_child;
		target->left_child = NULL;
		free(target);
		return;
	}
	if (node_data_count(get_immediate_sibling_node(M234, target)) >= 2) {
		NODE* parent = get_parent(M234->root, target);

		if ((node_data_count(parent) == 1 && parent->left_mid_child == target) 
			|| (node_data_count(parent) == 2 && parent->right_mid_child == target) 
			|| (node_data_count(parent) == 3 && parent->right_child == target)) 
		{
			delete_underflow_2moresibling_transfer_withleft(M234, target);
		}
		else {
			delete_underflow_2moresibling_transfer_withright(M234, target);
		}
	}
	else if (node_data_count(get_immediate_sibling_node(M234, target)) < 2) {
		NODE* parent = get_parent(M234->root, target);

		if (node_data_count(parent) == 3){
			delete_underflow_1sibling_merge_withrightleft_p3(M234, target);
		}
		else if (node_data_count(parent) == 2){
			delete_underflow_1sibling_merge_withrightleft_p2(M234, target);
		}
		else if (node_data_count(parent) == 1) {
			NODE* tmp = delete_underflow_1sibling_merge_withrightleft_p1(M234, target);
			handle_underflow_in_root(M234, tmp);
		}
	}

}

void delete(T34* M234, int data) {

	NODE* target = search_position(data, M234->root);
	if (target == NULL) {
		printf("  [Error] Can't find target\n");
		return;
	}

	NODE* heir = NULL;
	int heir_data;

	if (M234->root == target && node_data_count(target) == 1 && target->left_child == NULL) {
		target->left = -1;
		free(target);
		M234->root = NULL;
		M234->OnOff = 0;
		return;
	}

	if (target->left_child != NULL) {
		if (target->left == data) {
			heir = target->left_child;
		}
		else if (target->mid == data) {
			heir = target->left_mid_child;
		}
		else {
			heir = target->right_mid_child;
		}

		heir_data = get_max(heir);
		heir = search_position(heir_data, M234->root);

		if (target->left == data) {
			target->left = heir_data;
		}
		else if (target->mid == data) {
			target->mid = heir_data;
		}
		else if (target->right == data) {
			target->right = heir_data;
		}
	}

	if (heir == NULL) {
		NODE* parent = get_parent(M234->root, target);
		if (node_data_count(target) >= 2) {
			case1_delete_leaf_2data(target, data);
			return;
		}
		else if (node_data_count(get_immediate_sibling_node(M234, target)) >= 2) {
			if ((node_data_count(parent) == 1 && parent->left_mid_child == target)
				|| (node_data_count(parent) == 2 && parent->right_mid_child == target)
				|| (node_data_count(parent) == 3 && parent->right_child == target))
			{
				delete_underflow_2moresibling_transfer_withleft(M234, target);
			}
			else {
				delete_underflow_2moresibling_transfer_withright(M234, target);
			}
		}
		else if (node_data_count(get_immediate_sibling_node(M234, target)) == 1) {
			if (node_data_count(parent) == 3) {
				delete_underflow_1sibling_merge_withrightleft_p3(M234, target);
			}
			else if (node_data_count(parent) == 2) {
				delete_underflow_1sibling_merge_withrightleft_p2(M234, target);
			}
			else {
				handle_underflow_in_root(M234, delete_underflow_1sibling_merge_withrightleft_p1(M234, target));
			}
		}
		else {
			printf("  [Error] Can't handle this case\n");
		}
	}
	else {
		NODE* parent = get_parent(M234->root, heir);

		if (node_data_count(heir) >= 2) {
			case1_delete_leaf_2data(heir, heir_data);
		}
		else if (node_data_count(get_immediate_sibling_node(M234, heir)) >= 2) {
			if ((node_data_count(parent) == 1 && parent->left_mid_child == heir)
				|| (node_data_count(parent) == 2 && parent->right_mid_child == heir)
				|| (node_data_count(parent) == 3 && parent->right_child == heir))
			{
				delete_underflow_2moresibling_transfer_withleft(M234, heir);
			}
			else {
				delete_underflow_2moresibling_transfer_withright(M234, heir);
			}
		}
		else if (node_data_count(get_immediate_sibling_node(M234, heir)) == 1) {
			if (node_data_count(parent) == 3) {
				delete_underflow_1sibling_merge_withrightleft_p3(M234, heir);
			}
			else if (node_data_count(parent) == 2) {
				delete_underflow_1sibling_merge_withrightleft_p2(M234, heir);
			}
			else {
				handle_underflow_in_root(M234, delete_underflow_1sibling_merge_withrightleft_p1(M234, heir));
			}
		}
		else {
			printf("  [Error] Can't handle this case\n");
		}
	}
}

void clear(T34* M234) {
	if (M234->root == NULL) {
		printf("  [Error] Already Empty\n");
		return;
	}

	while (1) {
		if (M234->root == NULL) {
			printf("  Clear finished\n");
			break;
		}

		delete(M234, M234->root->left);
	}
}

int destroy(T34* M234) {
	if (M234->root != NULL) {
		printf("  [Error] Please clear 234 first\n");
		return 0;
	}

	free(M234);
	return 1;
}
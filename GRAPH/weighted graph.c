#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

typedef struct vertex {
	struct vertex* next;
	char data;
	int visited;
	struct edge* connect;
	int count_edge;
}VERTEX;

typedef struct edge {
	VERTEX* vertex;
	int weight; //가중치를 저장
	struct edge* more;
}EDGE;

typedef struct graph {
	int count_vertex;
	VERTEX* head;
}GRAPH;

void create(GRAPH*);
void print(GRAPH*);
void insert_vertex(GRAPH*, char);
int is_exist_vertex(GRAPH*, char);
int is_exist_edge(GRAPH*, char, char);
void add_edge(GRAPH*, char, char, int);
VERTEX* search_vertex(GRAPH*, char);
int degree_of_vertex(GRAPH*, char);
int is_connected(GRAPH*);
int is_empty(GRAPH*);
void adjacent(GRAPH*, char);
void delete_vertex(GRAPH*, char);
int path_exist(GRAPH*, VERTEX*, VERTEX*);
void visited_initialize(GRAPH*);
void find_shortest_path_dijsktra(GRAPH*, VERTEX*, VERTEX*);
int num_of_vertex(GRAPH*);
int num_of_edge(GRAPH*);
void delete_edge(GRAPH*, char, char);
void rename_vertex(GRAPH*, char, char);
void delete_vertex_for_clear(GRAPH*, char);
void clear(GRAPH*);
int destory(GRAPH*);
int StN(char[], int*); //String(char[]) to Number(int)


int main() {
	printf("\n");
	printf("─────────────────────────────────────────────────────────────────────────────\n");
	printf("\t      C O M M A N D   H E L P E R									\n");
	printf("─────────────────────────────────────────────────────────────────────────────\n");
	printf("  G        : Create Graph												\n");
	printf("  +@       : Insert Vertex with Data @                                  \n");
	printf("             (you can insert consecutively)							    \n");
	printf("  E(A,B,@) : Add Edge which connects Vertices A and B and set Weight @	\n");
	printf("  L        : Print all Data and Weight of Graph							\n");
	printf("  V(@)     : Get Degree of Vertex @									    \n");
	printf("  C        : Check Graph is Connected									\n");
	printf("  N        : Check Graph is Empty										\n");
	printf("  A(@)     : Print Adjacent of Vertex @ and Weight						\n");
	printf("  -@       : Delete Vertex @											\n");
	printf("  P(A,B)   : Check Existence of Path from Vertex A to B				    \n");
	printf("             * (If Path Exist, Find shortest Path and with ** Dijsktra) \n");
	printf("  X        : Get Num of Vertex                                          \n");
	printf("  H        : Get Num of Edge                                            \n");
	printf("  D(A,B)   : Delete Edge which connects Vertices A and B  				\n");
	printf("  R(A,Z)   : Rename Vertex A to Z										\n");
	printf("  ?@       : * Check Graph has Vertex @                                 \n");
	printf("  K        : Clear Graph                                                \n");
	printf("  Q        : * Destroy Graph and Quit									\n");
	printf("─────────────────────────────────────────────────────────────────────────────\n");
	printf("  The length of command must be shorter than 40						   \n");
	printf("  Make a space between commands										   \n");
	printf("  Programmed by 2019310181 Dongseop Lee								   \n");
	printf("─────────────────────────────────────────────────────────────────────────────\n");

	printf("  Please create Graph by command 'G' first\n");
	int signal = 1;
	char answer[30];
	GRAPH* MG = (GRAPH*)malloc(sizeof(GRAPH));


	while (signal) {
		printf("  >> ");
		gets(answer);

		for (int i = 0; answer[i] != '\0'; i++) {
			if (answer[i] == 'G') {
				create(MG);
			}
			else if (answer[i] == '+') {
				i++;
				insert_vertex(MG, answer[i]);
			}
			else if (answer[i] == 'E') {
				int data1, data2;
				data1 = answer[i + 2];
				data2 = answer[i + 4];
				i += 6;
				add_edge(MG, data1, data2, StN(answer, &i));
				
			}
			else if (answer[i] == 'L') {
				continue;
			}
			else if (answer[i] == 'V') {
				int degree = degree_of_vertex(MG, answer[i + 2]);
				if (degree >= 0) {
					printf("  Degree of %c is %d\n", answer[i + 2], degree);
				}
				i += 3;
			}
			else if (answer[i] == 'C') {
				if (is_connected(MG)) {
					printf("  Graph is Connected\n");
				}
				else
					printf("  Graph is Not Connected\n");
			}
			else if (answer[i] == 'N') {
				if (is_empty(MG)) {
					printf("  Graph is Empty\n");
				}
				else {
					printf("  Graph is Not Empty\n");
				}
			}
			else if (answer[i] == 'A') {
				adjacent(MG, answer[i + 2]);
				i += 3;
			}
			else if (answer[i] == '-') {
				delete_vertex(MG, answer[i + 1]);
				i++;
			}
			else if (answer[i] == 'P') {
				VERTEX* d1 = search_vertex(MG, answer[i + 2]);
				VERTEX* d2 = search_vertex(MG, answer[i + 4]);
				if (d1 == NULL || d2 == NULL) {
					i += 5;
					continue;
				}
				if (path_exist(MG, d1, d2)) {
					printf("  Path from %c to %c Exist\n", d1->data, d2->data);
					find_shortest_path_dijsktra(MG, d1, d2);
				}
				else {
					printf("  Path from %c to %c Not Exist\n", d1->data, d2->data);
				}
				i += 5;
				visited_initialize(MG);

			}
			else if (answer[i] == 'X') {
				printf("  Num of Vertex: %d\n", num_of_vertex(MG));
			}
			else if (answer[i] == 'H') {
				printf("  Num of Edge: %d\n", num_of_edge(MG));
			}
			else if (answer[i] == 'D') {
				delete_edge(MG, answer[i + 2], answer[i + 4]);
				i += 5;
			}
			else if (answer[i] == 'R') {
				rename_vertex(MG, answer[i + 2], answer[i + 4]);
				i += 5;
			}
			else if (answer[i] == 'K') {
				clear(MG);
			}
			else if (answer[i] == 'Q') {
				if (destroy(MG)) {
					printf("  System finshed\n");
					signal = 0;
				}
			}
			else if (answer[i] == '?') {
				int YN = is_exist_vertex(MG, answer[i + 1]);
				if (YN) {
					printf("  %c Exist in Graph\n", answer[i + 1]);
				}
				else
					printf("  %c Not Exist in Graph\n", answer[i + 1]);
				i++;
			}
		}
		if (signal)
			print(MG);
	}

	return 0;
}

void create(GRAPH* MG) {
	MG->head = NULL;
	MG->count_vertex = 0;
}

void print(GRAPH* MG) {
	VERTEX* tmp = MG->head;
	printf("  (");

	while (tmp) {
		printf("%c", tmp->data);

		EDGE* tmp2 = tmp->connect;
		while (tmp2) {
			if (tmp2 == tmp->connect) {
				printf("(");
			}
			printf("%c", tmp2->vertex->data);
			printf("(%d)", tmp2->weight);

			if (tmp2->more != NULL) {
				printf(",");
			}
			tmp2 = tmp2->more;
			if (tmp2 == NULL) {
				printf(")");
			}
		}

		if (tmp->next != NULL) {
			printf(", ");
		}
		tmp = tmp->next;
	}
	printf(")\n");
}

void insert_vertex(GRAPH* MG, char data) {
	if (!is_empty(MG) && is_exist_vertex(MG, data)) {
		printf("  [Error] Already Exist Data\n");
		return;
	}

	VERTEX* new = (VERTEX*)malloc(sizeof(VERTEX));
	new->connect = NULL;
	new->visited = 0;
	new->next = NULL;
	new->data = data;
	new->count_edge = 0;

	if (is_empty(MG)) {
		MG->head = new;
	}
	else {
		VERTEX* target = MG->head;

		while (target->next != NULL) {
			target = target->next;
		}
		target->next = new;
	}

	MG->count_vertex++;

}

int is_exist_vertex(GRAPH* MG, char data) {
	VERTEX* tmp = MG->head;

	while (1) {
		if (tmp == NULL) {
			return 0;
		}
		if (tmp->data == data) {
			return 1;
		}
		tmp = tmp->next;
	}
}

int is_exist_edge(GRAPH* MG, char data1, char data2) { //쓸 때 data 둘 다 이미 있는 거 알고 있어야 함
	VERTEX* tmp = search_vertex(MG, data1);

	EDGE* tmp2 = tmp->connect;

	while (1) {
		if (tmp2 == NULL) {
			return 0;
		}

		if (tmp2->vertex->data == data2) {
			return 1;
		}
		tmp2 = tmp2->more;
	}
}

void add_edge(GRAPH* MG, char data1, char data2, int weight) { //E(A,B,@)
	if (!is_exist_vertex(MG, data1) || !is_exist_vertex(MG, data2)) {
		printf("  [Error] Vertex doesn't Exist\n");
		return;
	}
	if (is_exist_edge(MG, data1, data2)) {
		printf("  [Error] Edge already Exist\n");
		return;
	}

	VERTEX* target1 = search_vertex(MG, data1);
	VERTEX* target2 = search_vertex(MG, data2);

	EDGE* new1 = (EDGE*)malloc(sizeof(EDGE));
	new1->more = NULL;
	new1->vertex = target2;
	new1->weight = weight;

	if (target1->connect == NULL) {
		target1->connect = new1;
	}
	else {
		EDGE* target3 = target1->connect;

		while (target3->more != NULL) {
			target3 = target3->more;
		}

		target3->more = new1;
	}
	target1->count_edge++;

	EDGE* new2 = (EDGE*)malloc(sizeof(EDGE));
	new2->more = NULL;
	new2->vertex = target1;
	new2->weight = weight;

	if (target2->connect == NULL) {
		target2->connect = new2;
	}
	else {
		EDGE* target4 = target2->connect;

		while (target4->more != NULL) {
			target4 = target4->more;
		}

		target4->more = new2;
	}
	target2->count_edge++;
}

VERTEX* search_vertex(GRAPH* MG, char data) {
	if (!is_exist_vertex(MG, data)) {
		printf("  [Error] Vertex doesn't Exist\n");
		return NULL;
	}
	VERTEX* result = MG->head;

	while (1) {
		if (result->data == data) {
			return result;
		}
		result = result->next;
	}
}

int degree_of_vertex(GRAPH* MG, char data) {
	VERTEX* tmp = search_vertex(MG, data);

	if (tmp == NULL) {
		return -1;
	}
	else {
		return tmp->count_edge;
	}
}

int is_connected(GRAPH* MG) {
	VERTEX* tmp = MG->head;

	while (tmp) {
		if (tmp->count_edge == 0) {
			return 0;
		}
		tmp = tmp->next;
	}
	return 1;
}

int is_empty(GRAPH* MG) {
	if (MG->head == NULL) {
		return 1;
	}
	else
		return 0;
}

void adjacent(GRAPH* MG, char data) {

	VERTEX* target = search_vertex(MG, data);
	if (target == NULL) {
		return;
	}
	EDGE* tmp = target->connect;

	printf("  {");
	while (1) {
		if (tmp == NULL) {
			break;
		}
		printf("%c", tmp->vertex->data);
		printf("(%d)", tmp->weight);

		if (tmp->more != NULL) {
			printf(", ");
		}
		tmp = tmp->more;
	}
	printf("}\n");
}

void delete_vertex(GRAPH* MG, char data) {
	VERTEX* target = search_vertex(MG, data);
	if (target == NULL) {
		return;
	}
	if (target->connect == NULL) {
		if (MG->head == target) {
			MG->head = MG->head->next;
			free(target);
		}
		else {
			VERTEX* tmp = MG->head;
			while (tmp->next != target) {
				tmp = tmp->next;
			}
			tmp->next = tmp->next->next;
			free(target);
		}
	}
	else {
		int A;
		printf("  Target has Edge, 1.Ignore and Delete  2. Don't Delete\n  : ");
		scanf("%d", &A);
		getchar();

		if (A == 2) {
			return;
		}
		else {

			EDGE* dt = target->connect;
			printf("  Deleted Edge: (");
			printf("%c", dt->vertex->data);
			for (int i = 1; i < target->count_edge; i++) {
				dt = dt->more;
				printf(",%c", dt->vertex->data);
			}
			printf(")\n");

			EDGE* e_target = target->connect;
			VERTEX* v_target = NULL; //가야하는 vertex
			EDGE* e_v_target = NULL; //가야하는 vertex에서 해당 edge를 찾음

			EDGE* d_e_v_target = NULL;
			EDGE* d_e_target = NULL;

			while (e_target) {
				v_target = search_vertex(MG, e_target->vertex->data);
				e_v_target = v_target->connect;

				if (e_v_target->vertex->data == target->data) {
					d_e_v_target = e_v_target;
					v_target->connect = v_target->connect->more;
				}
				else {
					while (e_v_target->more->vertex->data != target->data) {
						e_v_target = e_v_target->more;
					}
					d_e_v_target = e_v_target->more;
					e_v_target->more = e_v_target->more->more;
				}

				v_target->count_edge--;
				free(d_e_v_target);

				d_e_target = e_target;
				target->connect = target->connect->more;
				e_target = target->connect;

				target->count_edge--;
				free(d_e_target);
			}
			if (MG->head == target) {
				MG->head = MG->head->next;
				free(target);
			}
			else {
				VERTEX* tmp = MG->head;
				while (tmp->next != target) {
					tmp = tmp->next;
				}
				tmp->next = tmp->next->next;
				free(target);
			}
		}
	}
	MG->count_vertex--;
}

int path_exist(GRAPH* MG, VERTEX* d1, VERTEX* d2) {
	if (d1 == d2) {
		return 1;
	}

	EDGE* tmp = d1->connect;
	d1->visited = 1;

	while (tmp) {
		if (!tmp->vertex->visited) {
			if (path_exist(MG, tmp->vertex, d2))
				return 1;
		}
		tmp = tmp->more;
	}

	return 0;
}

void visited_initialize(GRAPH* MG) {
	VERTEX* tmp = MG->head;

	for (int i = 0; i < MG->count_vertex; i++) {
		tmp->visited = 0;
		tmp = tmp->next;
	}
}

void find_shortest_path_dijsktra(GRAPH* MG, VERTEX* start, VERTEX* end) {
	int distance[100];
	int check[100] = { 0 };
	char back[100] = { '\0' };
	char path[100] = { '\0' };
	int exist[100] = { 0 };

	int cycle = 0;
	int min;
	int i, now;

	for (i = 0; i < 100; i++) {
		distance[i] = 9999999; //infinite
	}
	distance[(start->data - 'A')] = 0;


	VERTEX* tmp = MG->head;
	while (tmp){
		exist[(tmp->data - 'A')] = 1;
		tmp = tmp->next;
	}

	while (1) {
		min = 9999999;
		for (i = 0; i < 100; i++) {
			if (exist[i] == 1 && distance[i] < min && check[i] == 0) {
				min = distance[i];
				now = i;
			}
		}
		check[now] = 1;
		tmp = search_vertex(MG, now + 'A');

		EDGE* tmp2 = tmp->connect;
		

		while (tmp2) {
			if (check[tmp2->vertex->data - 'A'] == 0 && (min + tmp2->weight) < distance[tmp2->vertex->data - 'A']) {
				distance[tmp2->vertex->data - 'A'] = (min + tmp2->weight);
				back[tmp2->vertex->data - 'A'] = (now + 'A');
			}

			tmp2 = tmp2->more;
		}

		if ((now + 'A') == end->data) {
			break;
		}
	}
	char endd = end->data;
	char startt = start->data;
	
	i = 0;
	while (endd != startt) {
		path[i] = back[(endd - 'A')];
		endd = back[(endd - 'A')];
		i++;
	}

	printf("  Path: ");
	int j = i - 1;

	while (j > -1) {
		printf("%c -> ", path[j]);
		j--;
	}

	printf("%c\n", end->data);

	printf("  Shortest Distance: %d\n", distance[end->data - 'A']);

}

int num_of_vertex(GRAPH* MG) {
	return MG->count_vertex;
}

int num_of_edge(GRAPH* MG) {
	int count = 0;

	VERTEX* tmp = MG->head;

	for (int i = 0; i < num_of_vertex(MG); i++) {
		count += tmp->count_edge;
		tmp = tmp->next;
	}

	return (count / 2);
}

void delete_edge(GRAPH* MG, char data1, char data2) {
	VERTEX* target1 = search_vertex(MG, data1);
	VERTEX* target2 = search_vertex(MG, data2);

	if (target1 == NULL || target2 == NULL) {
		return;
	}

	if (!is_exist_edge(MG, data1, data2)) {
		printf("  [Error] Edge already Not Exist\n");
		return;
	}

	EDGE* tmp1 = target1->connect;
	EDGE* del1 = NULL;

	if (tmp1->vertex->data == data2) {
		del1 = tmp1;
		target1->connect = target1->connect->more;
	}
	else {
		while (tmp1->more->vertex->data != data2) {
			tmp1 = tmp1->more;
		}
		del1 = tmp1->more;
		tmp1->more = tmp1->more->more;
	}

	target1->count_edge--;
	free(del1);

	EDGE* tmp2 = target2->connect;
	EDGE* del2 = NULL;

	if (tmp2->vertex->data == data1) {
		del2 = tmp2;
		target2->connect = target2->connect->more;
	}
	else {
		while (tmp2->more->vertex->data != data1) {
			tmp2 = tmp2->more;
		}
		del2 = tmp2->more;
		tmp2->more = tmp2->more->more;
	}

	target2->count_edge--;
	free(del2);

}

void rename_vertex(GRAPH* MG, char old, char new) {
	VERTEX* target_v = search_vertex(MG, old);
	if (target_v == NULL) {
		return;
	}

	if (is_exist_vertex(MG, new)) {
		printf("  [Error] New Data already Exist\n");
		return;
	}

	target_v->data = new;

	EDGE* target_e = target_v->connect;
	EDGE* search = NULL;

	while (target_e) {
		search = target_e->vertex->connect;
		while (search) {
			if (search->vertex->data == old) {
				search->vertex->data = new;
			}
			search = search->more;
		}
		target_e = target_e->more;
	}
}

void clear(GRAPH* MG) {
	if (is_empty(MG)) {
		printf("  [Error] Already Empty\n");
		return;
	}
	while (!is_empty(MG)) {
		delete_vertex_for_clear(MG, MG->head->data);
	}
	printf("  Clear Finished\n");
}

void delete_vertex_for_clear(GRAPH* MG, char data) {
	VERTEX* target = search_vertex(MG, data);
	if (target == NULL) {
		return;
	}
	if (target->connect == NULL) {
		if (MG->head == target) {
			MG->head = MG->head->next;
			free(target);
		}
		else {
			VERTEX* tmp = MG->head;
			while (tmp->next != target) {
				tmp = tmp->next;
			}
			tmp->next = tmp->next->next;
			free(target);
		}
	}
	else {
		EDGE* dt = target->connect;

		EDGE* e_target = target->connect;
		VERTEX* v_target = NULL; //가야하는 vertex
		EDGE* e_v_target = NULL; //가야하는 vertex에서 해당 edge를 찾음

		EDGE* d_e_v_target = NULL;
		EDGE* d_e_target = NULL;

		while (e_target) {
			v_target = search_vertex(MG, e_target->vertex->data);
			e_v_target = v_target->connect;

			if (e_v_target->vertex->data == target->data) {
				d_e_v_target = e_v_target;
				v_target->connect = v_target->connect->more;
			}
			else {
				while (e_v_target->more->vertex->data != target->data) {
					e_v_target = e_v_target->more;
				}
				d_e_v_target = e_v_target->more;
				e_v_target->more = e_v_target->more->more;
			}
			v_target->count_edge--;
			free(d_e_v_target);

			d_e_target = e_target;
			target->connect = target->connect->more;
			e_target = target->connect;

			target->count_edge--;
			free(d_e_target);
		}
		if (MG->head == target) {
			MG->head = MG->head->next;
			free(target);
		}
		else {
			VERTEX* tmp = MG->head;
			while (tmp->next != target) {
				tmp = tmp->next;
			}
			tmp->next = tmp->next->next;
			free(target);
		}
	}
	MG->count_vertex--;
}

int destroy(GRAPH* MG) {
	if (!is_empty(MG)) {
		printf("  [Error] Please clear GRAPH first\n");
		return 0;
	}

	free(MG);
	return 1;
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
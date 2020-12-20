#include <stdio.h>
#pragma warning (disable:4996)

int current = -1; //current point�� ��Ÿ���� ���� ����
int size = 0; //�迭�� �ִ� ���� ���� ��Ÿ���� ���� ����
void insert(char arr[], char data); //�迭�� ���Ҹ� �߰��ϴ� �Լ�
void traverse_front(char arr[], int count); //�迭�� ó������ current point�� �̵��ϴ� �Լ�
void traverse_rear(char arr[], int count); //�迭�� ���������� current point�� �̵��ϴ� �Լ�
void delete(char arr[]); //current point�� ���Ҹ� �����ϴ� �Լ�
char get_data(char arr[]); //current point�� ���Ҹ� return�ϴ� �Լ�
void replace(char arr[], char new_data); //current point�� ���Ҹ� ���ο� ���ҷ� �ٲٴ� �Լ�
void empty(char arr[]); //�迭�� �ִ� ���ҵ��� ��� �����ϴ� �Լ�
int data_count(char arr[]); //�迭�� ���� ���� ��ȯ�ϴ� �Լ�
void move(char arr[], int new_position); //current point�� ���Ҹ� �ٸ� ��ġ�� �ű�� �Լ�
void print(char arr[]); //�迭�� �ִ� ���ҵ��� ��� ����ϴ� �Լ�
void reverse(char arr[]); //�迭�� �ִ� ���ҵ��� ������ �Ųٷ� ������ �Լ�
void split(char arr[]); //current point�� �ִ� ���Ҹ� �����ϴ� �Լ� (ex) a b c (current point: b) -> a b b c
void capital(char arr[]); //current point�� ���Ұ� �빮���̸� �ҹ��ڷ�, �ҹ����̸� �빮�ڷ� �ٲٴ� �Լ�

int main() {
	char my_array[30]; //���ҵ��� ������� �迭(���ڿ�): create(array)
	char answer[30]; //command�� ���� �迭(���ڿ�)
	int i;
	int count = 0; //<NNN�� ���� ��Ȳ���� N�� ��� ���Դ��� ���� ����

	printf("\n");
	printf("��������������������������������������������������������������������������������������������������������������������������\n");
	printf("\t      C O M M A N D   H E L P E R \n");
	printf("��������������������������������������������������������������������������������������������������������������������������\n");
	printf("  + : Insert factor                                     \n");
	printf("      ex) +a+b+c+d                                      \n");
	printf("  < : Move current point to first                       \n");
	printf("  > : Move current point to last                        \n");
	printf("  <N : Move current point to first and move to next     \n");
	printf("  >P : Move current point to last and move to prev      \n");
	printf("  - : Delete current factor								\n");
	printf("  @ : Get data of current point					        \n");
	printf("  =? : Replace data of current point to ?		        \n");
	printf("  E : Delete all factors						        \n");
	printf("  M? : Move data of current point to index ?		    \n");
	printf("	   ex) M2: Move data of current point to index 2	\n");
	printf("	   ex) Mn: Move data of current point to last		\n");
	printf("	   ex) MP: Move data of current point to prev   	\n");
	printf("	   ex) MN: Move data of current point to next   	\n");
	printf("  L : Print all factors							     	\n");
	printf("* R : Reverse factors of my array				     	\n");
	printf("	   ex) a b c d -> d c b a						   	\n");
	printf("* S : Duplicate data of current point			     	\n");
	printf("	   ex) a b c (current point: b) -> a b b c 		   	\n");
	printf("* C : Upper or lower the letter			     		    \n");
	printf("	   ex) a b c (current point: b) -> a B c 		   	\n");
	printf("	   ex) a B c (current point: B) -> a b c 		   	\n");
	printf("��������������������������������������������������������������������������������������������������������������������������\n");
	printf("  This program can handle only 30 factors				\n");
	printf("  Don't make a space between commands					\n");
	printf("  Programmed by 2019310181 Dongseop Lee					\n");
	printf("��������������������������������������������������������������������������������������������������������������������������\n");
	while (1) {
		printf("  >> ");
		count = 0; //�Ź� �ʱ�ȭ
		scanf("%s", answer); //command �Է¹���
		
		//���Ҹ� �߰��� ��
		if (answer[0] == '+') {
			int a = 1;
			while (1) {
				insert(my_array, answer[a]);
				current++;
				size++;
				if (answer[a + 1] == '+') {
					a = a + 2;
				}
				else
					break;
			}
			print(my_array);
		} 
		//current point�� �� ������ �̵��� �� (�߰��� <N, <-, <M2, <Mn, <MN ����)
		if (answer[0] == '<') {
			int b = 1;
			while (1) {
				if (answer[b] == 'N') {
					count++;
					b++;
				}
				else
					break;
			}
			traverse_front(my_array, count);
			if (answer[b] == '-') {
				delete(my_array);
			}
			else if (answer[b] == 'M') {
				int np;
				if (answer[b+1] == 'n') {
					np = size - 1;
				}
				else if (answer[b+1] == 'P') {
					np = current - 1;
				}
				else if (answer[b+1] == 'N') {
					np = current + 1;
				}
				else {
					np = answer[b+1] - '0';
				}
				move(my_array, np);
			}
	
			print(my_array);
		}
		//current point�� �� �ڷ� �̵��� �� (�߰��� >P, >-, >M2, >Mn, >MP ����)
		if (answer[0] == '>') {
			int c = 1;
			while (1) {
				if (answer[c] == 'P') {
					count++;
					c++;
				}
				else
					break;
			}
			traverse_rear(my_array, count);
			if (answer[c] == '-') {
				delete(my_array);
			}
			else if (answer[c] == 'M') {
				int np;
				if (answer[c+1] == 'n') {
					np = size - 1;
				}
				else if (answer[c+1] == 'P') {
					np = current - 1;
				}
				else if (answer[c+1] == 'N') {
					np = current + 1;
				}
				else {
					np = answer[c+1] - '0';
				}
				move(my_array, np);
			}
			print(my_array);
		}
		//current point�� ���Ҹ� ������ ��
		if (answer[0] == '-') {
			delete(my_array);
			print(my_array);
		}
		//current point�� ���� ����ϰ� ���� ��
		if (answer[0] == '@') {
			printf("  %c\n", get_data(my_array));
		}
		//current point�� ���Ҹ� �ٸ� ���ҷ� ��ü�ϰ� ���� ��
		if (answer[0] == '=') {
			replace(my_array, answer[1]);
			print(my_array);
		}
		//�迭�� ���ҵ��� ��� ������ ��
		if (answer[0] == 'E') {
			empty(my_array);
			printf("  empty array\n");
		}
		//current point�� ���Ҹ� �ٸ� ��ġ�� �ű�� ���� ��
		if (answer[0] == 'M') {
			int np;
			if (answer[1] == 'n') {
				np = size - 1;
			}
			else if (answer[1] == 'P') {
				np = current - 1;
			}
			else if (answer[1] == 'N') {
				np = current + 1;
			}
			else {
				np = answer[1] - '0';
			}
			move(my_array, np);
			
			print(my_array);
		}
		//�迭�� ���ҵ��� ��� ����ϰ� ���� ��
		if (answer[0] == 'L') {
			print(my_array);
		}
		//�迭�� ���ҵ��� ������ ������ ���� ��
		if (answer[0] == 'R') {
			reverse(my_array);
			print(my_array);
		}
		//current point�� ���Ҹ� �����ϰ� ���� ��
		if (answer[0] == 'S') {
			split(my_array);
			print(my_array);
		}
		//current point�� ���Ұ� �빮�ڸ� �ҹ��ڷ�, �ҹ��ڸ� �빮�ڷ� �ٲٰ� ���� ��
		if (answer[0] == 'C') {
			capital(my_array);
			print(my_array);
		}
	}//while
	
	return 0;
}
	void insert(char arr[], char data) {
		if (current + 1 == size) { //�迭�� ���� ���Ҹ� �߰��� ��
			arr[current + 1] = data;
		}
		else //�迭�� ���� �ƴ� ���� ���Ҹ� �߰��� ��
			for (int i = size; i > current+1; i--) {
				arr[i] = arr[i - 1];
			}
			arr[current + 1] = data;
	}
	void traverse_front(char arr[], int count) {
		current = 0;
		if (count >= size) { //N�� �����ϰ� �ԷµǾ��� ��
			printf("�ִ� �̵� �Ÿ��� ������ϴ�\n");
			count = size - 1;
		}
		if (count) { //<���� N�� �ϳ��� ���� ��
			current = current + count;
		}
	}
	void traverse_rear(char arr[], int count) {
		current = size - 1;
		if (count >= size) { //P�� �����ϰ� �ԷµǾ��� ��
			printf("�ִ� �̵� �Ÿ��� ������ϴ�\n");
			count = size - 1;
		}
		if (count) { //>���� P�� �ϳ��� ���� ��
			current = current - count;
		}
	}
	void delete(char arr[]) {
		if (size <= 0) { //���̻� ���� ���Ұ� �������� ���� ��
			printf("���� �迭 ��Ұ� ���̻� �����ϴ�\n");
			return;
		}
		size--;
		for (int i = current; i < size; i++) {
			arr[i] = arr[i + 1];
		}
		if (current >= size) {//current point�� ����Ű�� ���� ���̻� ���Ұ� ���� ��
			current = 0;
			printf("�迭�� ũ�Ⱑ current point���� �۾��� current point�� 0���� �ʱ�ȭ �մϴ�\n");
		}
	}
	char get_data(char arr[]) {
		return arr[current];
	}
	void replace(char arr[], char new_data) {
		arr[current] = new_data;
	}
	void empty(char arr[]) {
		for (int i = 0; i < size; i++) {
			arr[i] = '\0';
		}
		current = -1; //�ʱ�ȭ
		size = 0; //�ʱ�ȭ
	}
	int data_count(char arr[]) {
		return size;
	}
	void move(char arr[], int new_position) {
		char temp;
		if (current == new_position) {
			printf("���� ��ġ�Դϴ�\n"); //���� ��ġ�� �����̷��� �� ���
		}
		else if (current > new_position) { //���� ��ġ���� ������ �����̷��� �� ���
			temp = arr[current];
			for (int i = current; i > new_position; i--) {
				arr[i] = arr[i - 1];
			}
			arr[new_position] = temp;
			current = new_position;
		}
		else { //���� ��ġ���� �ڷ� �����̷��� �� ���
			temp = arr[current];
			for (int i = current; i < new_position; i++) {
				arr[i] = arr[i + 1];
			}
			arr[new_position] = temp;
			current = new_position;
		}
	}
	void print(char arr[]) {
		printf("  ");
		for (int i = 0; i < size; i++) { //�迭�� ���ҵ��� ���
			printf("%c ", arr[i]);
		}
		if (size) { //�迭�� ���Ұ� �ϳ��� ������ current point�� ���
			printf("(current point: %c)\n", arr[current]);
		}
		else
			printf("empty array\n");
	}
	void reverse(char arr[]) {
		int r = (size / 2);
		char temp;
		for (int i = 0; i < r; i++) {
			temp = arr[i];
			arr[i] = arr[(size - 1) - i];
			arr[(size - 1) - i] = temp;
		}
	}
	void split(char arr[]) {
		for (int i = current + 2; i < size + 1; i++) {
			arr[i] = arr[i - 1];
		}
		arr[current + 1] = arr[current];
		size++;
		current++;
	}
	void capital(char arr[]) {
		if (arr[current] >= 'A' && arr[current] <= 'Z') { //current point�� ���Ұ� �빮���� ���
			arr[current] = arr[current] + 32;
		}
		else if (arr[current] >= 'a' && arr[current] <= 'z') { //current point�� ���Ұ� �ҹ����� ���
			arr[current] = arr[current] - 32;
		}
	}
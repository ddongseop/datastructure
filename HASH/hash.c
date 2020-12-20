#include <stdio.h>
#include <stdlib.h> 
#pragma warning (disable:4996)

int division_method(int key) {
	return (key % 137);
}

int double_hashing(int key, int count) {
	int step = 7 - (key % 7);

	return (division_method(key) + (count * step));
}

int main() {
	int hash_table[137] = { 0 };
	int key;
	int real_key;

	while (1) {
		printf("Key to Insert (0 to quit, -1 to print) >> ");
		scanf("%d", &key);

		int count = 0;

		if (key == 0) {
			break;
		}

		if (key == -1) {
			printf("{ ");
			for (int i = 0; i < 137; i++) {
				if (hash_table[i] != 0) {
					printf("[%3d]:%3d ", i, hash_table[i]);
				}
				else {
					printf("[%3d]:    ", i);
				}

				if ((i % 10) == 9) {
					printf("\n  ");
				}
			}
			printf("}\n");
			continue;
		}

		real_key = key;

		while (1) {
			if (hash_table[division_method(key)] == 0) {
				hash_table[division_method(key)] = real_key;
				printf("Double Hashing is Done %d times\n", count);
				printf("%d is inserted to Index %d\n", real_key, division_method(key));
				break;
			}
			else {
				count++;
				key = double_hashing(real_key, count);
			}
		}
	}

	return 0;
}

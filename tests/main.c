#include <stdio.h>
#include <stdbool.h>
#include "carray/carr.h"

void print_vector(CARR *vec)
{
	printf("Vector: [");

	for (size_t i = 0; i < vec->size; i++)
	{
		printf("%d", *(int*)vec->vec[i]);

		if (i < vec->size - 1)
			printf(", ");
	}

	printf("]\n");
}

int main(void)
{
	CARR vec = carr_init(4, true);

	int a = 10;
	int b = 20;
	int c = 30;
	int d = 40;

	printf("Initial vector:\n");
	print_vector(&vec);

	printf("\nPush back 10:\n");
	carr_pushBack(&vec, &a);
	print_vector(&vec);

	printf("\nPush back 20:\n");
	carr_pushBack(&vec, &b);
	print_vector(&vec);

	printf("\nPush front 30:\n");
	carr_pushFront(&vec, &c);
	print_vector(&vec);

	printf("\nReplace index 1 with 40:\n");
	carr_replaceIndex(&vec, &d, 1);
	print_vector(&vec);

	printf("\nReverse the vector\n");
	carr_reverse(&vec);
	print_vector(&vec);

	printf("\nDelete index 0:\n");
	carr_deleteIndex(&vec, 0, true);
	print_vector(&vec);

	printf("\nDestroy vector.\n");
	carr_destroy(&vec);

	return 0;
}


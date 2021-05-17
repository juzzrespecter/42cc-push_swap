//#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int	fill_stack_rand(int argc, char **argv)
{
	/*
	 * argv[1] == n de elementos a introducir ( == size )
	 * argv[2] si lo hubiera == { WORST_CASE, BEST_CASE }
	 * 
	 * seed rand() con srand()
	 * rand() [ INT_MIN, INT_MAX ]
	 * comprobar que no repite
	 * guarda cada elemento en stack como fill_stack();
	 * ret;
	 *
	 *
	 *
	 *
	 */





	int count = 0;
	int	count_2 = 0;
	time_t	t;
	int	num;

	srand((unsigned)&t);
	if (argc < 2)
	{
		printf("no");
		exit(0);
	}
	int	n = atoi(argv[1]);
	int arr[n];
	while (count < n)
	{
		num = rand() % INT_MAX;
		while (count_2 < count)
		{
			if (arr[count_2] == num)
				break ;
			count_2++;
		}
		if ( count_2 == count )
		{
			arr[count] = num;
			printf("%d ", num);
			count++;
		}
		count_2 = 0;
	}
}

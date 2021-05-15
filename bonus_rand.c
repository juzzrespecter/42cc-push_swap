//#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>

void	best_case(int n)
{
	int count = 0;

	while (count < n)
	{
		printf("%d ", count);
		count++;
	}
	exit(1);
}

void	worst_case(int n)
{
	int count = 0;

	while (count < n)
	{
		printf("%d ", n - count);
		count++;
	}
	exit(1);
}

int	main(int argc, char **argv)
{
	int count = 0;
	int	count_2 = 0;
	time_t	t;
	int	num;

	srand((unsigned)&t);
	if (argc != 3 && argc != 2)
	{
		printf("no");
		exit(0);
	}
	int	n = atoi(argv[1]);
	if (argc == 3)
	{
	if (!strcmp("BEST_CASE", argv[2]) && argc == 3)
		best_case(n);
	if (!strcmp("WORST_CASE", argv[2]) && argc == 3)
		worst_case(n);
	}
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

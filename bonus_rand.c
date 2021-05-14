//#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int	main(int argc, char **argv)
{
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

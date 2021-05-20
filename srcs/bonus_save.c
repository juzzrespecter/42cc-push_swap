#include "push_swap.h"

int	init_savefile(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY /* set open flags */);
	ft_putstr_fd("entradilla etc...\n", fd);
	return (fd);
}

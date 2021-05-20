#include "push_swap.h"

void	save_to_file(t_data *data)
{
	int	fd;
	/*
	 *
	 * open file
	 *
	 * imprimir en archivo la lista de comandos
	 * en exec_cmd: flag que monte la lista usada en checker
	 *				y meta los comandos ahi
	 *
	 * close file
	 *
	 *
	 *
	 *
	 *
	 *
	 */

	fd = open(data->filename, O_CREAT /* set open flags */);

	close(fd);
}

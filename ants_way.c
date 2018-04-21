#include "lem_in.h"

void	ants_way(t_parameters *params)
{
	t_tunnel	*tmp;
	int index;

	tmp = params->tnl;
	while (tmp)
	{
		index = -1;
		printf("ID[%d] got lenght = %d\n", tmp->id, tmp->lgt);
		while (++index < tmp->lgt)
			printf("%s ", get_node_by_id(params, tmp->path[index])->name);
		printf("\n");
		tmp = tmp->nxt;
	}
}

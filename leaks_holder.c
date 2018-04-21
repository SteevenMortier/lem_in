#include "lem_in.h"

void	leaks_holder(t_parameters *params)
{
	int		index;
	t_nodes	*tmp;

	tmp = params->node;
	index = -1;
	while (params->file[++index])
		ft_strdel(&params->file[index]);
	index = -1;
//	while (++index < params->nbr_tnl)
//		ft_memdel((void **)&params->tnl[index]);
//	ft_memdel((void **)&params->tnl);
	ft_memdel((void **)&params->file);
	ft_memdel((void **)&params->pile);
	ft_memdel((void **)&params->start_name);
	ft_memdel((void **)&params->end_name);
}
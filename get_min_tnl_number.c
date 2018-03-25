///HEADER
///HEADER
///HEADER
///HEADER
///HEADER
///HEADER
///HEADER
///HEADER
///HEADER

#include "lem_in.h"

void					get_min_tnl_number(t_parameters *params)
{
	t_nodes		*tmp;

	params->min_tnl_nbr = 4242424;
	tmp = params->node;
	while (tmp)
	{
		if (ft_strstr(params->start_name, tmp->name))
			params->min_tnl_nbr = (params->min_tnl_nbr >= tmp->nbr_links) ?
								tmp->nbr_links : params->min_tnl_nbr;
		if (ft_strstr(params->end_name, tmp->name))
			params->min_tnl_nbr = (params->min_tnl_nbr >= tmp->nbr_links) ?
								  tmp->nbr_links : params->min_tnl_nbr;
		tmp = tmp->nxt;
	}
}

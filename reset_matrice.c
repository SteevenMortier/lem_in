#include "lem_in.h"

t_tunnel	*new_tunnel(t_parameters *params, int lenght, int *tnl)
{
	t_tunnel	*new_tunnel;
	int			index;
	static int	id;

	if (!(new_tunnel = (t_tunnel *)ft_memalloc(sizeof(t_tunnel))))
		return (NULL);
	if (!(new_tunnel->path = (int *)ft_memalloc(sizeof(int) * lenght)))
		return (NULL);
	new_tunnel->lgt = lenght;
	index = -1;
	while (--lenght >= 0)
		new_tunnel->path[++index] = tnl[lenght];
	new_tunnel->nxt = NULL;
	new_tunnel->id = id;
	id += 1;
	return (new_tunnel);
}

t_tunnel	*create_tunnel(t_parameters *params, int lenhgt, int *tnl)
{
	t_tunnel	*tmp;
	t_tunnel	*save;

	if (params->tnl == NULL)
	{
		tmp = new_tunnel(params, lenhgt, tnl);
		return (tmp);
	}
	else
	{
		tmp = params->tnl;
		save = tmp;
		while (tmp->nxt)
			tmp = tmp->nxt;
		tmp->nxt = new_tunnel(params, lenhgt, tnl);
		return (save);
	}
}

void	reset_matrice(t_parameters *params, int *tnl, int for_tnl)
{
	int		x;
	int		y;

	params->tnl = create_tunnel(params, for_tnl + 1, tnl);
	x = -1;
	while (++x < params->nbr_node)
	{
		y  = -1;
		while (++y < params->nbr_node)
		{
			if (params->matrice[x][y])
			{
				params->matrice[x][y] = INF;
				params->matrice[y][x] = INF;
			}
		}
	}
	while (for_tnl >= 0)
	{
		y = -1;
		while (++y < params->nbr_node)
		{
			if (tnl[for_tnl] != get_node(params, params->start_name)->id &&
				tnl[for_tnl] != get_node(params, params->end_name)->id)
			{
				params->matrice[tnl[for_tnl]][y] = 0;
				params->matrice[y][tnl[for_tnl]] = 0;
			}
		}
//		printf("\e[32m%s \e[0m", get_node_by_id(params, tnl[for_tnl])->name);
		//ca nous le donne dans lordre la ptete faire un liste de tnl ici
		for_tnl -= 1;
	}
}

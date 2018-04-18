#include "lem_in.h"

void	check_matrice(t_parameters *params)
{
	int		x;
	int		y;
	int		nbr_links;

	x = -1;
	while (++x < params->nbr_node)
	{
		y = -1;
		nbr_links = 0;
		while (++y < params->nbr_node)
		{
			if (params->matrice[x][y] == INF)
				nbr_links += 1;
		}
		if (nbr_links < 2 && ft_strcmp(get_node_by_id(params, x)->name, params->start_name) &&
				ft_strcmp(get_node_by_id(params, x)->name, params->end_name))
		{
			y = -1;
			while (++y < params->nbr_node)
			{
				params->matrice[x][y] = 0;
				params->matrice[y][x] = 0;
			}
		}
	}
}

void	put_links(t_parameters *params, char *x, char *y)
{
	int		id_x;
	int		id_y;

	id_x = get_node(params, x)->id;
	id_y = get_node(params, y)->id;
	params->matrice[id_x][id_y] = INF;
	params->matrice[id_y][id_x] = INF;
}

void	fill_matrice(t_parameters *params, int index)
{
	char **split;
	int leaks_split;

	while (params->file[index])
	{
		leaks_split = 0;
		split = ft_strsplit(params->file[index], '-');
		put_links(params, split[0], split[1]);
		while (split[leaks_split])
		{
			ft_strdel(&split[leaks_split]);
			leaks_split += 1;
		}
		ft_memdel((void **)&split);
		index++;
	}
	check_matrice(params);
//	while (params->node)
//	{
//		printf("Node = [%s], id = [%d]\n", params->node->name, params->node->id);
//		params->node = params->node->nxt;
//	}
}
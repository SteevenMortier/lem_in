#include "lem_in.h"

t_pile	*init_pile(t_parameters *params)
{
	t_pile	*tmp;
	if (!(tmp = (t_pile *)ft_memalloc(sizeof(t_pile))))
		return NULL;
	tmp->bgn = get_node(params, params->start_name);
	tmp->end = get_node(params, params->start_name);
	return (tmp);
}

void	print_matrice(t_parameters *params)
{
	int		x;
	int		y;

	x = -1;
	while (++x < params->nbr_node)
	{
		y = -1;
		while (++y < params->nbr_node)
		{
			ft_putnbr(params->matrice[x][y]);
			ft_putchar(' ');
		}
		ft_putchar(10);
	}
}

void	get_chemin(t_parameters *params)
{
	int		x;
	int		y;
	int		current;
	int		for_tnl;
	int		tnl[1000];

	for_tnl = 0;
	current = get_node(params, params->end_name)->id;
	tnl[for_tnl] = current;
	while (current != get_node(params, params->start_name)->id)
	{
		x = -1;
		while (++x < params->nbr_node && params->matrice[x][current] != 1)
			;
		tnl[++for_tnl] = x;
		current = x;
	}
	tnl[for_tnl] = get_node(params, params->start_name)->id;
	x = -1;
	while (++x <= for_tnl)
	{
//		ft_putnbr(tnl[x]);
		printf("\e[32m %s \e[0m", get_node_by_id(params, tnl[x])->name);
	}
	printf("\n");
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
	while (--for_tnl)
	{
		y = -1;
		while (++y < params->nbr_node)
		{
			if (tnl[for_tnl] != get_node(params, params->start_name)->id &&
					tnl[for_tnl] != get_node(params, params->end_name)->id)
			params->matrice[tnl[for_tnl]][y] = 0;
			params->matrice[y][tnl[for_tnl]] = 0;
		}
	}
}

void	calcul_matrice(t_parameters *params)
{
	int		x;
	int		y;

	params->pile = init_pile(params);
	while (params->pile->bgn)
	{
		y = -1;
		x = params->pile->bgn->id;
		while (++y < params->nbr_node)
		{
			if (params->matrice[x][y] == INF)
			{
				params->pile->end->nxt_mat = get_node_by_id(params, y);
				params->pile->end = get_node_by_id(params, y);
				params->matrice[y][x] = 0;
				params->matrice[x][y] = 1;
			}
			if (params->matrice[x][get_node(params, params->end_name)->id] == INF)
				params->pile->bgn = NULL;
		}
		if (params->pile->bgn)
			params->pile->bgn = params->pile->bgn->nxt_mat;
	}
	if (params->pile)
		ft_memdel((void **)&params->pile);
}

int		check_if_needed(t_parameters *params)
{
	int		x;
	int		y;
	int		tof_start;
	int		tof_end;

	x = get_node(params, params->start_name)->id;
	tof_start = 0;
	y  = -1;
	while (++y < params->nbr_node)
	{
		if (params->matrice[x][y])
			tof_start = 1;
	}
	x = get_node(params, params->end_name)->id;
	y  = -1;
	tof_end = 0;
	while (++y < params->nbr_node)
	{
		if (params->matrice[x][y])
			tof_end = 1;
	}
	if (tof_start && tof_end)
		return (1);
	return (0);
}

void	resolve_tnl(t_parameters *params)
{
	while (check_if_needed(params))
	{
		calcul_matrice(params);
//		print_matrice(params);
		get_chemin(params);
		ft_putchar(10);
	}
}
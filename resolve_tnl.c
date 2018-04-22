/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_tnl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 08:40:11 by smortier          #+#    #+#             */
/*   Updated: 2018/04/22 08:40:13 by smortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_pile	*init_pile(t_parameters *params)
{
	t_pile	*tmp;

	if (!(tmp = (t_pile *)ft_memalloc(sizeof(t_pile))))
		return (NULL);
	tmp->bgn = get_node(params, params->start_name);
	tmp->end = get_node(params, params->start_name);
	return (tmp);
}

void	get_chemin(t_parameters *params)
{
	int		x;
	int		y;
	int		current;
	int		for_tnl;
	int		tnl[10000];

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
	params->nbr_tnl += 1;
	reset_matrice(params, tnl, for_tnl);
}

void	for_norm(t_parameters *params, int x, int y)
{
	params->matrice[y][x] = 0;
	params->matrice[x][y] = 1;
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
				for_norm(params, x, y);
			}
			if (params->matrice[x][get_node(params, params->end_name)->id]
				== INF)
				params->pile->bgn = NULL;
		}
		if (params->pile->bgn)
			params->pile->bgn = params->pile->bgn->nxt_mat;
	}
	if (params->pile)
		ft_memdel((void **)&params->pile);
}

void	resolve_tnl(t_parameters *params)
{
	while (check_if_needed(params))
	{
		calcul_matrice(params);
		get_chemin(params);
	}
}

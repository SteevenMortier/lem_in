/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_matrice.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 11:43:06 by smortier          #+#    #+#             */
/*   Updated: 2018/04/29 13:49:08 by smortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_tunnel	*new_tunnel(int lenght, int *tnl)
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
		tmp = new_tunnel(lenhgt, tnl);
		return (tmp);
	}
	else
	{
		tmp = params->tnl;
		save = tmp;
		while (tmp->nxt)
			tmp = tmp->nxt;
		tmp->nxt = new_tunnel(lenhgt, tnl);
		return (save);
	}
}

void		delete_in_matrice(t_parameters *params, int *tnl, int for_tnl)
{
	int		y;

	while (for_tnl >= 0)
	{
		if (for_tnl == 1)
		{
			params->matrice[get_node(params, params->start_name)->id]
			[get_node(params, params->end_name)->id] = 0;
			params->matrice[get_node(params, params->end_name)->id]
			[get_node(params, params->start_name)->id] = 0;
		}
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
		for_tnl -= 1;
	}
}

void		reset_matrice(t_parameters *params, int *tnl, int for_tnl)
{
	int		x;
	int		y;

	params->tnl = create_tunnel(params, for_tnl + 1, tnl);
	x = -1;
	while (++x < params->nbr_node)
	{
		y = -1;
		while (++y < params->nbr_node)
		{
			if (params->matrice[x][y])
			{
				params->matrice[x][y] = INF;
				params->matrice[y][x] = INF;
			}
		}
	}
	delete_in_matrice(params, tnl, for_tnl);
}

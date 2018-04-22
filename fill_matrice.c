/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_matrice.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 08:44:58 by smortier          #+#    #+#             */
/*   Updated: 2018/04/22 08:44:58 by smortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			nbr_links += (params->matrice[x][y] == INF) ? 1 : 0;
		if (nbr_links < 2 && ft_strcmp(get_node_by_id(params, x)->name,
				params->start_name) &&
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
	char	**split;
	int		leaks_split;

	while (params->file[index])
	{
		leaks_split = -1;
		split = ft_strsplit(params->file[index], '-');
		put_links(params, split[0], split[1]);
		while (split[++leaks_split])
			ft_strdel(&split[leaks_split]);
		ft_memdel((void **)&split);
		index++;
	}
	check_matrice(params);
}

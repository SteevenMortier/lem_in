/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 16:07:14 by smortier          #+#    #+#             */
/*   Updated: 2018/04/15 16:07:17 by smortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_nodes		*ft_new_node(char *x, char *y, char *name, int id)
{
	t_nodes		*new_node;

	if (!(new_node = (t_nodes *)ft_memalloc(sizeof(t_nodes))))
		return (NULL);
	new_node->pos_x = ft_atoi(x);
	new_node->pos_y = ft_atoi(y);
	new_node->id = id;
	new_node->name = ft_strdup(name);
	new_node->nxt = NULL;
	new_node->nxt_mat = NULL;
	return (new_node);
}

t_nodes		*create_list(t_parameters *params, char *line, int id)
{
	t_nodes		*temp;
	char		**split;

	split = ft_strsplit(line, ' ');
	if (params->node == NULL)
	{
		temp = ft_new_node(split[1], split[2], split[0], id);
		ft_strdel(&split[0]);
		ft_strdel(&split[1]);
		ft_strdel(&split[2]);
		ft_memdel((void **)&split);
		return (temp);
	}
	else
	{
		temp = params->node;
		while (temp->nxt)
			temp = temp->nxt;
		temp->nxt = ft_new_node(split[1], split[2], split[0], id);
		ft_strdel(&split[0]);
		ft_strdel(&split[1]);
		ft_strdel(&split[2]);
		ft_memdel((void **)&split);
		return (params->node);
	}
}

void	init_matrice(t_parameters *params, int nbr_nodes)
{
	int		index_x;
	int		index_y;

	if (!(params->matrice = ft_memalloc(sizeof(int *) * nbr_nodes)))
		return ;
	index_x = -1;
	while (++index_x < nbr_nodes)
	{
		if (!(params->matrice[index_x] =
					ft_memalloc(sizeof(int) * nbr_nodes)))
			return ;
	}
	params->nbr_node = nbr_nodes;
}

int		fill_list(t_parameters *params)
{
	int		index;
	int		leaks_index;
	int		nbr_nodes;
	char	**split;

	index = 0;
	nbr_nodes = 0;
	while (params->file[++index])
	{
		split = ft_strsplit(params->file[index], ' ');
		if (split[1] && split[2])
		{
//			printf("\e[33m[%s] \n\e[0m", params->file[index]);
			params->node = create_list(params, params->file[index], nbr_nodes);
			nbr_nodes += 1;
		}
		else if (!ft_strstr(params->file[index], "##"))
			break;
		leaks_index = -1;
		while (split[++leaks_index])
			ft_strdel(&split[leaks_index]);
		ft_memdel((void **)&split);
	}
	init_matrice(params, nbr_nodes);
	return (index);
}

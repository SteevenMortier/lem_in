/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 12:02:22 by smortier          #+#    #+#             */
/*   Updated: 2018/03/23 12:02:23 by smortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_nodes		*ft_new_node(char *x, char *y, char *name)
{
	t_nodes		*new_node;

	if (!(new_node = (t_nodes *)ft_memalloc(sizeof(t_nodes))))
		return (NULL);
	new_node->pos_x = ft_atoi(x);
	new_node->pos_y = ft_atoi(y);
	new_node->name = name;
	new_node->prev = NULL;
	new_node->nxt = NULL;
	return (new_node);
}

t_nodes		*create_list(t_parameters *params, char *line)
{
	t_nodes		*temp;
	char		**split;

	split = ft_strsplit(line, ' ');
	if (params->node == NULL)
	{
		temp = ft_new_node(split[1], split[2], split[0]);
		ft_strdel(&split[0]);
		ft_strdel(&split[1]);
		ft_strdel(&split[2]);
//		ft_memdel((void **)&split);
		return (temp);
	}
	else
	{
		temp = params->node;
		while (temp->nxt)
			temp = temp->nxt;
		temp->nxt = ft_new_node(split[1], split[2], split[0]);
		ft_strdel(&split[0]);
		ft_strdel(&split[1]);
		ft_strdel(&split[2]);
//		ft_memdel((void **)&split);
		return (params->node);
	}
}

void		fill_list(t_parameters *params)
{
	int		index;
	int		index_leaks;
	char	**split;

	index = 0;
	while (params->file[++index])
	{
		if ((params->file[index] && strchr(params->file[index], ' ')))
		{
			params->node = create_list(params, params->file[index]);
//			printf("\e[31m[%s]\e[0m\n", params->file[index]);
		}
	}
}

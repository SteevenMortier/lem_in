/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 12:02:22 by smortier          #+#    #+#             */
/*   Updated: 2018/03/25 11:15:18 by smortier         ###   ########.fr       */
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
	new_node->name = ft_strdup(name);
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
		ft_memdel((void **)&split);
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
		ft_memdel((void **)&split);
		return (params->node);
	}
}

void		add_links(t_parameters *params, char *line)
{
	char	**split;
	int		index;
	int		placed;
	t_nodes	*tmp;

	split = ft_strsplit(line, '-');
	tmp = params->node;
	while (tmp)
	{
		if (ft_strstr(split[0], tmp->name))
		{
			tmp->nbr_links += 1;
			tmp->links = ft_realloc((void **)&(tmp->links),
							ft_strlen(tmp->links),
							ft_strlen(tmp->links) + ft_strlen(split[1]) + 1);
			ft_strcat(tmp->links, split[1]);
			ft_strcat(tmp->links, " ");
		}
		if (ft_strstr(split[1], tmp->name))
		{
			tmp->nbr_links += 1;
			tmp->links = ft_realloc((void **)&(tmp->links),
									ft_strlen(tmp->links),
									ft_strlen(tmp->links) + ft_strlen(split[0]) + 1);
			ft_strcat(tmp->links, split[0]);
			ft_strcat(tmp->links, " ");
		}
		tmp = tmp->nxt;
	}
	ft_strdel(&split[0]);
	ft_strdel(&split[1]);
	ft_memdel((void **)&split);
}

void		fill_list(t_parameters *params)
{
	int		index;
	int		index_leaks;
	char	**split;

	index = 0;
	while (params->file[++index])
	{
		if (strchr(params->file[index], ' ') &&
				!ft_strstr(params->file[index], "##"))
			params->node = create_list(params, params->file[index]);
	}
	index = 0;
	while (params->file[++index])
	{
		if (ft_strchr(params->file[index], '-') &&
				!ft_strstr(params->file[index], "##"))
			add_links(params, params->file[index]);
	}
}

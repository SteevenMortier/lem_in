/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 11:16:34 by smortier          #+#    #+#             */
/*   Updated: 2018/04/29 13:54:06 by smortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_nodes		*get_node(t_parameters *params, char *name)
{
	t_nodes		*tmp;

	tmp = params->node;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp);
		tmp = tmp->nxt;
	}
	return (NULL);
}

t_nodes		*get_node_by_id(t_parameters *params, int id_tf)
{
	t_nodes		*tmp;

	tmp = params->node;
	while (tmp)
	{
		if (tmp->id == id_tf)
			return (tmp);
		tmp = tmp->nxt;
	}
	return (NULL);
}

char		*get_roomname_by_id(t_parameters *params, int id, int index)
{
	t_tunnel	*tmp;

	tmp = params->tnl;
	while (tmp)
	{
		if (id == tmp->id)
			return (get_node_by_id(params, tmp->path[index])->name);
		tmp = tmp->nxt;
	}
	return (NULL);
}

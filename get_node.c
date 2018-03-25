/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 11:16:34 by smortier          #+#    #+#             */
/*   Updated: 2018/03/25 11:16:36 by smortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_nodes		*get_node(t_parameters *params, char *name)
{
	t_nodes		*tmp;

	tmp = params->node;
	while (tmp)
	{
		if (ft_strstr(tmp->name, name))
			return (tmp);
		tmp = tmp->nxt;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tunnels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 11:21:19 by smortier          #+#    #+#             */
/*   Updated: 2018/03/25 11:21:22 by smortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		get_tunnels(t_parameters *params)
{
	t_nodes		*index;
	t_nodes		*tmp;
	char		**split;
	int			finded;
	int			shots;

	finded = 0;
	index = get_node(params, params->start_name);
	tmp = NULL;
	split = NULL;
	printf("\e[38;5;163mStart node : Name = [%s], links : [%s]\e[0m\n",
	index->name, index->links);
	while (finded <= params->min_tnl_nbr && shots < params->nbr_ants)
	{
		shots++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 09:55:53 by smortier          #+#    #+#             */
/*   Updated: 2018/04/29 11:40:11 by smortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_antparams	*new_ants(int ant_nbr)
{
	t_antparams	*new_ants;

	if (!(new_ants = (t_antparams *)ft_memalloc(sizeof(t_antparams))))
		return (NULL);
	new_ants->ant = ant_nbr;
	new_ants->index_tnl = 0;
	new_ants->index_start = 0;
	new_ants->nxt = NULL;
	return (new_ants);
}

t_antparams	*create_ants(t_parameters *params, int ant_nbr)
{
	t_antparams	*tmp;
	t_antparams	*save;

	if (params->ants == NULL)
	{
		tmp = new_ants(ant_nbr);
		return (tmp);
	}
	else
	{
		tmp = params->ants;
		save = tmp;
		while (tmp->nxt)
			tmp = tmp->nxt;
		tmp->nxt = new_ants(ant_nbr);
		return (save);
	}
}

void		init_tnl(t_parameters *params)
{
	t_tunnel *tmp;

	tmp = params->tnl;
	while (tmp)
	{
		tmp->diff = tmp->lgt - params->diff_tnl;
		params->diff_total += tmp->diff;
		tmp = tmp->nxt;
	}
}

void		get_ants_by_tnl(t_parameters *params)
{
	t_tunnel *tmp;

	tmp = params->tnl->nxt;
	while (tmp)
	{
		tmp->number_ants = params->tnl->number_ants - tmp->diff;
		tmp = tmp->nxt;
	}
}

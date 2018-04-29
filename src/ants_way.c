/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 08:39:48 by smortier          #+#    #+#             */
/*   Updated: 2018/04/29 11:39:30 by smortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_start(t_parameters *params)
{
	t_tunnel	*tnl;
	t_antparams	*ants;
	int			index_start;

	tnl = params->tnl;
	while (tnl)
	{
		index_start = 1;
		ants = params->ants;
		while (ants)
		{
			if (ants->tnl_id == tnl->id)
			{
				ants->index_start = index_start;
				index_start += 1;
			}
			ants = ants->nxt;
		}
		tnl = tnl->nxt;
	}
}

void	get_ants_tnl(t_parameters *params)
{
	int			index_ant;
	t_antparams	*ants;
	t_tunnel	*tnl;
	int			index;

	ants = params->ants;
	index_ant = 0;
	while (ants)
	{
		tnl = params->tnl;
		index = -1;
		while (++index < index_ant % params->nbr_tnl)
		{
			tnl = tnl->nxt;
			if (!tnl->number_ants)
				tnl = params->tnl;
		}
		ants->tnl_id = tnl->id;
		tnl->number_ants -= 1;
		ants = ants->nxt;
		index_ant++;
	}
	get_start(params);
}

void	print(t_parameters *params, t_antparams *ants, int start)
{
	if (!ft_strcmp(params->end_name, get_roomname_by_id(params,
									ants->tnl_id, ants->index_tnl)))
	{
		ft_printf("\e[38;5;154mL%d-\e[38;5;166m%s\e[0m ", ants->ant,
				get_roomname_by_id(params, ants->tnl_id, ants->index_tnl));
		ants->index_tnl = 0;
		params->nbr_ants -= 1;
	}
	if (ants->index_start == start)
		ants->index_tnl += 1;
	if (ants->index_tnl != 0 && ft_strcmp(get_roomname_by_id(params,
										ants->tnl_id, 1), params->end_name))
	{
		ft_printf("\e[38;5;154mL%d-\e[38;5;166m%s\e[0m ", ants->ant,
				get_roomname_by_id(params, ants->tnl_id, ants->index_tnl));
		ants->index_tnl++;
	}
}

void	final_print(t_parameters *params)
{
	t_antparams	*ants;
	int			start;

	start = 1;
	while (params->nbr_ants)
	{
		ants = params->ants;
		while (ants)
		{
			print(params, ants, start);
			ants = ants->nxt;
		}
		start++;
		printf("\n");
	}
}

void	ants_way(t_parameters *params)
{
	t_tunnel	*tmp;
	int			ants;

	ants = 0;
	params->diff_tnl = params->tnl->lgt;
	params->diff_total = 0;
	init_tnl(params);
	while (++ants <= params->nbr_ants)
		params->ants = create_ants(params, ants);
	tmp = params->tnl;
	params->tnl->number_ants = (((float)params->nbr_ants
							+ (float)params->diff_total) /
			(float)params->nbr_tnl) + 0.5;
	get_ants_by_tnl(params);
	get_ants_tnl(params);
	final_print(params);
}

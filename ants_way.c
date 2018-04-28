/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 08:39:48 by smortier          #+#    #+#             */
/*   Updated: 2018/04/22 08:39:50 by smortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_antparams	*new_ants(t_parameters *params, int ant_nbr)
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
		tmp = new_ants(params, ant_nbr);
		return (tmp);
	}
	else
	{
		tmp = params->ants;
		save = tmp;
		while (tmp->nxt)
			tmp = tmp->nxt;
		tmp->nxt = new_ants(params, ant_nbr);
		return (save);
	}
}

void	init_tnl(t_parameters *params)
{
	t_tunnel *tmp;

	tmp = params->tnl;
	while (tmp)
	{
		tmp->diff = tmp->lgt - params->diff_tnl;
//		params->diff_tnl = tmp->lgt;
//		printf("Tnl[%d], diff[%d], diff_tnl[%d]\n", tmp->id, tmp->diff, params->diff_tnl);
		params->diff_total += tmp->diff;
		tmp = tmp->nxt;
	}
}

void	get_ants_by_tnl(t_parameters *params)
{
	t_tunnel *tmp;

	tmp = params->tnl->nxt;
	while (tmp)
	{
		tmp->number_ants = params->tnl->number_ants - tmp->diff;
//		printf("tnl[%d],diff[%d], number_ants[%d]\n",tmp->id, tmp->diff, tmp->number_ants);
		tmp = tmp->nxt;
	}
}

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
//				printf("\e[32mAnts[%d], id_tnl[%d], start[%d]\e[0m\n",
//				ants->ant, ants->tnl_id, ants->index_start);
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
//		printf("ants = [%d], tnl_id = [%d], index[%d]\n", index_ant, ants->tnl_id, ants->index_tnl);
		ants = ants->nxt;
		index_ant++;
	}
	get_start(params);
}

char	*get_roomname_by_id(t_parameters *params, int id, int index)
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
			if (!ft_strcmp(params->end_name, get_roomname_by_id(params, ants->tnl_id, ants->index_tnl)))
			{
				printf("\e[38;5;154mL%d-\e[38;5;166m%s\e[0m ", ants->ant, get_roomname_by_id(params, ants->tnl_id, ants->index_tnl));
				ants->index_tnl = 0;
				params->nbr_ants -= 1;
			}
			if (ants->index_start == start)
				ants->index_tnl += 1;
			if (ants->index_tnl != 0)
			{
				printf("\e[38;5;154mL%d-\e[38;5;166m%s\e[0m ", ants->ant, get_roomname_by_id(params, ants->tnl_id, ants->index_tnl));
				ants->index_tnl++;
			}
			ants = ants->nxt;
		}
		start++;
//		params->nbr_ants -= 1;
		printf("\n");
	}
}

void	ants_way(t_parameters *params)
{
	t_tunnel	*tmp;
	int			index;
	int			ants;

	ants = 0;
	params->diff_tnl = params->tnl->lgt;
	params->diff_total = 0;
	init_tnl(params);
//	printf("diff_total = [%d]\n", params->diff_total);
	while (++ants <= params->nbr_ants)
		params->ants = create_ants(params, ants);
	tmp = params->tnl;
	params->tnl->number_ants = (((float)params->nbr_ants + (float)params->diff_total) /
			(float)params->nbr_tnl) + 0.5;
//	printf("%d  + %d / %d + 0.5\n", params->nbr_ants, params->diff_total, params->nbr_tnl);
//	printf("nbr_tnl = [%d], number_ants[%d]\n", params->nbr_tnl, params->tnl->number_ants);
	get_ants_by_tnl(params);
	get_ants_tnl(params);
	final_print(params);
	while (tmp)
	{
		index = -1;
		printf("ID[%d] got lenght = %d\n", tmp->id, tmp->lgt);
		while (++index < tmp->lgt)
			printf("%s ", get_node_by_id(params, tmp->path[index])->name);
		printf("\n");
		tmp = tmp->nxt;
	}
}

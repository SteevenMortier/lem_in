/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_needed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 08:41:50 by smortier          #+#    #+#             */
/*   Updated: 2018/04/29 13:52:02 by smortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_if_needed(t_parameters *params)
{
	int			x;
	int			y;
	int			tof_start;
	int			tof_end;
	static int	nbr_tnl;

	x = get_node(params, params->start_name)->id;
	tof_start = 0;
	y = -1;
	while (++y < params->nbr_node)
	{
		if (params->matrice[x][y])
			tof_start = 1;
	}
	x = get_node(params, params->end_name)->id;
	y = -1;
	tof_end = 0;
	while (++y < params->nbr_node)
	{
		if (params->matrice[x][y])
			tof_end = 1;
	}
	nbr_tnl += (tof_start && tof_end && nbr_tnl <= params->nbr_ants) ? 1 : 0;
	return ((tof_start && tof_end && nbr_tnl <= params->nbr_ants) ? 1 : 0);
}

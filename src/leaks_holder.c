/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_holder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 08:39:58 by smortier          #+#    #+#             */
/*   Updated: 2018/04/22 08:40:00 by smortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_matrice(t_parameters *params)
{
	int		index;

	index = -1;
	while (++index < params->nbr_node)
		ft_memdel((void **)&params->matrice[index]);
	ft_memdel((void **)&params->matrice);
}

void	leaks_holder(t_parameters *params)
{
	int		index;
	t_nodes	*tmp;

	tmp = params->node;
	index = -1;
	while (params->file[++index])
		ft_strdel(&params->file[index]);
	index = -1;
	free_matrice(params);
	ft_memdel((void **)&params->file);
	ft_memdel((void **)&params->pile);
	ft_memdel((void **)&params->start_name);
	ft_memdel((void **)&params->end_name);
}

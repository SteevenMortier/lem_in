/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_holder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 10:54:27 by smortier          #+#    #+#             */
/*   Updated: 2018/04/29 14:02:56 by smortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_start(t_parameters *params, int checker, int index)
{
	char		**split;

	if (params->file[index][0] == '#'
		&& ft_strstr(params->file[index], "start"))
	{
		checker += 1;
		if (params->file[index + 1] &&
			!ft_strchr(params->file[index + 1], ' '))
			return (0);
		else
		{
			split = ft_strsplit(params->file[index + 1], ' ');
			params->start_name = split[0];
			ft_strdel(&split[1]);
			ft_strdel(&split[2]);
			ft_memdel((void **)&split);
			if (!params->start_name)
				return (0);
		}
	}
	return (checker);
}

int		check_end(t_parameters *params, int checker, int index)
{
	char		**split;

	if (params->file[index][0] == '#'
		&& ft_strstr(params->file[index], "end"))
	{
		checker += 1;
		if (params->file[index + 1] &&
			!ft_strchr(params->file[index + 1], ' '))
			return (0);
		else
		{
			split = ft_strsplit(params->file[index + 1], ' ');
			params->end_name = split[0];
			ft_strdel(&split[1]);
			ft_strdel(&split[2]);
			ft_memdel((void **)&split);
			if (!params->end_name)
				return (0);
		}
	}
	return (checker);
}

int		parsing_holder(t_parameters *params)
{
	int			index;
	int			checker;

	checker = 0;
	if (params->file[0] && !ft_strchr(params->file[0], ' '))
		params->nbr_ants = ft_atoi(params->file[0]);
	if (params->nbr_ants <= 0 || ft_strcmp(params->file[0],
				ft_itoa(params->nbr_ants)))
	{
		ft_putstr("ERROR");
		exit(1);
	}
	index = 0;
	while (params->file[++index])
	{
		checker = check_start(params, checker, index);
		checker = check_end(params, checker, index);
	}
	if (checker != 2)
		return (0);
	return (1);
}

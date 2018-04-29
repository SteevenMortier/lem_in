/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 11:15:04 by smortier          #+#    #+#             */
/*   Updated: 2018/04/29 14:03:15 by smortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		returned_cases(char *line)
{
	if (!line)
		return (0);
	if ((ft_strchr(line, '#') && !ft_strstr(line, "##")) || ft_strstr(line,
													"###"))
		return (0);
	if (ft_strstr(line, "##") &&
		(!ft_strstr(line, "start") && !ft_strstr(line, "end")))
		return (0);
	return (1);
}

void	clear_file(t_parameters *params, char *line)
{
	char		**tmp;
	int			index;

	if (!returned_cases(line))
		return ;
	index = -1;
	params->file_line += 1;
	if (!(tmp = (char **)ft_memalloc(sizeof(char *) * params->file_line)))
		return ;
	if (params->file)
	{
		while (++index < params->file_line - 1)
		{
			if (params->file[index])
				tmp[index] = ft_strdup(params->file[index]);
			ft_memdel((void **)&params->file[index]);
		}
		ft_memdel((void **)&params->file);
	}
	params->file = tmp;
	params->file[params->file_line - 2] = ft_strdup(line);
	params->file[params->file_line - 1] = NULL;
}

void	check_line(char *line)
{
	int		index;

	index = -1;
	if (!ft_strchr(line, '#'))
	{
		while (line[++index])
		{
			if (!ft_isascii(line[index]))
			{
				ft_putendl("Error");
				exit(1);
			}
		}
	}
}

void	end(t_parameters *params)
{
	fill_matrice(params, fill_list(params));
	resolve_tnl(params);
	if (!params->nbr_tnl)
	{
		ft_putendl("There is no way i can find!");
		exit(1);
	}
	ants_way(params);
	leaks_holder(params);
}

int		main(void)
{
	char			*line;
	t_parameters	params;

	params.nbr_tnl = 0;
	params.nbr_ants = 0;
	params.tnl = NULL;
	if (!(params.file = (char **)ft_memalloc(sizeof(char *) * 1)))
		return (0);
	params.file[0] = NULL;
	params.file_line = 1;
	while (get_next_line(0, &line) > 0)
	{
		check_line(line);
		clear_file(&params, line);
		ft_putendl(line);
		ft_strdel(&line);
	}
	if (!parsing_holder(&params) || !params.start_name || !params.end_name)
	{
		ft_putendl("Error");
		exit(1);
	}
	end(&params);
	return (0);
}

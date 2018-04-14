/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 11:15:04 by smortier          #+#    #+#             */
/*   Updated: 2018/03/25 11:15:06 by smortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		clear_file(t_parameters *params, char *line)
{
	char		**tmp;
	int			index;

	index = -1;
	if (!line)
		return ;
	if ((ft_strchr(line, '#') && !ft_strstr(line, "##")) || ft_strstr(line,
													"###"))
		return ;
	if (strstr(line, "##") &&
		(!ft_strstr(line, "start") && !ft_strstr(line, "end")))
		return ;
	index = -1;
	params->file_line += 1;
	if (!(tmp = ft_memalloc(sizeof(char *) * params->file_line)))
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

int		parsing_holder(t_parameters *params)
{
	int			index;
	char		**split;

	index = -1;
	if (params->file[0] && ft_isdigit(params->file[0][0]))
		params->nbr_ants = ft_atoi(params->file[0]);
	else
		return (0);
	while (params->file[++index])
	{
		if (params->file[index][0] == '#' && ft_strstr(params->file[index], "start"))
		{
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
		if (params->file[index][0] == '#' && ft_strstr(params->file[index], "end"))
		{
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
	}
	return (1);
}

int		main(void)
{
	char			*line;
	t_parameters	params;
	int				index;
	t_nodes			*tmp;

	if (!(params.file = (char **)ft_memalloc(sizeof(char *) * 1)))
		return (0);
	params.file[0] = NULL;
	params.file_line = 1;
	while (get_next_line(0, &line) > 0)
	{
		clear_file(&params, line);
		ft_strdel(&line);
	}
	if (!parsing_holder(&params) || !params.start_name || !params.end_name)
	{
		ft_putendl("Error");
		return (0);
	}
	fill_list(&params);
	get_min_tnl_number(&params);
	get_tunnels(&params);

	tmp = params.node;
	while (tmp)
	{
		if (tmp->links)
			tmp->links[ft_strlen(tmp->links) - 1] = 0;
		printf("\e[38;5;87mNode = [%s], links = [%s], nbr_links = [%d] \e[0m\n",
			tmp->name, tmp->links, tmp->nbr_links);
		tmp = tmp->nxt;
	}
	printf("\e[38;5;226mStart : [%s]\e[0m\n", params.start_name);
	printf("\e[38;5;226mend   : [%s]\e[0m\n", params.end_name);
	printf("\e[38;5;226mMinimum of tunnel : [%d]\e[0m\n", params.min_tnl_nbr);

	/////LEAKS
	/*index = -1;
	while (++index < params.file_line)
		ft_strdel(&params.file[index]);
	ft_memdel((void **)&params.start_name);
	ft_memdel((void **)&params.end_name);
	ft_memdel((void **)&params.file);*/
//	while (1)
//		;
	//on leaks pas si on laisse le pointeur de la liste au debut hehe
	/////LEAKS
}

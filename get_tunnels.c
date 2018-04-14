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
////////LOURD LEAKS sur split et strsub surement
char		*breadth_first_search(t_parameters *params, char *start, char *road)
{
	char	*file;
	char	*save_file;
	char	*marqued;
	char	**split;

	if (!road)
		road = "| | |";
	file = ft_strnew(ft_strlen(start) + 1);
	ft_strcpy(file, start);
	marqued = ft_strdup(file);
	ft_strcat(marqued, " ");
	ft_strcat(file, " ");
	save_file = file;
	while (ft_strlen(file) && !ft_strstr(marqued, params->end_name))
	{
		split = ft_strsplit(get_node(params, ft_strsub(file, 0, ft_strclen(file, ' ')))->links, ' ');
		ft_strcat(marqued, ft_strsub(file, 0, ft_strclen(file, ' ')));
		ft_strcat(marqued, ":");
		while (*split)
		{
			if (((!ft_strstr(marqued, *split) && !ft_strstr(*split, start) &&
					!ft_strstr(*split, params->start_name)) ||
				ft_strstr(*split, params->end_name)) && !ft_strstr(road, *split))
			{
				if (!ft_strstr(*split, params->end_name))
				{
					file = ft_strcat(file, *split);
					file = ft_strcat(file, " ");
				}
				ft_strcat(marqued, *split);
			}
			split++;
		}
		file = ft_strchr(file, ' ') + 1;
		printf("\e[31mSEGV : file = [%s]\e[0m\n", file);
		ft_strcat(marqued, " ");
	}
	return (marqued);
}

char		*formate_it(t_parameters *params, char *tnl)
{
	int		index;
	char	*ret;
	char	**split;
	char	*find;

//	printf("\e[32m ENTRANCE = [%s] \e[0m\n", tnl);
	if (!ft_strstr(tnl, params->end_name))
		return (NULL);
	ret = ft_strnew(1000);
	index = 0;
	split = ft_strsplit(tnl, ' ');
	while (!ft_strstr(split[index], params->end_name)) {
		index++;
	}
	find = ft_strsub(split[index], 0, ft_strclen(split[index], ':'));
	ft_strcat(ret, find);
	ft_strcat(ret, " ");
	index--;
	while (split[index] && index > 0)
	{
		while (!ft_strstr(split[index], find))
			index--;
		find = ft_strsub(split[index], 0, ft_strclen(split[index], ':'));
		ft_strcat(ret, find);
		ft_strcat(ret, " ");
		if (index > 0)
			index--;
	}
	ret[ft_strlen(ret) - 1] = '\0';
	if (ft_strstr(ret, params->end_name))
		return ("direct");
	return (ret);
}

void		get_tunnels(t_parameters *params)
{
	int		index;
	char	*test;
	char	*over_all;
	char	**split;

	over_all = ft_strnew(1000);
	test = NULL;
	index = 0;
	split = ft_strsplit(get_node(params, params->start_name)->links, ' ');
	while (split[index])
	{
		printf("\e[32mSplit = [%s]\e[0m\n", split[index]);
		printf("\e[31mOver_all = [%s]\e[0m\n", over_all);
		if (!over_all)
			test = formate_it(params, breadth_first_search(params, split[index], NULL));
		else
			test = formate_it(params, breadth_first_search(params, split[index], over_all));
		if (test)
		{
			ft_strcat(over_all, test);
			printf("\e[31mChemin = [%s]\e[0m\n", test);
		}
		index ++;
	}
	if (!over_all)
		printf("\e[31mAUCUN CHEMIN TROUVE\e0m\n");
}

////HEADER
////HEADER
////HEADER
////HEADER
////HEADER
////HEADER
////HEADER
////HEADER

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
			if (params->file[index + 1] && params->file[index + 1][0] == '#')
			{
				ft_memdel((void **)&split);
				return (0);
			}
			else
			{
				split = ft_strsplit(params->file[index + 1], ' ');
				params->start_name = split[0];
				ft_strdel(&split[1]);
				ft_strdel(&split[2]);
				ft_memdel((void **)&split);
			}
		}
		if (params->file[index][0] == '#' && ft_strstr(params->file[index], "end"))
		{
			if (params->file[index + 1] && params->file[index + 1][0] == '#')
			{
				ft_memdel((void **)&split);
				return (0);
			}
			else
			{
				split = ft_strsplit(params->file[index + 1], ' ');
				params->end_name = split[0];
				ft_strdel(&split[1]);
				ft_strdel(&split[2]);
				ft_memdel((void **)&split);
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

	if (!(params.file = (char **)ft_memalloc(sizeof(char *) * 1)))
		return (0);
	params.file[0] = NULL;
	params.file_line = 1;
	while (get_next_line(0, &line) > 0)
	{
//		printf("\e[033mline = [%s]\e[0m\n", line);
		clear_file(&params, line);
		ft_strdel(&line);
	}
	if (!parsing_holder(&params))
	{
		ft_putendl("Error");
		return (0);
	}
	fill_list(&params);
	/////LEAKS
	index = -1;
	while (++index < params.file_line)
		ft_strdel(&params.file[index]);
	ft_memdel((void **)&params.start_name);
	ft_memdel((void **)&params.end_name);
	ft_memdel((void **)&params.file);
	while (params.node->nxt)
	while (1)
		;
	/////LEAKS
}
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
	if (!strstr(line, "##"))
	{
		while (line[++index])
			if (!ft_isdigit(line[index]) && line[index] != '-'
				&& line[index] != ' ')
				return ;
	}
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
	index = -1;
	while (++index < params.file_line)
	{
		printf("\e[031mline = [%s]\e[0m\n", params.file[index]);
		ft_memdel((void **)&params.file[index]);
	}
	ft_memdel((void **)&params.file);
	ft_memdel((void **)&params);
}
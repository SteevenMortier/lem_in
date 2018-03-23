////HEADER
////HEADER
////HEADER
////HEADER
////HEADER////HEADER////HEADER
////HEADER
////HEADER
////HEADER

#ifndef LEM_IN_H

# define LEM_IN_H

# include "libft/libft.h"

# include "libft/get_next_line.h"

# include <stdio.h>

# include <stdlib.h>

# include <unistd.h>

typedef struct			s_nodes
{
	char			*name;
	int				pos_x;
	int				pos_y;
	int				nbr_links;
	char			*links;
	struct s_nodes	*nxt;
	struct s_nodes	*prev;
}						t_nodes;

typedef struct			s_parameters
{
	int		nbr_ants;
	int		start_line;
	int		end_line;
	int		file_line;
	char	*start_name;
	char	*end_name;
	char	**file;
	t_nodes	*node;
}						t_parameters;

void					fill_list(t_parameters *params);

#endif
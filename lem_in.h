/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 11:14:47 by smortier          #+#    #+#             */
/*   Updated: 2018/03/25 11:14:51 by smortier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H

# define LEM_IN_H

# include "libft/libft.h"

# include "libft/get_next_line.h"

# include <stdio.h>

# include <stdlib.h>

# include <unistd.h>

#define INFINI 42424242

typedef struct			s_pile
{
	int				parent;
	struct s_pile	*bgn;
	struct s_pile	*end;
}
						t_pile;

typedef struct			s_nodes
{
	int				id;
	char			*name;
	int				pos_x;
	int				pos_y;
	struct s_nodes	*nxt;
}						t_nodes;

typedef struct			s_parameters
{
	int			nbr_ants;
	int			nbr_node;
	int			start_line;
	int			end_line;
	int			file_line;
	char		*start_name;
	char		*end_name;
	char		**file;
	t_nodes		*node;
}						t_parameters;

t_nodes		*get_node(t_parameters *params, char *name);

void		fill_list(t_parameters *params);

#endif

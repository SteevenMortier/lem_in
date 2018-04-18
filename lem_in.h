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

#define INF 42424242

typedef struct			s_nodes
{
	int				id;
	int				shots;
	char			*name;
	int				pos_x;
	int				pos_y;
	struct s_nodes	*nxt;
	struct s_nodes	*nxt_mat;
}						t_nodes;

typedef struct			s_pile
{
	int				parent;
	t_nodes	*bgn;
	t_nodes	*end;
}
		t_pile;

typedef struct			s_parameters
{
	int			nbr_ants;
	int			**matrice;
	int			nbr_node;
	int			start_line;
	int			end_line;
	int			file_line;
	char		*start_name;
	char		*end_name;
	char		**file;
	t_nodes		*node;
	t_pile		*pile;
}						t_parameters;

t_nodes		*get_node(t_parameters *params, char *name);

t_nodes		*get_node_by_id(t_parameters *params, int id_tf);

int		fill_list(t_parameters *params);

void	fill_matrice(t_parameters *params, int index);

void	resolve_tnl(t_parameters *params);

#endif

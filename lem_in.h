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
	t_nodes			*bgn;
	t_nodes			*end;
}
		t_pile;

typedef struct			s_antparams
{
	int					ant;
	int					tnl_id;
	int					index_tnl;
	int					index_start;
	struct s_antparams	*nxt;
}						t_antparams;

typedef struct			s_tunnel
{
	int				id;
	int				diff;
	int				lgt;
	int				number_ants;
	int				*path;
	struct s_tunnel	*nxt;
}						t_tunnel;

typedef struct			s_parameters
{
	int			diff_tnl;
	int			nbr_ants;
	int			diff_total;
	int			nbr_tnl;
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
	t_tunnel	*tnl;
	t_antparams	*ants;
}						t_parameters;

t_nodes		*get_node(t_parameters *params, char *name);

t_nodes		*get_node_by_id(t_parameters *params, int id_tf);

int		fill_list(t_parameters *params);

void	fill_matrice(t_parameters *params, int index);

void	resolve_tnl(t_parameters *params);

void		leaks_holder(t_parameters *params);

void		reset_matrice(t_parameters *params, int *tnl, int for_tnl);

int			check_if_needed(t_parameters *params);

void		ants_way(t_parameters *params);

t_tunnel	*create_tunnel(t_parameters *params, int lenhgt, int *tnl);

#endif

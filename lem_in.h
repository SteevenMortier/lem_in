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

//Les tnl sont split par un \n

typedef struct			s_tunnels
{
	int				nbr_tnl;
	int				*shots;
	char			*tnl;
}						t_tunnels;

typedef struct			s_parameters
{
	int			nbr_ants;
	int			start_line;
	int			end_line;
	int			min_tnl_nbr;
	int			file_line;
	char		*start_name;
	char		*end_name;
	char		**file;
	t_tunnels	tnl;
	t_nodes	*node;
}						t_parameters;

void					fill_list(t_parameters *params);

void					get_min_tnl_number(t_parameters *params);

t_nodes		*get_node(t_parameters *params, char *name);

void		get_tunnels(t_parameters *params);

#endif

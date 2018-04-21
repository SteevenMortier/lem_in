#include "lem_in.h"

int		check_if_needed(t_parameters *params)
{
	int			x;
	int			y;
	int			tof_start;
	int			tof_end;
	static int	nbr_tnl;

	x = get_node(params, params->start_name)->id;
	tof_start = 0;
	y  = -1;
	while (++y < params->nbr_node)
	{
		if (params->matrice[x][y])
			tof_start = 1;
	}
	x = get_node(params, params->end_name)->id;
	y  = -1;
	tof_end = 0;
	while (++y < params->nbr_node)
	{
		if (params->matrice[x][y])
			tof_end = 1;
	}
	if (tof_start && tof_end && nbr_tnl < params->nbr_ants)
	{
		nbr_tnl += 1;
		return (1);
	}
	return (0);
}

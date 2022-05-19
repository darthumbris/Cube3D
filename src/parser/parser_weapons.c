/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_weapons.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/18 10:07:02 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/19 15:56:12 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	bonus_weapons(char *line, t_data *data)
{
	if (ft_strncmp(line, "P0", 2) == 0)
		return (store_path(line, data, PISTOL0), true);
	else if (ft_strncmp(line, "P1", 2) == 0)
		return (store_path(line, data, PISTOL1), true);
	else if (ft_strncmp(line, "P2", 2) == 0)
		return (store_path(line, data, PISTOL2), true);
	else if (ft_strncmp(line, "P3", 2) == 0)
		return (store_path(line, data, PISTOL3), true);
	else if (ft_strncmp(line, "K0", 2) == 0)
		return (store_path(line, data, KNIFE0), true);
	else if (ft_strncmp(line, "K1", 2) == 0)
		return (store_path(line, data, KNIFE1), true);
	else if (ft_strncmp(line, "K2", 2) == 0)
		return (store_path(line, data, KNIFE2), true);
	else if (ft_strncmp(line, "K3", 2) == 0)
		return (store_path(line, data, KNIFE3), true);
	else if (ft_strncmp(line, "M0", 2) == 0)
		return (store_path(line, data, MACHINEGUN0), true);
	else if (ft_strncmp(line, "M1", 2) == 0)
		return (store_path(line, data, MACHINEGUN1), true);
	else if (ft_strncmp(line, "M2", 2) == 0)
		return (store_path(line, data, MACHINEGUN2), true);
	else if (ft_strncmp(line, "M3", 2) == 0)
		return (store_path(line, data, MACHINEGUN3), true);
	return (false);
}

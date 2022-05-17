/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_find_3.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/17 12:26:33 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/17 12:51:13 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	pathfind_cardinal(t_data *data, t_sprite *enemy)
{
	int		rand_card;
	int		cardinal;
	bool	backward;

	rand_card = rand() % 2;
	cardinal = try_cardinal(data, enemy, rand_card, 1);
	if (!cardinal)
	{
		cardinal = try_cardinal(data, enemy, (rand_card + 1) % 2, 1);
		if (!cardinal)
		{
			backward = true;
			cardinal = try_cardinal(data, enemy, rand_card, -1);
			if (!cardinal)
				cardinal = try_cardinal(data, enemy, (rand_card + 1) % 2, -1);
		}
	}
	if (cardinal && !backward)
		enemy->en_dat.path_dir = 4 + cardinal;
	else if (cardinal)
		enemy->en_dat.path_dir = 8 + cardinal;
}

void	pathfind_to_player(t_data *data, t_sprite *enemy)
{
	if (enemy->en_dat.path_dir == 0)
		enemy->en_dat.path_dir = try_diagonals(data, enemy);
	if (enemy->en_dat.path_dir == 0)
		pathfind_cardinal(data, enemy);
	else
		pathfind_in_direction(data, enemy);
}

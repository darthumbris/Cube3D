/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_textures_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:44:27 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/15 15:58:11 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	get_door_lst_nbr(int tile)
{
	if (tile >= 169 && tile <= 172)
		return (45);
	else if (tile > 172 && tile <= 176)
		return (46);
	else if (tile > 176 && tile <= 180)
		return (47);
	return (48);
}

static int	get_enemy_lst_nbr(int tile)
{
	switch (tile)
	{
	case 5 ... 16:
		return (0);
	case 17 ... 28:
		return (1);
	case 29 ... 40:
		return (2);
	case 41 ... 52:
		return (3);
	case 53 ... 64:
		return (4);
	case 65 ... 76:
		return (5);
	case 125 ... 136:
		return (6);
	case 137 ... 148:
		return (7);
	case 149 ... 160:
		return (8);
	case 161 ... 172:
		return (9);
	case 173 ... 184:
		return (10);
	case 185 ... 196:
		return (11);
	case 197 ... 208:
		return (12);
	case 209 ... 220:
		return (13);
	case 221 ... 232:
		return (14);
	case 233 ... 244:
		return (15);
	case 77 ... 88:
		return (16);
	case 89 ... 100:
		return (17);
	case 101 ... 112:
		return (18);
	case 113 ... 116:
		return (19);
	case 117 ... 120:
		return (20);
	case 121 ... 124:
		return (21);
	case 245 ... 249:
		return (22);
	default:
		return (1);
	}
}

void	check_textures_needed(t_data *data, int i, int j, int k)
{
	uint8_t	tile;

	k = -1;
	while (++k < 3)
	{
		i = -1;
		while (++i < data->level.map_h)
		{
			j = -1;
			while (++j < data->level.map_w)
			{
				tile = data->level.map_planes[i][j][k];
				if (k == 0 && tile && tile <= 45)
					data->mlx.txt_in_map.wall[tile - 1] = true;
				else if (k == 0 && tile && tile <= 188)
					data->mlx.txt_in_map.wall[get_door_lst_nbr(tile)] = true;
				else if (k == 1 && tile)
					data->mlx.txt_in_map.obj[tile - 1] = true;
				else if (k == 2 && tile >= 5 && tile <= 249)
					data->mlx.txt_in_map.enmy[get_enemy_lst_nbr(tile)] = true;
			}
		}
	}
}

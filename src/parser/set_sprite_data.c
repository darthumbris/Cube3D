/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_sprite_data.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 11:44:20 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/25 10:08:41 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static t_vector_int	get_transparency_begin(int kind, t_data *data)
{
	if (kind >= 0 && kind <= ITEM_8)
		return (data->config.dat[kind].transp_begin);
	else
		return ((t_vector_int){.x = -1, .y = -1});
}

static t_vector_int	get_transparency_end(int kind, t_data *data)
{
	if (kind >= 0 && kind <= ITEM_8)
		return (data->config.dat[kind].transp_end);
	else
		return ((t_vector_int){.x = -1, .y = -1});
}

static void	set_sprite_data(t_sprite *sprite, t_vector_int pos, char **map, \
	t_data *data)
{
	sprite->map_pos.x = pos.x + 0.5;
	sprite->map_pos.y = pos.y + 0.5;
	sprite->kind = get_sprite_kind(map[pos.y][pos.x], data);
	if (sprite->kind == GUARD || sprite->kind == DOG)
	{
		set_enemy_data(sprite, map, pos, data);
		data->level.enemies_count++;
	}
	else if (sprite->kind == TREASURE_0 || sprite->kind == TREASURE_1 || \
			sprite->kind == TREASURE_2)
		data->level.treasure_count++;
	sprite->transp_begin = get_transparency_begin(sprite->kind, data);
	sprite->transp_end = get_transparency_end(sprite->kind, data);
}

void	set_sprite_positions(char **map, t_data *data)
{
	int	i;
	int	j;
	int	sprite_cnt;

	data->sprite = ft_calloc(sizeof(t_sprite), data->level.number_of_sprites);
	if (!data->sprite)
		exit(1);
	i = 0;
	sprite_cnt = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_sprite_tile(map[i][j]))
			{
				set_sprite_data(&data->sprite[sprite_cnt++], \
					(t_vector_int){.x = j, .y = i}, map, data);
			}
			j++;
		}
		i++;
	}
}

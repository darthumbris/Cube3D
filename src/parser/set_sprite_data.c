/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_sprite_data.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 11:44:20 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/09 15:53:59 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	get_sprite_kind(char c, t_data *data)
{
	int	i;

	i = 0;
	if (data->bonus && data->config.size > 5)
		i = 4;
	while (i < data->config.size)
	{
		if (c == data->config.dat[i].value)
			return (i);
		i++;
	}
	return (0);
}

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
	if (is_nonblocking_kind(sprite->kind + 1))
		map[pos.y][pos.x] = '0';
	sprite->transp_begin = get_transparency_begin(sprite->kind, data);
	sprite->transp_end = get_transparency_end(sprite->kind, data);
}

void	set_sprite_positions(char **map, t_data *data)
{
	int	i;
	int	j;
	int	sprite_cnt;

	data->sprite = malloc(sizeof(t_sprite) * data->level.number_of_sprites);
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

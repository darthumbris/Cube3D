/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_sprite_data.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 11:44:20 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/04/26 16:46:17 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static int	get_sprite_kind(char c)
{
	if (c == 'B')
		return (BARREL);
	if (c == 'P')
		return (PILLAR);
	if (c == 'L')
		return (LAMP);
	if (c == 'b')
		return (BONES);
	if (c == 'G')
		return (GUARD);
	if (c == 'h')
		return (HIDDEN);
	if (c == 'c')
		return (DOG);
	return (DOOR_SPRITE);
}

static t_vector_int	get_transparency_begin(int kind)
{
	if (kind == BARREL)
		return ((t_vector_int){.x = 16, .y = 0});
	else if (kind == BONES)
		return ((t_vector_int){.x = -1, .y = 0});
	else if (kind == LAMP)
		return ((t_vector_int){.x = 22, .y = 11});
	else if (kind == GUARD)
		return ((t_vector_int){.x = 41, .y = -1});
	return ((t_vector_int){.x = -1, .y = -1});
}

static t_vector_int	get_transparency_end(int kind)
{
	if (kind == BARREL)
		return ((t_vector_int){.x = 48, .y = 30});
	else if (kind == BONES)
		return ((t_vector_int){.x = 128, .y = 45});
	else if (kind == LAMP)
		return ((t_vector_int){.x = 43, .y = -1});
	else if (kind == GUARD)
		return ((t_vector_int){.x = 87, .y = -1});
	return ((t_vector_int){.x = 128, .y = -1});
}

static void	set_sprite_data(t_sprite *sprite, int i, int j, char **map)
{
	sprite->map_pos.x = j + 0.5;
	sprite->map_pos.y = i + 0.5;
	sprite->kind = get_sprite_kind(map[i][j]);
	if (is_nonblocking_kind(sprite->kind))
		map[i][j] = '0';
	if (sprite->kind == HIDDEN)
		sprite->hidden = true;
	else
		sprite->hidden = false;
	sprite->transp_begin = get_transparency_begin(sprite->kind);
	sprite->transp_end = get_transparency_end(sprite->kind);
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
				set_sprite_data(&data->sprite[sprite_cnt++], i, j, map);
			j++;
		}
		i++;
	}
}

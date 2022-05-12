/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_sprite_data.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 11:44:20 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/12 16:14:44 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/*
GW,[,GUARD_WEST
GE,],GUARD_EAST
GS,@,GUARD_SOUTH
GN,!,GUARD_NORTH
*/
static	t_vector_double	get_direction_enemy(char c)
{
	if (c == '[' || c == 'G' || c == 'c' || c == '(')
		return ((t_vector_double){-1.0, 0.0});
	else if (c == ']' || c == ')')
		return ((t_vector_double){+1.0, 0.0});
	else if (c == '@' || c == '#')
		return ((t_vector_double){0.0, +1.0});
	else
		return ((t_vector_double){0.0, -1.0});
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
	sprite->player_detected = false;
	sprite->state = ATTACKING;
	if (sprite->kind == GUARD)
		sprite->health = 25;
	else if (sprite->kind == DOG)
		sprite->health = 1;
	else
		sprite->health = 0;
	if (is_enemy_tile(map[pos.y][pos.x]))
		sprite->dir = get_direction_enemy(map[pos.y][pos.x]);
	if (is_nonblocking_kind(sprite->kind))
		map[pos.y][pos.x] = '0';
	sprite->transp_begin = get_transparency_begin(sprite->kind, data);
	sprite->transp_end = get_transparency_end(sprite->kind, data);
	sprite->frame = 0;
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

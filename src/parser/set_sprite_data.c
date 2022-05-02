/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_sprite_data.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 11:44:20 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/04/29 14:18:09 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	get_sprite_kind(char c)
{
	if (c == 'B')
		return (BARREL);
	else if (c == 'P')
		return (PILLAR);
	else if (c == 'L')
		return (LAMP);
	else if (c == 'b')
		return (BONES);
	else if (c == 'G')
		return (GUARD);
	else if (c == 'h')
		return (HIDDEN);
	else if (c == 'c')
		return (DOG);
	else if (c == 'f')
		return (WELL_FULL);
	else if (c == 'w')
		return (WELL_EMPTY);
	else if (c == 't')
		return (TABLE);
	else if (c == 'C')
		return (CHANDELIER);
	else if (c == 'p')
		return (PLANT);
	else if (c == 'T')
		return (TABLE_CHAIRS);
	else if (c == 'H')
		return (HIDDEN_2);
	else if (c == 's')
		return (STATUE);
	else if (c == 'l')
		return (LAMP_STANDING);
	else if (c == 'g')
		return (TREE);
	else if (c == 'o')
		return (GREEN_BARREL);
	else if (c == 'a')
		return (POT);
	else if (c == 'A')
		return (FLAG);
	else if (c == 'e')
		return (STIMULANT);
	else if (c == 'F')
		return (MEDKIT);
	else if (c == 'i')
		return (SOUL);
	else if (c == 'I')
		return (DOGMEAL);
	else if (c == 'j')
		return (GUN);
	else if (c == 'J')
		return (AMMO);
	else if (c == 'k')
		return (TREASURE_0);
	else if (c == 'K')
		return (TREASURE_1);
	else if (c == 'm')
		return (TREASURE_2);
	return (DOOR_SPRITE);
}

static t_vector_int	get_transparency_begin(int kind)
{
	if (kind == BARREL)
		return ((t_vector_int){.x = 33, .y = 0});
	else if (kind == BONES)
		return ((t_vector_int){.x = 16, .y = 0});
	else if (kind == LAMP)
		return ((t_vector_int){.x = 43, .y = 20});
	else if (kind == GUARD)
		return ((t_vector_int){.x = 41, .y = 0});
	else if (kind == CHANDELIER)
		return ((t_vector_int){.x = 43, .y = 32});
	else if (kind == TABLE)
		return ((t_vector_int){.x = 22, .y = 0});
	else if (kind == WELL_EMPTY || kind == WELL_FULL)
		return ((t_vector_int){.x = 7, .y = 0});
	else if (kind == PLANT)
		return ((t_vector_int){.x = 48, .y = 0});
	else if (kind == TABLE_CHAIRS)
		return ((t_vector_int){.x = 11, .y = 0});
	else if (kind == LAMP_STANDING)
		return ((t_vector_int){.x = 43, .y = 0});
	else if (kind == DOG)
		return ((t_vector_int){.x = 40, .y = 0});
	else if (kind == STATUE)
		return ((t_vector_int){.x = 24, .y = 0});
	else if (kind == TREE)
		return ((t_vector_int){.x = 33, .y = 0});
	else if (kind == GREEN_BARREL)
		return ((t_vector_int){.x = 38, .y = 0});
	else if (kind == POT)
		return ((t_vector_int){.x = 44, .y = 0});
	else if (kind == FLAG)
		return ((t_vector_int){.x = 47, .y = 0});
	else if (kind == STIMULANT)
		return ((t_vector_int){.x = 35, .y = 0});
	else if (kind == MEDKIT)
		return ((t_vector_int){.x = 36, .y = 0});
	else if (kind == SOUL)
		return ((t_vector_int){.x = 42, .y = 0});
	else if (kind == DOGMEAL)
		return ((t_vector_int){.x = 49, .y = 0});
	else if (kind == GUN)
		return ((t_vector_int){.x = 26, .y = 0});
	else if (kind == AMMO)
		return ((t_vector_int){.x = 56, .y = 0});
	else if (kind == TREASURE_0)
		return ((t_vector_int){.x = 50, .y = 0});
	else if (kind == TREASURE_1)
		return ((t_vector_int){.x = 51, .y = 0});
	else if (kind == TREASURE_2)
		return ((t_vector_int){.x = 38, .y = 0});
	return ((t_vector_int){.x = -1, .y = -1});
}

static t_vector_int	get_transparency_end(int kind)
{
	if (kind == BARREL)
		return ((t_vector_int){.x = 94, .y = 61});
	else if (kind == BONES)
		return ((t_vector_int){.x = 122, .y = 110});
	else if (kind == LAMP)
		return ((t_vector_int){.x = 84, .y = -1});
	else if (kind == GUARD)
		return ((t_vector_int){.x = 87, .y = 34});
	else if (kind == CHANDELIER)
		return ((t_vector_int){.x = 85, .y = -1});
	else if (kind == TABLE)
		return ((t_vector_int){.x = 106, .y = 60});
	else if (kind == WELL_EMPTY || kind == WELL_FULL)
		return ((t_vector_int){.x = 107, .y = 60});
	else if (kind == PLANT)
		return ((t_vector_int){.x = 81, .y = 30});
	else if (kind == TABLE_CHAIRS)
		return ((t_vector_int){.x = 119, .y = 61});
	else if (kind == LAMP_STANDING)
		return ((t_vector_int){.x = 85, .y = 52});
	else if (kind == DOG)
		return ((t_vector_int){.x = 84, .y = 40});
	else if (kind == STATUE)
		return ((t_vector_int){.x = 105, .y = 2});
	else if (kind == TREE)
		return ((t_vector_int){.x = 96, .y = 21});
	else if (kind == GREEN_BARREL)
		return ((t_vector_int){.x = 90, .y = 63});
	else if (kind == POT)
		return ((t_vector_int){.x = 85, .y = 65});
	else if (kind == FLAG)
		return ((t_vector_int){.x = 81, .y = 6});
	else if (kind == STIMULANT)
		return ((t_vector_int){.x = 93, .y = 109});
	else if (kind == MEDKIT)
		return ((t_vector_int){.x = 91, .y = 107});
	else if (kind == SOUL)
		return ((t_vector_int){.x = 85, .y = 68});
	else if (kind == DOGMEAL)
		return ((t_vector_int){.x = 78, .y = 108});
	else if (kind == GUN)
		return ((t_vector_int){.x = 101, .y = 97});
	else if (kind == AMMO)
		return ((t_vector_int){.x = 72, .y = 108});
	else if (kind == TREASURE_0)
		return ((t_vector_int){.x = 77, .y = 89});
	else if (kind == TREASURE_1)
		return ((t_vector_int){.x = 76, .y = 95});
	else if (kind == TREASURE_2)
		return ((t_vector_int){.x = 90, .y = 101});
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

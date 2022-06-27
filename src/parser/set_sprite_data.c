/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_sprite_data.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 11:44:20 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/27 11:25:16 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	set_sprite_data(t_sprite *sprite, t_vector_int pos, uint8_t ***map, \
	t_data *data, bool is_enemy)
{
	sprite->map_pos.x = pos.x + 0.5;
	sprite->map_pos.y = pos.y + 0.5;
	if (!is_enemy)
		sprite->kind = map[pos.y][pos.x][1];
	else
		sprite->kind = get_enemy_kind(map[pos.y][pos.x][2]);
	if (is_enemy)
	{
		set_enemy_data(sprite, map, pos);
		data->level.enemies_count++;
	}
	else if (sprite->kind >= CROSS && sprite->kind <= CROWN)
		data->level.treasure_count++;
	if (is_enemy)
		sprite->texture = data->mlx.tex.enmy[0];// TODO fix this shit
	else
		sprite->texture = data->mlx.tex.obj[sprite->kind - 1];
	if (!is_enemy)
	{
		sprite->transp.start.x = (128 - data->mlx.tex.obj[sprite->kind - 1]->width) / 2 - 1;
		sprite->transp.end.x = 127 - sprite->transp.start.x;
		if (sprite->transp.start.x < 0)
		{
			sprite->transp.start.x = 0;
			sprite->transp.end.x = data->mlx.tex.obj[sprite->kind - 1]->width;
		}
		sprite->transp.start.y = 0;
		sprite->transp.end.y = data->mlx.tex.obj[sprite->kind - 1]->height;
		printf("kind: %d, transpbegin: %d,%d, end: %d,%d\n", sprite->kind, sprite->transp.start.x, sprite->transp.start.y, sprite->transp.end.x, sprite->transp.end.y);
	}
}

void	set_sprite_positions(uint8_t ***map, t_data *data)
{
	int	i;
	int	j;
	int	sprite_cnt;

	data->sprite = ft_calloc(sizeof(t_sprite), data->level.number_of_sprites);
	if (!data->sprite)
		exit(1);
	sprite_cnt = 0;
	i = -1;
	while (++i < data->level.map_h)
	{
		j = -1;
		while (++j < data->level.map_w)
		{
			if (is_sprite_tile(map[i][j][1]))
				set_sprite_data(&data->sprite[sprite_cnt++], \
					(t_vector_int){.x = j, .y = i}, map, data, false);
			else if (is_enemy_tile(map[i][j][2]))
				set_sprite_data(&data->sprite[sprite_cnt++], \
					(t_vector_int){.x = j, .y = i}, map, data, true);
		}
	}
}

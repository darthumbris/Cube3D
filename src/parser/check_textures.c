/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_textures.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/03 09:38:25 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/11 14:19:01 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//TODO make difference between bonus and not bonus
static bool	is_loaded(t_data *data, char c)
{
	if (data->mlx.tex.texarr[get_sprite_kind(c, data)] == NULL)
		return (false);
	return (true);
}

static bool	check_bonus_textures(t_data *data)
{
	if (data->bonus && (data->mlx.tex.texarr[HUD_MAIN] == NULL || \
		data->mlx.tex.texarr[HUD_NUMBERS] == NULL || \
		data->mlx.tex.texarr[HUD_FACES] == NULL || \
		data->mlx.tex.texarr[DOOR_FRAME] == NULL || \
		data->mlx.tex.texarr[SPRITESHEET_DOG] == NULL || \
		data->mlx.tex.texarr[SPRITESHEET_GUARD] == NULL))
	{
		printf("error: bonus texture failed to load\n");
		return (false);
	}
	if (!data->bonus)
		data->floor_ceiling = false;
	else if (data->mlx.tex.texarr[FLOOR] == NULL || \
		data->mlx.tex.texarr[CEILING] == NULL)
		data->floor_ceiling = false;
	else
		data->floor_ceiling = true;
	return (true);
}

bool	check_needed_textures_loaded(t_data *data)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (data->level.map[i])
	{
		j = 0;
		while (data->level.map[i][j])
		{
			c = data->level.map[i][j];
			if (c != '0' && c != ' ')
			{
				if (!is_loaded(data, c))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (check_bonus_textures(data));
}

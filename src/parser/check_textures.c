/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_textures.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/03 09:38:25 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/10 14:13:42 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static bool	is_loaded(t_data *data, char c, int i, int j)
{
	const int	kind = get_sprite_kind(c, data);

	if (data->mlx.tex.texarr[kind] == NULL)
	{
		if (DEBUG_MODE)
			printf("Failed to load a sprite\n");
		return (false);
	}
	if (is_nonblocking_kind(kind))
		data->level.map[i][j] = '0';
	return (true);
}

static bool	check_weapon_textures(t_lodtex tex)
{
	if (tex.texarr[PISTOL0] == NULL || tex.texarr[PISTOL1] == NULL || \
		tex.texarr[PISTOL2] == NULL || tex.texarr[PISTOL3] == NULL || \
		tex.texarr[KNIFE0] == NULL || tex.texarr[KNIFE1] == NULL || \
		tex.texarr[KNIFE2] == NULL || tex.texarr[KNIFE3] == NULL || \
		tex.texarr[MACHINEGUN0] == NULL || tex.texarr[MACHINEGUN1] == NULL || \
		tex.texarr[MACHINEGUN2] == NULL || tex.texarr[MACHINEGUN3] == NULL)
	{
		if (DEBUG_MODE)
			printf("Failed to load weapons.\n");
		return (true);
	}
	return (false);
}

static bool	check_bonus_textures(t_data *data)
{
	if (data->bonus && (data->mlx.tex.texarr[HUD_MAIN] == NULL || \
		data->mlx.tex.texarr[HUD_NUMBERS] == NULL || \
		data->mlx.tex.texarr[HUD_FACES] == NULL || \
		data->mlx.tex.texarr[DOOR_FRAME] == NULL || \
		data->mlx.tex.texarr[SPRITESHEET_DOG] == NULL || \
		data->mlx.tex.texarr[SPRITESHEET_GUARD] == NULL || \
		check_weapon_textures(data->mlx.tex) || \
		data->mlx.tex.texarr[SCORE_SCREEN] == NULL || \
		data->mlx.tex.texarr[SCORE_NUMBERS] == NULL || \
		data->mlx.tex.texarr[GAME_OVER] == NULL || \
		data->mlx.tex.texarr[ELEVATOR_UP] == NULL))
		return (error_msg("Bonus texture failed to load"));
	if (data->mlx.tex.texarr[FLOOR] == NULL || \
		data->mlx.tex.texarr[CEILING] == NULL)
		data->floor_ceiling = false;
	else
		data->floor_ceiling = true;
	if (data->floor_ceiling == false)
	{
		printf("Failed to load floor or ceiling textures. ");
		printf("Switching over to Colours\n");
	}
	if (data->floor_ceiling == false && data->level.colors_error != 0)
		return (error_msg("Colors not configured"));
	return (true);
}

bool	check_needed_textures_loaded(t_data *data)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < data->level.map_h)
	{
		j = 0;
		while (j < data->level.map_w)
		{
			c = data->level.map[i][j];
			if (c != '0' && c != ' ')
			{
				if (!is_loaded(data, c, i, j))
					return (error_msg("Failure loading textures"));
			}
			j++;
		}
		i++;
	}
	return (check_bonus_textures(data));
}

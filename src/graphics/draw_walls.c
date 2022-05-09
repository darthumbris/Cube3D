/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_walls.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/02 15:12:41 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/09 11:31:29 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static int	get_block_id(char c)
{
	if (c == 'D')
		return (DOOR_WALL_1);
	else if (c == '<')
		return (HIDDEN_WALL_1);
	else if (c == '{')
		return (HIDDEN_WALL_2);
	else if (c == '^')
		return (HIDDEN_WALL_3);
	else if (c == '_')
		return (HIDDEN_WALL_4);
	else
		return (c - '1' + WALL_1);
}

mlx_texture_t	*get_texture(t_data *data, t_vector_double pos)
{
	int				block_id;

	if (data->caster.door_hit)
		block_id = get_block_id(data->level.map[data->caster.door->y][data->caster.door->x]);
	else if (data->caster.secret_hit)
		block_id = get_block_id(data->level.map[data->caster.secret->y][data->caster.secret->x]);
	else
		block_id = get_block_id(data->level.map[(int)pos.y][(int)pos.x]);
	data->caster.secret = NULL;
	if (data->caster.side == 0)
	{
		if (block_id == DOOR_WALL_1)
		{
			if (data->caster.door->direction == EAST_WEST)
				return (data->mlx.tex.texarr[DOOR_WALL_1]);
			return (data->mlx.door_frame);
		}
		return (data->mlx.tex.texarr[block_id]);
	}
	else
	{
		if (block_id == DOOR_WALL_1)
		{
			if (data->caster.door->direction == EAST_WEST)
				return (data->mlx.door_frame);
			return (data->mlx.tex.texarr[DOOR_WALL_1]);
		}
		return (data->mlx.tex.texarr[block_id]);
	}
}

void	draw_walls(t_data *data, int x, mlx_texture_t *texture)
{
	int				y;
	uint8_t			*pix[2];
	const int		max = data->mlx.mlx_handle->height - \
	data->mlx.tex.texarr[HUD_MAIN]->height * data->hud.scale;

	y = data->caster.draw_start;
	pix[0] = texture->pixels;
	pix[1] = data->mlx.fg->pixels + ((y * data->floor.width4) + x * 4);
	while (y < data->caster.draw_end && y < max)
	{
		data->caster.tex.y = (int)data->caster.tex_pos % texture->height;
		data->caster.tex_pos += data->caster.step_y;
		*(uint32_t *)pix[1] = (*(int *)(pix[0] + \
		((data->caster.tex.y * texture->width + data->caster.tex.x) * 4)));
		pix[1] += data->floor.width4;
		++y;
	}
}

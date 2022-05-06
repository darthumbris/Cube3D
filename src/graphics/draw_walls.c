/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_walls.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/02 15:12:41 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/06 16:56:55 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static int	get_block_id(char c)
{
	if (c == 'D')
		return (DOOR_SPRITE);
	if (c == 'h')
		return (HIDDEN);
	if (c == 'H')
		return (HIDDEN_2);
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
	if (data->caster.side == 0)
	{
		if (block_id == DOOR_SPRITE)
		{
			if (data->caster.door->direction == EAST_WEST)
				return (data->mlx.tex.texarr[DOOR_SPRITE]);
			return (data->mlx.door_frame);
		}
		if (data->caster.dir == EAST)
			return (data->mlx.tex.texarr[block_id]);
		return (data->mlx.tex.texarr[block_id]);
	}
	else
	{
		if (block_id == DOOR_SPRITE)
		{
			if (data->caster.door->direction == EAST_WEST)
				return (data->mlx.door_frame);
			return (data->mlx.tex.texarr[DOOR_SPRITE]);
		}
		if (data->caster.dir == SOUTH)
			return (data->mlx.tex.texarr[block_id]);
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

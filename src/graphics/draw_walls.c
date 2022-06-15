/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_walls.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/02 15:12:41 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/15 16:18:20 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static mlx_texture_t	*select_correct_side(t_data *data, int block_id)
{
	if (data->caster.side == 0)
	{
		if (is_door_tile(block_id))
		{
			if (data->caster.door->direction == EAST_WEST)
				return (data->mlx.tex.wall[block_id]);
			return (data->mlx.tex.wall[50]);
		}
		return (data->mlx.tex.wall[block_id]);
	}
	else
	{
		if (is_door_tile(block_id))
		{
			if (data->caster.door->direction == EAST_WEST)
				return (data->mlx.tex.wall[50]);
			return (data->mlx.tex.wall[block_id]);
		}
		return (data->mlx.tex.wall[block_id]);
	}
}

mlx_texture_t	*get_texture(t_data *data, t_vector_double pos)
{
	int				block_id;

	if (data->caster.door_hit)
		block_id = data->level.map_planes[data->caster.door->y] \
								[data->caster.door->x][0] - 1;
	else if (data->caster.secret_hit)
		block_id = data->level.map_planes[data->caster.secret->y] \
								[data->caster.secret->x][0] - 1;
	else
		block_id = get_door_lst_nbr(data->level.map_planes[(int)pos.y][(int)pos.x][0]);
	return (select_correct_side(data, block_id));
}

void	draw_walls(t_data *data, int x, mlx_texture_t *texture)
{
	int				y;
	uint8_t			*pix[2];
	int				max;

	max = data->mlx.mlx_handle->height - \
		data->mlx.tex.hud[HUD_M_T]->height * data->hud.scale;
	y = data->caster.draw_start;
	pix[0] = texture->pixels;
	pix[1] = data->mlx.fg->pixels + ((y * data->floor.width4) + x * 4);
	// printf("x: %d, y: %d\n", x, y);
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

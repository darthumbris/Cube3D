/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_hud.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/28 16:50:48 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/15 16:12:25 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_single_nbr(t_data *data, int nbr, int x_pos)
{
	t_vector_int	pos;
	t_vector_int	tex_pos;
	int				wh[2];

	pos.x = x_pos;
	pos.y = data->mlx.mlx_handle->height - 24 * data->hud.scale;
	tex_pos.x = nbr % 10;
	tex_pos.y = 0;
	wh[0] = 8;
	wh[1] = 16;
	draw_texture_area(data->mlx.hud, data->mlx.tex.hud[HUD_N_T], \
						pos, tex_pos, wh, data->hud.scale);
}

void	draw_faces(t_data *data)
{
	t_vector_int	pos;
	t_vector_int	tex_pos;
	int				wh[2];

	pos.x = data->hud.face_pos_x;
	pos.y = data->mlx.mlx_handle->height - 35 * data->hud.scale;
	tex_pos.x = (rand() % 3);
	tex_pos.y = ((99 - data->player.health) / 20);
	wh[0] = 30;
	wh[1] = 31;
	draw_texture_area(data->mlx.hud, data->mlx.tex.hud[HUD_F_T], \
					pos, tex_pos, wh, 3);
}

void	draw_hud(t_data *data)
{
	t_vector_int	pos;

	pos.x = data->hud.border_width / 2;
	pos.y = data->mlx.mlx_handle->height - \
			data->mlx.tex.hud[HUD_M_T]->height * data->hud.scale;
	draw_texture(data->mlx.hud, data->mlx.tex.hud[HUD_M_T], pos, data->hud.scale);
}

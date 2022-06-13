/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_texture.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 08:50:05 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/13 11:41:28 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//TODO MAKE BOTH OF THESE FUNCTIONS ALSO BE USED FOR ALL OTHER DRAW FUNCTIONS
// (draw enemies draw hud etc.)
void	draw_texture_area(mlx_image_t *img, mlx_texture_t *tex, \
					t_vector_int start, t_vector_int tex_pos, \
					int wh[2], double scale)
{
	uint8_t			*pixels;
	t_vector_int	pos;
	t_vector_int	pos_tex;
	t_vector_int	end;
	uint32_t		color;
	const double	inv_scale = 1 / scale;

	pos.y = start.y;
	end.x = start.x + (wh[0] * scale);
	end.y = start.y + (wh[1] * scale);
	pixels = img->pixels + ((start.x + start.y * img->width) * 4);
	while (pos.y < end.y && pos.y < (int)img->height)
	{
		pos.x = start.x;
		while (pos.x < end.x && pos.x < (int)img->width)
		{
			pos_tex.x = (pos.x - start.x) * inv_scale + tex_pos.x * wh[0];
			pos_tex.y = (pos.y - start.y) * inv_scale + tex_pos.y * wh[1];
			color = (*(int *)(tex->pixels + ((pos_tex.x + \
				pos_tex.y * tex->width) * 4)));
			if (color)
				*(uint32_t *)pixels = color;
			pos.x++;
			pixels += 4;
		}
		if (pos.x < (int)img->width)
			pixels += (img->width * 4 - (end.x - start.x) * 4);
		pos.y++;
	}
}

void	draw_texture(mlx_image_t *img, mlx_texture_t *tex, \
					t_vector_int start, double scale)
{
	uint8_t			*pixels;
	t_vector_int	pos;
	t_vector_int	pos_tex;
	t_vector_int	end;
	uint32_t		color;
	const double	inv_scale = 1 / scale;

	pos.y = start.y;
	end.x = start.x + (tex->width * scale);
	end.y = start.y + (tex->height * scale);
	pixels = img->pixels + ((start.x + start.y * img->width) * 4);
	while (pos.y < end.y && pos.y < (int)img->height)
	{
		pos.x = start.x;
		while (pos.x < end.x && pos.x < (int)img->width)
		{
			pos_tex.x = (pos.x - start.x) * inv_scale;
			pos_tex.y = (pos.y - start.y) * inv_scale;
			color = (*(int *)(tex->pixels + ((pos_tex.x + \
				pos_tex.y * tex->width) * 4)));
			if (color)
				*(uint32_t *)pixels = color;
			pos.x++;
			pixels += 4;
		}
		if (pos.x < (int)img->width)
			pixels += (img->width * 4 - (end.x - start.x) * 4);
		pos.y++;
	}
}

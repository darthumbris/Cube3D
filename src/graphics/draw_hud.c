/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_hud.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/28 16:50:48 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/04/28 17:28:38 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//TODO make this draw the hud to scale using the hud.png. Also needs to be updated
//TODO the minimap can be put in the right corner of the hud
void	draw_hud(t_data *data)
{
	mlx_texture_t	*temp;
	t_vector_int	pixel;
	t_vector_int	tex;
	uint8_t			*pixels;
	uint8_t			*hud;

	data->mlx.hud = mlx_new_image(data->mlx.mlx_handle, SCREEN_WIDTH, SCREEN_HEIGHT);
	temp = mlx_load_png("assets/hud/hud.png");
	if (!temp)
		return ;
	pixel.x = 0;
	pixels = temp->pixels;
	while (pixel.x < data->mlx.mlx_handle->width)
	{
		tex.x = pixel.x / 4;
		hud = data->mlx.hud->pixels + \
			(((data->mlx.mlx_handle->height - 1) * \
			data->mlx.mlx_handle->width * 4 + (pixel.x * 4)));
		pixel.y = data->mlx.mlx_handle->height - HUD_HEIGHT;
		while (pixel.y < data->mlx.mlx_handle->height)
		{
			tex.y = ((data->mlx.mlx_handle->height - 1) - pixel.y) / 4;
			*(uint32_t *)hud = (*(int *)(pixels + ((tex.y * temp->width + tex.x) * 4)));
			hud -= data->mlx.mlx_handle->width * 4;
			pixel.y++;
		}
		pixel.x++;
	}
}

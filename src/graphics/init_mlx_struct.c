/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mlx_struct.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:37:12 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/06/15 14:16:56 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//temp for now
// static bool	init_sprites(t_data *data)
// {
// 	unsigned int	i;

// 	if (data->level.number_of_sprites == 0)
// 		return (true);
// 	data->sprite_lst = new_sprite(data->sprite[0]);
// 	i = 1;
// 	while (i < data->level.number_of_sprites)
// 	{
// 		add_sprite(&(data->sprite_lst), data->sprite[i]);
// 		i++;
// 	}
// 	sort_sprites(data, &data->sprite_lst);
// 	return (check_needed_textures_loaded(data));
// }

bool	init_mlx(t_data *data)
{
	if (SCREEN_WIDTH < 320 || SCREEN_HEIGHT < 240)
		return (error_msg("Screen size too small"));
	data->mlx.mlx_handle = mlx_init
		(SCREEN_WIDTH, SCREEN_HEIGHT, "cube3D", false);
	if (data->mlx.mlx_handle == NULL)
		return (error_msg("Failed to init mlx"));
	if (!data->bonus && data->level.colors_error != 0)
		return (error_msg("Colors not configured"));
	data->mlx.fg = mlx_new_image
		(data->mlx.mlx_handle, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->mlx.bg = mlx_new_image
		(data->mlx.mlx_handle, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (data->mlx.fg == NULL || data->mlx.bg == NULL)
		return (error_msg("Failed to init images"));
	data->floor.inverse_width = 1 / (double)data->mlx.mlx_handle->width;
	data->floor.pos_z = 0.5 * data->mlx.mlx_handle->height;
	data->floor.halve_height = data->mlx.mlx_handle->height / 2;
	data->floor.halve_width = data->mlx.mlx_handle->width / 2;
	data->floor.width4 = data->mlx.mlx_handle->width * 4;
	data->spr_cast.zbuffer = ft_calloc(sizeof(double), SCREEN_WIDTH);
	if (!data->spr_cast.zbuffer)
		return (error_msg("Malloc error"));
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:47:34 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/02 16:46:36 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <stdio.h>

/*
//TODO make a single texture for all the hurt faces
 * make the init_textures of the hud be depended on 
 * the path given in the .cub file.
 * make the draw hud function scalable and not have a 
 * fixed value for the textures and
 * positions of where the numbers will be drawn.
*/
static void	draw_hud_test(t_data *data)
{
	init_hud(data);
	data->level.level_number = 1;
	data->player.ammo = 8;
	data->player.lives = 3;
	data->player.health = 100;
	data->player.score = 0;
	draw_hud(data);
	draw_numbers(data);
	data->update_hud = false;
}

int	main(int argc, char **argv)
{
	t_data			data;

	data.bonus = false;
	data.number_of_textures = HUD_FACES;
	if (argc != 2 || !parse_config(&data) || !parse_input(argv, &data) || \
		!init_mlx(&data))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	draw_background(&data);
	raycaster(&data);
	mlx_set_mouse_pos(data.mlx.mlx_handle, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mlx_image_to_window(data.mlx.mlx_handle, data.mlx.bg, 0, 0);
	mlx_image_to_window(data.mlx.mlx_handle, data.mlx.fg, 0, 0);
	if (data.bonus)
	{
		draw_hud_test(&data);
		mlx_image_to_window(data.mlx.mlx_handle, data.mlx.hud, 0, 0);
		mlx_image_to_window(data.mlx.mlx_handle, data.mlx.minimap, \
		data.mlx.minimap->width + data.mlx.mlx_handle->width - \
		data.mlx.minimap->width - 71 * data.mlx.hud_scale, \
		data.mlx.mlx_handle->height - data.mlx.minimap->height - 1 - \
		data.mlx.hud_scale * 4);
	}
	mlx_loop_hook(data.mlx.mlx_handle, game_loop, &data);
	mlx_key_hook(data.mlx.mlx_handle, key_handler, &data);
	mlx_set_cursor_mode(data.mlx.mlx_handle, MLX_MOUSE_DISABLED);
	mlx_loop(data.mlx.mlx_handle);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:47:34 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/28 14:41:11 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_data		data;

	data.bonus = false;
	data.number_of_textures = ITEM_8;
	if (argc != 2 || !parse_input(argv, &data) || !init_mlx(&data))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	draw_background(&data);
	raycaster(&data);
	mlx_set_mouse_pos(data.mlx.mlx_handle, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mlx_image_to_window(data.mlx.mlx_handle, data.mlx.bg, 0, 0);
	mlx_image_to_window(data.mlx.mlx_handle, data.mlx.fg, 0, 0);
	mlx_loop_hook(data.mlx.mlx_handle, game_loop, &data);
	mlx_key_hook(data.mlx.mlx_handle, key_handler, &data);
	mlx_loop(data.mlx.mlx_handle);
	return (0);
}

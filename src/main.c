/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:47:34 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/19 14:26:57 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc != 2 || !parse_input(argv, &data))
	{
		write(2, "Error\n", 6); //nothings freed for now
		return (1);
	}
	init_mlx(&data);
	draw_background(&data);
	mlx_image_to_window(data.mlx.mlx_handle, data.mlx.bg, 0, 0);
	raycaster(&data);
	mlx_set_mouse_pos(data.mlx.mlx_handle, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mlx_image_to_window(data.mlx.mlx_handle, data.mlx.fg, 0, 0);
	mlx_loop_hook(data.mlx.mlx_handle, game_loop, &data);
	mlx_cursor_hook(data.mlx.mlx_handle, cursor_movement, &data);
	mlx_mouse_hook(data.mlx.mlx_handle, mouse_events, &data);
	mlx_key_hook(data.mlx.mlx_handle, key_handler, &data);
	mlx_loop(data.mlx.mlx_handle);
	return (0);
}

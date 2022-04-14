/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:47:34 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/14 16:00:17 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <stdio.h>

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param); //free shit afterwards
	if (mlx_is_key_down(param, MLX_KEY_W))
		;//change player pos
	if (mlx_is_key_down(param, MLX_KEY_S))
		;//change player pos
	if (mlx_is_key_down(param, MLX_KEY_A))
		;//change player pos
	if (mlx_is_key_down(param, MLX_KEY_D))
		;//change player pos
}

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
	mlx_image_to_window(data.mlx.mlx_handle, data.mlx.bg, 0 , 0);
	raycaster(&data);
	mlx_image_to_window(data.mlx.mlx_handle, data.mlx.fg, 0, 0);
	mlx_loop_hook(data.mlx.mlx_handle, game_loop, &data);
	mlx_loop(data.mlx.mlx_handle);
	return (0);
}

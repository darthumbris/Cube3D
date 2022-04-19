/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:47:34 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/04/19 15:23:19 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <stdio.h>

void	printfunc(t_data *data)
{
	for (int i = 0; data->level.map[i]; i++)
		printf("%s\n", data->level.map[i]);
	data->caster.framedone = true;
	printf("-------------------------------------\n");
	printf("%s\n", data->level.no_texture_path);
	printf("%s\n", data->level.so_texture_path);
	printf("%s\n", data->level.we_texture_path);
	printf("%s\n", data->level.ea_texture_path);
	printf("%x\n", data->level.floor_color);
	printf("%x\n", data->level.ceiling_color);
	printf("%f-%f\n", data->player.pos.x, data->player.pos.y);
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc != 2 || !parse_input(argv, &data) || !init_mlx(&data))
	{
		write(2, "Error\n", 6); //nothings freed for now
		return (1);
	}
	printfunc(&data); //TODO: remove;
	draw_background(&data);
	mlx_image_to_window(data.mlx.mlx_handle, data.mlx.bg, 0, 0);
	raycaster(&data);
	mlx_set_mouse_pos(data.mlx.mlx_handle, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mlx_image_to_window(data.mlx.mlx_handle, data.mlx.fg, 0, 0);
	mlx_loop_hook(data.mlx.mlx_handle, game_loop, &data);
	mlx_key_hook(data.mlx.mlx_handle, key_handler, &data);
	mlx_loop(data.mlx.mlx_handle);
	return (0);
}

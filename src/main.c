/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:47:34 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/11 10:51:43 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <stdio.h>
#include <time.h>

static void	draw_hud_test(t_data *data)
{
	init_hud(data);
	data->level.level_number = 1;
	data->player.ammo = 8;
	data->player.lives = 3;
	data->player.health = 100;
	data->player.score = 0;
	data->player.active_weapon = PISTOL;
	data->player.machine_gun_pickup = false;
	draw_hud(data);
	draw_numbers(data);
	draw_faces(data);
	data->update_hud = false;
}

int	main(int argc, char **argv)
{
	t_data			data;

	srand(time(NULL)); // for the random faces
	data.bonus = false;
	data.number_of_textures = HUD_FACES;
	data.level.number_of_sprites = 0;
	data.level.door_count = 0;
	data.level.secret_count = 0;
	if (argc != 2 || !parse_config(&data) || !parse_input(argv, &data) || \
		!init_mlx(&data))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (!init_door_map(&data))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	init_doors(&data);
	init_secrets(&data);
	draw_background(&data);
	raycaster(&data);
	mlx_image_to_window(data.mlx.mlx_handle, data.mlx.bg, 0, 0);
	mlx_image_to_window(data.mlx.mlx_handle, data.mlx.fg, 0, 0);
	if (data.bonus)
	{
		draw_hud_test(&data);
		init_weapons(&data);
		draw_weapons(&data, data.mlx.weapon_anim[PISTOL].tex0);
		mlx_image_to_window(data.mlx.mlx_handle, data.mlx.weapon, 0, 0);
		mlx_image_to_window(data.mlx.mlx_handle, data.mlx.hud, 0, 0);
		mlx_image_to_window(data.mlx.mlx_handle, data.mlx.minimap, \
		data.hud.pos_map.x, data.hud.pos_map.y);
	}
	mlx_loop_hook(data.mlx.mlx_handle, game_loop, &data);
	mlx_set_cursor_mode(data.mlx.mlx_handle, MLX_MOUSE_DISABLED);
	mlx_key_hook(data.mlx.mlx_handle, key_handler, &data);
	mlx_loop(data.mlx.mlx_handle);
	return (0);
}

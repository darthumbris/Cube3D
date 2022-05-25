/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:47:34 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/25 10:41:06 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "cubed.h"

static void	init_player(t_data *data)
{
	init_hud(data);
	data->level.level_number = 1;
	data->player.game_over = false;
	data->player.ammo = 8;
	data->player.lives = 3;
	data->player.health = 100;
	data->player.score = 0;
	data->player.active_weapon = PISTOL;
	data->player.machine_gun_pickup = false;
	data->player.start_pos.x = data->cam.pos.x;
	data->player.start_pos.y = data->cam.pos.y;
	data->player.start_dir.x = data->cam.dir.x;
	data->player.start_dir.y = data->cam.dir.y;
	data->player.start_plane.x = data->cam.plane.x;
	data->player.start_plane.y = data->cam.plane.y;
	data->player.enemies_killed = 0;
	data->player.secrets_found = 0;
	data->player.treasure_found = 0;
	draw_hud(data);
	draw_numbers(data);
	draw_faces(data);
	data->update_hud = false;
}

//srand is for the faces in the hud
static void	init_data(t_data *data)
{
	int	i;

	srand(time(NULL));
	data->floor_ceiling = false;
	data->bonus = false;
	data->number_of_textures = GAME_OVER;
	data->level.number_of_sprites = 0;
	data->level.door_count = 0;
	data->level.secret_count = 0;
	data->level.treasure_count = 0;
	data->level.enemies_count = 0;
	data->level.colors_error = 2;
	data->sound.cur = 0;
	i = 0;
	while (i <= data->number_of_textures)
		data->level.paths.path[i++] = NULL;
}

static void	images_to_window(t_data *data)
{
	struct timeval	timev;

	mlx_image_to_window(data->mlx.mlx_handle, data->mlx.bg, 0, 0);
	mlx_image_to_window(data->mlx.mlx_handle, data->mlx.fg, 0, 0);
	if (data->bonus)
	{
		init_player(data);
		init_weapons(data);
		draw_weapons(data, data->mlx.weapon_anim[PISTOL].tex0, \
					data->mlx.weapon);
		mlx_image_to_window(data->mlx.mlx_handle, data->mlx.weapon, 0, 0);
		mlx_image_to_window(data->mlx.mlx_handle, data->mlx.hud, 0, 0);
		mlx_image_to_window(data->mlx.mlx_handle, data->mlx.minimap, \
		data->hud.pos_map.x, data->hud.pos_map.y);
	}
	gettimeofday(&timev, NULL);
	data->player.start_time = timev.tv_sec;
}

int	main(int argc, char **argv)
{
	t_data			data;

	if (argc != 2)
	{
		write(2, "Error: Incorrect amount of arguments\n", 37);
		return (1);
	}
	init_data(&data);
	if (!parse_config(&data) || !parse_input(argv, &data) || \
		!sound_init(&data) || !init_mlx(&data) || !init_door_map(&data))
		return (1);
	if (data.bonus)
		ma_sound_start(data.sound.soundtrack[0]);
	init_doors(&data);
	init_secrets(&data);
	draw_background(&data);
	raycaster(&data);
	images_to_window(&data);
	mlx_loop_hook(data.mlx.mlx_handle, game_loop, &data);
	if (data.bonus)
		mlx_set_cursor_mode(data.mlx.mlx_handle, MLX_MOUSE_DISABLED);
	mlx_key_hook(data.mlx.mlx_handle, key_handler, &data);
	mlx_loop(data.mlx.mlx_handle);
	mlx_terminate(data.mlx.mlx_handle);
	return (0);
}

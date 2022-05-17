/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:47:34 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/17 14:16:19 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <stdio.h>
#include <time.h>
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

static void	init_player(t_data *data)
{
	init_hud(data);
	data->level.level_number = 1;
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
	data->bonus = false;
	data->number_of_textures = SPRITESHEET_DOG;
	data->level.number_of_sprites = 0;
	data->level.door_count = 0;
	data->level.secret_count = 0;
	i = 0;
	while (i < SPRITESHEET_DOG + 1)
		data->level.paths.path[i++] = NULL;
}

static void	images_to_window(t_data *data)
{
	mlx_image_to_window(data->mlx.mlx_handle, data->mlx.bg, 0, 0);
	mlx_image_to_window(data->mlx.mlx_handle, data->mlx.fg, 0, 0);
	if (data->bonus)
	{
		init_player(data);
		init_weapons(data);
		draw_weapons(data, data->mlx.weapon_anim[PISTOL].tex0);
		mlx_image_to_window(data->mlx.mlx_handle, data->mlx.weapon, 0, 0);
		mlx_image_to_window(data->mlx.mlx_handle, data->mlx.hud, 0, 0);
		mlx_image_to_window(data->mlx.mlx_handle, data->mlx.minimap, \
		data->hud.pos_map.x, data->hud.pos_map.y);
	}
}

int	main(int argc, char **argv)
{
	t_data			data;

	init_data(&data);
	if (argc != 2 || !parse_config(&data) || !parse_input(argv, &data) || \
		!init_mlx(&data) || !init_door_map(&data))
	{
		write(2, "Error\n", 6);
		return (1);
	}

    data.sound.result = ma_engine_init(NULL, &data.sound.engine);
    if (data.sound.result != MA_SUCCESS) 
	{
        printf("Failed to initialize audio engine.");
		return 1;
    }
	ma_sound_group_init(&data.sound.engine, 0, NULL, &data.sound.music_g);
	ma_sound_group_init(&data.sound.engine, 0, NULL, &data.sound.sfx_g);
	ma_sound_init_from_file(&data.sound.engine, "./searchn.mp3", 0, &data.sound.music_g, NULL, &data.sound.soundtrack[SEARCHN]);
	ma_sound_init_from_file(&data.sound.engine, "./warmarch.mp3", 0, &data.sound.music_g, NULL, &data.sound.soundtrack[WARMARCH]);
	ma_sound_init_from_file(&data.sound.engine, "./corner.mp3", 0, &data.sound.music_g, NULL, &data.sound.soundtrack[CORNER]);

	data.sound.curr = SEARCHN;
	ma_sound_start(&data.sound.soundtrack[SEARCHN]);
    //ma_engine_uninit(&engine);
	init_doors(&data);
	init_secrets(&data);
	draw_background(&data);
	raycaster(&data);
	images_to_window(&data);
	mlx_loop_hook(data.mlx.mlx_handle, game_loop, &data);
	mlx_set_cursor_mode(data.mlx.mlx_handle, MLX_MOUSE_DISABLED);
	mlx_key_hook(data.mlx.mlx_handle, key_handler, &data);
	mlx_loop(data.mlx.mlx_handle);
	return (0);
}

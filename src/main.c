/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:47:34 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/06/13 16:32:06 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "cubed.h"

// static void	test_map_to_file(void)
// {
// 	int		i;
// 	int		j;
// 	int		fd;
// 	char	**temp = NULL;

// 	fd = open("./maps/help.txt", O_RDONLY);
// 	temp = readmap(fd, temp);
// 	i = 0;
// 	while (temp[i])
// 	{
// 		j = 0;
// 		while (temp[i][j])
// 		{
// 			if (ft_isdigit(temp[i][j]))
// 			{
// 				if (temp[i][j] == '0')
// 					printf("%d %d 0 %d,", j, i, 160);
// 				else
// 					printf("%d %d 0 %d,", j, i, temp[i][j] - '0');
// 			}
// 			else if (temp[i][j] == 'N')
// 				printf("%d %d 2 19,", j, i);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// static void	init_player(t_data *data)
// {
// 	init_hud(data);
// 	data->level.level_number = 1;
// 	data->player.game_over = false;
// 	data->player.ammo = 8;
// 	data->player.lives = 3;
// 	data->player.health = 100;
// 	data->player.score = 0;
// 	data->player.active_weapon = PISTOL;
// 	data->player.machine_gun_pickup = false;
// 	data->player.start_pos.x = data->cam.pos.x;
// 	data->player.start_pos.y = data->cam.pos.y;
// 	data->player.start_dir.x = data->cam.dir.x;
// 	data->player.start_dir.y = data->cam.dir.y;
// 	data->player.start_plane.x = data->cam.plane.x;
// 	data->player.start_plane.y = data->cam.plane.y;
// 	data->player.enemies_killed = 0;
// 	data->player.secrets_found = 0;
// 	data->player.treasure_found = 0;
// 	draw_hud(data);
// 	draw_numbers(data);
// 	draw_faces(data);
// 	data->update_hud = false;
// }

//srand is for the faces in the hud
static void	init_data(t_data *data)
{
	int	i;

	srand(time(NULL));
	data->floor_ceiling = false;
	data->bonus = true;
	data->number_of_textures = GAME_OVER;
	data->level.number_of_sprites = 0;
	data->level.door_count = 0;
	data->level.secret_count = 0;
	data->level.treasure_count = 0;
	data->level.enemies_count = 0;
	data->level.colors_error = 2;
	data->sound.cur = 0;
	data->menu.cursor_pos = 0;
	data->menu.menu_level = 0;
	i = 0;
	while (i <= data->number_of_textures)
		data->level.paths.path[i++] = NULL;
}

static void	images_to_window(t_data *data)
{
	struct timeval	timev;

	mlx_image_to_window(data->mlx.mlx_handle, data->mlx.bg, 0, 0);
	mlx_image_to_window(data->mlx.mlx_handle, data->mlx.fg, 0, 0);
	mlx_image_to_window(data->mlx.mlx_handle, data->mlx.menu_editor, 0, 0);
	mlx_image_to_window(data->mlx.mlx_handle, data->mlx.menu_editor_fg, 0, 0);
	// init_player(data);
	// init_weapons(data);
	// draw_weapons(data, data->mlx.weapon_anim[PISTOL].tex0, \
	// 			data->mlx.weapon);
	// mlx_image_to_window(data->mlx.mlx_handle, data->mlx.weapon, 0, 0);
	// mlx_image_to_window(data->mlx.mlx_handle, data->mlx.hud, 0, 0);
	// mlx_image_to_window(data->mlx.mlx_handle, data->mlx.minimap, \
	// data->hud.pos_map.x, data->hud.pos_map.y);
	gettimeofday(&timev, NULL);
	// data->player.start_time = timev.tv_sec;
}

//TODO make the game only work according to bonus stuff. 
//TODO make it so it can go to next level etc.
//TODO make it so when map is saved it also includes all the needed textures 
// (either as numbers or actually the path names or something like that)
// (not sure how that would work with the enemies and their spritesheets)
int	main(void)
{
	t_data			data;

	init_data(&data);
	if (!sound_init(&data) || !init_map_data(&data) || !init_mlx(&data) || \
		!init_menu(&data))
		return (1);
	ma_sound_start(data.sound.soundtrack[0]);
	images_to_window(&data);
	mlx_loop_hook(data.mlx.mlx_handle, menu_loop, &data);
	mlx_key_hook(data.mlx.mlx_handle, menu_key_handler, &data);
	mlx_mouse_hook(data.mlx.mlx_handle, menu_mouse_handler, &data);
	mlx_scroll_hook(data.mlx.mlx_handle, scroll_function_btn, &data);
	mlx_set_cursor_mode(data.mlx.mlx_handle, MLX_MOUSE_DISABLED);
	mlx_loop(data.mlx.mlx_handle);
	mlx_terminate(data.mlx.mlx_handle);
	return (0);
}

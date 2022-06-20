/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/13 15:47:34 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/06/20 11:39:16 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "cubed.h"

//srand is for the faces in the hud
static void	init_data(t_data *data)
{
	int	i;

	srand(time(NULL));
	data->floor_ceiling = false;
	data->bonus = true;
	data->number_of_textures = 255;
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
	mlx_image_to_window(data->mlx.mlx_handle, data->mlx.bg, 0, 0);
	mlx_image_to_window(data->mlx.mlx_handle, data->mlx.fg, 0, 0);
	mlx_image_to_window(data->mlx.mlx_handle, data->mlx.menu_editor, 0, 0);
	mlx_image_to_window(data->mlx.mlx_handle, data->mlx.menu_editor_fg, 0, 0);
}

//TODO make the game only work according to bonus stuff. 
//TODO make it so it can go to next level etc.
//TODO make it so when map is saved it also includes all the needed textures 
// (either as numbers or actually the path names or something like that)
// (not sure how that would work with the enemies and their spritesheets)
//TODO Make all things properly work with the ***map_planes!!!
int	main(void)
{
	t_data			data;

	init_data(&data);
	if (!sound_init(&data) || !init_map_data(&data) || !init_mlx(&data) || \
		!init_menu(&data))
		return (1);
	ma_sound_start(data.sound.soundtrack[0]);
	images_to_window(&data);
	// mlx_loop_hook(data.mlx.mlx_handle, menu_loop, &data);
	mlx_key_hook(data.mlx.mlx_handle, menu_key_handler, &data);
	load_map(&data);//temp
	mlx_mouse_hook(data.mlx.mlx_handle, menu_mouse_handler, &data);
	mlx_scroll_hook(data.mlx.mlx_handle, scroll_function_btn, &data);
	mlx_set_cursor_mode(data.mlx.mlx_handle, MLX_MOUSE_DISABLED);
	mlx_loop(data.mlx.mlx_handle);
	mlx_terminate(data.mlx.mlx_handle);
	return (0);
}

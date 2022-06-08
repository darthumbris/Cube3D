/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 13:53:40 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/08 15:58:27 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//TODO make cleanup work properly in all states
// cleanup_data(data);
void	close_game(t_data *data)
{
	mlx_close_hook(data->mlx.mlx_handle, menu_loop, data);
	mlx_close_window(data->mlx.mlx_handle);
	exit(EXIT_SUCCESS);
}

static void	main_menu(t_data *data, t_vector_int *pos)
{
	pos->x = MENU_CURSOR_0_X_POS * data->hud.scale;
	pos->y = (MENU_CURSOR_0_Y_START * data->hud.scale) + \
			MENU_CURSOR_0_JUMP * data->menu.cursor_pos * \
			data->hud.scale;
	draw_menu_screen(data, data->mlx.menu_screen);
}

static void	level_select_menu(t_data *data, t_vector_int *pos)
{
	pos->x = MENU_CURSOR_1_X_POS * data->hud.scale;
	pos->y = (MENU_CURSOR_1_Y_START * data->hud.scale) + \
			MENU_CURSOR_1_JUMP * \
			data->menu.cursor_pos * data->hud.scale;
	draw_menu_screen(data, data->mlx.level_select);
}

static void	map_editor_menu(t_data *data, t_vector_int *pos)
{
	pos->x = MENU_CURSOR_1_X_POS * data->hud.scale;
	pos->y = (MENU_CURSOR_1_Y_START * data->hud.scale) + \
			MENU_CURSOR_1_JUMP * \
			data->menu.cursor_pos * data->hud.scale;
	draw_menu_screen(data, data->mlx.map_editor_screen);
	mlx_set_cursor_mode(data->mlx.mlx_handle, MLX_MOUSE_NORMAL);
	data->menu.cursor = false;
	if (data->menu.enemy_btn.active == true)
		draw_check_mark(data, data->menu.enemy_btn.rect.pos0);
	if (data->menu.floor_btn.active == true)
		draw_check_mark(data, data->menu.floor_btn.rect.pos0);
	if (data->menu.obj_btn.active == true)
		draw_check_mark(data, data->menu.obj_btn.rect.pos0);
	draw_map_editor(data);
}

void	menu_loop(void *v_data)
{
	t_data			*data;
	t_vector_int	pos;

	data = (t_data *)v_data;
	if (data->menu.update)
	{
		if (data->menu.menu_level == 0)
			main_menu(data, &pos);
		else if (data->menu.menu_level == 1)
			level_select_menu(data, &pos);
		else if (data->menu.menu_level == 2)
			map_editor_menu(data, &pos);
		if (data->menu.cursor)
			draw_cursor(data, pos);
		data->menu.update = false;
	}
	if (data->menu.menu_level == 2)
	{
		move_map(data, &data->menu);
		check_hover(data);
	}
}

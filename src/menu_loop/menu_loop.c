/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 13:53:40 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/23 11:45:39 by shoogenb      ########   odam.nl         */
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

static void	main_menu(t_mlx *mlx, double scale, int menu_level)
{
	t_vector_int	start;

	start.x = 0;
	start.y = 0;
	if (menu_level == 0)
		draw_texture(mlx->menu_editor, mlx->menu_screen, start, scale);
	else
		draw_texture(mlx->menu_editor, mlx->level_select, start, scale);
}

static void	map_editor_menu(t_data *data, t_menu *menu, t_mlx *mlx, t_map_edit *editor)
{
	t_vector_int	start;
	const double	scale = data->hud.scale;
	static bool		reset = false;

	start.x = 0;
	start.y = 0;
	if (!reset)
	{
		ft_memset(mlx->fg->pixels, 0, SCREEN_HEIGHT * SCREEN_WIDTH * 4);
		reset = true;
	}
	ft_memset(mlx->menu_editor->pixels + (225 * SCREEN_WIDTH * 4), 0, SCREEN_HEIGHT * SCREEN_WIDTH * 4);
	draw_texture(mlx->menu_editor, mlx->map_editor_screen, start, scale);
	mlx_set_cursor_mode(mlx->mlx_handle, MLX_MOUSE_NORMAL);
	menu->cursor = false;
	if (editor->vis_btns.enemy_btn.active == true)
	{
		start = editor->vis_btns.enemy_btn.rect.pos0;
		draw_texture(mlx->menu_editor, mlx->check_mark, start, scale);
	}
	if (editor->vis_btns.floor_btn.active == true)
	{
		start = editor->vis_btns.floor_btn.rect.pos0;
		draw_texture(mlx->menu_editor, mlx->check_mark, start, scale);
	}
	if (editor->vis_btns.obj_btn.active == true)
	{
		start = editor->vis_btns.obj_btn.rect.pos0;
		draw_texture(mlx->menu_editor, mlx->check_mark, start, scale);
	}
	draw_map_editor(data);
}

static void	set_cursor_pos(int menu_level, t_vector_int *pos, \
							double scale, int cursor_pos)
{
	if (menu_level == 1)
	{
		pos->x = MENU_CURSOR_1_X_POS * scale;
		pos->y = (MENU_CURSOR_1_Y_START * scale) + \
			MENU_CURSOR_1_JUMP * \
			cursor_pos * scale - 12 * scale;
	}
	else
	{
		pos->x = MENU_CURSOR_0_X_POS * scale;
		pos->y = (MENU_CURSOR_0_Y_START * scale) + \
			MENU_CURSOR_0_JUMP * cursor_pos * \
			scale - 12 * scale;
	}
}

void	menu_loop(void *v_data)
{
	t_data			*data;
	t_vector_int	pos;

	data = (t_data *)v_data;
	if (data->menu.update  && data->menu.editor.file.save_btn.active == false)
	{
		set_cursor_pos(data->menu.menu_level, &pos, \
					data->hud.scale, data->menu.cursor_pos);
		if (data->menu.menu_level == 0 || data->menu.menu_level == 1)
			main_menu(&data->mlx, data->hud.scale, data->menu.menu_level);
		else if (data->menu.menu_level == 2)
			map_editor_menu(data, &data->menu, &data->mlx, &data->menu.editor);
		if (data->menu.cursor)
			draw_texture(data->mlx.menu_editor, data->mlx.cursor, pos, data->hud.scale);
		data->menu.update = false;
	}
	if (data->menu.menu_level == 2 && data->menu.editor.file.save_btn.active == false)
	{
		move_map(data->mlx.mlx_handle, &data->menu, \
			&data->menu.editor.map_offset, data->menu.editor.max_tiles_on_map);
		check_hover(data);
	}
	if (data->menu.editor.file.save_btn.active)
		check_mouse_svbtn_clicked(data);
}

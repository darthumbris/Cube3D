/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_map_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/14 15:14:47 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/23 13:30:40 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	add_char(struct mlx_key_data keys, t_data *data, int *i);
void	remove_char(t_data *data, int *i);
bool	is_alpha_key(enum keys key);
bool	is_digit_key(enum keys key);

static void	end_filename(enum keys key, t_data *data)
{
	t_mlx		*mlx;
	t_file		*file;

	mlx = &data->mlx;
	file = &data->menu.editor.file;
	mlx_key_hook(mlx->mlx_handle, menu_key_handler, data);
	file->save_btn.active = false;
	ft_memset(mlx->menu_editor_fg->pixels, 0, SCREEN_HEIGHT * SCREEN_WIDTH * 4);
	if (key == MLX_KEY_ESCAPE)
		printf("\nCanceled saving\n");
	else if (key == 2)
		printf("\nfilename too long\n");
	else
	{
		if (ft_strncmp(file->filenname + \
			(ft_strlen(file->filenname) - 4), ".cub", 4) != 0)
			printf("\nfilename doesn't end with .cub. Canceling saving\n");
		else
		{
			printf("\n[%s] saved in the saves folder\n", file->filenname);
			map_to_file(data);
		}
	}
	printf("setting filename to 0\n");
	ft_memset(file->filenname, 0, 30);
}

static t_rect	text_field_rect(double scale, int rec)
{
	t_rect	rect;

	if (rec == 0)
	{
		rect.pos0.x = SCREEN_WIDTH / 2 - 75 * scale;
		rect.pos1.x = SCREEN_WIDTH / 2 + 75 * scale;
		rect.pos0.y = SCREEN_HEIGHT / 2 - 25 * scale;
		rect.pos1.y = SCREEN_HEIGHT / 2 + 25 * scale;
	}
	else if (rec == 1)
	{
		rect.pos0.x = SCREEN_WIDTH / 2 - 65 * scale;
		rect.pos1.x = SCREEN_WIDTH / 2 + 65 * scale;
		rect.pos0.y = SCREEN_HEIGHT / 2 - 15 * scale + 10 * scale;
		rect.pos1.y = rect.pos0.y + scale * 8;
	}
	else
	{
		rect.pos0.x = SCREEN_WIDTH / 2 - 65 * scale;
		rect.pos1.x = rect.pos0.x + 55 * scale;
		rect.pos0.y = SCREEN_HEIGHT / 2 + 12 * scale;
		rect.pos1.y = rect.pos0.y + scale * 10;
	}
	return (rect);
}

void	check_mouse_svbtn_clicked(t_data *data)
{
	t_rect			txt_rect;
	t_rect			save_rect;
	t_rect			cancel_rect;
	t_vector_int	pos;
	bool			clicked;

	save_rect = text_field_rect(data->hud.scale, 2);
	txt_rect = text_field_rect(data->hud.scale, 1);
	cancel_rect = save_rect;
	cancel_rect.pos0.x += 60 * 4;
	cancel_rect.pos1.x = txt_rect.pos1.x;
	clicked = mlx_is_mouse_down(data->mlx.mlx_handle, MLX_MOUSE_BUTTON_LEFT);
	mlx_get_mouse_pos(data->mlx.mlx_handle, &pos.x, &pos.y);
	if (is_mouse_in_rect(pos.x, pos.y, save_rect) && clicked)
		end_filename(0, data);
	else if (is_mouse_in_rect(pos.x, pos.y, cancel_rect) && clicked)
		end_filename(MLX_KEY_ESCAPE, data);
}

void	draw_rects(t_data *data, double scale, mlx_image_t *menu_img, \
					char *filename)
{
	t_rect			box_rect;
	t_rect			txt_rect;
	t_rect			save_rect;
	t_rect			cancel_rect;
	t_vector_int	pos;

	box_rect = text_field_rect(scale, 0);
	txt_rect = text_field_rect(scale, 1);
	save_rect = text_field_rect(scale, 2);
	cancel_rect = save_rect;
	cancel_rect.pos0.x += 60 * 4;
	cancel_rect.pos1.x = txt_rect.pos1.x;
	draw_rect(menu_img, box_rect, 0x424242ff);
	draw_rect(menu_img, txt_rect, 0x636363ff);
	draw_rect(menu_img, save_rect, 0x636363ff);
	draw_rect(menu_img, cancel_rect, 0x636363ff);
	pos.x = save_rect.pos0.x;
	pos.y = save_rect.pos0.y - scale * 0.67;
	draw_str(&data->mlx, "accept", pos, scale);
	pos.x = cancel_rect.pos0.x;
	draw_str(&data->mlx, "cancel", pos, scale);
	pos.y = box_rect.pos0.y;
	pos.x = box_rect.pos0.x + 20 * scale * 1.3;
	draw_str(&data->mlx, "filename", pos, scale * 1.3);
	draw_str(&data->mlx, filename, txt_rect.pos0, scale * 0.67);
}

void	filename_key_handler(struct mlx_key_data keys, void *param)
{
	t_data		*data;
	t_file		*file;
	static int	i = 0;

	data = (t_data *)param;
	file = &data->menu.editor.file;
	if (file->reset_filename)
	{
		i = 0;
		file->reset_filename = false;
	}
	if (keys.action == MLX_RELEASE)
		return ;
	if (keys.key == MLX_KEY_ESCAPE || keys.key == MLX_KEY_ENTER)
		end_filename(keys.key, data);
	if (keys.key == MLX_KEY_BACKSPACE)
		remove_char(data, &i);
	if (is_alpha_key(keys.key) || is_digit_key(keys.key) || \
		keys.key == MLX_KEY_PERIOD)
		add_char(keys, data, &i);
	if (i > 22)
		end_filename(2, data);
	if (keys.key == MLX_KEY_ESCAPE || keys.key == MLX_KEY_ENTER || i > 25)
		i = 0;
	draw_rects(data, data->hud.scale, data->mlx.menu_editor, file->filenname);
}

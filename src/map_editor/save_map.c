/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/14 11:04:48 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/14 13:28:11 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	is_digit_key(enum keys key)
{
	return (key >= 48 && key <= 57);
}

bool	is_alpha_key(enum keys key)
{
	return (key >= 65 && key <= 90);
}

void	draw_filename_input(t_data *data, t_rect rec, uint32_t color)
{
	uint8_t			*map;
	int				y;
	int				x;

	y = rec.pos0.y;
	map = data->mlx.menu_editor->pixels;
	if (y < 0)
		y = 0;
	while (y < rec.pos1.y && y < (int)data->mlx.fg->height)
	{
		x = rec.pos0.x - 1;
		if (x < -1)
			x = -1;
		while (++x < rec.pos1.x && x < (int)data->mlx.fg->width)
			*(uint32_t *)(map + ((y * data->mlx.fg->width + x) * 4)) = color;
		y++;
	}
}

void	end_filename(enum keys key, t_data *data, int *i)
{
	mlx_key_hook(data->mlx.mlx_handle, menu_key_handler, data);
	data->menu.save_btn.active = false;
	ft_memset(data->mlx.menu_editor_fg->pixels, 0, \
				SCREEN_HEIGHT * SCREEN_WIDTH * 4);
	if (key == MLX_KEY_ESCAPE)
		printf("\nCanceled saving\n");
	else
	{
		data->menu.filenname[*i] = 0;
		if (ft_strncmp(data->menu.filenname + \
			(ft_strlen(data->menu.filenname) - 4), ".cub", 4) != 0)
			printf("\nfilename doesn't end with .cub. Canceling saving\n");
		else
			printf("\n[%s] saved in the saves folder\n", data->menu.filenname);
	}
	ft_memset(data->menu.filenname, 0, 30);
	*i = 0;
}

void	add_char(struct mlx_key_data keys, t_data *data, int *i)
{
	if (is_alpha_key(keys.key) && keys.modifier != MLX_SHIFT)
	{
		ft_putchar_fd(keys.key + 32, 1);
		data->menu.filenname[*i] = keys.key + 32;
	}
	else
	{
		ft_putchar_fd(keys.key, 1);
		data->menu.filenname[*i] = keys.key;
	}
	(*i)++;
}

void	remove_char(t_data *data, int *i, t_rect rect)
{
	draw_filename_input(data, rect, 0x424242ff);
	if (*i > 0)
	{
		data->menu.filenname[*i] = '\0';
		(*i)--;
	}
	else
		data->menu.filenname[0] = '\0';
}

t_rect	text_field_rect(double scale)
{
	t_rect	rect;

	rect.pos0.x = SCREEN_WIDTH / 2 - 50 * scale;
	rect.pos1.x = SCREEN_WIDTH / 2 + 50 * scale;
	rect.pos0.y = SCREEN_HEIGHT / 2 - 25 * scale;
	rect.pos1.y = SCREEN_HEIGHT / 2 + 25 * scale;
	return (rect);
}

void	filename_key_handler(struct mlx_key_data keys, void *param)
{
	t_data		*data;
	t_rect		rect;
	static int	i = 0;

	data = (t_data *)param;
	rect = text_field_rect(data->hud.scale);
	if (data->menu.save_btn.active == false)
		return ;
	if (keys.action == MLX_RELEASE)
		return ;
	if (keys.key == MLX_KEY_ESCAPE || keys.key == MLX_KEY_ENTER)
		end_filename(keys.key, data, &i);
	if (keys.key == MLX_KEY_BACKSPACE)
		remove_char(data, &i, rect);
	if (is_alpha_key(keys.key) || is_digit_key(keys.key) || \
		keys.key == MLX_KEY_PERIOD)
		add_char(keys, data, &i);
	if (i > 25)
	{
		printf("filename too large\n");
		mlx_key_hook(data->mlx.mlx_handle, menu_key_handler, data);
		ft_memset(data->menu.filenname, 0, 30);
		data->menu.save_btn.active = false;
		i = 0;
	}
	draw_filename_input(data, rect, 0x424242ff);
	draw_str(data, data->menu.filenname, rect.pos0, 4, data->mlx.menu_editor);
}

void	save_map(t_data *data)
{
	printf("Enter filename> \n");
	draw_filename_input(data, text_field_rect(data->hud.scale), 0x424242ff);
	mlx_key_hook(data->mlx.mlx_handle, filename_key_handler, data);
}

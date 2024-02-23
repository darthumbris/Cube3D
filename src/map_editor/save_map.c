/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/14 11:04:48 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/23 13:23:56 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_rects(t_data *data, double scale, mlx_image_t	*menu_img, char* filename);

bool	is_digit_key(enum keys key)
{
	return (key >= 48 && key <= 57);
}

bool	is_alpha_key(enum keys key)
{
	return (key >= 65 && key <= 90);
}

void	add_char(struct mlx_key_data keys, t_data *data, int *i)
{
	if (is_alpha_key(keys.key) && keys.modifier != MLX_SHIFT)
	{
		ft_putchar_fd(keys.key + 32, 1);
		data->menu.editor.file.filenname[*i] = keys.key + 32;
	}
	else
	{
		ft_putchar_fd(keys.key, 1);
		data->menu.editor.file.filenname[*i] = keys.key;
	}
	if (*i < 30)
		data->menu.editor.file.filenname[(*i) + 1] = '\0';
	(*i)++;
}

void	remove_char(t_data *data, int *i)
{
	if (*i > 0)
	{
		(*i)--;
		data->menu.editor.file.filenname[*i] = '\0';
	}
	else
		data->menu.editor.file.filenname[0] = '\0';
}

void	save_map(t_data *data)
{
	printf("Enter filename> \n");
	draw_rects(data, data->hud.scale, data->mlx.menu_editor, NULL);
	data->menu.editor.file.reset_filename = true;
	mlx_key_hook(data->mlx.mlx_handle, filename_key_handler, data);
}

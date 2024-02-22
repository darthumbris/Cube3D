/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_mlx_struct.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:37:12 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/06/29 11:02:05 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static t_transp	get_transp(int enemy, int frame)
{
	switch (enemy)
	{
	case 0:
		return (g_guard[frame]);
	case 1:
		return (g_dog[frame]);
	case 8:
		return (g_barny[frame]);
	default :
		return (g_guard[frame]);
	}
}

static void	init_transparencies(t_transp **tr)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 23)
	{
		tr[i] = ft_calloc(g_enemy_sprt_data[i].total_sprites, sizeof(t_transp));
		j = -1;
		while (++j < g_enemy_sprt_data[i].total_sprites && j < 49)
			tr[i][j] = get_transp(i, j);
	}
}	

bool	init_mlx(t_data *data)
{
	if (SCREEN_WIDTH < 320 || SCREEN_HEIGHT < 240)
		return (error_msg("Screen size too small"));
	data->mlx.mlx_handle = mlx_init
		(SCREEN_WIDTH, SCREEN_HEIGHT, "cube3D", false);
	if (data->mlx.mlx_handle == NULL)
		return (error_msg("Failed to init mlx"));
	data->mlx.fg = mlx_new_image
		(data->mlx.mlx_handle, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->mlx.bg = mlx_new_image
		(data->mlx.mlx_handle, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (data->mlx.fg == NULL || data->mlx.bg == NULL)
		return (error_msg("Failed to init images"));
	data->floor.inverse_width = 1 / (double)data->mlx.mlx_handle->width;
	data->floor.pos_z = 0.5 * data->mlx.mlx_handle->height;
	data->floor.halve_height = data->mlx.mlx_handle->height / 2;
	data->floor.halve_width = data->mlx.mlx_handle->width / 2;
	data->floor.width4 = data->mlx.mlx_handle->width * 4;
	data->spr_cast.zbuffer = ft_calloc(sizeof(double), SCREEN_WIDTH);
	data->spr_cast.tr_lst = ft_calloc(23, sizeof(t_transp *));
	init_transparencies(data->spr_cast.tr_lst);
	if (!data->spr_cast.zbuffer)
		return (error_msg("Malloc error"));
	return (true);
}

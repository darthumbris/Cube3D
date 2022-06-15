/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/11 12:32:09 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/15 16:29:02 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	arr_cleanup(char **arr)
{
	int	i;

	i = 0;
	if (!arr || !*arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	cleanup_config(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->config.size_temp)
	{
		free(data->config.dat[i].key);
		i++;
	}
	free(data->config.dat);
}

static void	cleanup_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->number_of_textures)
	{
		if (data->mlx.tex.hud[i])
			mlx_delete_texture(data->mlx.tex.hud[i]);
		i++;
	}
}

static void	cleanup_wall_map(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->level.map_h)
		free(data->level.wall_map[i++]);
	free(data->level.wall_map);
}

void	cleanup_data(t_data *data)
{
	mlx_delete_image(data->mlx.mlx_handle, data->mlx.fg);
	mlx_delete_image(data->mlx.mlx_handle, data->mlx.bg);
	cleanup_textures(data);
	if (data->bonus)
	{
		mlx_delete_image(data->mlx.mlx_handle, data->mlx.weapon);
		mlx_delete_image(data->mlx.mlx_handle, data->mlx.hud);
		mlx_delete_image(data->mlx.mlx_handle, data->mlx.minimap);
		mlx_delete_image(data->mlx.mlx_handle, data->mlx.score_screen);
		clear_sprite_lst(&data->sprite_lst);
	}
	free(data->sprite);
	if (data->doors)
		free(data->doors);
	if (data->secrets)
		free(data->secrets);
	cleanup_soundtrack(data);
	free(data->spr_cast.zbuffer);
	arr_cleanup(data->level.unparsed);
	// arr_cleanup(data->level.map);//TODO cleanup mapplanes
	if (data->level.wall_map)
		cleanup_wall_map(data);
	if (data->config.dat)
		cleanup_config(data);
}

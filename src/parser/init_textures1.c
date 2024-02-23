/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_textures1.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:42:13 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/28 10:27:52 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	init_needed_wall_textures(t_lodtex *tex, t_data *data)
{
	int		i;
	char	*path;

	i = -1;
	tex->wall[50] = mlx_load_png("assets/walls/WALL013.png");
	if (tex->wall[50] == NULL)
		return (false);
	while (++i < 50)
	{
		if (data->mlx.txt_in_map.wall[i])
		{
			path = ft_strjoin_r("assets/walls/", wall_icon_lst[i].tex_name);
			tex->wall[i] = mlx_load_png(path);
			if (tex->wall[i] == NULL)
			{
				printf("failed to load %d name: %s\n", i, path);
				free(path);
				return (false);
			}
			free(path);
		}
		else
			tex->wall[i] = NULL;
	}
	return (true);
}

bool	init_needed_obj_textures(t_lodtex *tex, t_data *data)
{
	int		i;
	char	*path;

	i = -1;
	while (++i < 69)
	{
		if (data->mlx.txt_in_map.obj[i])
		{
			if (i < 49)
				path = ft_strjoin_r("assets/sprites/decor/", obj_icon_lst[i].tex_name);
			else
				path = ft_strjoin_r("assets/sprites/items/", item_icon_lst[i - 49].tex_name);
			tex->obj[i] = mlx_load_png(path);
			if (tex->obj[i] == NULL)
			{
				printf("failed to load %d name: %s\n", i, path);
				free(path);
				return (false);
			}
			free(path);
		}
		else
			tex->obj[i] = NULL;
	}
	return (true);
}

bool	init_needed_enemy_textures(t_lodtex *tex, t_data *data)
{
	// int		i;
	// char	*path;

	// i = -1;
	// while (++i < 23)
	// {
	// 	if (data->mlx.txt_in_map.enmy[i])
	// 	{
	// 		path = ft_strjoin_r("assets/sprites/guards/", enemy_icon_lst[i + 2].tex_name);
	// 		tex->enmy[i] = mlx_load_png(path);
	// 		printf("i: %d, path: %s\n", i, path);
	// 		if (tex->enmy[i] == NULL)
	// 		{
	// 			printf("failed to load %d name: %s\n", i, path);
	// 			free(path);
	// 			return (false);
	// 		}
	// 		free(path);
	// 	}
	// 	else
	// 		tex->enmy[i] = NULL;
	// }
	(void)tex;
	(void)data;
	return (true);
}

bool	init_textures(t_data *data)
{
	check_textures_needed(data, -1, -1, -1);
	if (init_hud_textures(&data->mlx) == false)
		return (false);
	printf("succesfully loaded hud textures\n");
	if (init_weapon_textures(&data->mlx) == false)
		return (false);
	printf("succesfully loaded weapon textures\n");
	if (init_needed_wall_textures(&data->mlx.tex, data) == false)
		return (false);
	printf("succesfully loaded wall textures\n");
	if (init_needed_obj_textures(&data->mlx.tex, data) == false)
		return (false);
	printf("succesfully loaded obj textures\n");
	if (init_needed_enemy_textures(&data->mlx.tex, data) == false)
		return (false);
	printf("succesfully loaded enemy textures\n");
	data->caster.ray_dist = 0;
	uint8_t	*pixels = data->mlx.tex.hud[2]->pixels;
	if (pixels == NULL)
		printf("error\n");
	return (true);
}

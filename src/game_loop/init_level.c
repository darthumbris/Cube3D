/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_level.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 12:09:30 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/28 12:06:30 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	init_player(t_data *data)
{
	init_hud(data);
	data->level.level_number = 1;
	data->player.game_over = false;
	data->player.ammo = 8;
	data->player.lives = 3;
	data->player.health = 100;
	data->player.score = 0;
	data->player.active_weapon = PISTOL;
	data->player.machine_gun_pickup = false;
	data->player.start_pos.x = data->cam.pos.x;
	data->player.start_pos.y = data->cam.pos.y;
	data->player.start_dir.x = data->cam.dir.x;
	data->player.start_dir.y = data->cam.dir.y;
	data->player.start_plane.x = data->cam.plane.x;
	data->player.start_plane.y = data->cam.plane.y;
	data->player.enemies_killed = 0;
	data->player.secrets_found = 0;
	data->player.treasure_found = 0;
	draw_hud(data);
	draw_numbers(data);
	draw_faces(data);
	data->update_hud = false;
}

static bool	init_sprites(t_data *data)
{
	unsigned int	i;

	if (data->level.number_of_sprites == 0)
		return (true);
	data->sprite_lst = new_sprite(data->sprite[0]);
	i = 1;
	while (i < data->level.number_of_sprites)
	{
		add_sprite(&(data->sprite_lst), data->sprite[i]);
		i++;
	}
	sort_sprites(data, &data->sprite_lst);
	return (true);
}

void	set_player_dir(t_data *data, uint8_t c)
{
	data->cam.dir.x = 0;
	data->cam.dir.y = 0;
	if (c == 1)
		data->cam.dir.y = -1.0;
	else if (c == 2)
		data->cam.dir.y = +1.0;
	else if (c == 3)
		data->cam.dir.x = -1.0;
	else
		data->cam.dir.x = +1.0;
	data->cam.plane.x = tan(M_PI_2 * FOV / 180.0) * -data->cam.dir.y;
	data->cam.plane.y = tan(M_PI_2 * FOV / 180.0) * data->cam.dir.x;
}

void	set_player_pos(t_data *data, uint8_t ***map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->level.map_h)
	{
		j = -1;
		while (++j < data->level.map_w)
		{
			if (is_player_tile(map[i][j][2]))
			{
				data->cam.pos.y = i + 0.5;
				data->cam.pos.x = j + 0.5;
				set_player_dir(data, map[i][j][2]);
				return ;
			}
		}
	}
}

static bool	init_textures_with_rotation(t_enmy_sprites *ssheet, int enemy)
{
	int				i;
	char			*path;
	char			*full_path;
	char			*png;
	t_sprt_sht_data	sheet;

	sheet = g_enemy_sprt_data[enemy];
	ssheet->tex = ft_calloc(sheet.total_sprites, sizeof(mlx_texture_t *));
	path = ft_strjoin_r("assets/sprites/guards/", sheet.name);
	png = ft_strdup("1.png");
	i = -1;
	while (++i < sheet.total_sprites)
	{
		if (i < (8 * sheet.move_frames))
			path[ft_strlen(path) - 1] = 'a' + i / 8;
		else
			path[ft_strlen(path) - 1] = 'a' + sheet.move_frames + i - (8 * sheet.move_frames);
		if (i < (8 * sheet.move_frames))
			png[0] = i % 8 + '1';
		else
			png[0] = '0';
		full_path = ft_strjoin_r(path, png);
		ssheet->tex[i] = mlx_load_png(full_path);
		if (ssheet->tex[i] == NULL)
		{
			free(path);
			free(png);
			printf("failed to load sprite %d: %s\n", i, full_path);
			free(full_path);
			return (false);
		}
		free(full_path);
	}
	free(path);
	free(png);
	return (true);
}

static bool	init_textures_without_rotation(t_enmy_sprites *ssheet, int enemy)
{
	int				i;
	char			*path;
	char			*full_path;
	t_sprt_sht_data	sheet;
	char			end;

	sheet = g_enemy_sprt_data[enemy];
	ssheet->tex = ft_calloc(sheet.total_sprites, sizeof(mlx_texture_t *));
	path = ft_strjoin_r("assets/sprites/guards/", sheet.name);
	end = sheet.name[ft_strlen(sheet.name) - 1];
	i = -1;
	while (++i < sheet.total_sprites)
	{
		path[ft_strlen(path) - 1] = end + i;
		full_path = ft_strjoin_r(path, "0.png");
		ssheet->tex[i] = mlx_load_png(full_path);
		if (ssheet->tex[i] == NULL)
		{
			free(path);
			printf("failed to load sprite %d: %s\n", i, full_path);
			free(full_path);
			return (false);
		}
		else
			printf("loaded sprite %d: %s\n", i, full_path);
		free(full_path);
	}
	free(path);
	return (true);
}

//TODO properly parse the level for player pos/dir and all sprites/ doors/ secrets enemies etc
bool	init_level(t_data *data)
{
	struct timeval	timev;
	int				i;
	int				player_count;

	player_count = 0;
	if (!init_textures(data))
		return (false);
	if (!norm_loop(data, data->level.map_planes, &player_count))
		return (false);
	set_player_pos(data, data->level.map_planes);
	set_sprite_positions(data->level.map_planes, data);
	init_sprites(data);
	init_door_map(data);
	init_doors(data);
	init_secrets(data);
	init_player(data);
	init_weapons(data);
	if (init_textures_with_rotation(&data->mlx.tex.enmy_sprites[0], 0) == false)
		return (false);
	if (init_textures_with_rotation(&data->mlx.tex.enmy_sprites[1], 1) == false)
		return (false);
	if (init_textures_without_rotation(&data->mlx.tex.enmy_sprites[8], 8) == false)
		return (false);
	draw_weapons(data, data->mlx.weapon_anim[PISTOL].tex0, \
				data->mlx.weapon);
	mlx_image_to_window(data->mlx.mlx_handle, data->mlx.weapon, 0, 0);
	mlx_image_to_window(data->mlx.mlx_handle, data->mlx.hud, 0, 0);
	mlx_image_to_window(data->mlx.mlx_handle, data->mlx.minimap, \
	data->hud.pos_map.x, data->hud.pos_map.y);
	gettimeofday(&timev, NULL);
	data->player.start_time = timev.tv_sec;
	data->level.wall_map = ft_calloc(data->level.map_h + 1, sizeof(int *));
	i = -1;
	while (++i < data->level.map_h)
		data->level.wall_map[i] = ft_calloc(data->level.map_w + 1, sizeof(int));
	return (true);
}

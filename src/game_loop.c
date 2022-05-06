/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 17:33:29 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/05/06 16:25:41 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	attempt_close_door(t_data *data, int i)
{
	if (data->doors[i].closing_timer < 5.0)
		data->doors[i].closing_timer += data->mlx.mlx_handle->delta_time;
	if (data->doors[i].closing_timer >= 5.0)
	{
		data->doors[i].state = CLOSED;
		if (is_door_open(data, (int)(data->cam.pos.y), (int)(data->cam.pos.x)))
			data->doors[i].state = OPEN;
		else
			data->doors[i].state = CLOSING;
	}
}

void	update_doors(t_data *data)
{
	int				i;

	i = 0;
	while (i < data->level.door_count)
	{
		if (data->doors[i].state == CLOSING)
		{
			data->doors[i].s_timer += data->mlx.mlx_handle->delta_time;
			if (data->doors[i].s_timer >= 1.0)
			{
				data->doors[i].s_timer = 1.0;
				data->doors[i].state = CLOSED;
			}
		}
		if (data->doors[i].state == OPENING)
		{
			data->doors[i].s_timer -= 0.03;
			if (data->doors[i].s_timer <= 0.0)
			{
				data->doors[i].s_timer = 0.0;
				data->doors[i].state = OPEN;
				data->doors[i].closing_timer = 0.0;
			}
		}
		else if (data->doors[i].state == OPEN)
			attempt_close_door(data, i);
		i++;
	}
}

void	change_camera_angle(t_data *data, double dir)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rotate_speed;
	double	cos_rotate;
	double	sin_rotate;

	rotate_speed = dir * ROTATE_SPEED * data->mlx.mlx_handle->delta_time;
	cos_rotate = cos(rotate_speed);
	sin_rotate = sin(rotate_speed);
	old_dir_x = data->cam.dir.x;
	data->cam.dir.x = data->cam.dir.x * \
		cos_rotate - data->cam.dir.y * sin_rotate;
	data->cam.dir.y = old_dir_x * sin_rotate + data->cam.dir.y * cos_rotate;
	old_plane_x = data->cam.plane.x;
	data->cam.plane.x = data->cam.plane.x * \
		cos_rotate - data->cam.plane.y * sin_rotate;
	data->cam.plane.y = old_plane_x * \
		sin_rotate + data->cam.plane.y * cos_rotate;
}

void	move_camera_pos(t_data *data, int dir, bool strafe)
{
	const double	move_speed = dir * MOVE_SPEED * \
		data->mlx.mlx_handle->delta_time;
	const double	temp_dir_x = data->cam.dir.x * move_speed;
	const double	temp_dir_y = data->cam.dir.y * move_speed;

	if (!strafe && (data->level.map[(int)(data->cam.pos.y + temp_dir_y)] \
		[(int)(data->cam.pos.x + temp_dir_x)] == '0' || is_door_open(data, (int)(data->cam.pos.y + temp_dir_y), (int)(data->cam.pos.x + temp_dir_x))))
	{
		data->cam.pos.x += temp_dir_x;
		data->cam.pos.y += temp_dir_y;
	}
	else if (strafe && (data->level.map[(int)(data->cam.pos.y + temp_dir_x)] \
		[(int)(data->cam.pos.x - temp_dir_y)] == '0' || is_door_open(data, (int)(data->cam.pos.y + temp_dir_x), (int)(data->cam.pos.x - temp_dir_y))))
	{
		data->cam.pos.x -= temp_dir_y;
		data->cam.pos.y += temp_dir_x;
	}
	else
		return ;
}

void	key_handler(struct mlx_key_data keys, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keys.key == MLX_KEY_ESCAPE && keys.action != MLX_RELEASE)
	{
		if (data->bonus)
			clear_sprite_lst(&data->sprite_lst);
		mlx_close_window(data->mlx.mlx_handle);
	}
	if (keys.key == MLX_KEY_H && keys.action != MLX_RELEASE)
	{
		data->player.health--;
		data->update_hud = true;
	}
	if (keys.key == MLX_KEY_KP_MULTIPLY && keys.action != MLX_RELEASE)
	{
		data->player.score += 10;
		data->update_hud = true;
	}
	if (keys.key == MLX_KEY_KP_SUBTRACT && keys.action != MLX_RELEASE)
	{
		data->mlx.minimap_zoom += 1;
		if (data->mlx.minimap_zoom > 20)
			data->mlx.minimap_zoom = 20;
	}	
	if (keys.key == MLX_KEY_KP_ADD && keys.action != MLX_RELEASE)
	{
		data->mlx.minimap_zoom -= 1;
		if (data->mlx.minimap_zoom < 2)
			data->mlx.minimap_zoom = 2;
	}
}

void	game_loop(void *v_data)
{
	t_data		*data;
	static int	oldx = 0;
	int			x;
	int			y;

	data = (t_data *)v_data;
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_LEFT))
		change_camera_angle(data, -1);
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_RIGHT))
		change_camera_angle(data, +1);
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_W))
		move_camera_pos(data, +1, false);
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_S))
		move_camera_pos(data, -1, false);
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_A))
		move_camera_pos(data, -1, true);
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_D))
		move_camera_pos(data, +1, true);
	if (mlx_is_key_down(data->mlx.mlx_handle, MLX_KEY_E) && is_nearby_door(data))
		printf("ok\n");
	mlx_get_mouse_pos(data->mlx.mlx_handle, &x, &y);
	if (oldx == 0)
		oldx = x;
	if (x > oldx)
		change_camera_angle(data, +1);
	else if (x < oldx)
		change_camera_angle(data, -1);
	oldx = x;
	raycaster(data);
	if (data->bonus)
	{

		draw_sprites(data);
		if (data->update_hud)
		{
			draw_hud(data);
			draw_numbers(data);
			data->update_hud = false;
		}
		if (data->delay > 50)
		{
			draw_faces(data);
			data->delay = 0;
		}
		draw_minimap(data);
		data->delay++;
	}
	update_doors(data);
}

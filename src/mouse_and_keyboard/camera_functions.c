/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   camera_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 13:33:49 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/17 16:08:01 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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
	if (DEBUG_MODE)
		printf("dir: %f,%f\n", data->cam.dir.y, data->cam.dir.x);
}

void	change_camera_angle_mouse(t_data *data, double rotate_speed)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rotate;
	double	sin_rotate;

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

void	get_new_pos(t_data *data, t_vector_double *pos, \
	t_vector_double temp, bool strafe)
{
	if (strafe)
	{
		pos->y = (data->cam.pos.y + temp.x);
		pos->x = (data->cam.pos.x - temp.y);
	}
	else
	{
		pos->x = (data->cam.pos.x + temp.x);
		pos->y = (data->cam.pos.y + temp.y);
	}
}

void	move_camera_pos(t_data *data, int dir, bool strafe)
{
	const double	move_speed = dir * MOVE_SPEED * \
		data->mlx.mlx_handle->delta_time;
	const double	temp_dir_x = data->cam.dir.x * move_speed;
	const double	temp_dir_y = data->cam.dir.y * move_speed;
	t_vector_double	pos;

	get_new_pos(data, &pos, (t_vector_double){temp_dir_x, temp_dir_y}, strafe);
	if (!strafe && (data->level.map[(int)pos.y][(int)pos.x] == '0' || \
		is_door_open(data, pos.y, pos.x) || data->level.map[(int)pos.y]
		[(int)pos.x] == '?') && !is_enemy_collision(data, pos))
	{
		data->cam.pos.x += temp_dir_x;
		data->cam.pos.y += temp_dir_y;
	}
	else if (strafe && (data->level.map[(int)pos.y][(int)pos.x] == '0' || \
		is_door_open(data, pos.y, pos.x) || data->level.map[(int)pos.y]
		[(int)pos.x] == '?') && !is_enemy_collision(data, pos))
	{
		data->cam.pos.x -= temp_dir_y;
		data->cam.pos.y += temp_dir_x;
	}
	else
		return ;
}

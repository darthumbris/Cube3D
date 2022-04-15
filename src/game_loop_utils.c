#include "cubed.h"

void	change_camera_angle(t_data *data, double dir)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rotate_speed;
	double	cos_rotate;
	double	sin_rotate;

	rotate_speed = dir * ROTATE_SPEED * 0.01;
	cos_rotate = cos(rotate_speed);
	sin_rotate = sin(rotate_speed);
	old_dir_x = data->cam.dir.x;
	data->cam.dir.x = data->cam.dir.x * cos_rotate \
		- data->cam.dir.y * sin_rotate;
	data->cam.dir.y = old_dir_x * sin_rotate + data->cam.dir.y * cos_rotate;
	old_plane_x = data->cam.plane.x;
	data->cam.plane.x = data->cam.plane.x * cos_rotate \
		- data->cam.plane.y * sin_rotate;
	data->cam.plane.y = old_plane_x * sin_rotate \
		+ data->cam.plane.y * cos_rotate;
	raycaster(data);
}

void	move_camera_pos(t_data *data, int dir, bool strafe)
{
	const double	move_speed = dir * MOVE_SPEED * 0.01;
	const double	temp_dir_x = data->cam.dir.x * move_speed;
	const double	temp_dir_y = data->cam.dir.y * move_speed;
	//TODO:its possible to jam yourself stuck inside a wall
	if (!strafe && data->level.map[(int)(data->cam.pos.y + temp_dir_y)][(int)(data->cam.pos.x + temp_dir_x)] == '0')
	{
		data->cam.pos.x += temp_dir_x;
		data->cam.pos.y += temp_dir_y;
	}
	else if (strafe && data->level.map[(int)(data->cam.pos.y + temp_dir_x)][(int)(data->cam.pos.x - temp_dir_y)] == '0')
	{
		data->cam.pos.x -= temp_dir_y;
		data->cam.pos.y += temp_dir_x;
	}
	else
		return ;
	//printf("tempdir:%f-%f\n", temp_dir_x, temp_dir_y);
	//printf("dir:%f-%f\n", data->cam.dir.x, data->cam.dir.y);
	//printf("pos:%f-%f\n", data->cam.pos.x, data->cam.pos.y);
	if (data->caster.framedone)
		raycaster(data);
}

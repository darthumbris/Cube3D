#include "cubed.h"

void	check_wall_collision(t_data *data)
{
	if (data->caster.side_dist.x < data->caster.side_dist.y)
	{
		data->caster.side_dist.x += data->caster.delta_dist.x;
		data->caster.map_pos.x += data->caster.step.x;
		if (data->caster.ray_dir.x < 0)
			data->caster.side = WEST;
		else
			data->caster.side = EAST;
	}
	else
	{
		data->caster.side_dist.y += data->caster.delta_dist.y;
		data->caster.map_pos.y += data->caster.step.y;
		if (data->caster.ray_dir.y < 0)
			data->caster.side = NORTH;
		else
			data->caster.side = SOUTH;
	}
	if (data->level.map[data->caster.map_pos.y][data->caster.map_pos.x] == '1')
		data->caster.hit = true;
}

void	set_caster_variables(t_data *data, int x)
{
	data->caster.camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	data->caster.ray_dir.x = data->cam.dir.x + \
		data->cam.plane.x * data->caster.camera_x;
	data->caster.ray_dir.y = data->cam.dir.y + \
		data->cam.plane.y * data->caster.camera_x;
	data->caster.map_pos.x = (int)(data->cam.pos.x);
	data->caster.map_pos.y = (int)(data->cam.pos.y);
	if (data->caster.ray_dir.x == 0)
		data->caster.delta_dist.x = 1e30;
	else
		data->caster.delta_dist.x = fabs(1 / data->caster.ray_dir.x);
	if (data->caster.ray_dir.y == 0)
		data->caster.delta_dist.y = 1e30;
	else
		data->caster.delta_dist.y = fabs(1 / data->caster.ray_dir.y);
	data->caster.hit = false;
}

void	set_step_direction(t_data *data)
{
	double	diff_x;
	double	diff_y;

	diff_x = data->cam.pos.x - data->caster.map_pos.x;
	diff_y = data->cam.pos.y - data->caster.map_pos.y;
	if (data->caster.ray_dir.x < 0)
	{
		data->caster.step.x = -1;
		data->caster.side_dist.x = diff_x * data->caster.delta_dist.x;
	}
	else
	{
		data->caster.step.x = 1;
		data->caster.side_dist.x = (1 - diff_x) * data->caster.delta_dist.x;
	}
	if (data->caster.ray_dir.y < 0)
	{
		data->caster.step.y = -1;
		data->caster.side_dist.y = diff_y * data->caster.delta_dist.y;
	}
	else
	{
		data->caster.step.y = 1;
		data->caster.side_dist.y = (1 - diff_y) * data->caster.delta_dist.y;
	}
}

void	calculate_perpendicular_wall_distance(t_data *data)
{
	if (data->caster.side < NORTH)
		data->caster.perp_wall_dist = \
		(data->caster.side_dist.x - data->caster.delta_dist.x);
	else
		data->caster.perp_wall_dist = \
		(data->caster.side_dist.y - data->caster.delta_dist.y);
	if (data->caster.perp_wall_dist != 0.0)
		data->caster.line_height = \
		(int)(SCREEN_HEIGHT / data->caster.perp_wall_dist);
	else
		data->caster.line_height = SCREEN_HEIGHT;
}

void	set_draw_values(t_data *data)
{
	data->caster.draw_start = -data->caster.line_height / 2 + SCREEN_HEIGHT / 2;
	if (data->caster.draw_start < 0)
		data->caster.draw_start = 0;
	data->caster.draw_end = data->caster.line_height / 2 + SCREEN_HEIGHT / 2;
	if (data->caster.draw_end >= SCREEN_HEIGHT)
		data->caster.draw_end = SCREEN_HEIGHT - 1;
	if (data->caster.side < NORTH)
		data->caster.wall_x = data->cam.pos.y + \
		data->caster.perp_wall_dist * data->caster.ray_dir.y;
	else
		data->caster.wall_x = data->cam.pos.x + \
		data->caster.perp_wall_dist * data->caster.ray_dir.x;
	data->caster.wall_x -= floor((data->caster.wall_x));
}

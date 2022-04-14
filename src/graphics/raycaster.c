#include "cubed.h"

static void	check_for_wall_collision(t_data *data)
{
	if (data->caster.side_dist.x < data->caster.side_dist.y)
	{
		data->caster.side_dist.x += data->caster.delta_dist.x;
		data->caster.map_pos.x += data->caster.step.x;
		data->caster.side = 0;
	}
	else
	{
		data->caster.side_dist.y += data->caster.delta_dist.y;
		data->caster.map_pos.y += data->caster.step.y;
		data->caster.side = 1;
	}
	if (data->level.map[data->caster.map_pos.x][data->caster.map_pos.y] > 0)
		data->caster.hit = true;
}

// Because the map is always surrounded by walls
// it should always hit a wall before it can go outside
// the map and overflow.
void	raycaster(t_data *data)
{
	int	draw_start;
	int	draw_end;

	while (!data->caster.hit)
		check_for_wall_collision(data);
	if (data->caster.side)
		data->caster.perp_wall_dist = \
		(data->caster.side_dist.y - data->caster.delta_dist.y);
	else
		data->caster.perp_wall_dist = \
		(data->caster.side_dist.x - data->caster.delta_dist.x);
	data->caster.line_height = \
		(int)(SCREEN_HEIGHT / data->caster.perp_wall_dist);
	draw_start = -data->caster.line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = data->caster.line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
}

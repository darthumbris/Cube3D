#include "cubed.h"
#include <stdio.h>
#include <string.h>

const char	*worldMap[15] = {
	"000000001111111111111111111111111",
	"000000001000000000110000000000001",
	"000000001011000001110000000000001",
	"000000001001000000000000000000001",
	"111111111011000001110000000000001",
	"100000000011000001110111111111111",
	"111101111111110111000000100010000",
	"111101111111110111010100100010000",
	"110000001101010111000000100010000",
	"100000000000000011000000100010000",
	"100000000000000011010100100010000",
	"110000011101010111110111100011100",
	"111101110111010101011110100010000",
	"111111110111111101111111111110000",
	NULL};

// Because the map is always surrounded by walls
// it should always hit a wall before it can go outside
// the map and overflow.
void	raycaster(t_data *data)
{
	int draw_start;
	int	draw_end;

	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		data->caster.camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		data->caster.ray_dir.x = data->cam.dir.x + data->cam.plane.x * data->caster.camera_x;
		data->caster.ray_dir.y = data->cam.dir.y + data->cam.plane.y * data->caster.camera_x;

		data->caster.map_pos.x = (int)(data->cam.pos.x);
		data->caster.map_pos.y = (int)(data->cam.pos.y);

		data->caster.delta_dist.x = (data->caster.ray_dir.x == 0) ? 1e30 : fabs(1 / data->caster.ray_dir.x);
	 	data->caster.delta_dist.y = (data->caster.ray_dir.y == 0) ? 1e30 : fabs(1 / data->caster.ray_dir.y);
		data->caster.hit = false;
		if(data->caster.ray_dir.x < 0)
		{
			data->caster.step.x = -1;
			data->caster.side_dist.x = (data->cam.pos.x - data->caster.map_pos.x) * data->caster.delta_dist.x;
		}
		else
		{
			data->caster.step.x = 1;
			data->caster.side_dist.x = (1.0 + data->caster.map_pos.x - data->cam.pos.x) * data->caster.delta_dist.x;
		}
		if(data->caster.ray_dir.y < 0)
		{
			data->caster.step.y = -1;
			data->caster.side_dist.y = (data->cam.pos.y - data->caster.map_pos.y) * data->caster.delta_dist.y;
		}
		else
		{
			data->caster.step.y = 1;
			data->caster.side_dist.y = (1.0 + data->caster.map_pos.y - data->cam.pos.y) * data->caster.delta_dist.y;
		}
		while (!data->caster.hit)
		{
			if(data->caster.side_dist.x < data->caster.side_dist.y)
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
		//Check if ray has hit a wall
			if(worldMap[data->caster.map_pos.x][data->caster.map_pos.y] > '0')
				data->caster.hit = true;
		}
		if(data->caster.side == 0) 
			data->caster.perp_wall_dist = (data->caster.side_dist.x - data->caster.delta_dist.x);
		else
			data->caster.perp_wall_dist = (data->caster.side_dist.y - data->caster.delta_dist.y);

		data->caster.line_height = (int)(SCREEN_HEIGHT / data->caster.perp_wall_dist);

		draw_start = -data->caster.line_height / 2 + SCREEN_HEIGHT / 2;
		if(draw_start < 0)
			draw_start = 0;
		draw_end = data->caster.line_height / 2 + SCREEN_HEIGHT / 2;
		if(draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;

		if(data->caster.side == 0)
			data->caster.wall_x = data->cam.pos.y + data->caster.perp_wall_dist * data->caster.ray_dir.y;
		else
			data->caster.wall_x = data->cam.pos.x + data->caster.perp_wall_dist * data->caster.ray_dir.x;
		data->caster.wall_x -= floor((data->caster.wall_x));

		int texX = (int)(data->caster.wall_x * (double)(TEXTURE_WIDTH));
		if(data->caster.side == 0 && data->caster.ray_dir.x > 0)
			texX = TEXTURE_WIDTH - texX - 1;
		if(data->caster.side == 1 && data->caster.ray_dir.y < 0)
			texX = TEXTURE_WIDTH - texX - 1;

		double step = 1.0 * TEXTURE_HEIGHT / data->caster.line_height;
		double texPos = (draw_start - SCREEN_HEIGHT / 2 + data->caster.line_height / 2) * step;
		for (int y = 0; y < draw_start; y++)
		{
			if (data->mlx.fg->pixels[(y * SCREEN_WIDTH + x) * sizeof(unsigned int)])
				mlx_put_pixel(data->mlx.fg, x, y, 0x00000000);
		}
		for(int y = draw_start; y <= draw_end; y++)
		{
			int texY = (int)texPos & (TEXTURE_HEIGHT - 1);
			texPos += step;
			unsigned int color = 0x00000000;
			color |= (data->mlx.no_texture->pixels[(texY * TEXTURE_WIDTH + texX) * sizeof(unsigned int)]) << 24;
			color |= (data->mlx.no_texture->pixels[(texY * TEXTURE_WIDTH + texX) * sizeof(unsigned int) + 1]) << 16;
			color |= (data->mlx.no_texture->pixels[(texY * TEXTURE_WIDTH + texX) * sizeof(unsigned int) + 2]) << 8;
			color |= (data->mlx.no_texture->pixels[(texY * TEXTURE_WIDTH + texX) * sizeof(unsigned int) + 3]);
			if (data->mlx.fg->pixels[(y * SCREEN_WIDTH + x) * sizeof(unsigned int)] != 
				data->mlx.no_texture->pixels[(texY * TEXTURE_WIDTH + texX) * sizeof(unsigned int)])
			mlx_put_pixel(data->mlx.fg, x, y, color);
		}
		for (int y = draw_end; y < SCREEN_HEIGHT; y++)
		{
			if (data->mlx.fg->pixels[(y * SCREEN_WIDTH + x) * sizeof(unsigned int)])
				mlx_put_pixel(data->mlx.fg, x, y, 0x00000000);
		}
	}
}

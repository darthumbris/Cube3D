/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycaster.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/18 13:42:01 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/18 13:45:33 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "sprites.h"

/**
 * Struct for the camera of the player.
 * @param pos camera position.
 * @param dir direction camera points to.
 * @param plane plane of camera.
 */
typedef struct s_camera
{
	t_vector_double	pos;
	t_vector_double	dir;
	t_vector_double	plane;
	int				pitch;
}			t_camera;

typedef struct s_sprite_raycaster
{
	double			*zbuffer;
	t_vector_double	pos;
	double			inverse_determinant;
	t_vector_double	transform;
	int				sprite_screen_x;
	int				sprite_height;
	double			inverse_sprite_height;
	int				sprite_width;
	int				sprite_width_halve;
	double			inverse_sprite_width;
	t_vector_int	draw_start;
	t_vector_int	draw_end;
	t_vector_int	tex;
	double			inverse_transform_y;
}				t_sprite_raycaster;

typedef struct s_floor_raycaster
{
	t_vector_double	ray_dir0;
	t_vector_double	ray_dir1;
	t_vector_double	pos_d;
	t_vector_double	step;
	t_vector_int	pos_int;
	t_vector_int	tex;
	double			inverse_width;
	double			row_dist;
	double			pos_z;
	int				pos_y;
	int				halve_height;
	int				halve_width;
	int				color_pos;
	int				width4;
	int				x4;
}			t_floor_raycaster;

/**
 * Struct for the raycaster
 * @param hit if the raycaster has hit something.
 * @param map_pos where in the map the raycaster is. Uses camera pos.
 * @param ray_dir direction of the ray. depended on dir camera and plane camera.
 * @param side_dist length of ray from current position to next side.
 * @param delta_dist length of ray from one side to next side 
 * (x side to next x side or y side to next y side)
 * @param perp_wall_dist perpendicular distance to side.
 * @param step direction to step in (+1 or -1) for the ray.
 * @param side what side of the wall was hit (north west south or east).
 */
typedef struct s_raycaster
{
	bool			hit;
	t_vector_double	map_pos;
	t_vector_double	ray_dir;
	t_vector_double	side_dist;
	t_vector_double	delta_dist;
	double			perp_wall_dist;
	t_vector_int	step;
	int				side;
	int				dir;
	int				line_height;
	int				halve_line_height;
	double			inv_line_height;
	double			wall_x;
	double			camera_x;
	int				draw_start;
	int				draw_end;
	t_vector_int	tex;
	int				ray_dist;
	t_intersect		dcas;
	double			step_y;
	double			tex_pos;
	t_doors			*door;
	int				door_hit;
	t_secrets		*secret;
	int				secret_hit;
}			t_raycaster;

#endif
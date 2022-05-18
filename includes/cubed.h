/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cubed.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/02 10:16:56 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/05/18 14:59:49 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include "../libs/libft/libft.h"
# include "raycaster.h"
# include "graphics.h"
# include "level_data.h"

# ifndef DEBUG_MODE
#  define DEBUG_MODE		0
# endif

/**
 * @brief Main struct for cubed
 * 
 * @param player player struct with player pos. 
 * (and maybe later extra stuff like hp).
 * 
 */
typedef struct s_data
{
	int					number_of_textures;
	bool				bonus;
	bool				update_hud;
	bool				floor_ceiling;
	uint32_t			delay;
	uint32_t			color;
	t_mlx				mlx;
	t_hud				hud;
	t_sound				sound;
	t_level				level;
	t_doors				*doors;
	t_secrets			*secrets;
	t_config			config;
	t_camera			cam;
	t_player			player;
	t_sprite			*sprite;
	t_sprite_lst		*sprite_lst;
	t_raycaster			caster;
	t_floor_raycaster	floor;
	t_sprite_raycaster	spr_cast;
}				t_data;

//============Init Functions==========================
bool			init_mlx(t_data *data);
bool			init_door_map(t_data *data);
void			init_secrets(t_data *data);
void			init_doors(t_data *data);
void			init_weapons(t_data *data);
void			init_hud(t_data *data);

//==========Raycaster Functions=======================
void			raycaster(t_data *data);

void			check_wall_collision(t_data *data, t_raycaster *ray, \
					t_vector_double *map);
void			set_caster_variables(t_data *data, int x);
void			set_step_direction(t_data *data, t_raycaster *ray);
void			calculate_perpendicular_wall_distance(t_data *data, \
						t_raycaster *ray);
bool			do_lines_intersect(t_line *m, t_line *n, \
					t_vector_double *result);
void			set_segment(t_vector_double *p, double x, double y);
void			set_new_map_pos(t_vector_double *map, t_vector_double ray, \
					t_vector_double rd);
void			segment_to_line(t_segment *segm, t_line *line);
mlx_texture_t	*get_texture(t_data *data, t_vector_double pos);

//==========Draw functions====================
void			draw_background(t_data *data);
void			draw_floor_ceiling(t_data *data, int x);
void			draw_walls(t_data *data, int x, mlx_texture_t *texture);
void			draw_transparency(t_data *data, int x);
void			draw_sprites(t_data *data);
bool			draw_door(t_data *data);
void			draw_hud(t_data *data);
void			draw_minimap(t_data *data);
void			draw_enemies(t_data *data, t_sprite *sprt);
void			draw_weapons(t_data *data, mlx_texture_t *gun, \
						mlx_image_t *weapon);
void			animate_weapon(t_data *data);
//==========Draw Door function util functions==============
void			extend_ray(t_data *data, t_raycaster *ray);
bool			secret_hit(t_data *dat, t_intersect *seg);
void			init_secret_segments(t_data *data, t_raycaster *r, \
					t_intersect *door, t_vector_double map);

//==========Draw hud utils functions=======================
void			draw_single_nbr(t_data *data, int nbr, int x_pos);
void			draw_numbers(t_data *data);
void			draw_faces(t_data *data);

//======Draw enemies Util functions=========================
int				get_ypos_sheet(t_sprite *sprt);
int				get_xpos_sheet(t_sprite *sprt, t_vector_double cam_dir);
t_vector_int	get_transp_y(t_sprite *sprt);
t_vector_int	get_transp_x(t_sprite *sprt, t_vector_double cam_dir);
enum e_compas	get_enemy_direction(t_vector_double dir_cam, \
						t_vector_double dir_enemy);

//==========Draw Sprites util function======================
void			sort_sprites(t_data *data, t_sprite_lst **begin);

//=========Functions for checking if player hits an enemy===
void			check_weapon_hit(t_data *data);
double			get_angle_of_attack(t_vector_double target_pos, \
				t_vector_double attacker_pos, t_vector_double attacker_dir);

//=============Path Find functions==========================
void			path_find(t_data *data);
void			pathfind_in_direction(t_data *data, t_sprite *enemy);
void			pathfind_to_player(t_data *data, t_sprite *enemy);
void			pathind_dog(t_data *data, t_sprite *dog);
int				try_cardinal(t_data *data, t_sprite *enemy, int cardinal, \
						int dir_to_p);
int				try_diagonals(t_data *data, t_sprite *enemy);
void			patrol_routine(t_data *data, t_sprite *enemy);
void			attack_player(t_sprite *sprite, t_data *data);
bool			is_target_visible(t_vector_double target_pos, \
					t_vector_double attacker_pos, t_vector_double attacker_dir, \
					t_data *data);
void			rotate_enemy(t_data *data, t_sprite *enemy);
void			check_for_player(t_data *data, t_sprite *enemy);
void			track_player(t_data *data, t_sprite *enemy);
bool			player_oustide_viewing_cone(t_data *data, t_sprite *enemy);
void			alert_neighbouring_enemies(t_data *data, t_sprite *enemy);
bool			is_out_of_bounds(t_vector_double new_pos, t_data *data);
void			set_new_y_pos(t_vector_double *temp_pos, \
					t_vector_double *collision, t_sprite *enemy, int dir);
void			set_new_x_pos(t_vector_double *temp_pos, \
					t_vector_double *collision, t_sprite *enemy, int dir);
bool			is_vision_blocked(t_vector_double player_pos, \
					t_sprite *enemy, t_data *data);
void			sound_alerts_enemies(t_data *data);
t_sprite_lst	*get_enemie_hit(t_data *data);
void			damage_player(t_data *data, double dodge_chance, \
					t_sprite *enemy, int max_dist);
bool			view_not_blocked(t_data *data, t_vector_int pc_pos, \
					t_vector_int g_pos);
bool			door_check(t_data *data, t_vector_double pos);
void			reset_player(t_data *data);

//================Minimap util functions=================
void			check_for_walls(t_data *data, t_vector_int c);
void			wall_detection(t_data *data);
void			clean_wall_map(t_data *data);
void			fill_corners(t_data *data);
bool			is_door_opening(t_data *data, int y, int x);
bool			check_corner(t_data *data, int y, int x);
bool			draw_square(t_data *data, t_vector_int rec, \
					t_vector_int wh, unsigned int c);

//================Game Loop Functions=====================
void			game_loop(void *data);
void			update_enemies(t_data *data);
void			update_doors(t_data *data, int i);
void			update_secret_walls(t_data *data);
void			update_items(t_data *data);
void			gun_actions(t_data *data);

//==============Door utils function====================
int				get_distance(int x, int y, t_vector_double player);
bool			is_nearby_door(t_data *data);
bool			is_door_open(t_data *data, int y, int x);
int				get_door(t_data *data, t_vector_int pos);
t_doors			*get_door_struct(t_data *data, t_vector_int pos);
t_secrets		*get_secret(t_data *data, t_vector_int pos);
bool			is_player_facing_door(t_data *data, int x, int y);

//===============Camera and movement functions===========
void			change_camera_angle(t_data *data, double dir);
void			change_camera_angle_mouse(t_data *data, double rotate_speed);
void			mouse_handler(t_data *data);
void			move_camera_pos(t_data *data, int dir, bool strafe);
void			key_handler(struct mlx_key_data keys, void *param);
void			mouse_events(mouse_key_t button, action_t action, \
					modifier_key_t mods, void *param);
void			cursor_movement(double xpos, double ypos, void *param);

//==================Parser Functions==========================
bool			parse_input(char **argv, t_data *data);
char			**readmap(int fd, char **temp);
bool			checkmap(char *map);
bool			playerposcheck(char c);
bool			validchar(char c);
bool			validchar_space(char c);
bool			mapjmptable(char *line, t_data *data);
bool			checktypes(t_data *data);
bool			parse_config(t_data *data);
bool			bonus_weapons(char *line, t_data *data);
char			**parse_map(char **upmap, t_data *data);
bool			check_needed_textures_loaded(t_data *data);
bool			verifyzero(char **upmap, int i, int j, t_data *data);
int				get_sprite_kind(char c, t_data *data);
void			store_path(char *line, t_data *data, int kind);
void			color_store(char *line, t_data *data, int kind);
typedef void	(*t_func)(char *line, t_data *data, int kind);
void			set_sprite_positions(char **map, t_data *data);
void			set_enemy_data(t_sprite *sprite, char **map, t_vector_int pos, \
							t_data *data);

//===============Util functions==============================
bool			is_player_tile(char c);
bool			is_sprite_tile(char c);
bool			is_wall_tile(char c);
bool			is_empty_tile(char c);
bool			is_door_tile(char c);
bool			is_finish_tile(char c);
bool			is_secret_tile(char c);
bool			is_wall_kind_tile(char c);
bool			is_item(int kind);
bool			is_enemy_tile(char c);
bool			is_enemy_kind(int kind);
bool			is_guard(int kind);
bool			is_dog(int kind);
bool			is_guard_tile(char c);
bool			is_dog_tile(char c);
bool			is_nonblocking_kind(int kind);
bool			is_enemy_collision(t_data *data, t_vector_double new_pos);
bool			is_enemy_movable(int state);
bool			is_enemy_patrol(t_data *data, t_sprite *sprite);
bool			is_block_patrol_tile(char c);

//===============Sound Functions============================
void			soundtrack(t_data *data);
bool			sound_init(t_data *data);
void			play_sound_vol(t_data *data, char *fpath, float vol);

//==============Cleanup Functions===========================
void			arr_cleanup(char **arr);
void			cleanup_data(t_data *data);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprites.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/21 13:01:41 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/27 11:23:32 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

# include "vectors.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"

# define M_PI_8		0.392699081698724154807830422909937860
# define M_PI32		4.712388980384689857693965074919254326
# define M_PI15_8	5.890486225480862322117456343649067907

enum	e_sprites
{
	BARREL_GREEN = 1,
	BONES1,
	BONES2,
	BONES3,
	BONES4,
	BONES5,
	BONES6,
	BONES7,
	BONES8,
	LAMP_G,
	STAND_LAMP_G,
	CHANDELIER,
	LAMP_R,
	WELL_EMPTY,
	WELL_WATER,
	WELL_BLOOD,
	TABLE,
	TABLE_CHAIR,
	STATUE,
	TREE1,
	BARREL_NORM,
	PILLAR_GREY,
	ORB,
	PIKE,
	CAGE1,
	CAGE2,
	CAGE3,
	CAGE4,
	HOOK,
	GARGOYLE,
	BLOOD_PUDDLE,
	SPIKES,
	VINES,
	PANS1,
	PANS2,
	SINK,
	PUDDLE_WTR,
	FURNACE,
	PILLAR_BRWN,
	DOGFOOD,
	POT,
	SPEARS,
	BED,
	FLAG,
	TREE2,
	PLANT1,
	TRUCK,
	PLANT2,
	SPOUT,
	AMMO,
	SILVER_KEY,
	DOG_MEAL,
	CROSS,
	CHALICE,
	CHEST,
	CROWN,
	BACKPACK,
	FUEL,
	CLIP,
	LAUNCHER,
	MEDKIT,
	MACHGUN,
	PLASMRIFLE,
	ROCKETS,
	SHELLS,
	SHOTGUN,
	SOUL,
	STIMULANT,
	GOLD_KEY
};

enum e_compas
{
	C_SOUTH,
	C_SOUTH_EAST,
	C_EAST,
	C_NORTH_EAST,
	C_NORTH,
	C_NORTH_WEST,
	C_WEST,
	C_SOUTH_WEST
};

enum e_door_states
{
	CLOSED,
	OPENING,
	OPEN,
	CLOSING,
	PERMA_CLOSED
};

enum	e_secret_directions
{
	S_NORTH = 42,
	S_WEST = 43,
	S_EAST = 44,
	S_SOUTH = 45
};

enum e_door_directions
{
	NORTH_SOUTH,
	EAST_WEST
};

typedef union u_tex_path
{
	char	*path[255];
}			t_tex_path;

enum	e_state
{
	STAND,
	PATROL,
	CHASE,
	ATTACK,
	HURT,
	DYING,
	DEAD
};

typedef struct s_doors
{
	double	s_timer;
	double	closing_timer;
	char	type;
	int		x;
	int		y;
	int		state;
	int		direction;
	int		delay;
}		t_doors;

typedef struct s_secrets
{
	double	s_timer;
	char	type;
	int		x;
	int		y;
	int		state;
	int		direction;
}				t_secrets;

typedef struct s_enemy_data
{
	t_vector_double	dir;
	enum e_state	state;
	int				health;
	int				frame;
	int				last_attack;
	bool			player_detected;
	bool			played_sound;
	int				counter;
	int				path_dir;
	double			speed;
}				t_enemy_data;

typedef struct s_transp
{
	t_vector_int	start;
	t_vector_int	end;
}	t_transp;

typedef struct s_sprite
{
	t_vector_double	map_pos;
	int				kind;
	t_transp		transp;
	double			dist;
	bool			dropped;
	t_enemy_data	en_dat;
	mlx_texture_t	*texture;
}				t_sprite;

typedef struct s_sprite_lst
{
	t_sprite			sprite_data;
	struct s_sprite_lst	*next;
	struct s_sprite_lst	*prev;
}			t_sprite_lst;

t_sprite_lst	*new_sprite(t_sprite data);
t_sprite_lst	*add_sprite(t_sprite_lst **begin, t_sprite data);
void			clear_sprite_lst(t_sprite_lst **begin);
double			sprite_dist(t_vector_double start, t_vector_double end);
t_sprite_lst	*add_ammo_to_lst(t_sprite_lst **begin, t_sprite data);
bool			is_obstacle(char c);

#endif

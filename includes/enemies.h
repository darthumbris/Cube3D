/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemies.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/20 10:03:47 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/24 11:03:19 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMIES_H
# define ENEMIES_H

enum e_enemy_kinds
{
	GUARD_STANDING = 127,
	GUARD_PATROL,
	OFFICER_STANDING,
	OFFICER_PATROL,
	SS_STANDING,
	SS_PATROL,
	DOG_STANDING,
	DOG_PATROL,
	MUTANT_STANDING,
	MUTANT_PATROL,
	SPECTRE_STANDING,
	SPECTRE_PATROL,
	DEATHKNIGHT_STANDING,
	DEATHKNIGHT_PATROL,
	UBERMUTANT_STANDING,
	UBERMUTANT_PATROL,
	BARNEY,
	DEVIL,
	FAKE,
	FATFACE,
	GRETEL,
	HANS,
	HITLER,
	MECHHITLER,
	OTTO,
	SCHABS,
	TRANS,
	GHOST1,
	GHOST2,
	GHOST3,
	GHOST4,
};

enum e_enemies
{
	GUARD = 255,
	DOG,
	OFFICER,
	SS,
	MUTANT,
	SPECTRE,
	DEATHKNIGHT,
	UBERMUTANT,
	BOSS_BARNEY,
	BOSS_DEVIL,
	BOSS_FAKE,
	BOSS_FAT,
	BOSS_GRET,
	BOSS_HANS,
	BOSS_HITL,
	BOSS_MECH,
	BOSS_OTTO,
	BOSS_SCHAB,
	BOSS_TRANS,
	PAC_1,
	PAC_2,
	PAC_3,
	PAC_4,
};

typedef struct s_enemy_sprt_sht
{
	char	*name;
	int		move_frames;
	int		attack_frames;
	int		hit_frames;
	int		death_frames;
	int		total_sprites;
	bool	rotation;
}	t_sprt_sht_data;

static const t_sprt_sht_data g_enemy_sprt_data[] = \
{
	{"Guard/gard", 5, 3, 1, 5, 49, true},
	{"Dog/dogy", 4, 3, 1, 4, 39, true},
};

static const t_transp g_guard[] = \
{
	{{42, 32}, {85, 127}},//a1
	{{50, 32}, {83, 127}},//a2
	{{56, 32}, {79, 127}},//a3
	{{44, 32}, {75, 127}},//a4
	{{44, 32}, {85, 127}},//a5
	{{51, 32}, {82, 127}},//a6
	{{48, 32}, {71, 127}},//a7
	{{44, 32}, {77, 127}},//a8
	{{47, 35}, {84, 127}},//b1
	{{40, 34}, {89, 127}},//b2
	{{40, 32}, {97, 127}},//b3
	{{34, 32}, {85, 127}},//b4
	{{46, 32}, {83, 127}},//b5
	{{41, 32}, {92, 127}},//b6
	{{30, 32}, {87, 127}},//b7
	{{38, 34}, {87, 127}},//b8
	{{42, 32}, {88, 127}},//c1
	{{42, 33}, {83, 127}},//c2
	{{52, 32}, {85, 127}},//c3
	{{46, 32}, {75, 127}},//c4
	{{44, 32}, {85, 127}},//c5
	{{53, 32}, {80, 127}},//c6
	{{42, 32}, {75, 127}},//c7
	{{44, 33}, {85, 127}},//c8
	{{45, 32}, {82, 127}},//d1
	{{40, 32}, {93, 127}},//d2
	{{40, 32}, {97, 127}},//d3
	{{40, 32}, {81, 127}},//d4
	{{46, 32}, {83, 127}},//d5
	{{45, 32}, {86, 127}},//d6
	{{30, 32}, {87, 127}},//d7
	{{34, 37}, {87, 127}},//d8
	{{41, 33}, {87, 127}},//e1
	{{42, 34}, {83, 127}},//e2
	{{52, 32}, {85, 127}},//e3
	{{46, 32}, {75, 127}},//e4
	{{44, 32}, {85, 127}},//e5
	{{51, 32}, {80, 127}},//e6
	{{42, 32}, {75, 127}},//e7
	{{44, 34}, {85, 127}},//e8
	{{36, 31}, {87, 127}},//f0
	{{40, 37}, {89, 127}},//g0
	{{40, 37}, {89, 127}},//h0
	{{36, 34}, {88, 126}},//i0
	{{40, 34}, {91, 127}},//j0
	{{50, 24}, {117, 120}},//k0
	{{59, 39}, {122, 109}},//l0
	{{51, 68}, {120, 117}},//m0
	{{41, 100}, {124, 127}},//n0

};

int	get_enemy_kind(uint8_t c);

#endif
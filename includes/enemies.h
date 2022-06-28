/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemies.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/20 10:03:47 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/28 14:55:39 by shoogenb      ########   odam.nl         */
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
	{"Guard/garda", 5, 3, 1, 5, 49, true},
	{"Dog/dogya", 4, 3, 1, 4, 39, true},
	{"Officer/offia", 5, 3, 1, 6, 50, true},
	{"Ss/sswva", 5, 3, 1, 5, 49, true},
	{"Mutant/mtnta", 5, 4, 1, 6, 51, true},
	{"Spectre/dogya", 4, 0, 0, 4, 8, false},
	{"Deathknight/KNGTA", 4, 5, 1, 4, 14, false},
	{"Ubermutant/UBERA", 4, 5, 1, 2, 12, false},
	{"Barny/BARNA", 4, 4, 1, 2, 11, false},
	{"AngelOfDeath/ANGLA", 4, 4, 1, 7, 16, false},
	{"Fake/FHA", 4, 3, 1, 6, 14, false},
	{"Fatface/FATFA", 4, 4, 0, 3, 11, false},
	{"Gretel/GRTLA", 4, 4, 0, 3, 11, false},
	{"Hans/HANSA", 4, 4, 0, 3, 11, false},
	{"Hitl/HTLRA", 4, 3, 0, 7, 14, false},
	{"Mech/MHTLA", 4, 3, 0, 4, 11, false},
	{"Otto/OTTOA", 4, 2, 0, 3, 9, false},
	{"Schab/SCHBA", 4, 2, 0, 4, 10, false},
	{"Trans/TRNSA", 4, 3, 0, 4, 11, false},
	{"Ghost/PACA", 2, 0, 0, 0, 2, false},
	{"Ghost/PACC", 2, 0, 0, 0, 2, false},
	{"Ghost/PACE", 2, 0, 0, 0, 2, false},
	{"Ghost/PACG", 2, 0, 0, 0, 2, false},
};

typedef struct s_transp_lst
{
	t_transp	**tr;
}	t_tr_lst;

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

static const t_transp g_dog[] = \
{
	{{52, 62}, {110, 127}},//a1
	{{38, 64}, {108, 127}},//a2
	{{20, 65}, {121, 127}},//a3
	{{32, 62}, {108, 127}},//a4
	{{55, 66}, {106, 127}},//a5
	{{19, 62}, {95, 127}},//a6
	{{6, 65}, {107, 127}},//a7
	{{19, 64}, {89, 127}},//a8
	{{52, 62}, {106, 127}},//b1
	{{31, 64}, {118, 127}},//b2
	{{20, 64}, {124, 127}},//b3
	{{30, 62}, {114, 127}},//b4
	{{53, 64}, {110, 127}},//b5
	{{13, 62}, {97, 127}},//b6
	{{3, 64}, {107, 127}},//b7
	{{9, 64}, {96, 127}},//b8
	{{52, 68}, {110, 127}},//c1
	{{30, 69}, {120, 127}},//c2
	{{20, 70}, {120, 127}},//c3
	{{30, 67}, {120, 127}},//c4
	{{51, 68}, {108, 127}},//c5
	{{7, 67}, {97, 127}},//c6
	{{7, 70}, {107, 127}},//c7
	{{7, 69}, {97, 127}},//c8
	{{49, 65}, {112, 127}},//d1
	{{32, 65}, {114, 127}},//d2
	{{18, 70}, {122, 127}},//d3
	{{30, 66}, {114, 127}},//d4
	{{54, 66}, {114, 127}},//d5
	{{13, 66}, {97, 127}},//d6
	{{5, 70}, {109, 127}},//d7
	{{13, 65}, {95, 127}},//d8
	{{44, 47}, {112, 127}},//e0
	{{40, 39}, {118, 127}},//f0
	{{38, 40}, {118, 127}},//g0
	{{34, 64}, {120, 127}},//h0
	{{24, 50}, {120, 127}},//i0
	{{12, 59}, {123, 127}},//j0
	{{9, 102}, {117, 127}},//k0
};

static const t_transp g_barny[] = 
{
	{{13, 12}, {111, 127}},//a0
	{{9, 11}, {112, 125}},//b0
	{{14, 12}, {111, 127}},//c0
	{{12, 11}, {116, 126}},//d0
	{{11, 11}, {114, 127}},//e0
	{{10, 12}, {114, 127}},//f0
	{{11, 12}, {117, 127}},//g0
	{{11, 11}, {112, 127}},//h0
	{{5, 9}, {115, 127}},//i0
	{{8, 23}, {115, 127}},//j0
	{{2, 89}, {126, 127}},//k0
};

int	get_enemy_kind(uint8_t c);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_textures2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 13:43:21 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/20 14:48:12 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

bool	init_hud_textures(t_mlx *gfx)
{
	gfx->tex.hud[HUD_M_T] = mlx_load_png("assets/hud/hud_transparent.png");
	gfx->tex.hud[HUD_N_T] = mlx_load_png("assets/hud/hud_numbers.png");
	gfx->tex.hud[HUD_F_T] = mlx_load_png("assets/hud/hud_faces.png");
	gfx->tex.hud[SCORE_M_T] = mlx_load_png("assets/hud/score_screen.png");
	gfx->tex.hud[SCORE_N_T] = mlx_load_png("assets/hud/score_numbers.png");
	gfx->tex.hud[GAMEOVER_T] = mlx_load_png("assets/hud/game_over.png");
	if (gfx->tex.hud[HUD_M_T] == NULL || gfx->tex.hud[HUD_N_T] == NULL || \
		gfx->tex.hud[HUD_F_T] == NULL || gfx->tex.hud[SCORE_M_T] == NULL || \
		gfx->tex.hud[SCORE_N_T] == NULL || gfx->tex.hud[GAMEOVER_T] == NULL)
		return (false);
	return (true);
}

bool	init_weapon_textures(t_mlx *gfx)
{
	gfx->tex.wpn[PISTOL0_T] = mlx_load_png("assets/sprites/weapons/pistol0.png");
	gfx->tex.wpn[PISTOL1_T] = mlx_load_png("assets/sprites/weapons/pistol1.png");
	gfx->tex.wpn[PISTOL2_T] = mlx_load_png("assets/sprites/weapons/pistol2.png");
	gfx->tex.wpn[PISTOL3_T] = mlx_load_png("assets/sprites/weapons/pistol3.png");
	gfx->tex.wpn[KNIFE0_T] = mlx_load_png("assets/sprites/weapons/knife0.png");
	gfx->tex.wpn[KNIFE1_T] = mlx_load_png("assets/sprites/weapons/knife1.png");
	gfx->tex.wpn[KNIFE2_T] = mlx_load_png("assets/sprites/weapons/knife2.png");
	gfx->tex.wpn[KNIFE3_T] = mlx_load_png("assets/sprites/weapons/knife3.png");
	gfx->tex.wpn[MACHINEGUN0_T] = mlx_load_png("assets/sprites/weapons/machinegun0.png");
	gfx->tex.wpn[MACHINEGUN1_T] = mlx_load_png("assets/sprites/weapons/machinegun1.png");
	gfx->tex.wpn[MACHINEGUN2_T] = mlx_load_png("assets/sprites/weapons/machinegun2.png");
	gfx->tex.wpn[MACHINEGUN3_T] = mlx_load_png("assets/sprites/weapons/machinegun3.png");
	if (gfx->tex.wpn[0] == NULL || gfx->tex.wpn[1] == NULL || gfx->tex.wpn[2] == NULL || \
		gfx->tex.wpn[3] == NULL || gfx->tex.wpn[4] == NULL || gfx->tex.wpn[5] == NULL || \
		gfx->tex.wpn[6] == NULL || gfx->tex.wpn[7] == NULL || gfx->tex.wpn[8] == NULL || \
		gfx->tex.wpn[9] == NULL || gfx->tex.wpn[10] == NULL || gfx->tex.wpn[11] == NULL)
		return (false);
	return (true);
}

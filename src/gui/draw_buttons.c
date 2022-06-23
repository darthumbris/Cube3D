/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_buttons.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/08 13:55:36 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/06/23 13:22:19 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	draw_button(mlx_image_t *menu_img, t_rect rec, uint32_t color)
{
	uint8_t			*menu;
	int				y;
	int				x;

	y = rec.pos0.y - 1;
	menu = menu_img->pixels;
	if (y < -1)
		y = -1;
	while (++y < rec.pos1.y && y < (int)menu_img->height)
	{
		x = rec.pos0.x - 1;
		if (x < -1)
			x = -1;
		while (++x < rec.pos1.x && x < (int)menu_img->width)
			*(uint32_t *)(menu + ((y * menu_img->width + x) * 4)) = color;
	}
}

static void	draw_transparency_btns(mlx_image_t *menu_img, mlx_image_t *bg, \
									t_rect rec, uint32_t c)
{
	uint8_t			*menu;
	uint8_t			*fg;
	int				y;
	int				x;
	uint32_t		fg_c;

	y = rec.pos0.y - 1;
	menu = bg->pixels;
	fg = menu_img->pixels;
	if (y < -1)
		y = -1;
	while (++y < rec.pos1.y && y < (int)menu_img->height)
	{
		x = rec.pos0.x - 1;
		if (x < -1)
			x = -1;
		while (++x < rec.pos1.x && x < (int)menu_img->width)
		{
			fg_c = *(uint32_t *)(fg + (y * menu_img->width + x) * 4);
			if (fg_c == 0x0000000)
				*(uint32_t *)(menu + ((y * menu_img->width + x) * 4)) = c;
		}
	}
}

static void	draw_click_idle(t_mlx *mlx, t_button btn)
{
	if ((btn.state == IDLE || btn.state == HOVER) && btn.active == false)
		draw_transparency_btns(mlx->menu_editor, mlx->bg, btn.rect, 0x4c0000ff);
	else
		draw_transparency_btns(mlx->menu_editor, mlx->bg, btn.rect, 0x850000ff);
	if (btn.state == HOVER)
		draw_button(mlx->menu_editor_fg, btn.rect, HOVER_COLOR);
	else if (btn.state == IDLE)
		draw_button(mlx->menu_editor_fg, btn.rect, 0);
}

static void	draw_hover_drop_down(mlx_image_t *menu_img, t_map_edit *editor, \
								t_sprt_drop *sprt, t_sp_drop *sp)
{
	if (editor->plane_ddlst.active.state == HOVER)
		draw_button(menu_img, editor->plane_ddlst.hvr_rct, HOVER_COLOR);
	else if (editor->plane_ddlst.active.state == IDLE)
	{
		draw_button(menu_img, editor->plane_ddlst.hvr_rct, 0);
		if (editor->plane_ddlst.active.active == false)
		{
			if (sprt->wall_ddlst.active.state == HOVER)
				draw_button(menu_img, sprt->wall_ddlst.hvr_rct, HOVER_COLOR);
			else if (sprt->wall_ddlst.active.state == IDLE)
				draw_button(menu_img, sprt->wall_ddlst.hvr_rct, 0);
			if (editor->active_plane == 4)
			{
				if (sp->rotate_ddlst.active.state == HOVER)
					draw_button(menu_img, sp->rotate_ddlst.hvr_rct, HOVER_COLOR);
				if (sp->diff_ddlst.active.state == HOVER)
					draw_button(menu_img, sp->diff_ddlst.hvr_rct, HOVER_COLOR);
			}
			if (sp->rotate_ddlst.active.state == IDLE)
				draw_button(menu_img, sp->rotate_ddlst.hvr_rct, 0);
			if (sp->diff_ddlst.active.state == IDLE)
				draw_button(menu_img, sp->diff_ddlst.hvr_rct, 0);
		}
	}
}

void	draw_buttons(t_mlx *mlx, t_map_edit *editor)
{
	t_vis_btns	*vis;
	t_pnt_btns	*pnt;
	t_file		*file;

	vis = &editor->vis_btns;
	pnt = &editor->pnt_btns;
	file = &editor->file;
	draw_hover_drop_down(mlx->menu_editor_fg, editor, \
					&editor->sprt_drops, &editor->sp_drops);
	draw_click_idle(mlx, vis->enemy_btn);
	draw_click_idle(mlx, vis->floor_btn);
	draw_click_idle(mlx, vis->obj_btn);
	draw_click_idle(mlx, pnt->bucket_btn);
	draw_click_idle(mlx, pnt->pen_btn);
	draw_click_idle(mlx, pnt->area_btn);
	draw_click_idle(mlx, pnt->picker_btn);
	draw_click_idle(mlx, file->load_btn);
	draw_click_idle(mlx, file->save_btn);
}

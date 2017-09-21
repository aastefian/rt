/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_info_spheres.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 13:55:08 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/20 14:13:23 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../../includes/rt.h"
#include "../header/nuklear.h"
#include "../header/gui.h"

static void	draw_infos(struct nk_context *c, struct media *m, t_world *w,\
	int i)
{
	ui_widget_value_infos(c, m, &w->spheres[i].pos.x, "POS X:");
	ui_widget_value_infos(c, m, &w->spheres[i].pos.y, "POS Y:");
	ui_widget_value_infos(c, m, &w->spheres[i].pos.z, "POS Z:");
	ui_widget_value_infos(c, m, &w->spheres[i].radius, "RADIUS:");
	ui_widget_value_infos(c, m, &w->spheres[i].reflection_coef,"REFLECTION:");
	ui_widget_value_infos(c, m, &w->spheres[i].refraction_coef,"REFRACTION:");
	ui_widget_value_infos(c, m, &w->spheres[i].transparence_coef, "TRANSPARENCE:");
	draw_infos_next(c, m, &w->spheres[i].perlin,w);
	draw_p_presets(c, m, w, &w->spheres[i].perlin);
}

static void	draw_delete_button(struct nk_context *c, struct media *media,\
								t_world *world, int i)
{
	t_intersection o;

	o.id_save = i;
	ui_widget_centered(c, media, 10);
	ui_widget_centered(c, media, 30);
	if (nk_button_image_label(c, media->del, "DELETE OBJECT",\
		NK_TEXT_CENTERED))
	{
		remove_sphere(&world->spheres_tmp, &o);
		load_spheres(&world->spheres, world->spheres_tmp, &world->spheres_len);
		world->redraw = 1;
	}
}

void		sphere_informations(t_world *world, struct nk_context *ctx,\
								struct media *media)
{
	int	i;

	i = 0;
	while (i < world->spheres_len)
	{
		if (world->id_save == world->spheres[i].id)
		{
			header_info(ctx, media->sphere, "SPHERE");
			draw_infos(ctx, media, world, i);
			ui_header(ctx, media, "---- Colors ----");
			draw_color_picker(ctx, &world->spheres[i].color, world);
			ui_widget_centered(ctx, media, 30);
			draw_chess_color(ctx, world, &world->spheres[i].chess);
			refresh_sphere(world, i);
			draw_delete_button(ctx, media, world, world->id_save);
			break ;
		}
		i++;
	}
}

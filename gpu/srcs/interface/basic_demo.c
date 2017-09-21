/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_demo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 20:55:58 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/11 13:47:06 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../includes/rt.h"
#include "header/nuklear.h"
#include "header/gui.h"

/* ===============================================================
 *
 *                          BASIC DEMO
 *
 * ===============================================================*/

void	basic_demo(struct nk_context *ctx, struct media *media, t_world *world)
{
	// static int image_active;
	// // static int check0 = 1;
	// // static int check1 = 0;
	// // static size_t prog = 80;
	// // static int selected_item = 0;
	// static int selected_image = 3;
	// static int selected_icon = 0;
	// static const char *items[] = {"Item 0","item 1","item 2"};
	static int piemenu_active = 0;
	static struct nk_vec2 piemenu_pos;
	// int i = 0;

	nk_style_set_font(ctx, &media->font_20->handle);
	if (nk_begin(ctx, "ADD OBJECTS", nk_rect(0, 602, 250, 200),
			NK_WINDOW_BORDER|NK_WINDOW_TITLE|NK_WINDOW_MINIMIZABLE))
	{
		nk_menubar_begin(ctx);
		{
			/* toolbar */
			ui_header(ctx, media, "---- Add Objects ----");
			nk_layout_row_static(ctx, 40, 40, 6);
			// if (nk_menu_begin_image(ctx, "Music", media->play, nk_vec2(110,120)))
			// {
			// 	/* settings */
			// 	nk_layout_row_dynamic(ctx, 25, 1);
			// 	nk_menu_item_image_label(ctx, media->play, "Play", NK_TEXT_RIGHT);
			// 	nk_menu_item_image_label(ctx, media->stop, "Stop", NK_TEXT_RIGHT);
			// 	nk_menu_item_image_label(ctx, media->pause, "Pause", NK_TEXT_RIGHT);
			// 	nk_menu_item_image_label(ctx, media->next, "Next", NK_TEXT_RIGHT);
			// 	nk_menu_item_image_label(ctx, media->prev, "Prev", NK_TEXT_RIGHT);
			// 	nk_menu_end(ctx);
			// }
			if(nk_button_image(ctx, media->sphere))
			{
				if(world->a_h != NULL)
					thread_free_and_add_sphere(&world->spheres, &world->spheres_tmp, &world->spheres_len, world->id);
				world->redraw = 1;
			}
			if(nk_button_image(ctx, media->cone))
			{
				if(world->a_h != NULL)
					thread_free_and_add_cone(&world->cones, &world->cones_tmp, &world->cones_len, world->id);
				world->redraw = 1;
			}
			if(nk_button_image(ctx, media->plane))
			{
				if(world->a_h != NULL)
					thread_free_and_add_plane(&world->planes, &world->planes_tmp, &world->planes_len, world->id);
					world->redraw = 1;
			}
			if(nk_button_image(ctx, media->cylinder))
			{
				if(world->a_h != NULL)
					thread_free_and_add_cylinder(&world->cylinders, &world->cylinders_tmp, &world->cylinders_len, world->id);
					world->redraw = 1;
			}
			if(nk_button_image(ctx, media->torus))
			{
				if(world->a_h != NULL)
					thread_free_and_add_torus(&world->torus, &world->torus_tmp, &world->torus_len, world->id);
					world->redraw = 1;
			}
			if(nk_button_image(ctx, media->moebius))
			{
				if(world->a_h != NULL)
					thread_free_and_add_mobius(&world->mobius, &world->mobius_tmp, &world->mobius_len, world->id);
					world->redraw = 1;
			}
			if(nk_button_image(ctx, media->disk))
			{
				if(world->a_h != NULL)
					thread_free_and_add_disk(&world->disks, &world->disks_tmp, &world->disks_len, world->id);
					world->redraw = 1;
			}
			if(nk_button_image(ctx, media->cube))
			{
				if(world->a_h != NULL)
					thread_free_and_add_cube(&world->cubes, &world->cubes_tmp, &world->cubes_len, world->id);
					world->redraw = 1;
			}
			if(nk_button_image(ctx, media->hyperboloid))
			{
				if(world->a_h != NULL)
					thread_free_and_add_hyperboloid(&world->hyperboloids, &world->hyperboloids_tmp, &world->hyperboloids_len, world->id);
					world->redraw = 1;
			}
			if(nk_button_image(ctx, media->paraboloid))
			{
				if(world->a_h != NULL)
					thread_free_and_add_paraboloid(&world->paraboloids, &world->paraboloids_tmp, &world->paraboloids_len, world->id);
					world->redraw = 1;
			}
			if(nk_button_image(ctx, media->triangle))
			{
				if(world->a_h != NULL)
					thread_free_and_add_triangle(&world->triangles, &world->triangles_tmp, &world->triangles_len, world->id);
				world->redraw = 1;
			}
			if(nk_button_image(ctx, media->h_cube))
			{
				if(world->a_h != NULL)
					thread_free_and_add_h_cube(&world->h_cubes, &world->h_cubes_tmp, &world->h_cubes_len, world->id);
				world->redraw = 1;
			}
			// nk_button_image(ctx, media->disk);
		}
		nk_menubar_end(ctx);













		// /*------------------------------------------------
		//  *                  POPUP BUTTON
		//  *------------------------------------------------*/
		// ui_header(ctx, media, "Popup & Scrollbar & Images");
		// ui_widget(ctx, media, 35);
		// if (nk_button_image_label(ctx, media->dir, "Images", NK_TEXT_CENTERED))
		// 	image_active = !image_active;

		// // /*------------------------------------------------
		// //  *                  SELECTED IMAGE
		// //  *------------------------------------------------*/
		// ui_header(ctx, media, "Selected Image");
		// ui_widget_centered(ctx, media, 100);
		// nk_image(ctx, media->images[selected_image]);

		// // /*------------------------------------------------
		// //  *                  IMAGE POPUP
		// //  *------------------------------------------------*/
		// if (image_active) {
		// 	// struct nk_panel popup;
		// 	if (nk_popup_begin(ctx, NK_POPUP_STATIC, "Image Popup", 0, nk_rect(265, 0, 320, 220))) {
		// 		nk_layout_row_static(ctx, 82, 82, 3);
		// 		for (i = 0; i < 9; ++i) {
		// 			if (nk_button_image(ctx, media->images[i])) {
		// 				selected_image = i;
		// 				image_active = 0;
		// 				nk_popup_close(ctx);
		// 			}
		// 		}
		// 		nk_popup_end(ctx);
		// 	}
		// }
		// /*------------------------------------------------
		//  *                  COMBOBOX
		//  *------------------------------------------------*/
		// ui_header(ctx, media, "Combo box");
		// ui_widget(ctx, media, 40);
		// if (nk_combo_begin_label(ctx, items[selected_item], nk_vec2(nk_widget_width(ctx), 200))) {
		// 	nk_layout_row_dynamic(ctx, 35, 1);
		// 	for (i = 0; i < 3; ++i)
		// 		if (nk_combo_item_label(ctx, items[i], NK_TEXT_LEFT))
		// 			selected_item = i;
		// 	nk_combo_end(ctx);
		// }

		// ui_widget(ctx, media, 40);
		// if (nk_combo_begin_image_label(ctx, items[selected_icon], media->images[selected_icon], nk_vec2(nk_widget_width(ctx), 200))) {
		// 	nk_layout_row_dynamic(ctx, 35, 1);
		// 	for (i = 0; i < 3; ++i)
		// 		if (nk_combo_item_image_label(ctx, media->images[i], items[i], NK_TEXT_RIGHT))
		// 			selected_icon = i;
		// 	nk_combo_end(ctx);
		// }

		// /*------------------------------------------------
		//  *                  CHECKBOX
		//  *------------------------------------------------*/
		// ui_header(ctx, media, "Checkbox");
		// ui_widget(ctx, media, 30);
		// nk_checkbox_label(ctx, "Flag 1", &check0);
		// ui_widget(ctx, media, 30);
		// nk_checkbox_label(ctx, "Flag 2", &check1);

		// /*------------------------------------------------
		//  *                  PROGRESSBAR
		//  *------------------------------------------------*/
		// ui_header(ctx, media, "Progressbar");
		// ui_widget(ctx, media, 35);
		// nk_progress(ctx, &prog, 100, nk_true);

		/*------------------------------------------------
		 *                  PIEMENU
		 *------------------------------------------------*/
		if (nk_input_is_mouse_click_down_in_rect(&ctx->input, NK_BUTTON_RIGHT,
					nk_window_get_bounds(ctx),nk_true)){
			piemenu_pos = ctx->input.mouse.pos;
			piemenu_active = 1;
		}

		if (piemenu_active) {
			int ret = ui_piemenu(ctx, piemenu_pos, 140, &media->menu[0], 6);
			if (ret == -2)
				piemenu_active = 0;
			if (ret != -1)
			{
				if(ret == 2 && world->a_h != NULL)
					thread_free_and_add_cone(&world->cones, &world->cones_tmp, &world->cones_len, world->id);
				fprintf(stdout, "piemenu selected: %d\n", ret);
				piemenu_active = 0;
				//Continuer a ecrire le reste;
				world->redraw = 1;

			}

		}
	}
	//nk_style_set_font(ctx, &media->font_14->handle);
	nk_end(ctx);
}

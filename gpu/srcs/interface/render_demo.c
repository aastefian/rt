/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_demo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 21:17:41 by aanzieu           #+#    #+#             */
/*   Updated: 2017/08/24 21:29:08 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "../../includes/rt.h"
#include "../cuda/cudaheader/gpu_rt.h"
#include "header/nuklear.h"
#include "header/gui.h"

/* ===============================================================
 *
 *                          RENDER DEMO
 *
 * ===============================================================*/

void ui_widget_render(struct nk_context *ctx, struct media *media, float height)
{
	(void)media;
	nk_layout_row_static(ctx, height, WIN_WIDTH, 1);
}

void load_video_buffer(int *a_h, unsigned char *video_buffer)
{
	int i;
	t_color tmp;    

	for (i = 0; i < WIN_WIDTH * WIN_HEIGHT; i++)
	{
		tmp = int_to_rgb(a_h[i]);
		video_buffer[4 * i + 0] = tmp.r;
		video_buffer[4 * i + 1] = tmp.g;
		video_buffer[4 * i + 2] = tmp.b;        
		video_buffer[4 * i + 3] = 255;
	}
}

struct nk_image screen_load(int *a_h, unsigned char *video_buffer)
{
	int x,y;//,n;
	GLuint tex;

	x = WIN_WIDTH;
	y = WIN_HEIGHT;

	load_video_buffer(a_h, video_buffer);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, video_buffer);
	glGenerateMipmap(GL_TEXTURE_2D);
	return nk_image_id((int)tex);
}

// int	key_press(struct nk_context *ctx, t_world *world)
// {
// 	if (ctx->input.keyboard.keys[NK_KEY_L].down)
// 		world->keys.light_none = 0;
// 	else if (ctx->input.keyboard.keys[NK_KEY_K].down)
// 		world->keys.light_none = 1;
// 	else
// 		return (1);
// 	// printf("valeur de light %d\n", world->keys.light_none);
// 	return(0);
// 	// rt(world);
	
	
// }

void	render_demo(struct nk_context *ctx, struct media *media, int *a_h, t_world *world)
{
	struct nk_image screen;
	struct nk_vec2	pos;

	screen = screen_load(a_h, world->video_buffer);
	nk_style_set_font(ctx, &media->font_20->handle);
	if(nk_begin(ctx, world->title, nk_rect(260, 0, WIN_WIDTH, WIN_HEIGHT),
			NK_WINDOW_MOVABLE|NK_WINDOW_NO_SCROLLBAR|NK_WINDOW_TITLE))
	{
		pos = nk_window_get_position(ctx);
		ui_widget_render(ctx, media, WIN_HEIGHT);
		nk_image(ctx, screen);
	/*------------------------------------------------
	 *                  SELECTED OBJET
	 *------------------------------------------------*/
		mousepress_right(ctx, world, pos);
		if(!(key_press(ctx, world)))
			rt(world);
		nk_end(ctx);
	}
}

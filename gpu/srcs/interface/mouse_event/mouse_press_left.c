/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press_left.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 21:17:41 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/26 17:57:27 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "../../cuda/cudaheader/gpu_rt.h"
#include "nuklear.h"
#include "gui.h"
#include "float.h"

int		mousepress_left(struct nk_context *ctx, t_world *world,\
						struct nk_vec2 pos)
{
	t_ray			ray;
	t_intersection	intersection;
	t_vec2d			pad;
	static int	press;

	press = 2;
	intersection.t = DBL_MAX;
	intersection.type = '0';
	intersection.id = -1;
	if (ctx->input.mouse.buttons[NK_BUTTON_LEFT].down)
	{
		pad.x = ctx->input.mouse.pos.x - pos.x;
		pad.y = ctx->input.mouse.pos.y - pos.y - 40;
		if (pad.x < 0 || pad.y < 0 || pad.x > WIN_WIDTH || pad.y > WIN_HEIGHT)
			return (0);
		get_up_left(world);
		get_ray_direction(*(world), &ray, pad.x, pad.y);
		get_closest_intersection(*(world), ray, &intersection);
		if (intersection.t != INFINITY)
		{
			world->id_save = intersection.id_save;
			world->ob_save = intersection.type;
			world->keys.select = 1;
		}
	}
	if (nk_input_is_mouse_released(&ctx->input, NK_BUTTON_LEFT) && press == 2)
		press = -1;
	return (press == -1 ? 1 : 0);
}

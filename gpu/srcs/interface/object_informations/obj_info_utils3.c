/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_info_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 13:31:03 by xpouzenc          #+#    #+#             */
/*   Updated: 2017/09/27 17:28:10 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define NK_INCLUDE_MEDIA
#define NK_INCLUDE_FONT_BAKING
#include "rt.h"
#include "nuklear.h"
#include "gui.h"

static int	get_light_type(int type)
{
	if (type == LIGHT_P)
		return (0);
	if (type == LIGHT_BOX)
		return (1);
	return (0);
}

<<<<<<< Updated upstream
void		draw_light_type(struct nk_context *c, struct media *m,\
							t_world *w, int *type)
=======
void			draw_light_type(struct nk_context *c, struct media *m, t_world *w,\
	int *type, double *intensity)
>>>>>>> Stashed changes
{
	int	option;

	option = get_light_type(*type);
	ui_header(c, m, "---- Light Type");
	ui_widget_special_mode(c, m, 20);
	if (nk_button_symbol_label(c, (option == 0) ?
	NK_SYMBOL_CIRCLE_SOLID : NK_SYMBOL_CIRCLE_OUTLINE, "POINT", NK_TEXT_LEFT))
	{
		option = 0;
		if (*type == LIGHT_BOX && *intensity >= 0.2)
			*intensity -= 0.2;
		*type = LIGHT_P;
		w->redraw = 1;
	}
	if (nk_button_symbol_label(c, (option == 1) ?
	NK_SYMBOL_CIRCLE_SOLID : NK_SYMBOL_CIRCLE_OUTLINE, "BOX", NK_TEXT_LEFT))
	{
		option = 1;
		if (*type == LIGHT_P && *intensity <= 0.8)
			*intensity += 0.2;
		*type = LIGHT_BOX;
		w->redraw = 1;
	}
}

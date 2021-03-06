/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cones.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 18:08:45 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/18 16:02:44 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../cuda/cudaheader/gpu_rt.h"

void					init_cone_add(t_cone *c)
{
	c->id = 0;
	c->half_angle = 0.2;
	c->pos = new_vector(0, 0, -0.5);
	c->up = new_vector(0, 1, -0.5);
	c->color = (t_color)
	{color_to_coef(6), color_to_coef(205), color_to_coef(62)};
	c->chess = (t_color){-1, -1, -1};
	c->reflection_coef = 0;
	c->refraction_coef = 0;
	c->transparence_coef = 0;
	c->height = 0;
	c->min = new_vector(1, 1, 1);
	c->max = new_vector(3, 3, 3);
	c->perlin.is_set = 0;
	c->perlin.pre_set = 0;
	c->perlin.scale = 0;
	c->perlin.amount = 0;
	c->next = NULL;
}

static unsigned int		count_cones(t_cone *cones)
{
	t_cone			*p;
	unsigned int	size;

	size = 0;
	p = cones;
	while (p)
	{
		size++;
		p = p->next;
	}
	return (size);
}

void					load_cones(t_cone **cones, t_cone *cones_tmp,
		int *cones_len)
{
	unsigned int	i;
	t_cone			*tmp;

	if (*cones != NULL)
	{
		free(*cones);
		*cones = NULL;
		*cones_len = 0;
	}
	i = 0;
	if ((*cones_len = count_cones(cones_tmp)) == 0)
		return ;
	if (!(*cones = (t_cone*)malloc(sizeof(t_cone) * *cones_len)))
		show_error("Don't Malloc\n");
	tmp = cones_tmp;
	while (tmp)
	{
		(*cones)[i] = *tmp;
		tmp = tmp->next;
		i++;
	}
}

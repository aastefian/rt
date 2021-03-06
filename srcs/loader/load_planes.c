/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_planes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 17:59:25 by aanzieu           #+#    #+#             */
/*   Updated: 2017/09/18 16:51:36 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"
#include "../cuda/cudaheader/gpu_rt.h"

void						init_plane_add(t_plane *p)
{
	p->id = 0;
	p->up = new_vector(0, 1, 0);
	p->pos = new_vector(0, -1, 0);
	p->color = (t_color)
	{color_to_coef(236), color_to_coef(205), color_to_coef(62)};
	p->chess = (t_color){1, 0, 1};
	p->reflection_coef = 0;
	p->refraction_coef = 0;
	p->transparence_coef = 0;
	p->perlin.is_set = 0;
	p->perlin.pre_set = 0;
	p->perlin.scale = 0;
	p->perlin.amount = 0;
	p->next = NULL;
}

static unsigned int			count_planes(t_plane *planes)
{
	t_plane			*p;
	unsigned int	size;

	size = 0;
	p = planes;
	while (p)
	{
		size++;
		p = p->next;
	}
	return (size);
}

void						load_planes(t_plane **planes, t_plane *planes_tmp,
															int *planes_len)
{
	unsigned int	i;

	if (*planes != NULL)
	{
		free(*planes);
		*planes = NULL;
		*planes_len = 0;
	}
	i = 0;
	if ((*planes_len = count_planes(planes_tmp)) == 0)
		return ;
	if (!(*planes = (t_plane*)malloc(sizeof(t_plane) * (*planes_len))))
		show_error("Don't Malloc\n");
	while (planes_tmp)
	{
		(*planes)[i] = *planes_tmp;
		planes_tmp = planes_tmp->next;
		i++;
	}
}

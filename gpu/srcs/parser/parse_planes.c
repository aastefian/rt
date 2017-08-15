/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_planes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 15:33:11 by aanzieu           #+#    #+#             */
/*   Updated: 2017/06/16 17:25:39 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

static void	get_plane_next(t_world *world, char **tmp, int i, t_plane *p)
{
	if (ft_strnequ(tmp[i], "<origin>", ft_strlen("<origin>")))
		parse_point(&p->pos, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<normal>", ft_strlen("<normal>")))
		parse_vector(&p->up, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<color>", ft_strlen("<color>")))
		parse_color(&p->color, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<translation>", ft_strlen("<translation>")))
		parse_point_translation(&p->pos, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<rotation>", ft_strlen("<rotation>")))
		parse_rotation_object(&p->up, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<reflection>", ft_strlen("<reflection>")))
		parse_reflection(&p->reflection_coef, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<refraction>", ft_strlen("<refraction>")))
		parse_refraction(&p->refraction_coef, tmp, world->line);
	else if (ft_strnequ(tmp[i], "<chess>", ft_strlen("<chess>")))
		parse_color(&p->chess, tmp, world->line);
}

void		parse_plane(t_world *world, t_list *lst)
{
	t_plane	*p;
	char	**tmp;
	int		i;

	if (!(p = (t_plane *)ft_memalloc(sizeof(t_plane))))
		ft_putendl_fd("Error Malloc Plan", 1);
	p->chess = (t_color){-1, -1, -1};
	while (lst && !ft_strequ(lst->content, "</surface>"))
	{
		tmp = ft_strsplit(lst->content, ' ');
		i = -1;
		while (tmp[++i] != NULL)
			get_plane_next(world, tmp, i, p);
		ft_cleanup_str(tmp);
		ft_memdel((void**)&tmp);
		lst = lst->next;
	}
	add_plan(&world->planes_tmp, new_plan(p, world->id++));
	free(p);
}
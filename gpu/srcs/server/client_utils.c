/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 16:06:39 by aanzieu           #+#    #+#             */
/*   Updated: 2017/07/27 17:25:08 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cluster.h"

static void			free_obj_next(t_world *world, char cmd)
{
	if (cmd == 'y' && world->cylinders != NULL)
	{
		free(world->cylinders);
		world->cylinders = NULL;
		world->cylinders_len = 0;
	}
	if (cmd == 'd' && world->disks != NULL)
	{
		free(world->disks);
		world->disks = NULL;
		world->disks_len = 0;
	}
}

void				free_obj(t_world *world, char cmd)
{
	if (cmd == 's' && world->spheres != NULL)
	{
		free(world->spheres);
		world->spheres = NULL;
		world->spheres_len = 0;
	}
	if (cmd == 'p' && world->planes != NULL)
	{
		free(world->planes);
		world->planes = NULL;
		world->planes_len = 0;
	}
	if (cmd == 'n' && world->cones != NULL)
	{
		free(world->cones);
		world->cones = NULL;
		world->cones_len = 0;
	}
	if (cmd == 'l' && world->lights != NULL)
	{
		free(world->lights);
		world->lights = NULL;
		world->lights_len = 0;
	}
	free_obj_next(world, cmd);
}

int					data_grow(t_data *data, size_t size)
{
	void	*new;
	size_t	new_total;

	new_total = data->total * size;
	new = ft_memalloc(new_total);
	ft_memcpy(new, data->data, data->used);
	free(data->data);
	data->data = new;
	data->total = new_total;
	return (1);
}

int					data_recv(t_data *data, size_t size)
{
	if (!size)
		return (0);
	if (!data->total)
	{
		data->data = ft_memalloc(size);
		data->total = size;
		data->used = 0;
	}
	if (data->total >= data->used + size)
		return (1);
	if (data->total == 1)
		data->total++;
	return (data_grow(data, size));
}
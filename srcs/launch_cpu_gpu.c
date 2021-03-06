/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_cpu_gpu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xpouzenc <xpouzenc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 10:49:50 by svilau            #+#    #+#             */
/*   Updated: 2017/10/03 12:25:55 by xpouzenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <gpu_rt.h>
#include <display.h>
#include <unistd.h>
#include <cluster.h>

static	void	*perform_thread(void *arg)
{
	t_thread_input	*t;
	int				x;
	int				x_aa;
	int				y;
	int				y_aa;

	t = (t_thread_input *)arg;
	y = (((t->th) * ((t->y_max - t->y_min) / NB_TH)
		+ t->y_min));
	y_aa = y * t->aa;
	while (y < (t->th + 1) * ((t->y_max - t->y_min) / NB_TH) + t->y_min)
	{
		x = -1;
		x_aa = 0;
		while (++x < t->world->viewplane.x_res)
		{
			t->world->a_h[(y - t->y_min) *
			t->world->viewplane.x_res + x] =
				ray_tracer_cpu(*t->world, x_aa, y_aa);
			x_aa += t->world->aa;
		}
		y_aa += t->world->aa;
		y++;
	}
	pthread_exit(0);
}

int				launch_thread(t_world *world, int y_min, int y_max, int aa)
{
	t_thread_input	tab[NB_TH];
	int				i;

	i = -1;
	while (++i < NB_TH)
	{
		tab[i].th = i;
		tab[i].world = world;
		tab[i].y_min = y_min;
		tab[i].y_max = y_max;
		tab[i].aa = aa;
		if (pthread_create(&world->thread[i], NULL, &perform_thread, &tab[i]))
			ft_putendl_fd("Error : Can't init launch_rtv1", 1);
	}
	i = -1;
	while (++i < NB_TH)
		pthread_join(world->thread[i], NULL);
	return (0);
}

void			launch_cpu(t_world *world)
{
	int i;

	i = -1;
	if (!world->p)
	{
		if (!(world->p = (int *)malloc(512 * sizeof(int))))
			show_error("Error malloc noise\n");
		perlin_noise_setup(world);
	}
	if (world->clientrender == 1)
	{
		ft_putendl("Calculating on Cpu");
		refresh_viewplane_cluster(world);
		get_viewplane_cluster(world);
		launch_thread(world, world->offsets.y_min / world->render_factor,
				world->offsets.y_max / world->render_factor, world->offsets.aa);
		ft_putendl("End of Calculate");
		return ;
	}
	refresh_viewplane_cluster(world);
	get_viewplane(world);
	launch_thread(world, 0, world->viewplane.y_res, world->aa);
}

/*
**	On event receive send data to handler
*/

void			launch_gpu(t_world *world)
{
	if (world->clientrender == 1)
	{
		ft_putendl("Calculating on Gpu");
		refresh_viewplane_cluster(world);
		get_viewplane_cluster(world);
		render_cuda(world->a_h, WIN_WIDTH,
				world->offsets.y_max - world->offsets.y_min, *world, 0);
		ft_putendl("End of Calculate");
		return ;
	}
	get_viewplane(world);
	render_cuda(world->a_h, world->viewplane.x_res,
		world->viewplane.y_res, *world, 0);
}

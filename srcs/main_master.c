/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanzieu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 14:03:16 by aanzieu           #+#    #+#             */
/*   Updated: 2017/10/09 12:53:55 by aanzieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cluster.h>
#include <display.h>
#include <unistd.h>
#include <gpu_rt.h>

/*
 ** Initialize Cluster to find if some Client is open
*/

void			*init_client(void *arg)
{
	t_client	*new;
	t_cluster	*self;
	int			fd;
	int			nbr_clients;

	self = arg;
	nbr_clients = 0;
	while (nbr_clients < MAX_CLIENTS)
	{
		fd = accept(self->sockfd, NULL, NULL);
		nbr_clients++;
		new = ft_memalloc(sizeof(*new));
		ft_bzero(new, sizeof(*new));
		new->fd = fd;
		new->status = 'a';
		new->ww = WIN_WIDTH;
		new->next = self->client_list;
		self->client_list = new;
	}
	close(self->sockfd);
	return (NULL);
}

void			cluster_initialize(t_world *world, t_cluster *cl)
{
	int					ret;
	int					pf;
	struct sockaddr_in	sk;
	int					enable;

	cl->client_list = NULL;
	if ((cl->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		ft_putendl_fd("Error : no create socket", 1);
	if (setsockopt(cl->sockfd,
				SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
		ft_putendl_fd("Error :setsockopt(SO_REUSEADDR) failed", 1);
	ft_bzero(&sk, sizeof(sk));
	sk.sin_family = AF_INET;
	sk.sin_port = FIND_PORT;
	sk.sin_addr.s_addr = INADDR_ANY;
	pf = 0;
	while (pf <= 5 && (ret = bind(cl->sockfd, (void *)&sk, sizeof(sk))) == -1)
		sk.sin_port = FIND_PORT + ++pf;
	if (ret == -1)
		ft_putendl_fd("Error : all ports used", 1);
	if (listen(cl->sockfd, 0) == -1)
		ft_putendl_fd("Error : listen", 1);
	cl->world = world;
	cl->nbr_clients = 0;
	pthread_create(&cl->client_thread, NULL, &init_client, cl);
}

void			put_buffer_together(t_cluster *cluster, t_client *clients,
		int x, int y)
{
	int	nbr_clients;
	int	y_max;
	int	i;

	nbr_clients = cluster->nbr_clients;
	while (nbr_clients-- && clients != NULL)
	{
		i = 0;
		if (clients->buffer)
		{
			y = nbr_clients *
				(cluster->world->viewplane.y_res / cluster->nbr_clients);
			y_max = y +
				(cluster->world->viewplane.y_res / cluster->nbr_clients);
			while (y < y_max)
			{
				x = -1;
				while (++x < cluster->world->viewplane.x_res)
					cluster->world->a_h[y *
					cluster->world->viewplane.x_res + x] = clients->buffer[i++];
				y++;
			}
		}
		clients = clients->next;
	}
}

void			render_clustering(t_cluster *cluster)
{
	int			tmp;

	cluster->world->render_factor = 1;
	refresh_viewplane(cluster->world);
	get_viewplane(cluster->world);
	cluster->world->size_main =
	cluster->world->viewplane.x_res *
			cluster->world->viewplane.y_res * sizeof(int);
	if (cluster->world->a_h == NULL)
	{
		if (!(cluster->world->a_h = ft_memalloc(cluster->world->size_main)))
			ft_putendl_fd("Error : Can't malloc cluster", 1);
	}
	ft_bzero(cluster->world->a_h, cluster->world->size_main);
	tmp = cluster->nbr_clients;
	if (cluster_stratege(cluster) == 1)
		launch_client(cluster, cluster->client_list);
	tmp = cluster->nbr_clients;
	remove_client_if(cluster, &cluster->client_list, NULL, NULL);
	if (cluster->nbr_clients == tmp)
		put_buffer_together(cluster, cluster->client_list, 0, 0);
	free_buffer(cluster);
	cluster->world->on = 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/24 23:08:38 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/06/26 02:42:09 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdio.h>
#include <stdlib.h>

static void		freed(t_rt *e)
{
	int			i;

	free(e->cam_ray);
	i = 0;
	while (e->objects[i])
	{
		free(e->objects[i]->center);
		free(e->objects[i]->surface_c);
		free(e->objects[i]->emission_c);
		if (!ft_strcmp(e->types[i], "plan"))
			free(e->objects[i]->normal);
		free(e->objects[i]);
		free(e->types[i]);
		i++;
	}
	free(e->types);
	free(e->objects);
	i = 0;
	while (e->spot[i])
		free(e->spot[i++]);
	free(e->spot);
	free(e);
}

int				key_hook(int keycode, t_rt *e)
{
	(void)e;
	if (keycode == EXIT)
		exit(0);
	return (0);
}

int				expose(t_rt *e)
{
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}

int				main(int ac, char **av)
{
	t_rt		*e;

	if (ac != 2)
		return (-1);
	e = (t_rt*)malloc(sizeof(t_rt));
	if (ft_parse(av[1], e) < 0)
	{
		ft_putstr("ERROR !\n");
		exit(0);
	}
	if (!(e->mlx = mlx_init()))
		return (0);
	e->win = mlx_new_window(e->mlx, LAR, LON, "RAY's");
	e->img = NULL;
	if (e->img)
		mlx_destroy_image(e->mlx, e->img);
	e->img = mlx_new_image(e->mlx, LAR, LON);
	e->data = mlx_get_data_addr(e->img, &e->bpp, &e->sizeline, &e->endian);
	ft_render(e);
	mlx_key_hook(e->win, key_hook, e);
	mlx_expose_hook(e->win, expose, e);
	mlx_loop(e->mlx);
	freed(e);
	return (0);
}

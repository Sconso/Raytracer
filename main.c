/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/24 23:08:38 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/06/25 23:10:56 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdio.h>

int		key_hook(int keycode, t_env *e)
{
	(void)e;
	if (keycode == EXIT)
		exit(0);
	return (0);
}

int		expose(t_env *e)
{
	if (e->img)
		mlx_destroy_image(e->mlx, e->img);
	e->img = mlx_new_image(e->mlx, LAR, LON);
	e->data = mlx_get_data_addr(e->img, &e->bpp,
								  &e->sizeline, &e->endian);

	ft_render(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);

	return (0);
}

int		main(int ac, char **av)
{
	t_env		*e;

	if (ac != 2)
		return (-1);
	e = (t_env*)malloc(sizeof(t_env));
	if (ft_parse(av[1], e) < 0)
	{
		ft_printf("ERROR !\n");
		exit(0);
	}
	if (!(e->mlx = mlx_init()))
		return (0);
	e->win = mlx_new_window(e->mlx, LAR, LON, "RAY's");
	e->img = NULL;

	mlx_key_hook(e->win, key_hook, e);
	mlx_expose_hook(e->win, expose, e);
	mlx_loop(e->mlx);
	return (0);
}

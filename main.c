/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/24 23:08:38 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/06/26 01:00:55 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include <stdio.h>

int		key_hook(int keycode, t_rt *e)
{
	(void)e;
	if (keycode == EXIT)
		exit(0);
	return (0);
}

int		loop(t_rt *e)
{
	e->mlx = e->cmlx;
	e->win = e->cwin;
	return (1);
}

int		expose(t_rt *e)
{
	printf("\nStruct Begin = %p\n", e);
	printf("Expose entry = \n\t%p - %p\n\t%p - %p\n\t%p\n\n", e->mlx, e->win, e->cmlx, e->cwin, e->img);
	printf("After Copy = \n\t%p - %p\n\t%p - %p\n\t%p\n\n", e->mlx, e->win, e->cmlx, e->cwin, e->img);
	if (e->img)
		mlx_destroy_image(e->mlx, e->img);
	e->img = mlx_new_image(e->mlx, LAR, LON);
	e->data = mlx_get_data_addr(e->img, &e->bpp, &e->sizeline, &e->endian);
	printf("Before Render = \n\t%p - %p\n\t%p - %p\n\t%p\n\n", e->mlx, e->win, e->cmlx, e->cwin, e->img);
	ft_render(e);
	printf("After Render = \n\t%p - %p\n\t%p - %p\n\t%p\n\n", e->mlx, e->win, e->cmlx, e->cwin, e->img);

	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	printf("Expose end = \n\t%p - %p\n\t%p - %p\n\t%p\n", e->mlx, e->win, e->cmlx, e->cwin, e->img);
	printf("Struct End = %p\n", e);
	return (0);
}

int		main(int ac, char **av)
{
	t_rt		*e;

	if (ac != 2)
		return (-1);
	e = (t_rt*)malloc(sizeof(t_rt));
	if (ft_parse(av[1], e) < 0)
	{
		ft_printf("ERROR !\n");
		exit(0);
	}
	if (!(e->mlx = mlx_init()))
		return (0);
	e->win = mlx_new_window(e->mlx, LAR, LON, "RAY's");

	e->cmlx = e->mlx;
	e->cwin = e->win;

	printf("%p - %p - %p - %p - %p\n", e->mlx, e->win, e->cmlx, e->cwin, e->img);

	e->img = NULL;

	mlx_key_hook(e->win, key_hook, e);
	mlx_expose_hook(e->win, expose, e);
	mlx_loop_hook(e->mlx, loop, e);
	mlx_loop(e->mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_fractal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 16:48:56 by oezzaou           #+#    #+#             */
/*   Updated: 2023/02/18 19:12:59 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

void	display_julia_fractal(t_img *img)
{
	t_pixel_grid	grid;
	t_equation		z;

	img->fractal = JULIASET;
	grid.x = -1;
	while (++(grid.x) < img->w)
	{
		grid.y = -1;
		while (++(grid.y) < img->h)
		{
			z.r = -img->p->b + (grid.x * img->p->a/ img->w) + img->p->dx;
			z.i = img->p->b - (grid.y * img->p->a/ img->h) + img->p->dy;
			z.n = -1;
			while (++z.n < img->nmax && (z.r * z.r) + (z.i * z.i) < 4.0)
			{
				z.tmp = z.r;
				z.r = (z.r * z.r) - (z.i * z.i) + img->julia->cr;
				z.i = (2 * z.tmp * z.i) + img->julia->ci;
			}
			if (z.n == img->nmax)
				mlx_pixel_put_in_img(img, grid.x, grid.y, 255);
			else
				mlx_pixel_put_in_img(img, grid.x, grid.y, 0);
		}
	}
	mlx_put_image_to_window(img->var->mlx, img->var->win, img->img, 0, 0);
	mlx_put_max_iteration(img);
}

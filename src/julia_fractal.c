/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_fractal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 16:48:56 by oezzaou           #+#    #+#             */
/*   Updated: 2023/02/17 17:58:06 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

void	display_julia_fractal(t_img *img)
{
	t_pixel_grid	grid;
	t_equation		z;

	printf("Cr ====> %f\n", img->julia->cr);
	printf("Ci ====> %f\n", img->julia->ci);
	img->fractal = JULIASET;
	grid.x = -1;
	while (++(grid.x) < img->w)
	{
		grid.y = -1;
		while (++(grid.y) < img->h)
		{
			z.r = -img->plan->y + (grid.x * img->plan->x/ img->w) + img->plan->dx;
			z.i = img->plan->y - (grid.y * img->plan->x/ img->h) + img->plan->dy;
			z.n = -1;
			while (++z.n < img->nmax && (z.r * z.r) + (z.i * z.i) < 4.0)
			{
				z.tmp = z.r;
				z.r = (z.r * z.r) - (z.i * z.i) + img->julia->cr;
				z.i = (2 * z.tmp * z.i) + img->julia->ci;
			}
			if (z.n == img->nmax)
				mlx_pixel_put_in_img(img, grid.x, grid.y, create_trgb(0, 0, 255, 0));
			else
				mlx_pixel_put_in_img(img, grid.x, grid.y, create_trgb(0, 0, 0, 0));
		}
	}
	mlx_put_image_to_window(img->var->mlx, img->var->win, img->img, 0, 0);
}

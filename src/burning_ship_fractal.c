/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship_fractal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:41:35 by oezzaou           #+#    #+#             */
/*   Updated: 2023/02/20 16:16:18 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

void	display_burning_ship_fractal(t_img *img)
{
	t_pixel_grid	grid;
	t_equation		z;

	img->fractal = BURNING_SHIP;
	grid.x = -1;
	while (++(grid.x) < img->w)
	{
		img->p->xc = -img->p->b + (grid.x * slope(img)) + img->p->dx;
		grid.y = -1;
		while (++(grid.y) < img->h)
		{
			img->p->yc = -img->p->b + (grid.y * slope(img)) + img->p->dy;
			z.r = 0;
			z.i = 0;
			z.n = -1;
			while (++z.n < img->nmax && (z.r * z.r) + (z.i * z.i) < 4)
			{
				z.tmp = AB(z.r);
				z.r = (AB(z.r) * AB(z.r)) - (A(z.i) * A(z.i)) + img->p->xc;
				z.i = 2 * AB(z.i) * z.tmp + img->p->yc;
			}
			mlx_pixel_put_in_img(img, grid.x, grid.y, create_color(z.n));
		}
	}
	mlx_put_image_to_window(img->var->mlx, img->var->win, img->img, 0, 0);
}

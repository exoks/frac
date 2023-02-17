/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship_fractal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:41:35 by oezzaou           #+#    #+#             */
/*   Updated: 2023/02/17 20:01:33 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# include "fractol.h"

int	creat_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	display_burning_ship_fractal(t_img *img)
{
	t_pixel_grid	grid;
	t_complex_plan	plan;
	t_equation		z;

	img->fractal = MANDELBROT;
	grid.x = -1;
	while (++(grid.x) < img->w)
	{
		plan.xc =  -img->plan->y + ((grid.x * img->plan->x) / img->w) + img->plan->dx;
		grid.y = -1;
		while (++(grid.y) < img->h)
		{
			plan.yc = img->plan->y - ((grid.y * img->plan->x) / img->h) + img->plan->dy;
			z.r = 0;
			z.i = 0;
			z.n  = -1;
			while (++z.n < img->nmax && (z.r * z.r) + (z.i * z.i) < 4)
			{
				z.tmp = z.r;
				z.r = (z.r * z.r) - (z.i * z.i) + plan.xc;
				z.i = 2 * z.i * z.tmp + plan.yc;
				if (z.r < 0)
					z.r = -z.r;
				if (z.i < 0)
					z.i = -z.i;
			}
			if (z.n != img->nmax)
				mlx_pixel_put_in_img(img, grid.x, grid.y, creat_trgb(0, 256 - z.n, z.n, 256 - z.n));
			else
				mlx_pixel_put_in_img(img, grid.x, grid.y, creat_trgb(0, 0, 0, 0));
		}
	}
	mlx_put_image_to_window(img->var->mlx, img->var->win, img->img, 0, 0);
}
/****** FROM COMPLEX PLAN TO PIXEL GRIDE ******/
/* 	x = (xc - 2) / step => ex step = 0.1      */
/*  y = (2 - yc) / step                       */
/**********************************************/

/****** FROM PIXEL GRIDE TO COMPLEX PALN ******/
/*	      xc = (2 - x / (h / 4))              */
/*        yc = (2 - y / (h / 4))              */
/**********************************************/

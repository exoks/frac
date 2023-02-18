/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_fractal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:41:35 by oezzaou           #+#    #+#             */
/*   Updated: 2023/02/18 19:11:49 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# include "fractol.h"

void	mlx_put_max_iteration(t_img *img)
{
	char	*tmp;
	char	*iter;

	tmp = ft_itoa(img->nmax);
	iter = ft_strjoin(ITERATIONS, tmp);
	mlx_string_put(img->var->mlx, img->var->win, 10, 1170, 255, iter);
	free(tmp);
	free(iter);
}

void	display_mandelbrot_fractal(t_img *img)
{
	t_pixel_grid	grid;
	t_equation		z;
	char			s;

	img->fractal = MANDELBROT;
	grid.x = -1;
	while (++(grid.x) < img->w)
	{
		img->p->xc =  -img->p->b + ((grid.x * img->p->a) / img->w) + img->p->dx;
		grid.y = -1;
		while (++(grid.y) < img->h)
		{
			img->p->yc = img->p->b - ((grid.y * img->p->a) / img->h) + img->p->dy;
			z.r = 0;
			z.i = 0;
			z.n  = -1;
			while (++z.n < img->nmax && (z.r * z.r) + (z.i * z.i) < 4)
			{
				z.tmp = z.r;
				z.r = (z.r * z.r) - (z.i * z.i) + img->p->xc;
				z.i = 2 * z.i * z.tmp + img->p->yc;
			}
			if (z.n != img->nmax)
				mlx_pixel_put_in_img(img, grid.x, grid.y,((255 - z.n) << 16));
			else
				mlx_pixel_put_in_img(img, grid.x, grid.y, 0);
		}
	}
	mlx_put_image_to_window(img->var->mlx, img->var->win, img->img, 0, 0);
	mlx_put_max_iteration(img);
}






/****** FROM COMPLEX PLAN TO PIXEL GRIDE ******/
/* 	x = (xc - 2) / step => ex step = 0.1      */
/*  y = (2 - yc) / step                       */
/**********************************************/

/****** FROM PIXEL GRIDE TO COMPLEX PALN ******/
/*	      xc = (2 - x / (h / 4))              */
/*        yc = (2 - y / (h / 4))              */
/**********************************************/

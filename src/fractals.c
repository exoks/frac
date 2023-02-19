/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_fractal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:41:35 by oezzaou           #+#    #+#             */
/*   Updated: 2023/02/18 22:36:55 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# include "fractol.h"

int	display_fractal(t_img *img, int ac, char **av)
{
	if ((ac == 2 && str2double(av[1]) == MANDELBROT)
			|| (img->fractal == MANDELBROT))
		return (display_mandelbrot_fractal(img), MANDELBROT);
	if ((ac == 2 && str2double(av[1]) == BURNING_SHIP)
			|| (img->fractal == BURNING_SHIP))
		return (display_burning_ship_fractal(img), 3);
	if ((ac == 4 && str2double(av[1]) == JULIASET)
			|| (img->fractal = JULIASET))
	{
		if (ac != 0)
		{
			img->julia->cr = str2double(av[2]);
			img->julia->ci = str2double(av[3]);
		}
		return (display_julia_fractal(img), JULIASET);
	}
	return (0);
}

void	display_mandelbrot_fractal(t_img *img)
{
	t_pixel_grid	grid;
	t_equation		z;

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
				mlx_pixel_put_in_img(img, grid.x, grid.y, z.n);
			else
				mlx_pixel_put_in_img(img, grid.x, grid.y, 0);
		}
	}
	mlx_put_image_to_window(img->var->mlx, img->var->win, img->img, 0, 0);
	mlx_put_max_iteration(img);
}

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

void	mlx_put_max_iteration(t_img *img)
{
	char	*tmp;
	char	*iter;

	tmp = ft_itoa(img->nmax);
	iter = ft_strjoin(ITERATIONS, tmp);
	mlx_string_put(img->var->mlx, img->var->win, 10, 1170, 255, iter);
	mlx_string_put(img->var->mlx, img->var->win, 10, 30, 255, "Usage:");
	mlx_string_put(img->var->mlx, img->var->win, 20, 90, 255, "Arows       : moving fractal");
	mlx_string_put(img->var->mlx, img->var->win, 20, 110, 255, "Mouse wheel : zoom in && zoom out");
	mlx_string_put(img->var->mlx, img->var->win, 20, 70, 255, "R           : reset");
	mlx_string_put(img->var->mlx, img->var->win, 20, 50, 255, "ESC         : exit");
	free(tmp);
	free(iter);
}

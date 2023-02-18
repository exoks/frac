/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:01:59 by oezzaou           #+#    #+#             */
/*   Updated: 2023/02/18 22:51:59 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

int	close_window(t_img *img)
{
	exit(mlx_destroy_window(img->var->mlx, img->var->win) * 0);
}

int	on_press_button(int code, t_img *img)
{
	if (code == ESC)
		close_window(img);
	if (code == PLUS || code == MINUS)
		img->nmax += 5 * ((code == PLUS) - (code == MINUS));
	if (code == RESET)
			mlx_create_image(img->var, img, img->julia, img->p);
	if (code >= RIGHT && code <= UP)
	{
		img->p->dx += (img->p->a / 10.0) * ((code == RIGHT) - (code == LEFT));
		img->p->dy += (img->p->b / 10.0) * ((code == DOWN) - (code == UP));
	}
	display_fractal(img, 0, 0);
	return (0);
}

// MAKE ANY POINT YOU CHOSE AS THE REFERENCE POINT
int	zoom(int code, int x, int y, t_img *img)
{
	double	new_xc;
	double	new_yc;

	img->p->old_xc = -img->p->b + (x * img->p->a / 1200) + img->p->dx;
	img->p->old_yc = img->p->b - (y * img->p->a / 1200) + img->p->dy;
	if (code == SCROLL_DOWN || code == SCROLL_UP)
	{
		img->p->a /= 1.3 * (code == 4) +  (1 / 1.4) * (code == 5);
		img->p->b /= 1.3 * (code == 4) + (1 / 1.3) * (code == 5);
		new_xc = -img->p->b + (((double) x) * img->p->a / img->w);
		new_yc = img->p->b - (((double) y) * img->p->a / img->h);
		img->p->dx = img->p->old_xc - new_xc;
		img->p->dy = img->p->old_yc - new_yc;
	}
	display_fractal(img, 0, 0);
	return (0);
}

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
int	main(int ac, char **av)
{
	t_var			var;
	t_img			img;
	t_complex_plan	p;
	t_julia			julia;
	
	mlx_create_window(&var);
	mlx_create_image(&var, &img, &julia, &p);
	if (!display_fractal(&img, ac, av))
		return (display_options(), EXIT_SUCCESS);
	mlx_key_hook(var.win, on_press_button, &img);
	mlx_mouse_hook(img.var->win, zoom, &img);
	mlx_hook(var.win, 17, 0, close_window, &img);
	mlx_loop(var.mlx);
	return (EXIT_SUCCESS);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	create_color(int iter)
{
	if (iter == 1)
		return (create_trgb(0, 255, 0, 0));
	if (iter == 2)
		return (create_trgb(0, 255, 100, 0));
	if (iter == 3)
		return (create_trgb(0, 0, 255, 0));
	if (iter == 4)
		return (create_trgb(0, 0, 100, 50));
	if (iter == 5)
		return (create_trgb(0, 0, 100, 25));
	return (create_trgb(0, 0, 255 - iter, iter));
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:58:10 by oezzaou           #+#    #+#             */
/*   Updated: 2023/02/21 23:38:56 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fractol.h"

void	mlx_create_window(t_var *var)
{
	var->mlx = mlx_init();
	if (!var->mlx)
		exit(EXIT_FAILURE);
	var->win = mlx_new_window(var->mlx, 1200, 1200, "FRACTAL");
}

void	mlx_create_image(t_var *var, t_img *img, t_julia *c, t_complex_plan *p)
{
	img->julia = c;
	img->nmax = 160;
	img->h = 1200;
	img->w = 1200;
	p->dx = 0;
	p->dy = 0;
	p->a = 4;
	p->b = 2;
	p->old_xc = 0;
	p->old_yc = 0;
	img->p = p;
	img->img = mlx_new_image(var->mlx, img->h, img->w);
	img->var = var;
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->l_len, &img->edn);
}

void	mlx_pixel_put_in_img(t_img *img, int x, int y, int color)
{
	int	*pixel;

	pixel = img->addr + (y * img->l_len + x * (img->bpp / 8));
	*pixel = color;
}

void	set_rgb(t_rgb *rgb, float r, float g, float b)
{
	rgb->r = r;
	rgb->g = g;
	rgb->b = b;
}

int	hsv_to_rgb(int hue, float saturation, float value)
{
	float	c;
	float	x;
	float	m;
	t_rgb	rgb;

	c = (value / 100.0) * (saturation / 100.0);
	x = c * (1 - ABS((fmod(((float) hue / 60.0), 2) - 1)));
	m = (value / 100.0) - c;
	if (hue >= 0 && hue < 60)
		set_rgb(&rgb, c, x, 0);
	if (hue >= 60 && hue < 120)
		set_rgb(&rgb, x, c, 0);
	if (hue >= 120 && hue < 180)
		set_rgb(&rgb, 0, c, x);
	if (hue >= 180 && hue < 240)
		set_rgb(&rgb, 0, x, c);
	if (hue >= 240 && hue < 300)
		set_rgb(&rgb, x, 0, c);
	if (hue >= 300 && hue < 360)
		set_rgb(&rgb, c, 0, x);
	rgb.r = (rgb.r + m) * 255;
	rgb.g = (rgb.g + m) * 255;
	rgb.b = (rgb.b + m) * 255;
	return ((int) rgb.r << 16 | (int) rgb.g << 8 | (int) rgb.b);
}

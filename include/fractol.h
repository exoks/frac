/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:59:22 by oezzaou           #+#    #+#             */
/*   Updated: 2023/02/17 18:48:04 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define INFO "The Mandelbrot set is :|the set of complex numbers c|for which the function|fc(z) = z^2 + c does not di|verge to infinity when|iterated from z = 0."
# define MENU "====> THIS MENU SHOWS YOU ALL THE AVAILIBLE FRACTALS : "
# define TITLE "===== (MANDELBROT SET ?) ========== (MANDELBORT FRACTAL) ===="
# define DEV "==================== (MADE BY OEZZAOU) ======================"
# define MANDEL "1|_Mandelbrot fractol ====> ./fractal 1"
# define JULIA "2|_Julia fractol      ====> ./fractal 2 [ARG1] [ARG2] (-2 <= ARG <= 2)"
# define MANDELBROT 1
# define JULIASET 2
# include "mlx.h"
# include "ft_printf.h"
#include <math.h>
# include <stdio.h>

# define SCROLL_UP 5
# define SCROLL_DOWN 4
//############################//
//        FRACTLAS            //
//############################//
# define MANDELBROT_FRACTAL "MANDELBROT FRACTAL"
# define JULIA_FRACTAL "JULIA FRACTAL"

//############################//
//        ARROWS              //
//############################//
# define MOVE_LEFT 124
# define MOVE_RIGHT 123
# define MOVE_UP 126
# define MOVE_DOWN 125
# define RESET	15
# define ESC 53
# define PLUS 69
# define MINUS 78

typedef struct s_var
{
	void	*mlx;
	void	*win;
}				t_var;

//############################//
//        COMPLEX PLAN        //
//############################//
typedef	struct	s_complex_plan
{
	double		xc;
	double		yc;
}				t_complex_plan;

//###########################//
//        PIXEL grid         //
//###########################//
typedef struct 	s_pixel_grid
{
	double		x;
	double		y;
}				t_pixel_grid;

typedef	struct	s_equation
{
	double		r;
	double		i;
	double		tmp;
	int			n;
}				t_equation;

typedef struct s_c_plan
{
	double	x;
	double	y;
	double	m_x;
	double	m_y;
	double	dx;
	double	dy;
	double	old_x;
	double	old_y;
}	t_c_plan;

typedef struct	s_julia
{
	double	cr;
	double	ci;
}				t_julia;
//How much should I weigh for my height and age?
typedef struct		s_img
{
	void			*addr;
	void			*img;
	int				line_len;
	int				bpp;
	int				endian;
	int				h;
	int				w;
	int				fractal;
	int				nmax;
	t_var			*var;
	t_julia			*julia;
	t_c_plan		*plan;
}					t_img;

int		create_trgb(int t, int r, int g, int b);
double	str2double(char *s);
void	mlx_pixel_put_in_img(t_img *img, int x, int y, int color);
void	mlx_create_window(t_var *var, char *title);
void	mlx_create_image(t_var *var, t_img *img, t_julia *j, t_c_plan *plan);
void	display_options(void);
void	display_mandelbrot_fractal(t_img *img);
void	display_burning_ship_fractal(t_img *img);
void    display_julia_fractal(t_img *img);
#endif

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 21:14:18 by oezzaou           #+#    #+#              #
#    Updated: 2023/02/18 11:55:48 by oezzaou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####################################
#           Compiler               #
####################################
CC = gcc
CFLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit
MLX_LINUX_FLAGS = -lmlx -lXext -lX11 -lz -lm

####################################
#              SRCS                #
####################################
NAME = fractol
OBJDIR = obj
SRCDIR = src
INC = -I include/ -I ft_printf/include -I ft_printf/libft
SRCS := burning_ship_fractal fractol_events fractol_utils fractol_menu fractals fractol
OBJS := $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRCS)))
SRCS := $(addprefix $(SRCDIR)/, $(addsuffix .c, $(SRCS)))
LIBFTPRINTF = ft_printf/libftprintf.a

#####################################
#              RULES                #
#####################################

all: $(OBJDIR) $(NAME)

$(NAME): $(OBJS) $(LIBFTPRINTF) 
	@$(CC) $(CFLAGS) $(INC) $^ -o $@ $(MLX_LINUX_FLAGS)
	@printf "\n%10s===========%10s\n <<<<<<<<<< FRACTOL >>>>>>>>>>\n" " " " "
	@printf "%10s===========%10s\n" " " " "

$(MLX_LIB):
	@make -C include/ clean
	@make -C include/ make

$(LIBFTPRINTF):
	@make -C ft_printf

$(OBJDIR):
	@echo "Creating >>>>>>>>>>> OBJDIR ..."
	@mkdir -p $@
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "Creating >>>>>>>>>>> $@ ..."

re: fclean all

mandel: 
	./$(NAME) 1
julia:
	./$(NAME) 2 0 0

clean:
	@rm -rf $(OBJDIR)
	@make -C ft_printf/ clean
	@echo "Cleaning OBJECTS >>>>>>>> ... -=> Done"

fclean: clean
	@make -C ft_printf/ fclean
	@rm -rf $(NAME)
	@echo "Cleaning $(NAME) >>>>>>>> ... -=> Done"

.PHONY: all clean fclean re $(LIBFTPRINTF) $(MLX_LIB)

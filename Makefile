# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 21:14:18 by oezzaou           #+#    #+#              #
#    Updated: 2023/02/21 22:42:09 by oezzaou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####################################
#           Compiler               #
####################################
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

####################################
#              SRCS                #
####################################
NAME := fractol
NAME_B := fractol_bonus
OBJDIR = obj
SRCDIR = src
BDIR := bonus
INC = -I include/ -I ft_printf/include -I ft_printf/libft
####################################
#             MONDATORY            #
####################################
SRCS := fractol fractol_menu fractol_window fractals fractol_events fractol_utils
OBJS := $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRCS)))
SRCS := $(addprefix $(SRCDIR)/, $(addsuffix .c, $(SRCS)))

####################################
#             BONUS                #
####################################
SRCB := burning_ship_fractal fractals_bonus fractol_events_bonus
OBJB := $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRCB)))
SRCB := $(addprefix $(SRCDIR)/$(BDIR)/, $(addsuffix .c, $(SRCB)))

PREQ := fractol fractol_menu fractol_window fractol_utils
OPREQ := $(addprefix $(OBJDIR)/, $(addsuffix .o, $(PREQ)))
PREQ := $(addprefix $(SRCDIR)/, $(addsuffix .c, $(PREQ)))

LIBFTPRINTF = ft_printf/libftprintf.a

#####################################
#              RULES                #
#####################################
all: $(OBJDIR) $(NAME)

$(NAME): $(OBJS) $(LIBFTPRINTF) 
	@$(CC) $(CFLAGS) $(INC) $^ -o $@ $(MLX_FLAGS)
	@printf "\n%10s===========%10s\n <<<<<<<<<< $(NAME) >>>>>>>>>>\n" " " " "
	@printf "%10s===========%10s\n" " " " "

bonus: $(OBJDIR) $(NAME_B) 

$(NAME_B): $(OBJB) $(OPREQ) $(LIBFTPRINTF)
	@$(CC) $(CFLAGS) $(INC) $^ -o $@ $(MLX_FLAGS)
	@printf "\n%10s===========%10s\n <<<<<<< $(NAME_B) >>>>>>>\n" " " " "
	@printf "%10s===========%10s\n" " " " "

$(LIBFTPRINTF):
	@make -C ft_printf

$(OBJDIR):
	@echo "Creating >>>>>>>>>>> OBJDIR ..."
	@mkdir -p $@
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "Creating >>>>>>>>>>> $@ ..."

$(OBJDIR)/%.o: $(SRCDIR)/$(BDIR)/%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "Creating >>>>>>>>>>> $@ ..."

re: fclean all

clean:
	@rm -rf $(OBJDIR)
	@make -C ft_printf/ clean
	@echo "Cleaning OBJECTS >>>>>>>> ... -=> Done"

fclean: clean
	@make -C ft_printf/ fclean
	@rm -rf $(NAME) $(NAME_B)
	@echo "Cleaning $(NAME) >>>>>>>> ... -=> Done"

.PHONY: all clean fclean re

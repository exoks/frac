# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 15:55:24 by oezzaou           #+#    #+#              #
#    Updated: 2023/02/21 11:55:56 by oezzaou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME := libftprintf.a
SRCDIR := src
OBJDIR := obj
INC = -I libft -I include/
CC := cc
CFLAGS := -Wall -Wextra -Werror
SRC := ft_manage_flags ft_putnbr_base_upx ft_print_char ft_print_str ft_putnbr_base_id ft_printf_utils ft_printf
OBJ := $(addprefix $(OBJDIR)/, $(addsuffix .o, $(SRC)))
SRC := $(addprefix $(SRCDIR)/, $(addsuffix .c, $(SRC)))
LIBFT = libft/

all: $(OBJDIR) $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	@ar -crs $@ $(LIBFT)*.o $(OBJ)
	@echo "Creating >>>>>>>>>> LIBFTPRINTF ... Done"

bonus: clean $(OBJDIR) $(NAME)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJDIR):
	@mkdir -p $@

clean:
	@$(MAKE) -C $(LIBFT) clean
	@rm -rf $(OBJDIR) 

fclean: clean
	@$(MAKE) -C $(LIBFT) fclean
	@rm -rf $(OBJDIR) $(NAME)
	@echo "Cleaning LIBFTPRINTF >>>>>>> ... -=> Done"

re: fclean all
	
.PHONY: test all clean fclean re bonus $(LIBFT)

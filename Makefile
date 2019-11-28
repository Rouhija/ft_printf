# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: srouhe <srouhe@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 16:29:02 by srouhe            #+#    #+#              #
#    Updated: 2019/11/28 18:14:51 by srouhe           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OUT		=	libftprintf.a
FLAGS   =   -Wall -Werror -Wextra
SDIR    =   srcs/
ODIR    =   objs/

CFILES	= 	ft_printf.c \
			parse.c \
			handle_nbr.c \
			utils.c \
			handle_csp.c \
			padding_csp.c \
			padding_nbr.c \
			helpers.c \
			bonus.c \
			ftoa.c \

SRCS =		$(addprefix $(SDIR)/,$(CFILES))
OBJS =		$(addprefix $(ODIR)/,$(CFILES:.c=.o))

all: $(OUT)

$(OUT): $(OBJS)
		@make -C libft
		@cp libft/libft.a ./$(OUT)
		@ar rc $(OUT) $(OBJS)
		@ranlib $(OUT)

$(ODIR)/%.o: $(SDIR)/%.c
		@mkdir -p objs
		@$(CC) $(FLAGS) -I includes/ -I libft/includes/ -o $@ -c $<

clean:
		@/bin/rm -rf $(OBJS)
		@/bin/rm -rf $(ODIR)
		@make clean -C libft

fclean: clean
		@/bin/rm -f $(OUT)
		@make fclean -C libft

re: fclean all

.PHONY: all clean flcean re

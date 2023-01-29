# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amejia <amejia@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/29 20:07:08 by amejia            #+#    #+#              #
#    Updated: 2023/01/29 20:58:47 by amejia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_printf.c ft_pseudolog.c ft_putnbrbase_int.c ft_putnbrbase_long.c \
    libft_utils.c libft_utils2.c tags_iusc_sym.c tags_pxX.c

OBJS = ${SRCS:.c=.o}

FLAGS = -Wall -Werror -Wextra

INCLUDE = ft_printf.h 

all: $(NAME)  

$(NAME): ${OBJS} $(INCLUDE)
	$(CC)  -c $(FLAGS) $(SRCS)   
	ar -crs $(NAME) $(OBJS)  $(INCLUDE) 

$(OBJS): $(SRCS)

clean: 
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all


.PHONY: all clean fclean


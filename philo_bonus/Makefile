CC = gcc

FLAGS = -Wall -Werror -Wextra

RM = rm -rf

AR = ar rcs

MAKE = make
# ------------------------------------------------------------------------------

NAME = 		philo_bonus

SRCS =		srcs/main.c				srcs/ft_error.c		srcs/ft_init_vars.c \
			srcs/ft_atoi.c			srcs/ft_do.c		srcs/ft_lst.c \
			srcs/ft_write.c			srcs/ft_get_time.c 		srcs/ft_check_dead.c \
			srcs/ft_sleep.c			srcs/ft_child.c 		srcs/ft_sem.c

OBJS = ${SRCS:%.c=%.o}

HEAD = inc/philo_bonus.h

LIB = philo_bonus.a

# ------------------------------------------------------------------------------
%.o :		%.c ${HEAD}
			${CC} ${FLAGS} -c -o $@ $<

${NAME}: 	${OBJS} ${HEAD}
			${AR} ${LIB} $?
			${CC} ${LIB} -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS} ${OBJS_B}

fclean:		clean
			${RM} ${NAME} ${LIB} ${LIB_B} ${NAME_B}

re:			fclean all

# ------------------------------------------------------------------------------

.PHONY: re all clean fclean

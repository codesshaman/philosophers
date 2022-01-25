CC = gcc

FLAGS = -Werror -Wall -Wextra

RM = rm -rf

AR = ar rcs

MAKE = make
# ------------------------------------------------------------------------------

NAME = 		philo

SRCS =		philo_srcs/ft_atoi.c \
			philo_srcs/check_dead.c \
			philo_srcs/init_vars.c \
			philo_srcs/init_list.c \
			philo_srcs/mutex_processing.c \
			philo_srcs/philo_sleep.c \
			philo_srcs/main.c
						
					

BONUS =		philo_bonus/main.c				philo_bonus/ft_error.c			philo_bonus/ft_init_vars.c \
			philo_bonus/ft_atoi.c			philo_bonus/ft_do.c				philo_bonus/ft_lst.c \
			philo_bonus/ft_write.c			philo_bonus/ft_get_time.c 		philo_bonus/ft_check_dead.c \
			philo_bonus/ft_sleep.c			philo_bonus/ft_child.c 			philo_bonus/ft_sem.c

OBJS = ${SRCS:%.c=%.o}

BOBJS = ${BONUS:%.c=%.o}

HEADER = philo_srcs/philo.h

BHEADER = philo_bonus/philo_bonus.h

LIB = philo.a

BLIB = philo_bonus.a

# ------------------------------------------------------------------------------
%.o :		%.c ${HEADER}
			${CC} ${FLAGS} -c -o $@ $<

${NAME}: 	${OBJS} ${HEADER}
			${AR} ${LIB} $?
			${CC} ${LIB} -o ${NAME}

bonus:	 	${BOBJS} ${BHEADER}
			${AR} ${LIB} $?
			${CC} ${LIB} -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS} ${BOBJS}

fclean:		clean
			${RM} ${NAME} ${LIB} ${BLIB} ${NAME_B}

re:			fclean all

# ------------------------------------------------------------------------------

.PHONY: re all clean fclean

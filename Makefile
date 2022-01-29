NAME = philo/philo

BONUS_NAME = philo_bonus/philo_bonus

CC = gcc -pthread

FLAGS = -Wall -Wextra -Werror

RM = rm -rf

AR = ar rcs

SRCS		=	philo/actions.c\
			philo/destroy.c\
			philo/init.c\
			philo/main.c\
			philo/processing.c\
			philo/utils.c

BONUS =		philo_bonus/actions.c	\
			philo_bonus/init.c \
			philo_bonus/main.c	\
			philo_bonus/utils.c

OBJS 	= $(SRCS:.c=.o)

BOBJS = ${BONUS:%.c=%.o}

HEADER = philo_src/philo.h

BHEADER = philo_bonus/philo_bonus.h

LIB = philo.a

%.o :		%.c ${HEADER}
			${CC} ${FLAGS} -c -o $@ $<

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

bonus:	 	${BOBJS} ${BHEADER}
			${AR} ${LIB} $?
			${CC} ${LIB} -o ${BONUS_NAME}

all:		${NAME}

clean:
			${RM} ${OBJS} ${BOBJS}

fclean:		clean
			${RM} ${NAME} ${LIB} ${BLIB} ${BONUS_NAME}

re:			fclean all

.PHONY: re all clean fclean

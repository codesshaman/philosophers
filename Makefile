NAME = philo

CC = gcc -pthread

FLAGS = -Wall -Wextra -Werror

RM = rm -rf

AR = ar rcs

SRCS		=	philo_src/actions.c\
			philo_src/destroy.c\
			philo_src/init.c\
			philo_src/main.c\
			philo_src/processing.c\
			philo_src/utils.c

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
			${CC} ${LIB} -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS} ${BOBJS}

fclean:		clean
			${RM} ${NAME} ${LIB} ${BLIB} ${NAME_B}

re:			fclean all

.PHONY: re all clean fclean

NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror
SRC = routine.c Philo_init.c monitor.c parsing_cheack.c \
	parsing_utilise.c routine_help.c
OBJC = ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJC}
	${CC} ${FLAGS} ${OBJC} -o ${NAME}

clean:
	rm -f ${OBJC}

fclean: clean
	rm -f ${NAME}

re: fclean all

# .P all clean fclean re
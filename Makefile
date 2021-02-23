# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schene <schene@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/07 12:35:42 by schene            #+#    #+#              #
#    Updated: 2021/02/23 11:52:38 by schene           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VECTOR_SRCS	= test/test_vector.cpp test/vector_test_string.cpp 
VECTOR_OBJS	= ${VECTOR_SRCS:.cpp=.o}

LIST_SRCS	= test/test_list.cpp
LIST_OBJS	= ${LIST_SRCS:.cpp=.o}

MAP_SRCS	= test/test_map.cpp
MAP_OBJS	= ${MAP_SRCS:.cpp=.o}

STACK_SRCS	= test/test_stack.cpp
STACK_OBJS	= ${STACK_SRCS:.cpp=.o}

QUEUE_SRCS	= test/test_queue.cpp
QUEUE_OBJS	= ${QUEUE_SRCS:.cpp=.o}

SRCS		= ${VECTOR_SRCS} ${LIST_SRCS} ${MAP_SRCS} ${STACK_SRCS} ${QUEUE_SRCS}

OBJS		= ${VECTOR_OBJS} ${LIST_OBJS} ${MAP_OBJS} ${STACK_OBJS} ${QUEUE_OBJS}

RM			= rm -f

NAMES		= vector list map stack queue

CC			= clang++

CFLAGS		= -Wall -Wextra -Werror -std=c++98

all:		${NAMES}

vector:		${VECTOR_OBJS}
			@${CC} ${CFLAGS} -o vector ${VECTOR_OBJS}
			@echo "✅ \033[32mCompilation Done, ./vector created.\033[0m"


list:		${LIST_OBJS}
			@${CC} ${CFLAGS} -o list ${LIST_OBJS}
			@echo "✅ \033[32mCompilation Done, ./list created.\033[0m"


map:		${MAP_OBJS}
			@${CC} ${CFLAGS} -o map ${MAP_OBJS}
			@echo "✅ \033[32mCompilation Done, ./map created.\033[0m"


stack:		${STACK_OBJS}
			@${CC} ${CFLAGS} -o stack ${STACK_OBJS}
			@echo "✅ \033[32mCompilation Done, ./stack created.\033[0m"


queue:		${QUEUE_OBJS}
			@${CC} ${CFLAGS} -o queue ${QUEUE_OBJS}
			@echo "✅ \033[32mCompilation Done, ./queue created.\033[0m"


%.o: %.cpp
			@${CC} ${CFLAGS} -c $< -o $@

clean:		
			@${RM} ${OBJS}
			@echo "✅ \033[32mObjects files deleted.\033[0m"


fclean:		clean
			@${RM} ${NAMES}
			@echo "✅ \033[32mExecutables files deleted.\033[0m"

re:			clean all

.PHONY:		all clean fclean re
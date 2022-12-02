# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/13 15:31:38 by nhwang            #+#    #+#              #
#    Updated: 2022/06/16 16:00:28 by nhwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SERVERNAME = server

CLIENTNAME = client

SERVER = server.c

CLIENT = client.c

BSERVER = server_bonus.c

BCLIENT = client_bonus.c

SERVER_OBJS = $(SERVER:.c=.o)

CLIENT_OBJS = $(CLIENT:.c=.o)

SERVER_OBJS_BONUS = $(BSERVER:.c=.o)

CLIENT_OBJS_BONUS = $(BCLIENT:.c=.o)

OBJS := $(*.o)

HEADER = minitalk.h

ifdef BONUS
	SERVER_OBJECTS = $(SERVER_OBJS_BONUS)
	CLIENT_OBJECTS = $(CLIENT_OBJS_BONUS)
else
	SERVER_OBJECTS = $(SERVER_OBJS)
	CLIENT_OBJECTS = $(CLIENT_OBJS)
endif

all : $(NAME)

bonus :
	$(MAKE) BONUS=1 all

$(SERVERNAME) : $(SERVER_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(CLIENTNAME) : $(CLIENT_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(NAME): $(SERVERNAME) $(CLIENTNAME)

clean :
	$(RM) *.o

fclean : clean
	$(RM) ${OBJS} $(SERVERNAME) ${CLIENTNAME}

re : fclean all

.PHONY : all clean fclean re bonus
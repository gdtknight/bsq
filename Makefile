# Makefile v1.0

CFLAGS		=	-Wall -Wextra -Werror --debug
ARFLAGS		=	rcs
CC			=	gcc
AR			=	ar

NAME		=	bsq

BUILD_DIR	:=	build
BIN_DIR		:=	bin
SRC_DIR		=	srcs
HEADERS		=	includes
OBJS		:=	$(patsubst %.c,%.o, $(wildcard $(SRC_DIR)/*.c))

.PHONY: all clean fclean re $(TARGET) $(OBJS) $(SRCS)
all: $(NAME)

${NAME}: $(OBJS) 
	$(CC) $(CFLAGS) -o $@ $^

$(OBJS):
	$(CC) $(CFLAGS) -o $@ -c $*.c -I$(HEADERS)

clean: 
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

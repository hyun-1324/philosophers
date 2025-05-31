NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
INCLUDE = -Iinclude

SRCS_PATH = ./src
OBJS_PATH = ./obj

SRCS	= $(SRCS_PATH)/manage_resources.c\
		  $(SRCS_PATH)/monitor_philo.c \
		  $(SRCS_PATH)/philo_routine.c \
		  $(SRCS_PATH)/print_state.c \
		  $(SRCS_PATH)/utils.c \
		  $(SRCS_PATH)/main.c \

OBJS = $(SRCS:$(SRCS_PATH)/%.c=$(OBJS_PATH)/%.o)

.SECONDARY: $(OBJS)

all : $(LIBFT) $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_PATH)/%.o : $(SRCS_PATH)/%.c
	@mkdir -p $(OBJS_PATH)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean :
	$(RM) -r $(OBJS_PATH)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re

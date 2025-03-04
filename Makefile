# **************************************************************************** #
#                                   Makefile                                   #
# **************************************************************************** #

NAME        = Philosophers
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g -I./src/includes
LDFLAGS     = -lreadline

# Directorios
LIBFT_DIR   = src/includes/libft
PARSEO_DIR  = src/parseo
FREE_DIR    = src/free
UTILS_DIR   = src/utils
ACCTIONS_DIR = src/acctions

PARSEO_SRCS = \
		$(PARSEO_DIR)/ft_verify_nbr.c \
		$(PARSEO_DIR)/ft_init_const.c \

FREE_SRCS = \

UTILS_SRCS = \
		$(UTILS_DIR)/prints.c \
		$(UTILS_DIR)/ft_mutex_destroyer.c \
		$(UTILS_DIR)/get_time_s.c \
		$(UTILS_DIR)/ft_check_dead_time.c

ACCTIONS_SRCS = \
		$(ACCTIONS_DIR)/ft_acctions.c

MAIN_SRCS = main.c

# Unir todas las fuentes
SRCS = \
	$(MAIN_SRCS) \
	$(PARSEO_SRCS) \
	$(FREE_SRCS) \
	$(UTILS_SRCS) \
	$(ACCTIONS_SRCS)

# Create object directories
OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Create necessary directories
DIRS = $(OBJ_DIR) \
       $(OBJ_DIR)/$(PARSEO_DIR) \
       $(OBJ_DIR)/$(FREE_DIR) \
       $(OBJ_DIR)/$(UTILS_DIR) \
	   $(OBJ_DIR)/$(ACCTIONS_DIR)

# Regla principal para compilar
all: $(DIRS) $(LIBFT_DIR)/libft.a $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DIRS):
	mkdir -p $@

$(LIBFT_DIR)/libft.a:
	@if [ ! -f "$@" ]; then \
		make -C $(LIBFT_DIR); \
	fi

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

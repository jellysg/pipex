OBJS_PX = $(SRCS_PX:.c=.o)
SRCS_PX = $(addprefix $(SRC_DIR), \
	main.c utils.c \
)

SRC_DIR	= ./sources/
INC_DIR	= ./includes/
CC = cc
MF = Makefile

NAME = pipex
LIBFT_PATH = ./libft/libft.a
PS_HEADER_FILE = $(INC_DIR)/pipex.h
CFLAGS = -g -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(MF) $(LIBFT_PATH) $(OBJS_PX)
	@$(CC) $(CFLAGS) $(OBJS_PX) $(LIBFT_PATH) -o $(NAME)
	@echo  ""
	@printf "\033[1;32m%s\033[0m\n" "[pipex] Compiled successfully."
	@cat pipex_splash.txt

%.o: %.c $(PS_HEADER_FILE) $(MF)
	@printf "\033[1;32m|\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

$(LIBFT_PATH): .libft

.libft:
	@make -s -C ./libft

clean:
	@make -s clean -C ./libft
	@rm -f $(OBJS_PX)
	@printf "\033[1;31m%s\033[0m\n" "[pipex] Object files cleaned."

fclean: clean
	@make -s fclean -C ./libft
	@rm -f $(NAME)
	@printf "\033[1;31m%s\033[0m\n" "[pipex] Cleaned successfully."

re: fclean all

.PHONY: all clean fclean re
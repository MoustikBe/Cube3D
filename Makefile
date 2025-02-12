NAME        = cub3d
CC          = cc
CFLAGS      = #-Wall -Werror -Wextra 
LDFLAGS     = -g3 #-fsanitize=address
RM          = rm -rf

SOURCES     = main.c \
			  src/parsing/parsing_main.c

OBJECTS     = $(SOURCES:%.c=%.o)

%.o: %.c
	@printf "\033[0;30mGenerating minishell objects... %-33.33s\r" $@
	@$ $(CC) $(CFLAGS) -c -g3 $< -o $@

$(NAME): $(OBJECTS)
	@echo "\n"
	@echo "\033[0;32mCompiling minishell..."
	@$(CC) $(OBJECTS) $(LDFLAGS) -L src/libs/libft -lft -o $(NAME) 
	@echo "\n\033[0;32mDone !"

clean:
	@ $(RM) $(OBJECTS)
	@ $(RM)
	@echo "\033[33;36mClean ✅"

fclean: clean
	@echo "\n\033[33;36mFclean ✅\n"
	@ $(RM) $(NAME)

all: $(NAME)

re: fclean all

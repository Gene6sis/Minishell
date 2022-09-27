SRCDIR = src/
OBJDIR = bin/
INCDIR = include/ 
FTPATH = libft/

FTINC = $(FTPATH)include/
LIBFT = $(FTPATH)libft.a
######################################################################
SRCS =	main.c							\
		bintree/bintree.c				\
		bintree/utils_bintree.c			\
		bintree/utils_bintree2.c		\
		bintree/add_to_stacks.c			\
		bintree/exec_tree.c				\
		bintree/expand.c				\
		bintree/expand2.c				\
		bintree/expand3.c				\
		bintree/expand4.c				\
		bintree/expand_wild_args.c		\
		bintree/expand_wild_args2.c		\
		bintree/verif_syntax.c			\
		bintree/wildcard_matching.c		\
		bintree/sort_lst.c				\
		\
		builtins/cd/cd.c				\
		builtins/echo/echo.c			\
		builtins/env/env.c				\
		builtins/exit/exit.c			\
		builtins/export/export.c		\
		builtins/export/export_check.c	\
		builtins/pwd/pwd.c				\
		builtins/unset/unset.c			\
		\
		execution/execution.c			\
		execution/pipex_utils.c			\
		execution/pipex.c				\
		execution/pipexchild.c			\
		execution/pipexfather.c			\
		execution/readline.c			\
		execution/pipex_child_utils.c	\
		\
		parsing/ft_shlvl.c				\
		parsing/unit_word.c				\
		parsing/unit_tokens.c			\
		parsing/unit_first_tokens.c		\
		parsing/ft_pre_exec.c			\
		parsing/ft_pre_exec_bis.c		\
		parsing/lexer.c					\
		parsing/lexer_utils.c			\
		parsing/parsing.c				\
		parsing/split_words.c			\
		\
		redirection/here_docs.c			\
		\
		trash/trash.c					\
		\
		utils/utils.c					\
		utils/delete_quotes.c			\
		utils/utils_1.c					\
		utils/utils_builtin.c			\
		utils/utils_env.c				\
		utils/utils_env_1.c				\
		utils/utils_env_2.c				\
		utils/utils_env_3.c				\
		utils/utils_execution.c			\
		utils/utils_execution_1.c		\
		utils/utils_execution_2.c		\
		utils/utils_parsing.c			\
		utils/utils_parsing_1.c			\
		utils/utils_redirection.c		\
		utils/utils_redirection_1.c		\
		\
		signals/signals.c

OBJS = $(addprefix $(OBJDIR),$(SRCS:.c=.o))
DEPENDS = $(OBJS:.o=.d)
######################################################################
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror -MMD -MP
LINK = -lft -lreadline 
INCPATH = -I$(INCDIR) -I$(FTINC)
LIBPATH = -L$(FTPATH)
NAME = minishell
######################################################################
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBPATH) $(LINK) -o $(NAME)

-include $(DEPENDS)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) -c $(CFLAGS) $(INCPATH) $< -o $@

$(LIBFT):
	make -C $(FTPATH)

clean:
	rm -rf $(OBJS)
	rm -rf $(DEPENDS)
	@$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C libft fclean

re: fclean $(NAME)

.PHONY: all libft clean fclean re

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 04:30:56 by nthimoni          #+#    #+#             */
/*   Updated: 2022/08/21 20:52:50 by adben-mc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "parser.h"
# include "color.h"
# include <stdio.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# define ERROR -1

extern int	g_sig;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}	t_env;

typedef struct s_trash
{
	void				*to_free;
	struct s_trash		*next;
}		t_trash;

typedef struct s_data
{
	t_env			*env_lst;
	char			**env_str;
	t_list			*command;
	t_trash			*trash;
	unsigned char	last_exit_code;
}		t_data;

typedef struct s_strpair
{
	char	*s;
	char	*w;
}	t_strpair;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	char			**str_split;
	char			*name;
	char			*content;
}	t_token;

typedef enum e_node_type
{
	NONE = 0,
	OPERATOR,
	CMD,
}	t_node_type;

typedef struct s_node
{
	struct s_node	*left;
	struct s_node	*right;
	t_node_type		type;
	t_list			*tokens;
}	t_node;

/*	|||||||||||||| 	 UTILS		 |||||||||||	*/
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strslen(char **strs);
char	*ft_strjoin3(const char *s1, const char *s2, const char *s3);
char	*ft_strncpy(char *str, size_t size);
char	**ft_append_to_tab(char **tab, char *str, t_data *data);
void	ft_print_char_star_star(char **str);
void	ft_printtlist(t_list *lst);
int		ft_nb_partition(t_data *data);
t_token	*get_n_command(t_data *data, int n);
void	free_array(char **tab);
void	ft_lstdeloneelmt(t_list **list, t_list *to_delete);
char	*ft_strjoinbis(int size, char **strs, char *sep);
char	**ft_split_words(char const *s, t_data *data);
void	rp_wild(char *str);
void	rp_back_wild(char *str);
char	*delete_quotes(char *str);

/*	|||||||||||||| 	 ULTILS ENV	 |||||||||||	*/
char	*get_env_name_from_string(char *str);
t_env	*envlst_last(t_env *lst);
t_env	*envlst_new(char *var_name, char *var_value);
void	envlst_add_back(t_env **env, t_env *new);
void	ft_envdeloneelmt(t_env **list, t_env *to_delete);
int		update_env_strs(t_data *data, char *name, char *value);

/*	|||||||||||||| 	 ENV		 |||||||||||	*/
char	*get_env_val(t_env *env, const char *var_name);
t_env	*env_to_lst(char **env, t_data *data);
void	print_env(t_env *env);
t_env	*get_env(t_env *env, const char *name);
int		update_env_lst(t_data *data, char *name, char *value);
int		update_env_str(t_data *data, t_env *env);

/*	|||||||||||||| 	 PARSING	 |||||||||||	*/
int		ft_parsing(t_data *data, char **env);
int		ft_parse_input(t_data *data, char *input);
t_list	*get_tokens(char *line, t_data *data);
int		get_token_len(t_token_type type, char *str);
int		add_token(t_list **head, char *line, t_token_type type, t_data *data);
int		have_multiple_str_in_redirection(t_data *data);
int		nb_word_in_partition(t_list *lst);
int		nb_words_in_partition(t_list *lst);
t_list	*next_word(t_list *lst);
void	remove_other_words(t_list *lst, t_data *data);
int		ft_is_ws(char c);
int		ft_pre_exec_bis(t_data *data);
int		ft_pre_exec(t_data *data);
int		unit_tokens(t_list **lst, t_data *data);
int		unit_first_tokens(t_list **lst, t_data *data);
int		is_only_space(char *str);
int		unit_tokens(t_list **lst, t_data *data);
char	**unified_token(char *s1, char *s2, char **strs, t_data *data);
int		unit_word(t_data *data);
int		ft_ft(char ***ft, t_data *data, int size);
int		ft_shlvl(t_data *data);

/*	|||||||||||||| 	 TRASH		 |||||||||||	*/
int		ft_addtotrash(t_data *data, void *addr);
void	free_trash(t_data *data);

/*	|||||||||||||| 	 READLINE	 |||||||||||	*/
void	ft_readlinehistory(t_data *data, char *input);

/*	|||||||||||||| 	 EXECUTION	 |||||||||||	*/
int		exec(t_data *data);
int		ft_error(char *str);
int		ft_error_pipe(int prevfd);
int		ft_error_fork(int prevfd, int pipefd[2]);
char	*get_absolute_path(char **cmd, t_env *envp, t_data *data);
int		pid_child(t_data *data, int prevfd, int pipefd[2], t_list *lst);
int		pid_father(t_data *data, int *prevfd, int pipefd[2], t_list *lst);
int		getpos_partition(t_data *data, t_list *cmd);
int		ft_pre_exec(t_data *data);
t_list	*find_cmd(t_list *lst);
int		bultin_simple_command(t_data *data, t_list *lst);
int		simple_exec(t_data *data, t_list *lst);
int		exec_command(t_data *data, t_list *lst, int status);
void	not_found(char *str, int len);
int		ft_wait(int pid);
int		open_fd(t_list *lst, int *fd);

/*	|||||||||||||| 	REDIRECTION	 |||||||||||	*/
int		have_command(t_list *lst);
int		have_redirection_in(t_list *lst);
int		have_redirection_out(t_list *lst);
int		opening_fd(t_token *token);
int		fd_exit(t_list *lst);
int		fd_entry(t_list *lst);
t_list	*next_partition(t_list *lst);
int		is_partition(t_list *lst);
void	print_partition(t_list *lst); //can be del
int		check_redirection(t_list *lst);

/*	|||||||||||||| 	HERE_DOCS	 |||||||||||	*/
int		exec_heredocs(t_data *data);
int		have_heredocs(t_list *lst);

/*	|||||||||||||| 	BUILTINS	 |||||||||||	*/
int		builtins(t_token *token, t_data *data, int parent);
int		builtin_echo(t_data *data, t_token *token);
int		builtin_pwd(t_data *data, t_token *token);
int		builtin_env(t_data *data, t_token *token);
int		builtin_cd(t_data *data, t_token *token);
int		builtin_export(t_data *data, t_token *token, int parent);
int		export_add(t_data *data, char *name_tmp, char *value_tmp);
int		check_export(char *name, char *value);
int		builtin_unset(t_data *data, t_token *token);
int		check_export_return(t_token *token);
int		builtin_exit(t_data *data, t_token *token, int parent);
int		wildcard_matching(char *wild, char *string);
char	**expand_wild_args(char **args, t_data *data);
char	**expand(char **args, t_data *data);
char	*expand1(char *str, t_data *data);
char	*expand2(char *str, t_data *data);

/*	|||||||||||||| 	BINTREE		 |||||||||||	*/
t_node	*new_node(t_node_type type, t_node *left, t_node *right);
t_node	*build_tree(t_list **head, struct s_data *data);
int		exec_tree(struct s_data *data, t_node *tree);
int		verif_syntax(t_list *token, int should_print);
int		var_len(char *str, t_data *data);
int		process_dollar(char *str, int *i, t_data *data);
void	expand_len_quote(char *word, t_data *data, int *i, int *len);
char	**convert_lst_to_2d_char(t_list *lst, t_data *data);
t_list	*new_lst_str(char *str, t_data *data);
int		is_in(char *str, char a);
int		check_flag(int flag, char *str, t_data *data, t_list **lst);
int		syntax_error(t_list *token, int should_print);
int		expand_len(char *word, t_data *data);
void	add_exit_code(char *ret);
void	cpy_var(char *word, int *s, char *ret, t_data *data);
void	expand_quote(char *word, char *ret, int *s, t_data *data);
int		add_all(t_list **head, char **sp, t_data *data);
void	delete_parenthesis(t_list **operators);
void	link_node(t_list *penult, t_list **words);
void	process_double_op(t_list **operators, t_list **words);
int		verif_parenth(t_list *lst);
void	sort_lst(t_list *to_sort, t_list **lst);

/*	|||||||||||||| 	ADD_TO_STACKS	|||||||||||	*/
int		add_to_stacks(t_list **op, t_list **words, t_list *tmp, t_data *data);
int		is_op_or_parenth(t_token *token);
void	process_tree(t_list **operators, t_list **words);

/*	|||||||||||||| 	SIGNALS		 |||||||||||	*/
void	signal_set(char *stage);
void	child_c(int sig);
void	print_signal(int signal);

#endif

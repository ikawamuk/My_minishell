# ----------------------------------------------------------------------------- #
#                                   VARIABLES                                   #
# ----------------------------------------------------------------------------- #

# --- EXECUTABLE NAMES ---
NAME            = minishell

# --- COMPILER & FLAGS ---
CC              = cc
CFLAGS          = -Wall -Wextra -Werror $(addprefix -I,$(INCDIRS)) -I$(LIBFTDIR)/include
AR              = ar
ARFLAGS         = rcs

# --- COMMANDS ---
RM              = rm -f
RMDIR           = rm -rf

# --- DIRECTORIES ---
INCDIRS          = include\
                   include/exec_cmd\
				   include/parse_cmd

LIBFTDIR        = ./libft
LIBFT			= libft.a

SRCDIR_BASE     = ./src
SRCDIR          = $(SRCDIR_BASE)

OBJDIR_BASE     = ./obj
OBJDIR          = $(OBJDIR_BASE)

# --- LIBRARIES ---
LIBFT           = $(LIBFTDIR)/libft.a

# --- SOURCES ---
SRC_FILES       =	append_pid.c \
					delete_env_var.c \
					env_utils.c \
					exec_cd.c \
					exec_echo.c \
					exec_env.c \
					exec_exit.c \
					exec_export.c \
					exec_pwd.c \
					exec_unset.c \
					update_env_var.c \
					child_process.c \
					convert_fd_to_stdio.c \
					create_child_process.c \
					create_clean_envp.c \
					create_pipe.c \
					do_redirect.c \
					exec_built_in.c \
					exec_command.c \
					exec_external_command.c \
					exec_multiple_command.c \
					exec_simple_built_in.c \
					exec_simple_command.c \
					exec_util.c \
					find_exec_file.c \
					get_paths_arr.c \
					init_info.c \
					is_ambiguous_redirect.c \
					redirect_expand.c \
					set_redirection.c \
					wait_child_process.c \
					main.c \
					minishell.c \
					create_argv.c \
					create_command_list.c \
					create_redir_list.c \
					gather_heredoc.c \
					write_herdoc.c \
					make_command.c \
					do_heredoc.c \
					get_element_node.c \
					get_token_list_node.c \
					lex.c \
					lex_word_token.c \
					parse.c \
					validated_lex.c \
					parse_command.c \
					bool_char_util.c \
					bool_util.c \
					element_free_util.c \
					expand_util.c \
					list_util.c \
					dequote_token_list.c \
					expand_token_list.c \
					expand_var.c \
					get_var_value.c \
					quote_token_list.c \
					shell_expand.c \
					split_string.c \
					split_token_list.c \
					read_command.c \
					reader_loop.c \
					set_signal_handler.c \
					count_str_arr.c \
					free_util.c \
					ft_getenv.c \
					is_space.c \
					wait_all_child_process.c \
					check_redir_file.c \
					heredoc_loop.c \
					expand_ps_loop.c \
					minishell_readline.c \
					get_format_value.c \
					get_trimed_pwd.c \
					get_trimed_host_name.c \
					ft_strcpy.c \
					ft_strndup.c \

SRCS            = $(foreach file,$(SRC_FILES),$(shell find $(SRCDIR) -name $(file)))


# --- OBJECTS ---
OBJS            = $(patsubst $(SRCDIR_BASE)/%.c, $(OBJDIR_BASE)/%.o, $(SRCS))

# --- DEBUGGING ---
VALGRIND        = valgrind
VALGRIND_FLAGS  = --leak-check=full --track-origins=yes --show-leak-kinds=all
DFLAGS          = -g -O0
ASAN_FLAGS      = -g -fsanitize=address

# ----------------------------------------------------------------------------- #
#                                     RULES                                     #
# ----------------------------------------------------------------------------- #

# --- MAIN TARGETS ---
all:            $(NAME)

# --- EXECUTABLE BUILDING ---
$(NAME):        $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline -L$(LIBFTDIR) -lft
	@echo "\n\033[1;32m'$(NAME)' has been created!\033[0m"

# --- LIBRARY BUILDING ---
$(LIBFT):
	@make -sC $(LIBFTDIR)

# --- OBJECT FILE COMPILATION ---
$(OBJDIR_BASE)/%.o: $(SRCDIR_BASE)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# --- CLEANUP RULES ---
clean:
	@$(RMDIR) $(OBJDIR_BASE)
	@make clean -C $(LIBFTDIR)
	@echo "\033[1;33mObject files cleaned.\033[0m"

fclean:         clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFTDIR)
	@echo "\033[1;31mAll cleaned.\033[0m"

re:             fclean all

# --- DEBUGGING & TESTING ---
debug: fclean
	@$(MAKE) CFLAGS="$(CFLAGS) $(DFLAGS)" $(NAME)
	@echo "\n\033[1;35mLaunching LLDB for '$(NAME)'...\033[0m"
	@lldb $(NAME)

asan: fclean
	@$(MAKE) CFLAGS="$(CFLAGS) $(ASAN_FLAGS)" LDFLAGS="$(ASAN_FLAGS)" $(NAME)
	@echo "\n\033[1;35mCompiled with AddressSanitizer. Run './$(NAME)' to test.\033[0m"

valgrind: fclean
	@$(MAKE) CFLAGS="$(CFLAGS) $(DFLAGS)" $(NAME)
	@echo "\n\033[1;36mRunning Valgrind for '$(NAME)'...\033[0m"
	$(VALGRIND) $(VALGRIND_FLAGS) ./$(NAME)

test: all
	@$(MAKE) all
	@echo "\033[1;36mRunning tests with Valgrind...\033[0m"
	@$(CC) $(CFLAGS) test.c $(NAME) -o test_runner
	$(VALGRIND) $(VALGRIND_FLAGS) ./test_runner
	@$(RM) test_runner

# --- PHONY TARGETS ---
.PHONY:         all clean fclean re test debug asan valgrind

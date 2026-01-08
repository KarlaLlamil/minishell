NAME :=	minishell

# --- Directories ---

ENVCTL_DIR := envctl
BUILTINS_DIR := builtins
EXECUTION_DIR := execution
LEXER_DIR := lexer
PARSER_DIR := parser
EXPANSION_DIR := expansion
HERE_DOC_DIR := here_doc
SIGNALS_DIR := signaling
UTILS_DIR := utils
LIBFT_DIR := libft

LIBFT := $(LIBFT_DIR)/libft.a

DEPS :=	$(LIBFT_DIR)/libft.h \
		$(BUILTINS_DIR)/builtins.h \
		$(ENVCTL_DIR)/envctl.h $(ENVCTL_DIR)/hash.h \
		$(EXECUTION_DIR)/execution.h \
		$(SIGNALS_DIR)/signaling.h \
		$(PARSER_DIR)/ast.h $(PARSER_DIR)/utilities_parser.h \
		$(LEXER_DIR)/tokens.h $(LEXER_DIR)/lexer_state.h \
		$(HERE_DOC_DIR)/here_doc.h \
		$(EXPANSION_DIR)/expansion.h \
		$(UTILS_DIR)/utils.h

SRCS_MAIN := main.c
		
SRCS_BUILTINS := $(BUILTINS_DIR)/cd.c $(BUILTINS_DIR)/echo.c $(BUILTINS_DIR)/env.c \
				$(BUILTINS_DIR)/exec_builtin.c $(BUILTINS_DIR)/exit.c $(BUILTINS_DIR)/export.c \
				$(BUILTINS_DIR)/meta_export.c $(BUILTINS_DIR)/pwd.c $(BUILTINS_DIR)/unset.c $(BUILTINS_DIR)/which_builtin.c

SRCS_ENVCTL := $(ENVCTL_DIR)/clear_env.c $(ENVCTL_DIR)/clear_tmp_vars.c \
			$(ENVCTL_DIR)/export_env.c $(ENVCTL_DIR)/hash.c $(ENVCTL_DIR)/init_env.c \
			$(ENVCTL_DIR)/lock_tmp_vars.c $(ENVCTL_DIR)/lookup_env_var.c \
			$(ENVCTL_DIR)/set_env_var.c $(ENVCTL_DIR)/set_exit_status_var.c $(ENVCTL_DIR)/set_tmp_var.c \
			$(ENVCTL_DIR)/store_ast.c $(ENVCTL_DIR)/unset_env_var.c
		
SRCS_LEXER := $(LEXER_DIR)/tokens.c $(LEXER_DIR)/make_tokens.c $(LEXER_DIR)/lexer_handle_states.c \
			$(LEXER_DIR)/lexer_handle_operators.c

SRCS_PARSER	:= $(PARSER_DIR)/ast.c $(PARSER_DIR)/parser_tree_generator.c $(PARSER_DIR)/parse_simple_cmd.c \
			$(PARSER_DIR)/redirections.c $(PARSER_DIR)/assignments.c $(PARSER_DIR)/ast_delete_node.c \

SRCS_HEREDOC := $(HERE_DOC_DIR)/here_doc.c $(HERE_DOC_DIR)/heredoc_make_tmpfile.c \
			$(HERE_DOC_DIR)/heredoc_reading.c

SRCS_EXPANSION := $(EXPANSION_DIR)/expand_substitute_var.c $(EXPANSION_DIR)/expansion_heredoc.c \
			$(EXPANSION_DIR)/expansion_ifs.c $(EXPANSION_DIR)/expansion_quotes.c $(EXPANSION_DIR)/expansion.c

SRCS_EXECUTION :=	$(EXECUTION_DIR)/do_pipe.c $(EXECUTION_DIR)/exec_cmd.c $(EXECUTION_DIR)/find_path.c \
					$(EXECUTION_DIR)/set_redirections.c $(EXECUTION_DIR)/tree_interpreter.c

SRCS_SIGNALS := $(SIGNALS_DIR)/signal_state.c $(SIGNALS_DIR)/prompt_signals.c \
				$(SIGNALS_DIR)/heredoc_signals.c $(SIGNALS_DIR)/write_to_tty.c

SRCS_UTILS := $(UTILS_DIR)/free_arr.c $(UTILS_DIR)/sep_join.c $(UTILS_DIR)/strict_split.c

SRCS_MINISHELL := $(SRCS_MAIN) $(SRCS_BUILTINS) $(SRCS_ENVCTL) $(SRCS_LEXER) \
			$(SRCS_PARSER) $(SRCS_HEREDOC) $(SRCS_EXPANSION) $(SRCS_EXECUTION) $(SRCS_SIGNALS) \
			$(SRCS_UTILS)

OBJS_DIR :=	./objs
OBJS :=		$(SRCS_MINISHELL:%.c=$(OBJS_DIR)/%.o)

CC = cc
CWARN = -Wall -Wextra -Werror
CINCLUDES =	-I. \
			-I $(LIBFT_DIR) \
			-I $(PARSER_DIR) \
			-I $(LEXER_DIR) \
			-I $(HERE_DOC_DIR) \
			-I $(EXPANSION_DIR) \
			-I $(ENVCTL_DIR) \
			-I $(BUILTINS_DIR) \
			-I $(EXECUTION_DIR) \
			-I $(UTILS_DIR) \
			-I $(SIGNALS_DIR)

CFLAGS = $(CWARN) $(CINCLUDES)
CLIBS = -L$(LIBFT_DIR) -lft -lreadline

all: $(NAME)

bonus: all

$(NAME): $(OBJS) $(DEPS) $(LIBFT)
	@echo Compiling: $@
	@$(CC) $(CFLAGS) $(OBJS) $(CLIBS) -o $(NAME)

$(OBJS): $(OBJS_DIR)/%.o: %.c $(DEPS) | $(OBJS_DIR)
	@echo Compiling: $@
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@ echo MAKE: libft
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJS_DIR):
	@echo Creating objs dirs
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/builtins/
	@mkdir -p $(OBJS_DIR)/envctl/
	@mkdir -p $(OBJS_DIR)/here_doc/
	@mkdir -p $(OBJS_DIR)/expansion/
	@mkdir -p $(OBJS_DIR)/lexer/
	@mkdir -p $(OBJS_DIR)/parser/
	@mkdir -p $(OBJS_DIR)/execution/
	@mkdir -p $(OBJS_DIR)/signaling/
	@mkdir -p $(OBJS_DIR)/utils/

clean:
	@ echo CLEAN
	@rm -f $(OBJS)
	@rm -df $(OBJS_DIR)/builtins/
	@rm -df $(OBJS_DIR)/envctl/
	@rm -df $(OBJS_DIR)/expansion/
	@rm -df $(OBJS_DIR)/lexer/
	@rm -df $(OBJS_DIR)/parser/
	@rm -df $(OBJS_DIR)/here_doc/
	@rm -df $(OBJS_DIR)/execution/
	@rm -df $(OBJS_DIR)/signaling/
	@rm -df $(OBJS_DIR)/utils/
	@rm -df $(OBJS_DIR)

fclean: clean
	@ echo FCLEAN
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
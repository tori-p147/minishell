NAME = minishell

SRC_DIR = src
INC_DIR = includes
BLD_DIR = obj
LIBS_DIR = libs
LIBFT_DIR = $(LIBS_DIR)/libft
LIBFT_A = $(LIBFT_DIR)/libft.a
LIBS = $(LIBFT_A)
INC_LIBS_DIR = $(LIBFT_DIR)/$(INC_DIR)

CC        = cc
CFLAGS    = -Wall -Wextra -Werror
LDFLAGS = -lreadline
COPY = cp
RM = rm -rf
INCLUDES  = -I$(INC_DIR) -I$(INC_LIBS_DIR)

SRC_FILES = main.c \
			signal_handler.c \
			tokenizer.c \
			tokenizer_utils.c \
			expander.c \
			cmd_parser.c \
			cmd_parser_utils.c \
			executor.c \
			executor_service.c \
			executor_external.c \
			executor_path_utils.c \
			free_utils.c \
			validation.c \
			error.c \
			env_utils.c \
			common_utils.c \
			pipeline_service.c 
		
SOURCES = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJS = $(patsubst $(SRC_DIR)/%.c, $(BLD_DIR)/%.o,$(SOURCES))

all: $(NAME)

$(BLD_DIR)/%.o: $(SRC_DIR)/%.c | $(BLD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#make libft.a
$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(BLD_DIR):
	mkdir -p $(BLD_DIR)

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(OBJS) $(LIBS) $(INCLUDES) $(LDFLAGS) -o $(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) $(BLD_DIR)

fclean: 
	$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(BLD_DIR) $(NAME)

re: fclean all

.PHONY: all clean fclean re
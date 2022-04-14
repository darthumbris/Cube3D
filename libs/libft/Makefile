NAME = libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

SRC = ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_intlen.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strrev.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_memalloc.c \
		ft_arrlen.c \
		ft_hextoint.c \
		ft_swap.c \
		ft_arrjoin.c \
		ft_strcmp.c \
		./gnl/get_next_line.c \
		./gnl/get_next_line_utils.c

BONUS = ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c


OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(BONUS:.c=.o)

GREEN   = \x1b[32m
LGREEN = \x1b[92m
RESET = \033[0m

.c.o:
	@printf "\rCompiling  $(notdir $<)"
	@${CC} ${FLAGS} -g -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): ${OBJ}
	@${AR} ${NAME} ${OBJ}
	@printf "\nDone!\n"

bonus:	${OBJ} ${OBJ_BONUS}
	@${AR} ${NAME} ${OBJ} ${OBJ_BONUS}

clean:
	@${RM} ${OBJ} ${OBJ_BONUS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all, clean, fclean, re, bonus

NAME =		Cub3D

SRCS =		srcs/main.c \
			srcs/init1.c \
			srcs/init2.c \
			srcs/parsing.c \
			srcs/map.c \
			srcs/checks.c \
			srcs/draw.c \
			srcs/raycasting.c \
			srcs/sprites.c \
			srcs/controller.c \
			srcs/movements.c \
			srcs/utils_strings.c \
			srcs/utils_pixels.c \
			srcs/utils_bmp.c \
			srcs/memory.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c

BONUS =		bonus/main.c \
			bonus/init1.c \
			bonus/init2.c \
			bonus/parsing.c \
			bonus/map.c \
			bonus/checks.c \
			bonus/game.c \
			bonus/draw.c \
			bonus/raycasting.c \
			bonus/display.c \
			bonus/sprites.c \
			bonus/controller.c \
			bonus/movements.c \
			bonus/utils_strings.c \
			bonus/utils_pixels.c \
			bonus/utils_bmp.c \
			bonus/memory.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c

FLAGS =		-Wall -Werror -Wextra

INC =		/usr/local/include

LIB =		/usr/local/lib

GFX_FLAGS =	-framework OpenGL -framework AppKit

LIB_FLAGS =	-lX11 -lXext -lm -lbsd -lmlx

all: 		$(NAME)

$(NAME):
			clang $(FLAGS) -I $(INC) -g -L $(LIB) $(SRCS) -o $(NAME) $(LIB_FLAGS)

clean:
			/bin/rm -rf $(SRCS:.c=.o) $(BONUS:.c=.o)

fclean:		clean
			/bin/rm -f $(NAME)

re: 		fclean all

bonus:
			clang $(FLAGS) -I $(INC) -g -L $(LIB) $(BONUS) -o $(NAME)_bonus $(LIB_FLAGS)

.PHONY:		all clean fclean re bonus

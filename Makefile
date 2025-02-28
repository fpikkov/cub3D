# --------		COLORS		--------
RED = \033[1;31m
GREEN = \033[1;32m
CYAN = \033[1;36m
YELLOW = \033[1;33m
CLEAR = \033[0m

# --------	MAKE VARIABLES	--------
CC = cc
CFLAGS = -Wall -Wextra -Werror
DBG_FLAGS = -fdiagnostics-color=always -g
INC_FLAGS = -I$(INCLUDE_DIR) -I$(LFT_DIR)/$(INCLUDE_DIR) -I$(MLX_INCLUDE)
LIB_FLAGS = -L$(LFT_DIR) -l$(LFT) -L$(MLX_BUILD) -l$(LMLX)
MLX_FLAGS = -ldl -lglfw -pthread -lm

MLX_URL = https://github.com/codam-coding-college/MLX42.git

INCLUDE_DIR = ./include
MLX_INCLUDE = $(MLX_DIR)/$(INCLUDE_DIR)/MLX42

BUILD_DIR = ./build
SRC_DIR = ./src
OBJ_DIR = ./obj
LIB_DIR = ./lib
MLX_DIR = $(LIB_DIR)/mlx
LFT_DIR = $(LIB_DIR)/libft

NAME = cub3d
DBG_NAME = debug

LFT = ft
LMLX = mlx42

MLX_BUILD = ${MLX_DIR}/${BUILD_DIR}
BUILD = ${BUILD_DIR}/${NAME}
DBG_BUILD = ${BUILD_DIR}/${DBG_NAME}

# Paths to source files, add additinal dirs here
VPATH = ${SRC_DIR}/main/ \

SRCS =	main.c \

OBJS = ${SRCS:%.c=${OBJ_DIR}/%.o}

# --------	MAKE TARGETS	--------
all: lftbuild ${MLX_BUILD} | ${BUILD}

${BUILD}: ${OBJS}
	@echo "${GREEN}Generating build...${CLEAR}"
	@mkdir -p ${BUILD_DIR}
	@make -C ${LFT_DIR}
	@${CC} ${CFLAGS} -o $@ $^ ${LIB_FLAGS} ${MLX_FLAGS}
	@echo "${GREEN}Executable ${YELLOW}${NAME}${GREEN} was created in ${YELLOW}"${BUILD_DIR}"${CLEAR}"

${OBJ_DIR}/%.o : %.c
	@echo "${CYAN}Generating object files...${CLEAR}"
	@mkdir -p ${OBJ_DIR}
	@$(CC) $(CFLAGS) -c $< -o $@ ${INC_FLAGS}

${MLX_BUILD}:
	@if [ ! -d ${MLX_DIR} ]; then \
		@echo "${CYAN}Cloning mlx42 repository...${CLEAR}"; \
		@git clone ${MLX_URL} ${MLX_DIR}; \
	fi
	@echo "${CYAN}Building mlx42 library...${CLEAR}"
	@cmake -S ${MLX_DIR} -B ${MLX_BUILD}
	@make -C ${MLX_BUILD}

lftbuild:
	@make --no-print-directory -C ${LFT_DIR}

debug: CFLAGS = ${DBG_FLAGS}
debug: lftbuild ${MLX_BUILD} | ${DBG_BUILD}

${DBG_BUILD}: ${OBJS}
	@echo "${GREEN}Generating debug build...${CLEAR}"
	@mkdir -p ${BUILD_DIR}
	@make -C ${LFT_DIR}
	@$(CC) $(DBG_FLAGS) -o $@ $^ $(LIB_FLAGS) $(MLX_FLAGS)
	@echo "${GREEN}Executable ${YELLOW}${DBG_NAME}${GREEN} was created in ${YELLOW}"${BUILD_DIR}"${CLEAR}"

clean:
	@echo "${RED}Cleaning object files...${CLEAR}"
	@make clean --no-print-directory -C ${LFT_DIR}
	@rm -rf ${OBJ_DIR}

fclean: clean
	@echo "${RED}Fully cleaning project...${CLEAR}"
	@rm -rf ${BUILD_DIR}
	@if [ -d ${MLX_BUILD} ]; then \
		rm -rf ${MLX_BUILD}; \
	fi
	@make fclean --no-print-directory -C ${LFT_DIR}

mlxbuild: ${MLX_BUILD}

mlxclean: fclean
	@echo "${RED}Removing MLX repository...${CLEAR}"
	@rm -rf ${MLX_DIR}

re: fclean all

.PHONY: all re clean fclean mlxbuild mlxclean lftbuild debug

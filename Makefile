# --------		COLORS		--------
RED = \033[1;31m
GREEN = \033[1;32m
CYAN = \033[1;36m
YELLOW = \033[1;33m
CLEAR = \033[0m

# --------	MAKE VARIABLES	--------
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ofast
DBG_FLAGS = -fdiagnostics-color=always -g -DDEBUG=1
INC_FLAGS = -I$(INCLUDE_DIR) -I$(LFT_DIR)/$(INCLUDE_DIR) -I$(MLX_INCLUDE)
LIB_FLAGS = -L$(LFT_DIR) -l$(LFT) -L$(MLX_BUILD) -l$(LMLX)
MLX_FLAGS = -ldl -lglfw -pthread -lm
AUD_FLAGS = -lopenal

MLX_URL = https://github.com/codam-coding-college/MLX42.git
DR_WAV_URL = https://raw.githubusercontent.com/mackron/dr_libs/refs/heads/master/dr_wav.h
OPENAL_URL = https://github.com/kcat/openal-soft.git

INCLUDE_DIR = ./include
MLX_INCLUDE = $(MLX_DIR)/$(INCLUDE_DIR)/MLX42

BUILD_DIR = ./build
SRC_DIR = ./src
OBJ_DIR = ./obj
LIB_DIR = ./lib
MLX_DIR = $(LIB_DIR)/mlx
LFT_DIR = $(LIB_DIR)/libft
DR_DIR = $(LIB_DIR)/drlib

NAME = cub3d
DBG_NAME = debug

LFT = ft
LMLX = mlx42
DRWAV = dr_wav.h

MLX_BUILD = ${MLX_DIR}/${BUILD_DIR}
BUILD = ${BUILD_DIR}/${NAME}
DBG_BUILD = ${BUILD_DIR}/${DBG_NAME}
DRLIB_BUILD = ${DR_DIR}/${DRWAV}

# Check if OpenAL is installed on the system
SYS_OPENAL := $(shell pkg-config --exists openal && echo yes || echo no)

# Paths to source files, add additinal dirs here
VPATH = ${SRC_DIR}/main/ \
		${SRC_DIR}/parser/ \
		${SRC_DIR}/utils/ \
		${SRC_DIR}/game/ \
		${SRC_DIR}/renderer/ \
		${SRC_DIR}/minimap/ \
		${SRC_DIR}/audio/ \

SRCS =	parser.c \
		launch_parser.c \
		path_builder.c \
		parse_textures.c \
		parse_sprite_textures.c \
		parse_texture_utils.c \
		flashlight_images.c \
		flashlight_setup.c \
		texture_path.c \
		parse_colors.c \
		linked_level.c \
		parse_map.c \
		parse_map_utils.c \
		extract_map.c \
		validate_map.c \
		resize_map.c \
		error.c \
		cleanup.c \
		location_utils.c \
		hook.c \
		tick.c \
		flashlight.c \
		renderer.c \
		render_sprites.c \
		render_utils.c \
		raycast.c \
		refresh.c \
		depth_of_field.c \
		light.c \
		light_floor.c \
		movement.c \
		rotation.c \
		level_change.c \
		conversions.c \
		interpolation.c \
		init_minimap.c \
		draw_minimap.c \
		door_actions.c \
		monster_actions.c \
		minimap.c \
		main.c \

SRCS_AUDIO = audio_setup.c \

OBJS = ${SRCS:%.c=${OBJ_DIR}/%.o}
OBJS_AUDIO = ${SRCS_AUDIO:%.c=${OBJ_DIR}/%.o}

# --------	MAKE TARGETS	--------
all: lftbuild ${MLX_BUILD} | build

build: ${OBJS}
	@echo "${GREEN}Generating build...${CLEAR}"
	@mkdir -p ${BUILD_DIR}
	@${CC} ${CFLAGS} -o ${BUILD} $^ ${LIB_FLAGS} ${MLX_FLAGS}
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
	@make --no-print-directory -C ${MLX_BUILD}

lftbuild:
	@make --no-print-directory -C ${LFT_DIR}

# Rules for the debugging build

debug: CFLAGS = ${DBG_FLAGS}
debug: lftbuild ${MLX_BUILD} | ${DBG_BUILD}

${DBG_BUILD}: ${OBJS}
	@echo "${GREEN}Generating debug build...${CLEAR}"
	@mkdir -p ${BUILD_DIR}
	@$(CC) $(DBG_FLAGS) -o $@ $^ $(LIB_FLAGS) $(MLX_FLAGS)
	@echo "${GREEN}Executable ${YELLOW}${DBG_NAME}${GREEN} was created in ${YELLOW}"${BUILD_DIR}"${CLEAR}"

# Rules for building the project with audio features enabled

audio: audiodeps lftbuild ${MLX_BUILD} | audiobuild

audiodeps: ${DRLIB_BUILD}
ifeq ($(SYS_OPENAL),yes)
	${eval LIB_FLAGS += ${AUD_FLAGS}}
else
	${error OpenAL is not installed on the system}
endif
	${eval CFLAGS += -DAUDIO=1}
	${eval INC_FLAGS += -I${DR_DIR}}

audiobuild: ${OBJS} ${OBJS_AUDIO}
	@echo "${GREEN}Generating build...${CLEAR}"
	@mkdir -p ${BUILD_DIR}
	@${CC} ${CFLAGS} -o ${BUILD} $^ ${LIB_FLAGS} ${MLX_FLAGS}
	@echo "${GREEN}Executable ${YELLOW}${NAME}${GREEN} was created in ${YELLOW}"${BUILD_DIR}"${CLEAR}"

${DRLIB_BUILD}:
	@if [ ! -d ${DR_DIR} ]; then \
		mkdir -p ${DR_DIR}; \
	fi
	@if [ ! -f ${DRLIB_BUILD} ]; then \
		curl -L -o ${DRLIB_BUILD} ${DR_WAV_URL}; \
	fi

# Cleanup rules

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
	@if [ -d ${DR_DIR} ]; then \
		rm -rf ${DR_DIR}; \
	fi
	@make fclean --no-print-directory -C ${LFT_DIR}

re: fclean all

mlxbuild: ${MLX_BUILD}

mlxclean: fclean
	@echo "${RED}Removing MLX repository...${CLEAR}"
	@rm -rf ${MLX_DIR}

.PHONY: all re clean fclean mlxbuild mlxclean lftbuild debug audio

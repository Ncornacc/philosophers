# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ncornacc <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2023/03/16 14:29:04 by ncornacc      #+#    #+#                  #
#    Updated: 2023/07/19 13:39:23 by ncornacc      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	:=	philosophers

CC		:=	gcc
HEADER	:=	includes/philosophers.h
HEAD	:= -Iincludes
FLAGS	:=	-Wall -Werror -Wextra -fsanitize=thread -g

RM		:=	rm	-rf

#############################SOURCES##########################

OBJ_DIR	:=	obj/
SRC_DIR	:=	src/

FILE	:=	main free initialization threads utils actions

SRC		:=	${addprefix ${SRC_DIR}, ${addsuffix .c, ${FILE}}}
OBJ		:=	${addprefix ${OBJ_DIR}, ${addsuffix .o, ${FILE}}}


#############################RULES############################

all: ${NAME}

${OBJ_DIR}%.o: ${SRC_DIR}%.c ${HEADER}
	@mkdir -p ${OBJ_DIR}
	@${CC} ${FLAGS} ${HEAD} -o $@ -c $< && printf "${YELLOW} Compiling: $(notdir $<) ${DEF_COLOR}"

${NAME}: ${OBJ}
	@${CC} ${FLAGS} ${HEAD} ${OBJ} -o ${NAME}
	@echo "${GREEN} so_long compiled!${DEF_COLOR}"

clean:
	${RM} ${OBJ_DIR}
	@echo "${MAGENTA} Object files cleaned!${DEF_COLOR}"

fclean: clean
	${RM}	${NAME}
	@echo  "${MAGENTA} executable/archive files cleaned!${DEF_COLOR}"

re:	fclean all
	@echo	"${GREEN} Cleaned and rebuild everything for so_long!${DEF_COLOR}:"

mem:
	memdetect.sh ${SRC} ${FLAGS} ${HEAD} ${1}

.PHONY:	re, all, clean, fclean, libs, mem

##############################################################
#############################COLORS###########################

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m

NAME = out

CC = clang++
CC_FLAGS = -g  -Wall -Wextra -Werror -std=c++98 -Wfatal-errors -Wpedantic -Wconversion -Wshadow

SRCS = $(wildcard *.cpp)

OBJS = $(SRCS:%.cpp=$(OBJS_DIR)/%.o)
OBJS_DIR = ./objs
DEP = $(OBJS:%.o=%.d)
HEADER = -I .

all				: 	${NAME}
$(NAME) 		: 	$(OBJS)	
						@mkdir -p $(@D)
						$(CC) $(CC_FLAGS) $^ -o $@
-include $(DEP)
$(OBJS_DIR)/%.o	:	%.cpp
						@mkdir -p $(@D)
						$(CC) $(CC_FLAGS) ${HEADER} -MMD -c $< -o $@

clean	:
				rm -rf $(OBJS_DIR)
fclean	:	clean
				rm -rf ${NAME}
re		:	fclean
				make all

.PHONY : all clean fclean re

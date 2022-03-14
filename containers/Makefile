NAME = a.out

CC = c++
DEBUG_FLAG = -g -Wfatal-errors -Wpedantic -Wconversion -Wshadow
CC_FLAGS = -Wall -Wextra -Werror  -std=c++98 -g #${DEBUG_FLAG} 
TEST_FLAGS = -D NAMESPACE=std



SRCS = main.cpp 

OBJS = $(SRCS:%.cpp=$(OBJS_DIR)/%.o)
OBJS_DIR = ./objs
DEP = $(OBJS:%.o=%.d)
HEADER = -I .

all				: 	${NAME}
$(NAME) 		: 	$(OBJS)	
						@mkdir -p $(@D)
						@$(CC) $(CC_FLAGS) $^ -o $@
						@echo Compiling...
-include $(DEP)
$(OBJS_DIR)/%.o	:	%.cpp
						@mkdir -p $(@D)
						@$(CC) $(CC_FLAGS) ${HEADER} -MMD -c $< -o $@


#********************** TEST *******************************************************
NAME_TEST		= ft_containers_std

OBJS_TEST		= $(SRCS:%.cpp=$(OBJS_DIR_TEST)/%.o)
OBJS_DIR_TEST	= ./objs_test
DEP_TEST		= $(OBJS_TEST:%.o=%.d)



test					:   re ${NAME_TEST}
							@echo exec ft...
							@./${NAME}	> ft.ret
							@echo exec std...
							@./${NAME_TEST}	> std.ret
							diff ft.ret std.ret
					#		@make fclean
							@echo DIFF OK !

${NAME_TEST}			: ${OBJS_TEST}
							@mkdir -p $(@D)
							@$(CC) $(CC_FLAGS) ${TEST_FLAGS} $^ -o $@
							@echo Compiling test...

-include $(DEP_TEST)
$(OBJS_DIR_TEST)/%.o	: %.cpp
							@mkdir -p $(@D)
							@$(CC) $(CC_FLAGS) ${TEST_FLAGS} ${HEADER} -MMD -c $< -o $@



clean	:
				@rm -rf $(OBJS_DIR) ${OBJS_DIR_TEST}
fclean	:	clean
				@rm -rf ${NAME} ${NAME_TEST} ft.ret std.ret 
			@echo fclean
re		:	fclean
				@make all

.PHONY : all clean fclean re test

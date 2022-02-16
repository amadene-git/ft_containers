NAME = out

CC = clang++
CC_FLAGS =  -g -Wall -Wextra -Werror  -std=c++98 -Wfatal-errors -Wpedantic -Wconversion -Wshadow

SRCS = main.cpp 

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


TESTNAME	= testout
TESTSRCS = __test_${SRCS}

TESTOBJS = $(TESTSRCS:%.cpp=$(OBJS_DIR)/%.o)
TESTDEP = $(TESTOBJS:%.o=%.d)

test			:   fclean ${TESTNAME}
					@./${NAME} 		> 	${NAME}.ret
					@./${TESTNAME} 	> 	${TESTNAME}.ret 
					@diff out.ret testout.ret
					@make fclean
					@echo "\033[0;32m"TEST OK !	
${TESTSRCS}		:
						@make re
						@cp ${SRCS} ${TESTSRCS} ; sed -i s/ft::/std::/g ${TESTSRCS}

${TESTOBJS}		:	${TESTSRCS}


$(TESTNAME) 		: 	$(TESTOBJS)	
						@mkdir -p $(@D)
						@$(CC) $(CC_FLAGS) $^ -o $@
-include $(TESTDEP)
$(OBJS_DIR)/%.o	:	%.cpp
						@mkdir -p $(@D)
						@$(CC) $(CC_FLAGS) ${HEADER} -MMD -c $< -o $@

savetest :		${TESTNAME}
				@./${NAME} 					> 	${NAME}.ret
				@./${TESTNAME} 				> 	${TESTNAME}.ret
				@diff out.ret testout.ret
				@echo "\033[0;32m"TEST OK !

clean	:
				@rm -rf $(OBJS_DIR)
fclean	:	clean
				@rm -rf ${NAME} ${TESTNAME} ${NAME}.ret ${TESTNAME}.ret ${TESTSRCS}
			@echo fclean
re		:	fclean
				@make all

.PHONY : all clean fclean re test

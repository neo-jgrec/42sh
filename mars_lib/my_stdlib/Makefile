##
## EPITECH PROJECT, 2023
## mars_lib
## File description:
## Makefile
##

include src/string/string.mk
include src/memory/memory.mk
include src/numbers/numbers.mk
include src/array/array.mk
include ../../tests/my_stdlib/my_stdlib_tests.mk

PROJECT_NAME			=	my_stdlib
NAME					=	libstd.a

BUILD_DIR				=	build
OBJ						=	$(SRC:%.c=$(BUILD_DIR)/%.o)

CFLAGS					=	-I include/
WFLAGS					=	-Wall -Wextra

CRITERION				=	-lcriterion --coverage
TEST_NAME				=	unit_tests
TEST_INCLUDE_DIR		=	../../tests/include
BUILD_TESTS_DIR			=	$(BUILD_DIR)/tests
TESTS_OBJ				=	$(TEST_SRC:%.c=$(BUILD_DIR)/%.o)
LCOV 					:= 	-fprofile-arcs -ftest-coverage

all:	$(NAME)

$(NAME):	$(OBJ)
	@ar rcs $(NAME) $(OBJ)\
	&& echo -e "\033[1;32m[SUCCES]\033[0m" $(NAME)\
	|| echo -e "\033[1;31m[ERROR]\033[0m" $(NAME)

$(BUILD_DIR)/%.o:	%.c
	@mkdir -p $(dir $@)
	@gcc -c -o $@ $< $(CFLAGS) $(WFLAGS)\
	&& echo -e "\033[1;32m[OK]\033[0m" $<\
	|| echo -e "\033[1;31m[KO]\033[0m" $<

debug:	CFLAGS += -g
debug:	re

clean:
	@for file in $(BUILD_DIR)/*; do\
		if [ -d $$file ]; then\
			rm -rf $$file;\
			echo -e "\033[1;31m[DELETED]\033[0m" $$file;\
		fi;\
	done
	@echo -e "\033[1;31m[CLEAN]\033[0m" $(PROJECT_NAME)
	@rm -f $(shell find -name '*.gc*' -type f)

fclean: clean
	@rm -f $(TEST_NAME)
	@echo -e "\033[1;31m[DELETED]\033[0m" $(TEST_NAME)
	@rm -rf $(BUILD_DIR)
	@echo -e "\033[1;31m[DELETED]\033[0m" $(BUILD_DIR)
	@rm -f $(NAME)
	@echo -e "\033[1;31m[DELETED]\033[0m" $(NAME)

re:	fclean all

tests_run:	CFLAGS += -lcriterion --coverage -Wl,--wrap=malloc
tests_run:	fclean
	@mkdir -p $(BUILD_DIR)
	@gcc -o $(TEST_NAME) $(SRC) $(TEST_SRC) $(CFLAGS) $(WFLAGS) $(CRITERION) \
	$(LCOV) -I $(TEST_INCLUDE_DIR)\
	&& echo -e "\033[1;32m[OK]\033[0m" $(TEST_NAME)\
	|| echo -e "\033[1;31m[KO]\033[0m" $(TEST_NAME)
	@./$(TEST_NAME) --always-succeed
	mv *.gc* $(BUILD_DIR)

.PHONY: all clean fclean re debug tests_run

.SILENT: all clean fclean re debug tests_run

%:
	@echo -e "\033[1;31m[ERROR]\033[0m" "No rule to make target '$@'"

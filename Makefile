NAME = push_swap
NAME_BONUS = checker

CC = cc
FLAGS = -Wextra -Wall -Werror -g -fPIE -I$(HEADER_FOLDER) -lm
FLAGS2 = -Wextra -Wall -Werror -g -fPIE -I$(HEADER_FOLDER)
# FLAGS = -Wextra -g -fPIE -I$(HEADER_FOLDER) -lm

all: $(NAME)

# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	        TESTING                    	         │
# ╰──────────────────────────────────────────────────────────────────────╯

# Some list of valid args to test 
ARGS = 1 0 4 3 2
ARGS2 = 1 6 5 7 9 4 8 33
ARGS3 = 7 6 5 4 3 2 1 0
ARGS4 = 5 4 8 66 -11 9 7 6
ARGS5 = -648 -249 -651 -970 -581 -19 482 -116 76 910 -388 -41 631 -49 696 973 -543 105 -75 21 542 2 478 549 -670

# Number minimum when generating random number
MIN = -999
# Number maximum when generating random number
MAX = 999
# How many numbers to generate
HOW_MANY = 100
# How many times to test
HOW_MANY_TIMES = 3

# MAKE A: call push swap with the $ARGS list
a: libft $(NAME) inc/push_swap.h
	@$(call random_shmol_cat, "\'tis push shwap... $@", 'hav fun ね?', $(CLS), );
	./$(word 2, $^) $(ARGS)

# MAKE B: call push swap BONUS with the $ARGS list
b: libft $(NAME_BONUS) inc/push_swap.h
	@$(call random_shmol_cat, "\'tis push shwap... $@", 'hav fun ね?', $(CLS), );
	./$(word 2, $^) $(ARGS3)

# MAKE C: call push swap with a random list of $HOW_MANY number between $MIN & $MAX
c: libft $(NAME) inc/push_swap.h
	@$(call random_shmol_cat, "\'tis push shwap tesshter", $(HOW_MANY) number ね?, $(CLS), );
	@ARGS=$$(seq $(MIN) $(MAX) | shuf -n $(HOW_MANY) | tr '\n' ' ' | sed -r 's/ $$//'); \
	echo $$ARGS; \
	./$(word 2, $^) $$ARGS

# MAKE C: call push swap with a random list of $HOW_MANY number between $MIN & $MAX
d: libft visualiser
	@$(call random_shmol_cat, "\'tis push shwap tesshter", $(HOW_MANY2) number ね?, $(CLS), );
	-@ARGS=$$(seq $(MIN) $(MAX) | shuf -n $(HOW_MANY2) | tr '\n' ' ' | sed -r 's/ $$//'); \
	make -C .. re; \
	echo "ARGS: $$ARGS"; \
	> _output ../$(NAME) $$ARGS; \
	< _output ./visualiser $$ARGS

# Call push swap $ARGS with VALGRIND
v: libft $(NAME) inc/push_swap.h
	@$(call random_shmol_cat, "vlgrininnng ... $(NAME)!", "$@: $(MAP1)", $(CLS), );
	-$(VALGRIND) ./$(word 2, $^) $(ARGS)


OK = $(GREEN) OK $(RESET)
NOK = $(RED) KO $(RESET)
CHECKER_NAME = checker_linux

# Call push swap $HOW_MANY_TIMES
m: libft $(NAME) inc/push_swap.h
	@$(call shmol_cat_color, $(C_123), $(C_321), "\'tis push shwap tesshter", "$(HOW_MANY) numbers、$(HOW_MANY_TIMES) times ね?", $(CLS), );
	@total=0; \
	for i in $$(seq 1 $(HOW_MANY_TIMES)); do \
		ARGS=$$(seq $(MIN) $(MAX) | shuf -n $(HOW_MANY) | tr '\n' ' ' | sed -r 's/ $$//'); \
		output=$$(./$(NAME) $$ARGS); \
		return_code=$$?; \
		count=$$(echo "$$output" | wc -l); \
		echo -e -n "$(C_123)" "test $$i: " "$(C_321)" "$$count" "$(C_123)" "moves: "; \
		if [ $$return_code -eq 1 ]; then \
			echo -e "$(NOK)"; \
			echo -e "$(C_411)" "FAILED args saved in bad_args, output saved in bad_output"; \
			echo "$$ARGS" > bad_args; \
			echo "$$output" >> bad_output; \
		else \
			echo -e "$(OK)"; \
		fi; \
		total=$$((total + count)); \
	done; \
	average=$$((total / $(HOW_MANY_TIMES))); \
	$(call random_shmol_cat, "heres average numbar:", $$average, , )


# List of bad args to test 
BAD_ARGS =  "0 1 2 2a 5" "0 1 2 wtf" "0 1 2 -2147483648 -2147483650" "0 1 2 9999999999 9" "4" "" "i want ..." "0 1-2 8 5" "0 1 2 8 1 5"

# Cycle through the bad args with valgrind
n: libft $(NAME) inc/push_swap.h
	@for arg in $(BAD_ARGS); do \
	$(call random_shmol_cat, teshting lots of bad args:, $$arg, $(CLS), ); \
	$(VALGRIND) ./$(NAME) $$arg; \
	echo -e "\t$(BLINK)$(C_430)~ Press Enter to continue...$(RESET)"; \
	read -p "" key; \
	done
	$(call random_shmol_cat, this one should work fine:, 1 5 2 7 -3, $(CLS), )
	$(VALGRIND) ./$(NAME) 1 5 2 7

# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	        SOURCES                    	         │
# ╰──────────────────────────────────────────────────────────────────────╯

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, src/obj/%.o, $(SRC))

SRC_FOLDER = src
OBJ_FOLDER = src/obj
HEADER_FOLDER = inc

# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	        Libft                      	         │
# ╰──────────────────────────────────────────────────────────────────────╯

libft:
	@make -sC lib all;

libclean:
	@make -sC lib clean

relib:
	@make -sC lib re

libtest:
	@make -sC lib test_color

# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	       PROJECT                   	         │
# ╰──────────────────────────────────────────────────────────────────────╯

$(NAME): libft $(OBJ) main.c
	@clear
	@if ! $(CC) $(FLAGS) $(OBJ) main.c lib/libft.a -o $(NAME); then \
		$(call print_cat, "", $(RED), $(GOLD), $(RED_L), $(call pad_word, 10, "ERROR"), $(call pad_word, 12, "COMPILING..")); \
		exit 1; \
	fi
	$(call print_cat, $(CLEAR), $(GOLD), $(GREEN1), $(GREEN1), $(call pad_word, 10, $(NAME)), $(call pad_word, 12, "Compiled~"));


src/obj/%.o: src/%.c
	@if [ ! -e $(OBJ_FOLDER) ]; then\
		mkdir -p $(OBJ_FOLDER);\
	fi
	@if ! $(CC) -c $(FLAGS2) $< -o $@; then \
		$(call shmol_cat_error, $(RED), $(RED_L)); \
		exit 1; \
	fi

# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	       BONUS	                   	         │
# ╰──────────────────────────────────────────────────────────────────────╯

SRC_B = $(wildcard src/*.c)
OBJ_B = $(patsubst src/%.c, src/obj/%.o, $(SRC_B))

OBJ_FOLDER_B = src/obj

$(NAME_BONUS): bonus

bonus: libft $(OBJ_B) main_bonus.c inc/push_swap.h
	@clear
	@if ! $(CC) $(FLAGS) $(OBJ_B) main_bonus.c lib/libft.a -o $(NAME_BONUS); then \
		$(call print_cat, "", $(RED), $(GOLD), $(RED_L), $(call pad_word, 10, "ERROR"), $(call pad_word, 12, "COMPILING..")); \
		exit 1; \
	fi
	$(call print_cat, $(CLEAR), $(GOLD), $(GREEN1), $(C_415), $(call pad_word, 10, $(NAME_BONUS)), $(call pad_word, 12, "Compiled~"));

src_bonus/obj/%.o: src_bonus/%.c inc/push_swap.h
	@clear
	@if [ ! -e $(OBJ_FOLDER_B) ]; then\
		mkdir -p $(OBJ_FOLDER_B);\
	fi
	@if ! $(CC) -c $(FLAGS2) -O3 -c $< -o $@; then \
		$(call shmol_cat_error, $(RED), $(RED_L)); \
		exit 1; \
	fi

visualiser: libft $(OBJ_B) main_visu.c
	@clear
	@if ! $(CC) $(FLAGS) $(OBJ_B) main_visu.c lib/libft.a -o visualiser; then \
		$(call print_cat, "", $(RED), $(GOLD), $(RED_L), $(call pad_word, 10, "ERROR"), $(call pad_word, 12, "COMPILING..")); \
		exit 1; \
	fi
	$(call print_cat, $(CLEAR), $(GOLD), $(GREEN1), $(C_415), $(call pad_word, 10, $(VISUALISER)), $(call pad_word, 12, "Compiled~"));

# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	       OTHERS	                   	         │
# ╰──────────────────────────────────────────────────────────────────────╯

test:	libft
	@rm -f ./lib/a.out
	-@cc ./lib/test.c ./lib/libft.a -o ./lib/a.out -lm
	@if [ ! -e ./lib/a.out ]; then\
		$(call print_cat, "", $(RED), $(GOLD), $(RED_L), $(call pad_word, 10, "The⠀Cake"), $(call pad_word, 12, "Is⠀A⠀Lie..")); \
		exit 3; \
	fi
	@$(call random_cat, $(call pad_word, 12, "Making"), $(call pad_word, 14, "Science"), $(CLS), $(RESET));
	@lib/a.out

test2:	libft $(OBJ_B)
	@rm -f ./lib/a.out
	@cc ./lib/test.c $(OBJ_B) -I$(HEADER_FOLDER) lib/libft.a -lm -o ./lib/a.out
	@$(call random_cat, $(call pad_word, 12, "TESTING"), $(call pad_word, 14, "SCIENCE"), $(CLS), $(RESET));
	-@$(VALGRIND) lib/a.out map/map4.ber

vtest:	libft
	@cc -g3 ./lib/test.c ./lib/libft.a -o ./lib/a.out -lm
	$(call print_cat, "", $(RED), $(GOLD), $(BLUE1), $(call pad_word, 10, "TESTING"), $(call pad_word, 12, "SCIENCE.."));
	@$(VALGRIND) lib/a.out

clean:
	@rm -rf $(OBJ_FOLDER)
	$(call print_cat, $(CLEAR), $(C_225), $(C_320), $(C_450), $(call pad_word, 10, "Objects"), $(call pad_word, 12, "Exterminated"));

fclean: clean
	@rm -f _args _output
	@rm -rf $(NAME) $(NAME_BONUS)
	@make -sC lib clean_silent;
	$(call print_cat, $(CLEAR), $(C_120), $(C_300), $(C_210), $(call pad_word, 10, "All⠀clean"), $(call pad_word, 12, "Miaster"));

re: fclean all bonus

re_bonus: fclean

.PHONY: all clean fclean re bonus

.SILENT: $(NAME) bonus

# - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - -  - VALGRIND
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --track-fds=yes
# VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --trace-children=yes --track-fds=yes
#
# lldb: clean all
# 	@lldb ./$(NAME) $(ARGS)
#
# ↑さ↓ぎょう  を  ↓ほ↑ぞん
# 																	GITHUB
git: fclean
	@$(call random_shmol_cat_blink, 作業を保存してるかな.., いいね、いいねえー , $(CLS), );
	@current_date=$$(date); \
	git add .; \
	git commit; \
	git push

NORM_FILE = inc/

norm: fclean
	@$(call random_shmol_cat_blink, 掃除してるかな..、いいね、いいねえー, giv file to norm, $(CLS), );
	-@read -p 'file...:' path; \
	if [ -z "$$path" ]; then \
		watch -n 0.5 norminette $(NORM_FILE); \
	else \
		watch -n 0.5 norminette $$path; \
	fi

#
# ╭──────────────────────────────────────────────────────────────────────╮
# │                  	 	       PRINT                     	         │
# ╰──────────────────────────────────────────────────────────────────────╯

# C_213
PURPLE = \033[38;5;97m
# C_430
GOLD = \033[38;5;178m
# C_040
GREEN1 = \033[38;5;40m
# C_045
BLUE1 = \033[38;5;45m

# $(C_105), $(C_510), $(C_025)
# $(RED), $(GOLD), $(BLUE1)

test_color666:
	@$(call random_cat, $(call pad_word, 12, The⠀Cake), $(call pad_word, 14, Is⠀A⠀Lie⠀...), $(CLS), $(RESET));
	@$(call random_cat, $(call pad_word, 13, The⠀Cake), $(call pad_word, 15, Is⠀A⠀Lie⠀...), , $(RESET));


# $(call pad_word, 12, The⠀Cake)
pad_word = $(BLINK)$(shell printf "%$(1)s" "$(2)")$(RESET)
# improve with: STRING1=$$(printf "\033[38;5;%dm" $$(shuf -i 0-255 -n 1));

# --------------------------------------------------------------------------------- >
# @$(call print_cat, $(CLEAR), $(body), $(eye), $(txt), $(call pad_word, 12, "The⠀Cake"), $(call pad_word, 12, "Is⠀A⠀Lie..."));
# print_cat (resest?)(c_c)_sctt$padded_txt_top))($(padded_txt_bot))
define print_cat
    @echo -e "$(1)$(2)\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠒⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠇⠀⠘⡄⠀⠀⠀⠀⠀⠀⣀⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⠀⠀⠀⠁⠉⠉⠉⠒⠊⠉⠀⡇⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜$(3)$(BLINK)⣀⡀$(RESET)$(2)⠀⠀⠀⠀⠀⠀⠀⢰⠁⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠲⢴⠁$(3)$(BLINK)⠛⠁$(RESET)$(2)$(3)$(BLINK)⢀⣄$(RESET)$(2)⠀⠀⠀⢸⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠑⠺⡀⠀⠀⢶⠤$(3)$(BLINK)⠈⠋$(RESET)$(2)⠀⠀⠀⡘⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⢄⡀⠀⠀⠀⠠⣉⠑⠂⠀⢠⠃⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠊⠀⠀⠀⠀⠀⠀⠁⠀⠀⠈⢆⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡆⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠤⠒⠒⠃⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠀\n\
	\t\t\t\t\t\t\t	⠀⠔⠑⠄⠀⠀⠀⠀⠀⠀⠀⠀⡎⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇\n\
	\t\t\t\t\t\t\t	⠸⡀⠀⢣⠀⠀⠀⠀⠀⠀⠀⠀⡇$(4)$(5)$(2)⠀⠀⠀⠀⠀⡇\n\
	\t\t\t\t\t\t\t	⠀⠱⡀⠀⠳⡀⠀⠀⠀⠀⠀⠀⢃$(4)$(6)$(2)⠀⠀⡸⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠑⢄⠀⠈⠒⢄⡀⠀⠀⠀⠸⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡰⠁⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠑⠦⣀⠀⠈⠉⠐⠒⠒⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⢢⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠉⠐⠒⠠⠤⠤⠤⠤⠔⠂⠠⠤⠤⠤⠄⠐⠒⠂⠉⠉⠉⠉⠉⠁\n$(RESET)"
endef

# --------------------------------------------------------------------------------- >
# @$(call random_cat, $(call pad_word, 12, txt1), $(call pad_word, 12, txt2), $(CLS), $(RESET));
# print_cat (resest?)(c_c)_sctt$padded_txt_top))($(padded_txt_bot))
define random_cat
	COLOR=$$(printf "\033[38;5;%dm" $$(shuf -i 0-255 -n 1)); \
	COLOR2=$$(printf "\033[38;5;%dm" $$(shuf -i 0-255 -n 1)); \
	COLOR3=$$(printf "\033[38;5;%dm" $$(shuf -i 0-255 -n 1)); \
    echo -e "$(3)$${COLOR}\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠒⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠇⠀⠘⡄⠀⠀⠀⠀⠀⠀⣀⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⠀⠀⠀⠁⠉⠉⠉⠒⠊⠉⠀⡇⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⠀$${COLOR2}$(BLINK)⣀⡀$(RESET)$${COLOR}⠀⠀⠀⠀⠀⠀⠀⠀⢰⠁⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠲⢴⠁⠀$${COLOR2}$(BLINK)⠛⠁$(RESET)$${COLOR}$${COLOR2}$(BLINK)⠀⠀⢀⣄$(RESET)$${COLOR}⠀⠀⠀⠀⢸⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠑⠺⡀⠀⠀⢶⠤$${COLOR2}$(BLINK)⠀⠈⠋$(RESET)$${COLOR}⠀⠀⠀⠀⡘⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⢄⡀⠀⠀⠀⠠⣉⠑⠂⠀⢠⠃⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠊⠀⠀⠀⠀⠀⠀⠁⠀⠀⠈⢆⠀⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡆⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠤⠒⠒⠃⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠀\n\
	\t\t\t\t\t\t\t	⠀⠔⠑⠄⠀⠀⠀⠀⠀⠀⠀⠀⡎⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇\n\
	\t\t\t\t\t\t\t	⠸⡀⠀⢣⠀⠀⠀⠀⠀⠀⠀⠀⡇$${COLOR3}$(1)$${COLOR}⠀⠀⠀⠀⠀⡇\n\
	\t\t\t\t\t\t\t	⠀⠱⡀⠀⠳⡀⠀⠀⠀⠀⠀⠀⢃$${COLOR3}$(2)$${COLOR}⠀⠀⡸⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠑⢄⠀⠈⠒⢄⡀⠀⠀⠀⠸⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡰⠁⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠑⠦⣀⠀⠈⠉⠐⠒⠒⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⢢⠀\n\
	\t\t\t\t\t\t\t	⠀⠀⠀⠀⠀⠀⠀⠉⠐⠒⠠⠤⠤⠤⠤⠔⠂⠠⠤⠤⠤⠄⠐⠒⠂⠉⠉⠉⠉⠉⠁\n$(4)"
endef

# --------------------------------------------------------------------------------- >
# @$(call shmol_cat_color, $(c_c), $(c_t), txt1, txt2, $(CLS), $(RESET));
# $(1)=COLOR1, $(2)=COLOR2; $(3)= text1; $(4)= text2; $(5)=$(CLEAR); $(6)=$(RESET)
define shmol_cat_color
	echo -e "$(5)$(2)\
	\tにゃ~$(1)\t⠀╱|、\n\
	\t\t(˚ˎ。7⠀⠀⠀$(2)~ $(3) ~$(1)\n\
	\t\t⠀|、˜\\\\\t\t$(2)$(4)$(1)\n\
	\t\t⠀じしˍ)ノ\n$(6)"
endef
# --------------------------------------------------------------------------------- >
# @$(call random_shmol_cat, text 1, text 2, $(CLS), $(RESET));
# $(1)= $(CLEAR); $(2)= text1; $(3)= text2; $(4)= $(RESET)
define random_shmol_cat
	COLOR=$$(printf "\033[38;5;%dm" $$(shuf -i 1-255 -n 1)); \
	COLOR2=$$(printf "\033[38;5;%dm" $$(shuf -i 0-255 -n 1)); \
	echo -e "$(3)$${COLOR2}\
	\tにゃ~$${COLOR}\t⠀╱|、\n\
	\t\t(˚ˎ。7⠀⠀⠀$${COLOR2}~ $(1) ~$${COLOR}\n\
	\t\t⠀|、˜\\\\\t\t$${COLOR2}~ $(2)$${COLOR}\n\
	\t\t⠀じしˍ)ノ\n$(4)"
endef

# // <!> - - - - - - - - - - - </!>
# --------------------------------------------------------------------------------- >
rscs:
	@$(call random_shmol_cat_surligne, text 1, text 2, $(CLS), $(RESET));

define random_shmol_cat_surligne
	COLOR=$$(printf "\033[0m\033[38;5;%dm" $$(shuf -i 0-255 -n 1)); \
	COLOR2=$$(printf "\033[48;5;%dm" $$(shuf -i 0-255 -n 1)); \
	echo -e "$(3)$${COLOR2}\
	\tにゃ~$${COLOR}\t⠀╱|、\n\
	\t\t(˚ˎ。7⠀⠀⠀$${COLOR2}~ $(1) ~$${COLOR}\n\
	\t\t⠀|、˜\\\\\t\t$${COLOR2}~ $(2)$${COLOR}\n\
	\t\t⠀じしˍ)ノ\n$(4)"
endef

rscb:
	@$(call random_shmol_cat_blink, text 1, text 2, $(CLS), $(RESET));

define random_shmol_cat_blink
	COLOR=$$(printf "\033[0m\033[38;5;%dm" $$(shuf -i 0-255 -n 1)); \
	COLOR2=$$(printf "\e[5m\033[38;5;%dm" $$(shuf -i 0-255 -n 1)); \
	echo -e "$(3)\n$${COLOR2}\
	\tにゃ~$${COLOR}\t⠀╱|、\n\
	\t\t(˚ˎ。7⠀⠀⠀$${COLOR2}~ $(1) ~$${COLOR}\n\
	\t\t⠀|、˜\\\\\t\t$${COLOR2}~ $(2)$${COLOR}\n\
	\t\t⠀じしˍ)ノ\n$(4)"
endef
# // <!> - - - - - - - - - - - </!>
# --------------------------------------------------------------------------------- >
# @$(call shmol_cat_error, $(RED), $(RED_L));
# $(1) = $(c_c)$2) = $(c_ttN CLS
define shmol_cat_error
	echo -e "$(2)\
	\tにゃ~$(1)\t⠀╱|、\n\
	\t\t(˚ˎ。7⠀⠀⠀$(2)~ somshin wen wong ~$(1)\n\
	\t\t⠀|、˜\\\\\n\
	\t\t⠀じしˍ)ノ\n$(RESET)"
endef

# 					Define all 256 colors
CLEAR = \033[2J\033[H
CLS = \033[2J\033[H
RESET = \033[0m
BLINK = \033[5m
# U+2800 to U+28FF Braile
# <Esc>[38;5;ColorNumberm
BLACK = \033[38;5;0m
RED = \033[38;5;1m
GREEN = \033[38;5;2m
YELLOW = \033[38;5;3m
BLUE = \033[38;5;4m
MAGENTA = \033[38;5;5m
CYAN = \033[38;5;6m
GRAY = \033[38;5;7m

BLACK_L = \033[38;5;8m
RED_L = \033[38;5;9m
GREEN_L = \033[38;5;10m
YELLOW_L = \033[38;5;11m
BLUE_L = \033[38;5;12m
MAGENTA_L = \033[38;5;13m
CYAN_L = \033[38;5;14m
WHITE = \033[38;5;15m

C_000 = \033[38;5;16m
C_001 = \033[38;5;17m
C_002 = \033[38;5;18m
C_003 = \033[38;5;19m
C_004 = \033[38;5;20m
C_005 = \033[38;5;21m
C_010 = \033[38;5;22m
C_011 = \033[38;5;23m
C_012 = \033[38;5;24m
C_013 = \033[38;5;25m
C_014 = \033[38;5;26m
C_015 = \033[38;5;27m
C_020 = \033[38;5;28m
C_021 = \033[38;5;29m
C_022 = \033[38;5;30m
C_023 = \033[38;5;31m
C_024 = \033[38;5;32m
C_025 = \033[38;5;33m
C_030 = \033[38;5;34m
C_031 = \033[38;5;35m
C_032 = \033[38;5;36m
C_033 = \033[38;5;37m
C_034 = \033[38;5;38m
C_035 = \033[38;5;39m
C_040 = \033[38;5;40m
C_041 = \033[38;5;41m
C_042 = \033[38;5;42m
C_043 = \033[38;5;43m
C_044 = \033[38;5;44m
C_045 = \033[38;5;45m
C_050 = \033[38;5;46m
C_051 = \033[38;5;47m
C_052 = \033[38;5;48m
C_053 = \033[38;5;49m
C_054 = \033[38;5;50m
C_055 = \033[38;5;51m
C_100 = \033[38;5;52m
C_101 = \033[38;5;53m
C_102 = \033[38;5;54m
C_103 = \033[38;5;55m
C_104 = \033[38;5;56m
C_105 = \033[38;5;57m
C_110 = \033[38;5;58m
C_111 = \033[38;5;59m
C_112 = \033[38;5;60m
C_113 = \033[38;5;61m
C_114 = \033[38;5;62m
C_115 = \033[38;5;63m
C_120 = \033[38;5;64m
C_121 = \033[38;5;65m
C_122 = \033[38;5;66m
C_123 = \033[38;5;67m
C_124 = \033[38;5;68m
C_125 = \033[38;5;69m
C_130 = \033[38;5;70m
C_131 = \033[38;5;71m
C_132 = \033[38;5;72m
C_133 = \033[38;5;73m
C_134 = \033[38;5;74m
C_135 = \033[38;5;75m
C_140 = \033[38;5;76m
C_141 = \033[38;5;77m
C_142 = \033[38;5;78m
C_143 = \033[38;5;79m
C_144 = \033[38;5;80m
C_145 = \033[38;5;81m
C_150 = \033[38;5;82m
C_151 = \033[38;5;83m
C_152 = \033[38;5;84m
C_153 = \033[38;5;85m
C_154 = \033[38;5;86m
C_155 = \033[38;5;87m
C_200 = \033[38;5;88m
C_201 = \033[38;5;89m
C_202 = \033[38;5;90m
C_203 = \033[38;5;91m
C_204 = \033[38;5;92m
C_205 = \033[38;5;93m
C_210 = \033[38;5;94m
C_211 = \033[38;5;95m
C_212 = \033[38;5;96m
C_213 = \033[38;5;97m
C_214 = \033[38;5;98m
C_215 = \033[38;5;99m
C_220 = \033[38;5;100m
C_221 = \033[38;5;101m
C_222 = \033[38;5;102m
C_223 = \033[38;5;103m
C_224 = \033[38;5;104m
C_225 = \033[38;5;105m
C_230 = \033[38;5;106m
C_231 = \033[38;5;107m
C_232 = \033[38;5;108m
C_233 = \033[38;5;109m
C_234 = \033[38;5;110m
C_235 = \033[38;5;111m
C_240 = \033[38;5;112m
C_241 = \033[38;5;113m
C_242 = \033[38;5;114m
C_243 = \033[38;5;115m
C_244 = \033[38;5;116m
C_245 = \033[38;5;117m
C_250 = \033[38;5;118m
C_251 = \033[38;5;119m
C_252 = \033[38;5;120m
C_253 = \033[38;5;121m
C_254 = \033[38;5;122m
C_255 = \033[38;5;123m
C_300 = \033[38;5;124m
C_301 = \033[38;5;125m
C_302 = \033[38;5;126m
C_303 = \033[38;5;127m
C_304 = \033[38;5;128m
C_305 = \033[38;5;129m
C_310 = \033[38;5;130m
C_311 = \033[38;5;131m
C_312 = \033[38;5;132m
C_313 = \033[38;5;133m
C_314 = \033[38;5;134m
C_315 = \033[38;5;135m
C_320 = \033[38;5;136m
C_321 = \033[38;5;137m
C_322 = \033[38;5;138m
C_323 = \033[38;5;139m
C_324 = \033[38;5;140m
C_325 = \033[38;5;141m
C_330 = \033[38;5;142m
C_331 = \033[38;5;143m
C_332 = \033[38;5;144m
C_333 = \033[38;5;145m
C_334 = \033[38;5;146m
C_335 = \033[38;5;147m
C_340 = \033[38;5;148m
C_341 = \033[38;5;149m
C_342 = \033[38;5;150m
C_343 = \033[38;5;151m
C_344 = \033[38;5;152m
C_345 = \033[38;5;153m
C_350 = \033[38;5;154m
C_351 = \033[38;5;155m
C_352 = \033[38;5;156m
C_353 = \033[38;5;157m
C_354 = \033[38;5;158m
C_355 = \033[38;5;159m
C_400 = \033[38;5;160m
C_401 = \033[38;5;161m
C_402 = \033[38;5;162m
C_403 = \033[38;5;163m
C_404 = \033[38;5;164m
C_405 = \033[38;5;165m
C_410 = \033[38;5;166m
C_411 = \033[38;5;167m
C_412 = \033[38;5;168m
C_413 = \033[38;5;169m
C_414 = \033[38;5;170m
C_415 = \033[38;5;171m
C_420 = \033[38;5;172m
C_421 = \033[38;5;173m
C_422 = \033[38;5;174m
C_423 = \033[38;5;175m
C_424 = \033[38;5;176m
C_425 = \033[38;5;177m
C_430 = \033[38;5;178m
C_431 = \033[38;5;179m
C_432 = \033[38;5;180m
C_433 = \033[38;5;181m
C_434 = \033[38;5;182m
C_435 = \033[38;5;183m
C_440 = \033[38;5;184m
C_441 = \033[38;5;185m
C_442 = \033[38;5;186m
C_443 = \033[38;5;187m
C_444 = \033[38;5;188m
C_445 = \033[38;5;189m
C_450 = \033[38;5;190m
C_451 = \033[38;5;191m
C_452 = \033[38;5;192m
C_453 = \033[38;5;193m
C_454 = \033[38;5;194m
C_455 = \033[38;5;195m
C_500 = \033[38;5;196m
C_501 = \033[38;5;197m
C_502 = \033[38;5;198m
C_503 = \033[38;5;199m
C_504 = \033[38;5;200m
C_505 = \033[38;5;201m
C_510 = \033[38;5;202m
C_511 = \033[38;5;203m
C_512 = \033[38;5;204m
C_513 = \033[38;5;205m
C_514 = \033[38;5;206m
C_515 = \033[38;5;207m
C_520 = \033[38;5;208m
C_521 = \033[38;5;209m
C_522 = \033[38;5;210m
C_523 = \033[38;5;211m
C_524 = \033[38;5;212m
C_525 = \033[38;5;213m
C_530 = \033[38;5;214m
C_531 = \033[38;5;215m
C_532 = \033[38;5;216m
C_533 = \033[38;5;217m
C_534 = \033[38;5;218m
C_535 = \033[38;5;219m
C_540 = \033[38;5;220m
C_541 = \033[38;5;221m
C_542 = \033[38;5;222m
C_543 = \033[38;5;223m
C_544 = \033[38;5;224m
C_545 = \033[38;5;225m
C_550 = \033[38;5;226m
C_551 = \033[38;5;227m
C_552 = \033[38;5;228m
C_553 = \033[38;5;229m
C_554 = \033[38;5;230m
C_555 = \033[38;5;231m

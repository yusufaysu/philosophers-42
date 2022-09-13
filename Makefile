NAME = philo

src = src/philo.c src/utils.c src/main.c  src/init.c src/utils2.c

obj = $(src:.c=.o)

header = inc/philo.h

flags = -Wall -Werror -Wextra -pthread #-g -fsanitize=thread 

cc = cc

all : $(NAME)

$(NAME): $(src) $(obj) $(header)
	$(cc) $(flags) $(src) -o $(NAME)

%.o : %.c
	$(cc) $(flags) -c $< -o $@
	
clean:
	rm -rf $(obj) $(obj_b)

fclean: clean
	rm -rf $(NAME)

re: fclean all

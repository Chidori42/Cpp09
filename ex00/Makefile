CC = c++ -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp\
		BitcoinExchange.cpp

NAME = btc

OBJS = $(SRCS:.cpp=.o)

RM = rm -f

all: $(NAME)

%.o : %.cpp
	$(CC) -o $(NAME) $(OBJS)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
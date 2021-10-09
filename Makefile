CXX		= clang++
CXXFLAGS	= -Wall -Werror -Wextra -std=c++98 -fsanitize=address -g
SRCS	= main.cpp
OBJS	= ${SRCS:.cpp=.o}
NAME	= tests

all		:	$(NAME)

$(NAME)	:	$(OBJS)
				$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS) 

clean:
				rm -rf $(OBJS)

fclean:		clean
				rm -f $(NAME)

re:			fclean all

.PHONY:		all fclean re
CXX		= clang++
CXXFLAGS	= -Wall -Werror -Wextra -std=c++98
SRCS	= 
OBJS	= ${SRCS:.cpp=.o}
NAME	= 

all		:	$(NAME)

$(NAME)	:	$(OBJS)
				$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS) 

clean:
				rm -rf $(OBJS)

fclean:		clean
				rm -f $(NAME)

re:			fclean all

.PHONY:		all fclean re
CXX		= clang++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -fsanitize=address -g -D STL=${STL} -D VERSION=${VERSION}
SRCS	= main.cpp
OBJS	= ${SRCS:.cpp=.o}
OBJS_stl	= ${SRCS:.cpp=.o} 
OBJS_mine	= ${SRCS:.cpp=.o}

NAME	= tests


all		:	$(NAME)

$(NAME)	:	$(OBJS)
				$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
help	:	
			@echo "Specify STL=1 for the STL version and STL=0 for my containers,\nand specify VERSION=0/1/2 for my main, the performance main, the subject main and the complete cplusplus function test respectively"

clean:
				rm -rf $(OBJS)

fclean:		clean
				rm -f $(NAME)

re:			fclean all

.PHONY:		all fclean re

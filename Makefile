NAME	:= webserv

CC		:=	clang++
CPPFLAGS:=-fsanitize=address -g3	#-Wall -Wextra -Werror 
CPPFLAG	:=	-std=c++98

SRCS	:=	webserv.cpp srcs/conf_reader.cpp srcs/conf_parser.cpp srcs/location_storage.cpp srcs/server_storage.cpp srcs/help.cpp multiserver/server.cpp multiserver/Request.cpp multiserver/StatusCodes.cpp multiserver/Post.cpp
INCS	:=	incs/parse_config/
OBJS	:=	$(SRCS:.cpp=.o)

%.o:%.cpp
	$(CC)  $(CPPFLAGS) $(CPPFLAG) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(INCS)
	$(CC) $(OBJS) -I $(INCS) $(CPPFLAGS) $(CPPFLAG) -o $@

clean:
	rm -rf $(OBJS)

fclean:		clean
	rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

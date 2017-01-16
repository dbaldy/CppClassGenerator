# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmanet <tmanet@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/09 10:10:37 by tmanet            #+#    #+#              #
#    Updated: 2017/01/16 14:37:03 by dbaldy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER = headerGenerator

CLASS = classGenerator

CPP = clang++

FLAGS = -Wall -Wextra -Werror

HEADER_SRC = HeaderGenerator.cpp

CLASS_SRC = ClassGenerator.cpp

LIBRARY = -lncurses

HEADER_OBJ = $(HEADER_SRC:.cpp=.o)

CLASS_OBJ = $(CLASS_SRC:.cpp=.o)

all: $(HEADER) $(CLASS)

$(HEADER): $(HEADER_OBJ)
	@$(CPP) $(FLAGS) -o $@ $(HEADER_OBJ) $(LIBRARY)
	@echo "\x1b[32;01mCompilation de $(HEADER)\x1b[0;m"

$(CLASS): $(CLASS_OBJ)
	@$(CPP) $(FLAGS) -o $@ $(CLASS_OBJ) $(LIBRARY)
	@echo "\x1b[32;01mCompilation de $(CLASS)\x1b[0;m"

%.o: %.cpp
	@$(CPP) $(FLAGS) -o $@ -c $<
	@echo "\x1b[32;01mCompilation de $<\x1b[0;m"

clean:
	@/bin/rm -f $(HEADER_OBJ) $(CLASS_OBJ)
	@echo "\x1b[32;01mclean\x1b[0;m"

fclean: clean
	@/bin/rm -f $(HEADER) $(CLASS)
	@echo "\x1b[32;01mfclean $(NAME)\x1b[0;m"

re: fclean all

.PHONY: all clean fclean re

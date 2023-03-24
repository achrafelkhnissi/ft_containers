NAME		= ft_containers
LIB_DIR		= lib
LIB         = $(LIB_DIR)libft.a

CC			= c++
FSANITIZE	= -fsanitize=address -g
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 ${FSANITIZE}
RM			= rm -rf

OBJDIR		= build
# Tester
TESTER		= tester
VEC_TEST	= $(TESTER)/vector_test.cpp
STACK_TEST	= $(TESTER)/stack_test.cpp
MAP_TEST	= $(TESTER)/map_test.cpp
SET_TEST	=
TESTER_INC	= -I $(TESTER)
TESTER_HEADER = $(TESTER)/tester.hpp
TESTER_SRC	= $(VEC_TEST) $(STACK_TEST) $(MAP_TEST) $(SET_TEST)

# Vector
VECTOR		= containers/vector
VECTOR_SRC	= $(addprefix $(VECTOR)/, )
VECTOR_INC	= -I $(VECTOR)
VECTOR_HEADER = $(addprefix $(VECTOR)/, vector.hpp iterator.hpp const_iterator.hpp reverse_iterator.hpp const_reverse_iterator.hpp)
VEC_OUT		= $(TESTER)/vectors_output

# Stack
STACK		= containers/stack
STACK_SRC	=
STACK_INC	= -I $(STACK)
STACK_HEADER = $(STACK)/stack.hpp
STACK_OUT	= $(TESTER)/stacks_output

# Map
MAP			= containers/map
MAP_SRC		=
MAP_INC		= -I $(MAP)
MAP_HEADER	= $(MAP)/map.hpp
MAP_OUT		= $(TESTER)/maps_output

# red black tree
RBTREE		= rbtree
RBTREE_SRC	= $(addprefix $(RBTREE)/, )
RBTREE_INC	= -I $(RBTREE)
RBTREE_HEADER = $(addprefix $(RBTREE)/, rbtree.hpp, rbtree_node.hpp, rbtree_iterator.hpp, rbtree_const_iterator.hpp \
		rbtree_reverse_iterator.hpp, rbtree_const_reverse_iterator.hpp)

# Set
SET			= containers/set
SET_SRC		=
SET_INC		= -I $(SET)
SET_HEADER	= $(SET)/set.hpp
SET_OUT		= $(TESTER)/sets_output

# Utils
UTILS		= utils
UTILS_SRC	= $(addprefix $(UTILS)/, ) # utils.cpp
UTILS_INC	= -I $(UTILS)
UTILS_HEADERS = $(addprefix $(UTILS)/, enable_if.hpp lexicographical_compare.hpp is_integral.hpp)

# Iterator traits
ITERATOR_TRAITS_INC	= -I ./containers
ITERATOR_TRAITS	= ./containers/iterator_traits.hpp

INCLUDES  = $(TESTER_INC) $(VECTOR_INC) $(STACK_INC) $(MAP_INC) $(SET_INC) $(UTILS_INC) $(ITERATOR_TRAITS_INC)
SOURCES   = main.cpp $(TESTER_SRC) $(VECTOR_SRC) $(STACK_SRC) $(MAP_SRC) $(SET_SRC) $(UTILS_SRC)
HEADERS   = $(TESTER_HEADER) $(VECTOR_HEADER) $(STACK_HEADER) $(MAP_HEADER) $(SET_HEADER) $(UTILS_HEADERS) $(ITERATOR_TRAITS)

OBJ			= $(SOURCES:%.cpp=$(OBJDIR)/%.o)

# Colors:
GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
GRAY		=	\e[33;2;37m
PURPLE		=	\e[35;5;141m
BLUE		=	\e[34;5;75m
WHITE		=	\e[97;5;255m
RED			=	\e[91;5;196m
RESET		=	\e[0m

# Symbols:
SUCCESS		=	\e[92;5;118m[ SUCCESS ]\e[0m
ERROR		=	\e[91;5;196m[ ERROR ]\e[0m
WARNING		=	\e[93;5;226m[ WARNING ]\e[0m
INFO		=	${PURPLE}[ INFO ]${RESET}

# Styles:
CURSIVE		=	\e[33;3m
BOLD		=	\e[33;1m
UNDERLINE	=	\e[33;4m
CROSS		=	\e[33;9m


#Debug
ifeq ($(DEBUG), 1)
   OPTS = -g
endif

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	@$(CC) $(INCLUDES) $(CXXFLAGS) $(OBJ) $(OPTS) -o $(NAME)
	@printf "\n\n$(SUCCESS) $(GREEN)- Executable ready: $(BOLD)$(UNDERLINE)${RED}$(NAME)$(RESET)\n\n"

$(OBJDIR)/%.o: %.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	@printf "${CURSIVE}${GRAY}	- Making object file: ${BOLD}${GREEN}%-20s ${RESET}\r" $(notdir $@)
	@$(CC) $(INCLUDES) $(CXXFLAGS) $(OPTS) -c $< -o $@

$(LIB): $(OBJ)
	@printf "${INFO} - Making ${BOLD}${UNDERLINE}${WHITE}libft${RESET}...\n"
	@mkdir -p $(dir $@)
	@ar rc $(LIB) $(OBJ)

clean:
	@$(RM) $(OBJDIR) $(OBJ)
	@printf "\n${INFO} - Object files ${BOLD}${UNDERLINE}${WHITE}removed${RESET}.\n"

fclean: clean
	@$(RM) $(NAME) $(VEC_OUT) $(STACK_OUT) $(MAP_OUT) $(SET_OUT) $(LIB_DIR)
	@printf "${INFO} - Executable [${BOLD}${UNDERLINE}${RED}${NAME}${RESET}] removed.$(RESET)\n\n"

re: fclean all
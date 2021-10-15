COMPILER = clang++
FLAGS = --std=c++98 -Wall -Wextra -Werror -fsanitize=address
FILES = maptest.cpp
OUTPUT = vector.out

all : $(OUTPUT)

$(OUTPUT):
	@$(COMPILER) $(FLAGS) $(FILES) -o $(OUTPUT)

clean:
	rm $(OUTPUT)

re: clean all
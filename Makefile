NAME = ush

SRCS = src/*.c

LIB = libmx/libmx.a

CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -ledit

all: install

install: 
	@make -C libmx/
	@clang $(CFLAGS) $(SRCS) $(LIB) -o $(NAME)

uninstall:
	@rm -rf $(NAME)

clean:
	@rm -rf $(LIB)	
cl:
	@make uninstall
	@clang $(CFLAGS) $(SRCS) $(LIB) -o $(NAME)

reinstall:
	@make uninstall
	@make

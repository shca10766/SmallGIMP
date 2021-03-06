CC=g++ -std=c++11 -Wall -Wextra -Werror -Wno-sign-compare -O2
clean:
	rm -f *.o main

main: clean
	g++ *.cpp *.c -o main `pkg-config --cflags --libs opencv`

SRC = src/main.cpp src/RenderWindow.cpp src/TileMap.cpp src/Player.cpp src/EventWindow.cpp src/tools.cpp
OBJ = ${SRC:.cpp=.o}
INC = include/

CXX = g++
CFLAGS = -Wall -Werror -Wextra -O3
USELIB = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image #-mwindows
SDLINC = SDL2/x86_64-w64-mingw32/include
SDLLIB = SDL2/x86_64-w64-mingw32/lib

NAME = bin/SDLGAME.exe

all: ${NAME}

${NAME}: ${OBJ}
	${CXX} ${OBJ} -I${SDLINC} -I${INC} -L${SDLLIB} ${USELIB} -o ${NAME}

%.o: %.cpp
	${CXX} -c ${CFLAGS} $< -I${SDLINC} -I${INC} -o $@

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

re: clean fclean ${NAME}

.PHONY: clean fclean re

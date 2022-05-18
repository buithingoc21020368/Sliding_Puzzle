All:
	g++ source/*.cpp -ISDL2/include/SDL2 -LSDL2/lib -Iinclude -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o Sliding-Puzzle.exe
all:
	g++ -w -ISDL2\include -LSDL2\lib -o Sliding_Puzzle *.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
all:
	g++ -I"Libraries/SDL2/include" -I"Libraries/SDL2_image/include" -I"Libraries/SDL2_mixer/include"\
	 	-I"Libraries/SDL2_ttf/include" -I"Libraries/SQLite3/include" -L"Libraries/SDL2/lib"\
		-L"Libraries/SDL2_image/lib" -L"Libraries/SDL2_mixer/lib" -L"Libraries/SDL2_ttf/lib"\
	  	-o "Executables/Play.exe" "Source/Main.cpp" "Executables/SQLite3.dll" -lmingw32 -lSDL2main\
		-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf\
		\
		\
		-I"Source" -I"Source/physics" -I"Source/renderables" -I"Source/database" -I"Source/temp"
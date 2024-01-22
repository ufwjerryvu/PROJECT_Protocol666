# Directories
SDL_DIR := Libraries/SDL2
SDL_IMG_DIR := Libraries/SDL2_image
SDL_MIX_DIR := Libraries/SDL2_mixer
SDL_TTF_DIR := Libraries/SDL2_ttf
SQLITE_DIR := Libraries/SQLite3

SRC_DIR := Source

EXE_DIR := Executables

# Compiler and flags
CC := g++
CFLAGS := -I$(SDL_DIR)/include -I$(SDL_IMG_DIR)/include -I$(SDL_MIX_DIR)/include -I$(SDL_TTF_DIR)/include -I$(SQLITE_DIR)/include -I$(SRC_DIR)
LDFLAGS := -L$(SDL_DIR)/lib -L$(SDL_IMG_DIR)/lib -L$(SDL_MIX_DIR)/lib -L$(SDL_TTF_DIR)/lib

LIBS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
# Targets
all: Subsystems Executable Clean

# Compiling the systems object to run other things (no linking)
Subsystems:
	$(CC) -c $(SRC_DIR)/Systems.cpp $(CFLAGS) $(LDFLAGS) $(LIBS)

# Compiling the systems object with main
Executable:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXE_DIR)/Play.exe $(SRC_DIR)/Main.cpp Systems.o $(EXE_DIR)/SQLite3.dll $(LIBS)

# Delete all object files
Clean:	
	del *.o
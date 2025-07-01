# Cross-platform Makefile for Protocol 666
# Supports both macOS and Windows builds

# Detect OS
ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
    # Additional Windows detection
    UNAME_S := Windows
else
    UNAME_S := $(shell uname -s 2>/dev/null || echo Unknown)
    ifeq ($(UNAME_S),Darwin)
        DETECTED_OS := macOS
    else ifeq ($(UNAME_S),Linux)
        DETECTED_OS := Linux
    else
        DETECTED_OS := Unix
    endif
endif

# Common settings
SRC_DIR = Source
EXE_DIR = Executables
BUILD_DIR = Build

# Project include paths (common to both platforms)
PROJECT_CFLAGS = -I$(SRC_DIR) \
                 -I$(SRC_DIR)/physics \
                 -I$(SRC_DIR)/renderables \
                 -I$(SRC_DIR)/database \
                 -I$(SRC_DIR)/pages \
                 -I$(SRC_DIR)/creators \
                 -I$(SRC_DIR)/interfaces \
                 -I$(SRC_DIR)/characters \
                 -I$(SRC_DIR)/animators \
                 -I$(SRC_DIR)/terrain \
                 -I$(SRC_DIR)/projectiles

# Platform-specific settings
ifeq ($(DETECTED_OS),Windows)
    # Windows settings
    CC = g++
    EXE = "Protocol 666.exe"
    
    # Library directories
    SDL_DIR = Libraries/SDL2
    SDL_IMG_DIR = Libraries/SDL2_image
    SDL_MIX_DIR = Libraries/SDL2_mixer
    SDL_TTF_DIR = Libraries/SDL2_ttf
    SQLITE_DIR = Libraries/SQLite3
    
    # Windows-specific flags
    SDL_CFLAGS = -I$(SDL_DIR)/include -I$(SDL_IMG_DIR)/include -I$(SDL_MIX_DIR)/include -I$(SDL_TTF_DIR)/include
    SQLITE_CFLAGS = -I$(SQLITE_DIR)/include
    CFLAGS = $(SDL_CFLAGS) $(SQLITE_CFLAGS) $(PROJECT_CFLAGS) -std=c++17 -g
    
    LDFLAGS = -L$(SDL_DIR)/lib -L$(SDL_IMG_DIR)/lib -L$(SDL_MIX_DIR)/lib -L$(SDL_TTF_DIR)/lib
    LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lsqlite3
    
    # Windows-specific source files
    SRCS = $(shell find $(SRC_DIR) -name '*.cpp' | grep -v Main.cpp)
    OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
    
    # Commands
    MKDIR = mkdir
    RM = del /Q
    RMDIR = rmdir /S /Q
    
else
    # macOS/Linux settings
    CC = clang++
    EXE = Protocol666
    
    # Homebrew paths for macOS
    SDL_LIBS = -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
    SDL_CFLAGS = -I/opt/homebrew/include/SDL2
    SQLITE_CFLAGS = -I/opt/homebrew/opt/sqlite/include
    
    CFLAGS = $(SDL_CFLAGS) $(SQLITE_CFLAGS) $(PROJECT_CFLAGS) \
             -std=c++17 -g -fsanitize=address 
    
    LIBS = $(SDL_LIBS) -L/opt/homebrew/opt/sqlite/lib -lsqlite3 -fsanitize=address
    
    # Unix-style source files
    SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
    OBJS = $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SRCS:.cpp=.o))
    
    # Commands
    MKDIR = mkdir -p
    RM = rm -f
    RMDIR = rm -rf
endif

# Build rules
all: $(EXE_DIR)/$(EXE)

ifeq ($(DETECTED_OS),Windows)
# Windows build process
$(EXE_DIR)/$(EXE): compile-sources compile-icon link-objects clean-temp
	@echo "Windows build completed: $(EXE_DIR)/$(EXE)"

compile-sources:
	@echo "Compiling source files for Windows..."
	$(CC) -c $(SRCS) $(CFLAGS) $(LDFLAGS) $(LIBS)

compile-icon:
	@echo "Compiling Windows resources..."
	windres $(SRC_DIR)/Info.rc -O coff -o $(SRC_DIR)/Info.res

link-objects:
	@echo "Linking objects for Windows..."
	@$(MKDIR) $(EXE_DIR) 2>nul || echo.
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXE_DIR)/$(EXE) $(SRC_DIR)/Main.cpp *.o $(SRC_DIR)/Info.res $(EXE_DIR)/SQLite3.dll $(LIBS) -mwindows

clean-temp:
	@echo "Cleaning temporary files..."
	-$(RM) *.o 2>nul

else
# macOS/Linux build process
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(MKDIR) $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXE_DIR)/$(EXE): $(OBJS)
	@$(MKDIR) $(EXE_DIR)
	$(CC) $^ $(LIBS) -o $@
	@echo "macOS/Linux build completed: $(EXE_DIR)/$(EXE)"
endif

clean:
ifeq ($(DETECTED_OS),Windows)
	-$(RM) *.o 2>nul
	-$(RM) $(SRC_DIR)\Info.res 2>nul
	-$(RM) $(EXE_DIR)\$(EXE) 2>nul
else
	$(RMDIR) $(BUILD_DIR)
	$(RM) $(EXE_DIR)/$(EXE)
endif
	@echo "Clean completed for $(DETECTED_OS)"

info:
	@echo "Detected OS: $(DETECTED_OS)"
	@echo "Compiler: $(CC)"
	@echo "Executable: $(EXE_DIR)/$(EXE)"

.PHONY: all clean info compile-sources compile-icon link-objects clean-temp
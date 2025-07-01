# Cross-platform Makefile for Protocol 666
# Supports Windows, macOS, and Linux

ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
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

# Project include paths (project-level and are common to all platforms)
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
    # Windows with MinGW/MSYS2
    CC = g++
    EXE = "Protocol 666.exe"
    
    # Library directories
    SDL_DIR = Libraries/SDL2
    SDL_IMG_DIR = Libraries/SDL2_image
    SDL_MIX_DIR = Libraries/SDL2_mixer
    SDL_TTF_DIR = Libraries/SDL2_ttf
    SQLITE_DIR = Libraries/SQLite3
    
    # Windows-specific flags
    SDL_CFLAGS = -I$(SDL_DIR)/include \
              -I$(SDL_IMG_DIR)/include \
              -I$(SDL_MIX_DIR)/include \
              -I$(SDL_TTF_DIR)/include

    SQLITE_CFLAGS = -I$(SQLITE_DIR)/include
    CFLAGS = $(SDL_CFLAGS) $(SQLITE_CFLAGS) $(PROJECT_CFLAGS)
    
    LDFLAGS = -L$(SDL_DIR)/lib -L$(SDL_IMG_DIR)/lib -L$(SDL_MIX_DIR)/lib -L$(SDL_TTF_DIR)/lib
    LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
    
    # Windows-specific source compilation
    SUBSRC_CPP = $(SRC_DIR)/*.cpp \
              $(SRC_DIR)/renderables/*.cpp \
              $(SRC_DIR)/physics/*.cpp \
              $(SRC_DIR)/database/*.cpp \
              $(SRC_DIR)/pages/*.cpp \
              $(SRC_DIR)/creators/*.cpp \
              $(SRC_DIR)/interfaces/*.cpp \
              $(SRC_DIR)/characters/*.cpp \
              $(SRC_DIR)/animators/*.cpp \
              $(SRC_DIR)/terrain/*.cpp \
              $(SRC_DIR)/projectiles/*.cpp
    
    # Windows file handling
    MKDIR_P = @if not exist "$(@D)" mkdir "$(@D)" 2>nul || echo.
    RM = del /Q /F
    RMDIR = rmdir /S /Q
    NULL_REDIRECT = 2>nul
    
else ifeq ($(DETECTED_OS),macOS)
    # macOS settings
    CC = clang++
    EXE = Protocol666
    
    # Homebrew paths
    BREW_PREFIX = /opt/homebrew
    SDL_LIBS = -L$(BREW_PREFIX)/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
    SDL_CFLAGS = -I$(BREW_PREFIX)/include/SDL2
    SQLITE_CFLAGS = -I$(BREW_PREFIX)/opt/sqlite/include
    
    CFLAGS = $(SDL_CFLAGS) $(SQLITE_CFLAGS) $(PROJECT_CFLAGS) \
             -std=c++17 -g -fsanitize=address
    
    # Add -Wall -Werror later.
    LIBS = $(SDL_LIBS) -L$(BREW_PREFIX)/opt/sqlite/lib -lsqlite3 -fsanitize=address
    
    # Unix commands
    MKDIR_P = @mkdir -p $(@D)
    RM = rm -f
    RMDIR = rm -rf
    NULL_REDIRECT = 2>/dev/null
    
else
    # Linux and other Unix-like systems
    CC = g++
    EXE = Protocol666
    
    # Use pkg-config for better portability
    SDL_CFLAGS = $(shell pkg-config --cflags sdl2 SDL2_image SDL2_mixer SDL2_ttf 2>/dev/null || echo -I/usr/include/SDL2)
    SQLITE_CFLAGS = $(shell pkg-config --cflags sqlite3 2>/dev/null || echo)
    
    SDL_LIBS = $(shell pkg-config --libs sdl2 SDL2_image SDL2_mixer SDL2_ttf 2>/dev/null || echo -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf)
    SQLITE_LIBS = $(shell pkg-config --libs sqlite3 2>/dev/null || echo -lsqlite3)
    
    CFLAGS = $(SDL_CFLAGS) $(SQLITE_CFLAGS) $(PROJECT_CFLAGS) -std=c++17 -g
    LIBS = $(SDL_LIBS) $(SQLITE_LIBS)
    
    # Unix commands
    MKDIR_P = @mkdir -p $(@D)
    RM = rm -f
    RMDIR = rm -rf
    NULL_REDIRECT = 2>/dev/null
endif

# Find source files - cross-platform approach
SOURCES_CMD = find $(SRC_DIR) -name "*.cpp" $(NULL_REDIRECT)
SRCS = $(shell $(SOURCES_CMD) || echo "$(SRC_DIR)/*.cpp $(SRC_DIR)/*/*.cpp")
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(filter-out $(SRC_DIR)/Main.cpp $(SRC_DIR)/main.cpp,$(SRCS)))

# Build rules
all: $(EXE_DIR)/$(EXE)

# Object file compilation - works for all platforms
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(MKDIR_P)
	$(CC) $(CFLAGS) -c $< -o $@

# Platform-specific linking
ifeq ($(DETECTED_OS),Windows)
$(EXE_DIR)/$(EXE): compile-sources compile-icon link-objects clean-temp
	@echo "Windows build completed: $(EXE_DIR)/$(EXE)"

compile-sources:
	@echo "Compiling source files for Windows..."
	$(CC) -c $(SUBSRC_CPP) $(CFLAGS) $(LDFLAGS) $(LIBS)
	-$(RM) Main.o $(NULL_REDIRECT) || echo.

compile-icon:
	@echo "Compiling Windows resources..."
	windres $(SRC_DIR)/Info.rc -O coff -o $(SRC_DIR)/Info.res

link-objects:
	@echo "Linking objects for Windows..."
	@if not exist "$(EXE_DIR)" mkdir "$(EXE_DIR)" $(NULL_REDIRECT) || echo.
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXE_DIR)/$(EXE) $(SRC_DIR)/Main.cpp *.o \
              $(SRC_DIR)/Info.res \
              $(EXE_DIR)/SQLite3.dll \
              $(LIBS) -mwindows

clean-temp:
	@echo "Cleaning temporary files..."
	-$(RM) *.o $(NULL_REDIRECT) || echo.

else
$(EXE_DIR)/$(EXE): $(OBJS)
	@mkdir -p $(EXE_DIR)
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/Main.cpp $(OBJS) $(LIBS)
endif

clean:
ifeq ($(DETECTED_OS),Windows)
	-$(RM) $(BUILD_DIR)\*.o $(NULL_REDIRECT) || echo.
	-$(RM) $(SRC_DIR)\Info.res $(NULL_REDIRECT) || echo.
	-$(RM) $(EXE_DIR)\$(EXE) $(NULL_REDIRECT) || echo.
	-$(RMDIR) $(BUILD_DIR) $(NULL_REDIRECT) || echo.
else
	-$(RMDIR) $(BUILD_DIR) $(NULL_REDIRECT)
	-$(RM) $(EXE_DIR)/$(EXE) $(NULL_REDIRECT)
endif
	@echo "Clean completed for $(DETECTED_OS)"

info:
	@echo "Detected OS: $(DETECTED_OS)"
	@echo "System: $(UNAME_S)"
	@echo "Compiler: $(CC)"
	@echo "Executable: $(EXE_DIR)/$(EXE)"
	@echo "Build directory: $(BUILD_DIR)"

.PHONY: all clean info compile-sources compile-icon link-objects clean-temp
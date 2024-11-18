# Protocol 666 🎮

## Introduction 📚

Protocol 666 is a 2D game developed using C++ and SDL. It features a unique blend of action and strategy, backed by a robust SQLite database for game state management. In short, this is a development project spearheaded by a small team of university students for fun. 

### Dependencies 📦
**Required libraries**:
```
SDL2 (>= 2.0.14)
SDL2_image
SDL2_mixer
SDL2_ttf
SQLite3 (>= 3.35.0)
```
The libraries listed here should already come with the repository. They can be found in the `Libraries/` directory. 

**Development tools**:
```
GNU/GCC C++ Compiler
GNU/GCC Make
Git
```

Currently, it is only working on Windows but we are working to get the game to run on MacOS and Linux. 

### Playing ⚙️
Make sure you are in the base directory containing the Makefile and make sure you have all the dependencies and all of the GNU/GCC C++ compilers/linkers in place. 

Then, to compile, just run:
```
make
```
This should create an executable file in your `Executables/` directory. You need to change directory into the folder and run (on Windows):

```
./"Protocol 666.exe"
```
Don't forget to do a nice little `git clone` before you do all this. 

### Contributing 🤝
Make sure you read the style guide `STYLE.md` before you write any code or decide to help out with the project.

### Authors 👤

- **Programmers**: Jerry Vu, Kenny Nguyen, and An Luu.
- **Art and design**: An Luu.

### Acknowledgments 🙏

- SDL2 development team
- SQLite3 development team
- Open-source community

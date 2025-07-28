# Game Programming 25
Repository for the IT University of Copenhagen Game Programming course.

## Setup
You are free to use any development setup you want, as long as you can confortably build and debug CMake projects.

If you don't have an IDE setup, you can follow this quick platform-independent setup:
1. download and install [CMake](https://cmake.org/download/) (for mac users, use [brew](https://brew.sh/) instead of downloading from the website)
2. download [VSCode](https://code.visualstudio.com/download) and install the C/C++ Extension Pack and the CMake Tools Pack (the ones from Microsoft)
4. clone the exercise repository `git clone --recurse-submodules https://github.com/Chris-Carvelli/game-programming-25.git` 
5. open repository in VSCode
6. in `Preferences->Settings`, search for `cmake path` and replace the content with the path to your CMake executable (you can find in typing `where cmake` or `which cmake` on the command line)
7. restart the editor

After reopening the editor, you should see all available targets in the cmake tab, in the `Project Outline` section.

Build and run them from there, or set one to be the "default" target (`right-click->Set Launch/Debug Target`)

## Before the course start
- [ ] setup and test you development environment
- [ ] build and run the files in the `examples` folder
- [ ] be sure to befamiliar with the basics of C/C++ (syntax, control flow, variable and functions, structs/arrays/enums/unions/, pointers). You can check the [course page](https://learnit.itu.dk/course/view.php?id=3024686#section-1) for additional resources on this
- [ ] refresh a bit of linear algebra and trigonometry

I've setu up a folder for you (`playground`) if you want to test things out. Just create a `.cpp` file in there and reconfigure the CMake project, and you can try everything that doesn't involve external dependencies.

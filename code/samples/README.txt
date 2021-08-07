A small project should contain at least these parts:
1. README file.
2. project files, may include traditional Makefile, autoconfig files.
   or mordern CMakeLists.txt (CMake).
3. source files.
4. test scripts and test cases.

Before you say it is done, test your program intensively.

Usage:

$ export prog=1-21; make; make test;

Or

$ prog=1-21 make

It is a good start to learn some basic techniques from this
sample:

1. Write basic makefiles. Nowadays, CMake is a good choice.
2. Write program to read from stdin and write to stdout.
   It can then support pipes: cat foo.c | a.out | ...
3. Write shell scripts to test the cmd line programs.

As for the editors or IDEs, many improvements are seen through
the years. 

1. Basic Vim or emacs.
2. Vim 8.0 with powerful plugins.
3. CLion, VSCode are more popular.

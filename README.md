# Advanced Programming Course Material (Engineering Science)

Assignments and the final project from the Advanced Programming course in Engineering Science. The work is in C++, starting with command-line programs and moving on to a music player and an SFML game. The assignment sheets are in Persian.

## Coursework

| Work | Topic |
| --- | --- |
| [CA1](assignments/ca1) | A task manager with dependencies and task states |
| [CA2](assignments/ca2) | Backtracking: Sudoku, dictionary anagrams, and eight queens with blocked squares |
| [CA3](assignments/ca3) | A package installer with nested dependencies, rollback, and logging |
| [CA4 — Terminal Music Player](https://github.com/SMani24/Terminal-Music-Player) | A terminal interface for a music library, playlists, and audio playback |
| [Final project — Doodle Jump](https://github.com/SMani24/Doodle-Jump) | An endless jumping game built with SFML |

The assignment folders contain the source and available test inputs. Assignment sheets are under `docs/`; earlier Sudoku attempts are kept separately in CA2. [Clean code notes](references/clean_code.pdf) are under `references/`, and the original submission ZIPs are under `archives/submissions/`.

## Getting the projects

The music player and Doodle Jump have their own repositories and histories. This repository includes them as Git submodules:

```bash
git clone --recurse-submodules https://github.com/SMani24/Advanced-Programming-Course-Material-Engineering-Science.git
```

If you have already cloned it:

```bash
git submodule update --init --recursive
```

## Building

For the command-line assignments, use a C++ compiler such as `g++`. CA1 and CA2 can be compiled directly:

```bash
cd assignments/ca1
g++ -std=c++17 CA1.cpp -o task_manager
./task_manager < tests/in1.txt
```

```bash
cd assignments/ca2
g++ -std=c++17 problem_1.cpp -o sudoku
```

Compile `problem_2.cpp` and `problem_3.cpp` separately for the other CA2 problems. Each program reads from standard input.

CA3 has a Makefile and a local judge:

```bash
cd assignments/ca3
make
bash localJudge.sh
```

CA3 builds, but the included judge currently reports 0/100 passing tests for the submitted implementation.

The [music player README](assignments/ca4/Terminal-Music-Player/README.md) and [Doodle Jump README](projects/Doodle-Jump/README.md) cover their dependencies and controls.

Full repository backups are kept locally in `archives/backups/`. They are excluded from Git because the projects and their histories are already available in the linked repositories.

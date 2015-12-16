# Mazemaker
Mazemaker creates intricate, hard-to-solve mazes that always have only one solution path.
### Installing Mazemaker
For installation on Debian machines, copy the following into the command line:
```
wget -q http://git.io/v0rRH -O /tmp/Mazemaker && bash /tmp/Mazemaker
```

### Using Mazemaker
You may provide maze.sh with two command line arguments that represent the number of rows and colums of cells for the maze.
If no arguments are provided, the default is 60 X 80.

##### Example
The following code produces a 100 X 100 cell maze:
```
UNIX> ./maze.sh 100 100
UNIX> ls
UNIX> Mazemaker_support/  maze_path.png  maze.png  maze.sh*
```
- *maze.png* is the file containing just the maze ready to be sovled.<br>
- *maze_path.png* is the same image overlaid with the solution path.

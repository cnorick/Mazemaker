# Mazemaker
Mazemaker creates intricate, hard-to-solve mazes that always have only one solution path.
### Installing Mazemaker
For installation on Debian machines, copy the following into the command line:
```bash
wget -q http://git.io/v0rRH -O /tmp/Mazemaker && sudo bash /tmp/Mazemaker
```
___
### Using Mazemaker
You may provide maze.sh with two command line arguments that represent the number of rows and colums of cells for the maze.
If no arguments are provided, the default is 60 X 80.
###### Creating a Maze
The following code produces a 100 X 100 cell maze:
```bash
UNIX> mazemaker 100 100
UNIX> ls
      maze_path_100x100.png  maze_100x100.png
```
- *maze_100x100.png* is the image of just the maze ready to be sovled
  - This image can be printed and the maze can be solved
- *maze_path_100x100.png* is the same image overlaid with the solution path

###### Deleting Mazes
The following code deletes all maze and path files in the current directory:
```bash
UNIX> ls
      maze_path_100x100.png  maze_100x100.png
UNIX> mazemaker --clean
UNIX> ls
UNIX>
```

###### Uninstalling Mazemaker
To uninstall Mazemaker, use the --uninstall option:
```bash
mazemaker --uninstall
```
This removes all of the support files for Mazemaker. However, it does not delete any maze files made by Mazemaker.

#! /bin/sh

R=$1
C=$2
folder=./Mazemaker_support

cd $folder

./mazemake ${R:=60} ${C:=80} > maze.txt
./mazesolve < maze.txt > path.txt 

./mazeshow 10 maze.txt | convert - maze.png
./mazeshow 10 maze.txt path.txt | convert - maze_path.png

mv maze.png maze_path.png ..
rm maze.txt path.txt

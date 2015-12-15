# downloads the required files, make the exacutable, and deletes the downloaded files

URL="https://github.com/cnorick/Mazemaker.git"
folder="/tmp/Mazesolver"
currentDir=`pwd`

mkdir Mazemaker_support

echo downloading source
git clone $URL $folder

cd $folder
make

cp game.sh $currentDir
cp mazemake mazesolve mazeshow $currentDir/Mazemaker_support

cd $curentDir

echo deleting source
rm -rf $folder

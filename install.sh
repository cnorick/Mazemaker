# downloads the required files, make the exacutable, and deletes the downloaded files

URL="https://github.com/cnorick/Mazemaker.git"
folder="/tmp/Mazesolver"
currentDir=`pwd`

mkdir mazemaker_support

echo downloading source
git clone $URL $folder

cd $folder
make

cp mazemaker $currentDir
cp mazemake mazesolve mazeshow $currentDir/mazemaker_support

cd $curentDir

echo deleting source
rm -rf $folder

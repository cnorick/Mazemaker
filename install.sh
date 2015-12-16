# downloads the required files, make the exacutable, and deletes the downloaded files

URL="https://github.com/cnorick/Mazemaker.git"
folder="/tmp/Mazesolver"
Dir="/opt/Mazemaker"


install(){
	mkdir $Dir;
	cd $Dir;
	mkdir mazemaker_support;

	echo downloading source...;
	git clone $URL $folder;
	cd $folder/source;
	make;

	cp mazemake mazesolve mazeshow $Dir/mazemaker_support;
	cd ..;
	cp mazemaker $Dir;

	ln -s $Dir/mazemaker /bin;

	echo deleting source...;
	rm -rf $folder;
}

clean(){
	if [ -e $Dir ]; then
		rm -fr $Dir;
	fi;

	if [ -L /bin/mazemaker ]; then
		rm -fr /bin/mazemaker;
	fi;
}



if [ $USER != "root" ]; then
echo must run as root;
exit;
fi;

clean;
install;

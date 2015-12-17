# downloads the required files, make the exacutable, and deletes the downloaded files

URL="https://github.com/cnorick/Mazemaker.git"
tmp="/tmp/Mazesolver"
Dir="/opt/Mazemaker"


install_log(){
	echo -e "\n\033[1;32mMAZEMAKER INSTALL: $*\033[m";
}

install_error(){
	echo -e "\n\033[1;37;41mMAZEMAKER INSTALL ERROR: $*\033[m";
	exit 1;
}

create_directories(){
	install_log "Creating Mazemaker directories";
	if [ ! -d "$Dir/mazemaker_support" ]; then
		sudo mkdir -p "$Dir/mazemaker_support" || 
			install_error "Couldn't create directory '$Dir/mazemaker_support'";
	fi
}

compile_source(){
	install_log "Compiling source";
	
	if [ -d $tmp ]; then
		sudo rm -rf $tmp;
	fi;

	sudo git clone $URL $tmp || install_error "Couldn't fetch source";
	cd $tmp/source;
	sudo make || install_error "Could not compile source";

	sudo cp mazemake mazesolve mazeshow $Dir/mazemaker_support ||
		install_error "Could not copy support files to $Dir";
	cd ..;
	sudo cp mazemaker $Dir || install_error "Could not copy support files to $Dir";

	if [ ! -L /bin/mazemaker ]; then
		sudo ln -s $Dir/mazemaker /bin ||
			install_error "Could not link executable in /bin/mazemaker";
	fi;

	sudo rm -rf $tmp;
}

update_system_packages(){
	install_log "Updating packages";
	sudo apt-get update || install_error "Couldn't update package list";
	sudo apt-get upgrade || install_error "Couldn't upgrade packages";
}

install_dependencies(){
	install_log "Installing required packages";
	sudo apt-get install imagemagick build-essential || 
		install_error "Couldn't install dependencies";
}



create_directories;
update_system_packages;
install_dependencies;
compile_source;

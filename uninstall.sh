#!/bin/bash

Dir="/opt/Mazemaker"

install_log(){
        echo -e "\n\033[1;32mMAZEMAKER INSTALL: $*\033[m";
}

install_error(){
        echo -e "\n\033[1;37;41mMAZEMAKER INSTALL ERROR: $*\033[m";
        exit 1;
}

remove_binary(){
	if [ -L /bin/mazemaker ]; then
		sudo rm -fr /bin/mazemaker || install_error "Unable to remove link in /bin/mazemaker";
	fi;
}

remove_directory(){
	if [ -d $Dir ]; then
		sudo rm -fr $Dir;
	fi
}

success(){
	install_log "Mazemaker successfully uninstalled";
}

remove_binary;
remove_directory;
success;

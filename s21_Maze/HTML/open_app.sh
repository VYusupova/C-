#!/bin/bash

if [ "$1" != "app://" ]; then
	app=${1#app://}
	nohup "$app" &>/dev/null &
else	
	cd ~/s21_maze/
	gnome-terminal -- ./s21_maze.o
fi

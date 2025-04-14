#!/usr/bin/env bash

MAIN_DIR=$(pwd)
INCLUDE="${MAIN_DIR}/include"

CXX="g++"
CXX_FLAGS="-g -Wall -Wextra -I${INCLUDE}"

build(){
	echo "********************************"
	echo  "[BUILDING] Tiny VM"
	mkdir -p build
	cd src
	obj_file=""
	for file in *.cxx; do
		obj_file="${file%.cxx}.o"

		echo "  [G++] " $file " -> " ${obj_file}
		${CXX} ${CXX_FLAGS} -o ../build/${obj_file} -c ${file}
	done
	cd ../build

	echo "********************************"
	echo "[LINKING]"
	files_to_link=""
	for file in *.o; do
		echo "  [G++] " $file
		files_to_link+=" ${file}"
	done

		${CXX} ${files_to_link} -o "./main"
		echo "********************************"
		echo "[G++] Executable -> ./build/main"
		echo "********************************"

	exit
}

run(){
	echo "********************************"
	echo  "[RUNNING] Tiny VM"
	echo "********************************"
	./build/main
	exit
}

clean(){
	echo  "[CLEANING] Tiny VM"
	for file in ./build/*; do
		echo "  [RM] " ${file}
	done
	rm -rf ./build/*
	exit
}

if [[ -z $1 ]]; then
	echo "[ERROR] NO ARGS"
	exit
fi

if [[ $1 == "--build" ]]; then
	if [[ -n $2 ]]; then
		CXX_FLAGS+=" "
		CXX_FLAGS+=${@:2}
	fi
	build
	exit
fi

if [[ $1 == "--run" ]]; then
		run
		exit
fi

if [[ $1 == "--clean" ]]; then
	clean
	exit
fi

if [[ $1 == "--help" ]]; then
	echo "--build [pass in compile flags]"
	echo "--run"
	echo "--clean [cleans build/]"
	echo "NOTE: This script doesnt build debug and main in seperate directories."
	echo "      It will rebuild the entire project regardless if nothing changed."
	echo "      passing in compile flags to --build like -DDEBUG will still end up in ./build/ and not in ./debug"
	echo "      and --run will execute the latest elf file in ./build/ ."
	echo "      Use the makefile for more control."
	exit
fi

echo "[ERROR] UNKOWN" $1



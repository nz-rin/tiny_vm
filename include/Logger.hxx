#ifndef LOGGER_H
#define LOGGER_H

#include <string.h>
#include <iostream>

template<typename T>
void log_info(T &&info){
	std::cout << info << "\n";
}

template<typename T, typename ... args>
void log_info(T &&first, args ... rest){
	std::cout << first << ' ';
	log_info(std::forward<args>(rest) ...);
}

template<typename T>
void log_error(T &&error){
	std::cerr << error << "\n";
}

template<typename T, typename ...args>
void log_error(T &&first, args ...rest){
	std::cerr << first << ' ';
	log_error(std::forward<args>(rest)...);
}

template<typename T, typename ...args>
void log_error_and_exit(T &&first, args ...rest){
	std::cerr << first << ' ';
	log_error(std::forward<args>(rest)...);
	exit(EXIT_FAILURE);
}

template<typename T>
void log_error_and_exit(T &&first){
	std::cerr << first << '\n';
	exit(EXIT_FAILURE);
}


template<typename T, typename ...args>
void log_error_and_sterror(T &&first, args ...rest){
	std::cerr << first << ' ' << strerror(errno) << ' ';
	log_error(std::forward<args>(rest)...);
}

#endif

#include <iostream>

using std::cout;

void error_callback(int error_code, const char* discription) {
	cout << "[ERROR]: " << error_code << ": " << discription << "\n";
} 

void info_callback(const char* msg) {
	cout << "[INFO]: " << msg << "\n";
}
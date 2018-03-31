#ifndef FILE_HANLDER
#define FILE_HANDLER

#include <cstdio>
#include <iostream>
using namespace std;

struct file_handler {
	file_handler() : fptr(NULL) { }
	file_handler(string f_name) {
		open(f_name);
	}
	string get_next_word() {
		char ch;
		while(true) {
			ch = fgetc(fptr);
			if(ch == EOF) return "";
			if(ch >= 'a' and ch <= 'z') break;
		}
		string res;
		while(ch >= 'a' and ch <= 'z') {
			res.push_back(ch);
			ch = fgetc(fptr);
		}
		// apply processing here
		return res;
	}
	void open(string f_name) {
		fptr = fopen(f_name.c_str(), "r");
	}
	void close() {
		if(fptr != NULL) fclose(fptr), fptr = NULL;
	}
	~file_handler() {
		close();
	}
private:
	FILE* fptr;
};

#endif

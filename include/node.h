#ifndef FILE_NODE
#define FILE_NODE

#include <iostream>
#include <vector>
#include <cassert>
#include <cstring>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

struct node {
	node() : path("-") { }
	node(string _path) : path(_path) {
		struct stat s;
		if(stat(path.c_str(), &s) == 0) {
			if(s.st_mode & S_IFDIR) {
				is_file = false;
			} else if(s.st_mode & S_IFREG) {
				is_file = true;
			} else {
				assert(false);
			}
		} else {
			assert(false);
		}
	}
	vector<node> get_children() const {
		if(is_file) return vector<node>();
		DIR *dir = opendir(path.c_str());
		assert(dir != NULL);
		dirent* entry = NULL;
		vector<node> res;
		string ff = string(path) + "/";
		while((entry = readdir(dir)) != NULL) {
			if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
				// pass
			} else {
				res.push_back(node(ff + string(entry->d_name)));
			}
		}
		return res;
	}
	string get_path() const { return path; }
	bool is_leaf() const { return is_file; }
private:
	bool is_file;
	string path;
	friend ostream& operator<<(ostream &os, const node &n) {
		return os << "-" << (n.is_file ? "f" : "d") << "-> " << n.path;
	}
};

#endif

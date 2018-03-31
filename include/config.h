#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <iostream>

struct config {
	std::vector<std::string> root_dirs;
	int k;
	int num_threads;
};

#endif

#include "Util.hpp"

#include <iostream>
#include <fstream>

std::string GetFileContent(const std::string& path) {
	std::ifstream fin(path);
	if (!fin) {
		std::cerr << "Open file failed: " << path << std::endl;
		return nullptr;
	}

	std::string content;
	std::string line;
	while (fin.good()) {
		std::getline(fin, line);
		content += line + '\n';
	}

	return std::move(content);
}

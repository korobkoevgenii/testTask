#pragma once
#include <iostream>
#include <boost/filesystem/operations.hpp>
#include <vector>
#include <fstream>
#include <algorithm>

enum resultOfCompare {
	EQUAL,
	NOT_EQUAL,
	DIFFERENT_SIZE
};

int getSize(std::string path1);
std::vector<std::string> getAllFiesPaths(std::string folderPaths);
int compareFiles(std::string path1, std::string path2);
std::vector<std::vector<std::string>> compareFolders(std::string folder1, std::string folder2, bool &emptyDirectory);
std::vector<std::string> parser(std::string input);
std::string clearParsedPath(std::string dirtyPath);
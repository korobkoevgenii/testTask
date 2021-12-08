#include "Header.h"
int getSize(std::string path1) {
	int size = boost::filesystem::file_size(path1);
	return size;
}

std::vector<std::string> getAllFiesPaths(std::string folderPaths) {

	boost::filesystem::path directory{ folderPaths };
	std::vector<std::string> filesPaths;
	if (boost::filesystem::is_directory(directory)) {
		boost::filesystem::directory_iterator begin(folderPaths);
		boost::filesystem::directory_iterator end;
		for (; begin != end; ++begin) {
			filesPaths.push_back(begin->path().string());
		}
	}


	return filesPaths;
}
int compareFiles(std::string path1, std::string path2) {
	std::ifstream* file1 = new std::ifstream(path2, std::ios::binary);
	std::ifstream* file2 = new std::ifstream(path2, std::ios::binary);


	if (file1 && file2)
	{
		unsigned long sizefin1 = getSize(path1);
		unsigned long sizefin2 = getSize(path2);

		if (sizefin1 != sizefin2)
			return DIFFERENT_SIZE;
		else {
			char ch1, ch2;
			bool result = false;

			while (file1->get(ch1) && file2->get(ch2))
			{
				if (ch1 != ch2)
				{
					result = true;
					break;
				}
			}

			if (!result)
				return EQUAL;
			else
				return NOT_EQUAL;
		}
	}
	file1->close();
	file2->close();
}
std::vector<std::vector<std::string>> compareFolders(std::string folder1, std::string folder2, bool &emptyDirectory) {
	std::vector<std::vector<std::string>> result;

	std::vector<std::string> filesPaths1 = getAllFiesPaths(folder1);
	std::vector<std::string> filesPaths2 = getAllFiesPaths(folder2);

	if (!filesPaths1.empty() && !filesPaths2.empty()) {
		for (int i = 0; i < filesPaths1.size(); i++) {
			for (int j = 0; j < filesPaths2.size(); j++) {
				if (boost::filesystem::status(filesPaths1[i]).type() != boost::filesystem::directory_file &&
					boost::filesystem::status(filesPaths2[j]).type() != boost::filesystem::directory_file &&
					(compareFiles(filesPaths1[i], filesPaths2[j]) == EQUAL)) {
					std::vector<std::string> duplicate;
					duplicate.push_back(filesPaths1[i]);
					duplicate.push_back(filesPaths2[j]);
					result.push_back(duplicate);
				}
			}

		}
	}
	else
		emptyDirectory = true;
	return result;

}
std::string clearParsedPath(std::string dirtyPath) {
	int i = dirtyPath.size()-1;
	std::string res = dirtyPath;
	while (i != 0 && res[i] == ' ') {
		res.erase(i, 1);
		i--;		
	}
	return res;
	
}
std::vector<std::string> parser(std::string input) {
	int i = 0;

	std::vector<std::string> res;
	bool findPaths = false;
	std::string path("");

	for (int i = 0; i < input.size(); i++) {
		if ((i + 1) != input.size() && input[i] == '-' && input[i + 1] == 'p') {
			if (path != "") {

				res.push_back(path);
				path = "";
			}
			findPaths = true;
			i+=2;
			continue;
		}

		if (findPaths) {
			path = path + input[i];
			if ((i + 1) == input.size())
				res.push_back(path);
			continue;
		}	
		/*else if (input[i] == ' '&& findPaths) {
			findPaths = false;
			res.push_back(path);
			path = "";
		}*/

	}
	return res;
}
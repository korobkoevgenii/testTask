#include "Header.h"

int main() {
	std::string input;

	std::cout << "Hello! this is test task for Open Media!\n";
	std::cout << "If you want to compare two folders and find equals files in them, you need to print there paths like:\n";
	std::cout << "-p C:/yourFolder -p C:/yourSecondFolder\n";
	std::cout << "Sorry, but the program only works with Latin characters :-( \n";
	//-p C:/Users/vicuesoft/Documents -p C:/Users/vicuesoft/testplan -p C:\Program Files\ViCue\VQAnalyzer\samples -p C:/Users/vicuesoft/Downloads
	while (true) {
		std::getline(std::cin, input);
		std::cout << "\n\n";
		std::vector <std::string>folderPaths = parser(input);
		if (folderPaths.size() >= 2) {
			folderPaths[0] = clearParsedPath(folderPaths[0]);
			folderPaths[1] = clearParsedPath(folderPaths[1]);

			bool emptyDirectory = false;

			std::vector<std::vector<std::string>> filesPaths;

			filesPaths = compareFolders(folderPaths[0], folderPaths[1], emptyDirectory);

			if (emptyDirectory)
				std::cout << "\none of folder is empty or path is wrong\n";
			else {
				if (filesPaths.size() == 0)
					std::cout << "\n Can't find equals files";
				else {
					for (int i = 0; i < filesPaths.size(); i++) {
						std::cout << filesPaths[i][0] << " " << filesPaths[i][1] << "\n";
					}
				}
				
			}
		}
		else
			std::cout << "\nMaybe paths is wrong or you enter less then 2 folders paths\n";
	}
	return 0;
}
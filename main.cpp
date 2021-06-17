#include <iostream>
#include <fstream>
#include <sstream>
#include "Element.h"

int main(int argc, char* argv[]) {

	std::cout << "Check text for links" << std::endl;
	std::string text;
	if(argc > 1) {
		std::cout << "Get link from argument" << std::endl;
		text = argv[1];
	}
	else {
		std::cout << "Get default link" << std::endl;
		text = "C:\\Users\\Lukas\\Desktop\\Test\\file.txt";
	}
	//Saves File from text
	std::ifstream myFile(text, std::ios::in);

	//Create object for operations
	Element e;

	if (myFile) {

		for (std::string line; std::getline(myFile, line);) {

			std::cout << line << std::endl;
			if (e.checkIfLink(line)) {
				std::cout << "There is a Link in the line. \n" << std::endl;
				auto links = e.getLinks(line);
				for (auto link : links) {
					e.openLink(link);
				}
				std::cout << "\n";
			}
			else
				std::cout << "There is no Link in the line. \n" << std::endl;
		}
	}
	myFile.close();
	return 0;
}
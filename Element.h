#include <string>
#include <windows.h>
#include <shellapi.h>
#include <iostream>
#include <vector>

class Element
{
private:
	//Acceptable country codes
	std::vector<std::string> endingURL{ ".de", ".com" };

	//Vector for country code positions
	std::vector<std::size_t> positionCountryCodeURL;

	//Gets position of country code
	std::vector<std::size_t> getLinkEndingPosition(std::string line);

	std::vector<std::size_t> getAndClearLinkEndingPosition(std::string line);

public:
	//Opens link in browser
	void openLink(std::string file);

	//Checks if possible link is in given line
	bool checkIfLink(const std::string line);

	//Returns possible links in vector
	std::vector<std::string> getLinks(const std::string line);
};


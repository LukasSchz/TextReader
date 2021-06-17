#include "Element.h"

void Element::openLink(std::string file) {
	ShellExecuteA(0, "open", file.c_str() , 0, 0, SW_SHOW);
}

bool Element::checkIfLink(const std::string line) {
	auto countryCode = getAndClearLinkEndingPosition(line);
	return countryCode.empty() == true ? false : true;
}

std::vector<std::size_t> Element::getLinkEndingPosition(std::string line) {
	std::cout << "getLinkEndingPosition: start " << std::endl;
	for (auto value : endingURL) {
		std::size_t endingURLFinding = line.rfind(value);
		if (endingURLFinding != std::string::npos) {
			positionCountryCodeURL.push_back(endingURLFinding);
			std::cout << "getLinkEndingPosition: add position: " << endingURLFinding << std::endl;
			std::string subLine = line.substr(0, endingURLFinding);
			getLinkEndingPosition(subLine);
		}
	}
	return positionCountryCodeURL;
}

std::vector<std::size_t> Element::getAndClearLinkEndingPosition(std::string line) {
	auto links = getLinkEndingPosition(line);
	positionCountryCodeURL.clear();
	return links;
}

std::vector<std::string> Element::getLinks(const std::string line) {
	std::vector<std::string> links;

	std::vector<std::size_t> positionCountryCodeURL = getAndClearLinkEndingPosition(line);
	if (!positionCountryCodeURL.empty()) {
		for (auto value : positionCountryCodeURL) {
			if (value != std::string::npos) {
				std::string firstPart = line.substr(0, value);
				std::cout << "getLinks: firstPart: " << firstPart << std::endl;

				if (!firstPart.empty()) {
					std::size_t positionLastTab = firstPart.find_last_of(" ");
					std::cout << "getLinks: positionLastTab: " << positionLastTab << std::endl;

					if (positionLastTab != std::string::npos) {
						std::string partWithTheLink = line.substr(positionLastTab + 1);
						std::size_t positionFirstTab = partWithTheLink.find_first_of(" ");
						std::cout << "getLinks: partWithTheLink: " << partWithTheLink << std::endl;
						if (positionFirstTab != std::string::npos) {
							std::string Url = partWithTheLink.substr(0, positionFirstTab);
							std::cout << "getLinks: Get URL from partWithTheLink with tab on position: " << positionFirstTab << ", " << Url << std::endl;
							links.push_back(Url);
						}
						else {
							std::cout << "getLinks: Get URL from partWithTheLink without tab: " << partWithTheLink << std::endl;
							links.push_back(partWithTheLink);
						}
					}
					else {
						std::size_t positionFirstTab = line.find_first_of(" ");
						std::cout << "getLinks: positionFirstTab: " << positionFirstTab << std::endl;
						if (positionFirstTab != std::string::npos) {
							std::string URL = line.substr(0, positionFirstTab);
							std::cout << "getLinks: Get URL from line with tab " << URL << std::endl;
							links.push_back(URL);
						}
						else {
							std::cout << "getLinks: Get URL line with tab " << line << std::endl;
							links.push_back(line);
						}
					}
				}
				else {
					std::cout << "getLinks:  There aren`t any country codes in URL. " << std::endl;
				}
			}
			else {
				std::cout << "getLinks:  There aren`t any links in this line. " << std::endl;
			}
		}
	}
	return links;
}
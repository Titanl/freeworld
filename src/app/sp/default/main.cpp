#include <iostream>

//use functions from the sp LIB
#include "../../../sp/sp.h"

int main(int argc, const char** args)
{
	std::vector<std::string> pkgs;
	pkgs.push_back("std");
	try {
		Freeworld::Sp::start("asdf", pkgs, pkgs);
	} catch (const std::string& err) {
		std::cout << "Freeworld threw an exception:\n" << err << std::endl;
	}
	Freeworld::Sp::stop();
}

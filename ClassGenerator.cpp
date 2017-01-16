/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClassGenerator.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 11:42:23 by dbaldy            #+#    #+#             */
/*   Updated: 2017/01/16 14:34:20 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#define REQUIRED_NB_ARG 2

bool hasEnding (std::string fullString, std::string ending)
{
	if (fullString.length() >= ending.length())
		return (0 == fullString.compare (fullString.length() - ending.length(),
					ending.length(), ending));
	else
		return false;
}

std::string cleanResult(std::string method) {
	std::string keywords[] = {"virtual "};
	int i = 0;
	std::size_t pos;
	while (i < 1 && (pos = method.find(keywords[i])) != std::string::npos)
	{
		method = method.replace(pos, keywords[i].size(), "");
		i++;
	}
	return method;
}

std::string generateMethod(std::string line, std::string className, std::size_t pos)
{
	std::ostringstream oss;
	std::string subLine = line.substr(0, pos);
	std::string::reverse_iterator rev = subLine.rbegin();
	int methodSize = 0;
	while (rev!=line.rend())
	{
		if (*rev == '\t' || *rev == '\n' || *rev == ' ' || *rev == '*' || *rev == '&')
			break;
		methodSize++;
		rev++;
	}
	int start = pos - methodSize;
	std::string endWithSemi = line.substr(start);
	std::string end = endWithSemi.substr(0, endWithSemi.find(";", 0));
	int indentation = 0;
	std::string::iterator it = line.begin();
	while (*it == ' ' || *it == '\t')
	{
		indentation++;
		it++;
	}
	std::string begin = line.substr(indentation, pos - methodSize - indentation);
	oss << begin << className << "::"
		<< end << " {" << std::endl << "}" << std::endl << std::endl;
	return cleanResult(oss.str());
}

std::string generateClass(std::ifstream & infile, std::string className)
{
	std::ostringstream oss;
	std::string line;
	while (std::getline(infile, line))
	{
		std::size_t pos;
		// is a function
		if ((pos = line.find("(", 0)) != std::string::npos &&
		line.find(")", 0) != std::string::npos &&
		// isn't an abstract function
		line.find("= 0") == std::string::npos && line.find("=0") == std::string::npos)
		{
			oss << generateMethod(line, className, pos);
		}
		//TODO static at the end
	}
	return oss.str();
}

void	generateFile(std::string headerName)
{
	std::ifstream infile(headerName);
	std::string h = headerName;
	std::string fileName = headerName.replace(headerName.size() - 3, 3, "cpp");
	std::ofstream ofs(fileName);
	ofs << "#include \"" << h << "\"" << std::endl << std::endl;
	std::string line;
	std::string firstElement;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		iss >> firstElement;
		if (firstElement.compare("class") == 0)
		{
			std::string className;
			iss >> className;
			ofs << generateClass(infile, className);
			return ;
		}
	}

}

int		main(int argc, char *argv[])
{
	if (argc < REQUIRED_NB_ARG)
		return 0;
	argv++;
	while (*argv)
	{
		std::string fileName(*argv);
		if (!hasEnding(fileName, ".hpp"))
			std::cout << "\x1b[33;01m" << fileName << " isn't a cpp header.\x1b[0;m" << std::endl;
		else
			generateFile(fileName);
		argv++;
	}
	return 0;
}

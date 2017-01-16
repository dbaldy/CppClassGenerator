/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeaderGenerator.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaldy <dbaldy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 11:52:48 by dbaldy            #+#    #+#             */
/*   Updated: 2017/01/16 13:21:15 by dbaldy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

const std::string 	to_upper(std::string const arg)
{
	std::string	result;

	for (std::string::const_iterator it = arg.cbegin(); it != arg.cend(); it++)
	{
		if (*it >= 'a' && *it <= 'z')
			result += *it - 'a' + 'A';
		else
			result += *it;
	}
	return result;
}

void	generateHeader(char *className)
{
	std::string name(className);
	ofstream ofs(name + ".hpp");
	ostringstream oss;
	oss << "#ifndef " << to_upper(name) << "_HPP" << endl
		<< "# define " << to_upper(name) << "_HPP" << endl << endl
		<< "class " << name << endl
		<< "{" << endl
		<< "\tpublic:" << endl
		<< "\t\t" << name << "(void);" << endl
		<< "\t\t" << name << "(" << name << " const & cpy);" << endl
		<< "\t\t" << "~" << name << "(void);" << endl << endl
		<< "\t\t" << name << " & operator=(" << name << " const & rhs);" << endl
		<< "};" << endl << endl
		<< "#endif";
	ofs << oss.str();
}

int		main(int argc, char *argv[])
{
	if (argc < 2)
		return 0;
	argv++;
	while (*argv)
	{
		generateHeader(*argv);
		argv++;
	}
	return 0;
}

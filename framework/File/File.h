#ifndef FILE_H
#define FILE_H

#include <exception>
#include <string>
#include <Windows.h>
#include <fstream>

class FileException : public std::exception
{
private:
	std::string error;

public:
	FileException(std::string error) : error(error)
	{
	};

	virtual const char* what() const throw() // my call to the std exception class function (doesn't nessasarily have to be virtual).
	{
		return error.c_str();
	}
};

class File
{
private:

	std::string file;

	char szResult[512]; // usado no método get para retornar strings do *.ini

private:
	void release()
	{
		SecureZeroMemory(szResult, sizeof(szResult));
	}

public:
	File(const std::string &file)  // Construtor, parâmetro File recebe o nome do ini ( Ex: config.ini )
	{
		std::ifstream infile(file);
		char buffer[MAX_PATH] = { 0 };

		if(!infile.good())
			throw FileException("File doesn't exists ( " + file + " )");

		GetCurrentDirectory(MAX_PATH, buffer);

		this->file = buffer + std::string("\\") + file;

		infile.close();
	}

	void write(const std::string &Section, const std::string &Key, const std::string &Value)
	{
		this->release(); // limpa as variáveis antes de utilizá-las

		WritePrivateProfileString(Section.c_str(), Key.c_str(), Value.c_str(), file.c_str());
	}
	void write(const std::string &Section, const std::string &Key, int value)
	{
		write(Section, Key, std::to_string(value));
	}

	int readInt(const std::string &Section, const std::string &Key)
	{
		return GetPrivateProfileInt(Section.c_str(), Key.c_str(), 0, file.c_str());
	}

	std::string readString(const std::string &Section, const std::string &Key)
	{
		this->release(); // limpa as variáveis antes de utilizá-las

		GetPrivateProfileString(Section.c_str(), Key.c_str(), NULL, szResult, sizeof(szResult), file.c_str());
		return szResult;
	}
};

#endif // FILE_H
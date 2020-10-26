#ifndef BASE64_H
#define BASE64_H

#include <string>

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

class Base64
{
private:

	static inline bool is_base64(unsigned char c)
	{
		return (isalnum(c) || (c == '+') || (c == '/'));
	}

public:
	Base64();
	~Base64();


	std::string encode(unsigned char const* bytes_to_encode, unsigned int in_len);
	std::string decode(std::string const& encoded_string);
};

#endif //BASE64_H
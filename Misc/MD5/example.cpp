#include <iostream>
#include <fstream>
#include "md5.h"

void PrintMD5(const string &str, MD5 &md5) {
	std::cout << "MD5(\"" << str << "\") = " << md5.toString() << std::endl;
}
string FileDigest(const string &file) {

	ifstream in(file.c_str(), std::ios::binary);
	if (!in)
		return "";

	MD5 md5;
	char buffer[1024];
	while (!in.eof()) {
		in.read(buffer, 1024);
		const auto length = in.gcount();
		if (length > 0)
			md5.update(buffer, length);
	}
	in.close();
	return md5.toString();
}
int main()
{
	std::ios_base::sync_with_stdio(false);
	_wsetlocale(LC_ALL, L"");
	
	const auto filename1 = R"(D:\test.txt)";
	const auto filename2 = R"(D:\test.exe)";
	auto fs1 = ifstream(filename1);
	auto fs2 = ifstream(filename2, std::ios::binary);

	std::cout << MD5("abc").toString() << std::endl;
	std::cout << MD5(fs1).toString() << std::endl;
	std::cout << MD5(fs2).toString() << std::endl;
	std::cout << FileDigest(filename2) << std::endl;

	MD5 md5;
	md5.update(""); 
	PrintMD5("", md5);//d41d8cd98f00b204e9800998ecf8427e

	md5.update("a");
	PrintMD5("a", md5);//0cc175b9c0f1b6a831c399e269772661

	md5.update("bc");
	PrintMD5("abc", md5);//900150983cd24fb0d6963f7d28e17f72

	md5.update("defghijklmnopqrstuvwxyz");
	PrintMD5("abcdefghijklmnopqrstuvwxyz", md5);//c3fcd3d76192e4007dfb496cca67e13b

	md5.reset();
	md5.update("message digest");
	PrintMD5("message digest", md5);//f96b697d7cb7938d525a2f31aaf161d0

	md5.reset();
	md5.update(fs1);
	PrintMD5(filename1, md5);
	
	md5.reset();
	md5.update(u8"鄙哥");
	PrintMD5("鄙哥", md5);//6948cbac42bd269cc4bcf94a7bacbf17

    return 0;
}
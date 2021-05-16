#pragma once
#include <fstream>

class CBinaryReader {
private:
	std::ifstream* InternalStream;
public:

	CBinaryReader(std::ifstream* is);

	bool eof();
	std::istream& seekg(std::streamoff _Offs, std::ios_base::seek_dir _Way);
	std::istream& seekg(std::streampos _Pos);
	std::istream& read(char* _str, std::streamsize _Count);

	int8_t read8();
	int16_t read16();
	int32_t read32();
	int64_t read64();
	double readDouble();

};
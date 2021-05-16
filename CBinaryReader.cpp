#include "CBinaryReader.hpp"

CBinaryReader::CBinaryReader(std::ifstream* is) :
	InternalStream{ is }
{
	if (is == NULL)
		throw "Undefined input stream!";
}

bool CBinaryReader::eof()
{
	return InternalStream->eof();
}

int8_t CBinaryReader::read8() {
	int8_t value;
	InternalStream->read((char*)&value, 1);
	return value;
}

int16_t CBinaryReader::read16() {
	int16_t value;
	InternalStream->read((char*)&value, 2);
	return value;
}

int32_t CBinaryReader::read32() {
	int32_t value;
	InternalStream->read((char*)&value, 4);
	return value;
}

int64_t CBinaryReader::read64() {
	int64_t value;
	InternalStream->read((char*)&value, 8);
	return value;
}

double CBinaryReader::readDouble() {
	double value;
	InternalStream->read((char*)&value, sizeof(double));
	return value;
}

std::istream& CBinaryReader::read(char* _str, std::streamsize _Count) {
	return InternalStream->read(_str, _Count);
}

std::istream& CBinaryReader::seekg(std::streamoff _Offs, std::ios_base::seek_dir _Way)
{
	return InternalStream->seekg(_Offs, _Way);
}

std::istream& CBinaryReader::seekg(std::streampos _Pos)
{
	return InternalStream->seekg(_Pos);
}
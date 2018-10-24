#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <iterator>
#include <windows.h>

using namespace std;
typedef std::vector<std::string> stringvec;


bool GetImageSize(const char *fn, int *x, int *y)
{
	FILE *f;
	fopen_s(&f, fn, "r");
	if (f == 0) {
		cout << "failed to load file" << endl;
		return false;
	}
	fseek(f, 0, SEEK_END);
	long len = ftell(f);
	fseek(f, 0, SEEK_SET);
	if (len < 24) {
		fclose(f);
		return false;
	}
	// Strategy:
	// reading GIF dimensions requires the first 10 bytes of the file
	// reading PNG dimensions requires the first 24 bytes of the file
	// reading JPEG dimensions requires scanning through jpeg chunks
	// In all formats, the file is at least 24 bytes big, so we'll read that always
	unsigned char buf[24]; fread(buf, 1, 24, f);

	// For JPEGs, we need to read the first 12 bytes of each chunk.
	// We'll read those 12 bytes at buf+2...buf+14, i.e. overwriting the existing buf.
	if (buf[0] == 0xFF && buf[1] == 0xD8 && buf[2] == 0xFF && buf[3] == 0xE0 && buf[6] == 'J' && buf[7] == 'F' && buf[8] == 'I' && buf[9] == 'F')
	{
		long pos = 2;
		while (buf[2] == 0xFF)
		{
			if (buf[3] == 0xC0 || buf[3] == 0xC1 || buf[3] == 0xC2 || buf[3] == 0xC3 || buf[3] == 0xC9 || buf[3] == 0xCA || buf[3] == 0xCB) break;
			pos += 2 + (buf[4] << 8) + buf[5];
			if (pos + 12 > len) break;
			fseek(f, pos, SEEK_SET); fread(buf + 2, 1, 12, f);
		}
	}

	fclose(f);

	// JPEG: (first two bytes of buf are first two bytes of the jpeg file; rest of buf is the DCT frame
	if (buf[0] == 0xFF && buf[1] == 0xD8 && buf[2] == 0xFF)
	{
		*y = (buf[7] << 8) + buf[8];
		*x = (buf[9] << 8) + buf[10];
		//cout << *x << endl;
		return true;
	}

	// GIF: first three bytes say "GIF", next three give version number. Then dimensions
	if (buf[0] == 'G' && buf[1] == 'I' && buf[2] == 'F')
	{
		*x = buf[6] + (buf[7] << 8);
		*y = buf[8] + (buf[9] << 8);
		return true;
	}

	// PNG: the first frame is by definition an IHDR frame, which gives dimensions
	if (buf[0] == 0x89 && buf[1] == 'P' && buf[2] == 'N' && buf[3] == 'G' && buf[4] == 0x0D && buf[5] == 0x0A && buf[6] == 0x1A && buf[7] == 0x0A
		&& buf[12] == 'I' && buf[13] == 'H' && buf[14] == 'D' && buf[15] == 'R')
	{
		*x = (buf[16] << 24) + (buf[17] << 16) + (buf[18] << 8) + (buf[19] << 0);
		*y = (buf[20] << 24) + (buf[21] << 16) + (buf[22] << 8) + (buf[23] << 0);
		return true;
	}

	return false;
}

void read_directory(const std::string& name, stringvec& v)
{
	std::string pattern(name);
	pattern.append("\\*");
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			if (strncmp(data.cFileName, ".", 0) != 0 || strncmp(data.cFileName, "..", 1) != 0) {
				v.push_back(data.cFileName);
			}
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}
}
string readPos(const char *fileName) {
	char result[500];   // array to hold the result.
	const char *folder = "./training/pos/";

	strncpy_s(result, folder, 500); // copy string one into the result.
	strncat_s(result, fileName, 500);

	int the_x = 0;
	int the_y = 0;
	bool didRun = false;
	char buffer[20];
	didRun = GetImageSize(result, &the_x, &the_y);
	char dimensions[500];
	strncpy_s(dimensions, " 1 0 0 ", 500);
	_itoa_s(the_x, buffer, 20);
	strncat_s(dimensions, buffer, 500);
	strncat_s(dimensions, " ", 500);
	_itoa_s(the_y, buffer, 20);
	strncat_s(dimensions,buffer, 500);
	strncat_s(result, dimensions, 500);


	return result;

}

int main() {
	stringvec neg;
	read_directory("C:/Users/arrastador/source/repos/ComputerVision/Trainer/training/neg", neg);
	std::copy(neg.begin(), neg.end(),
		std::ostream_iterator<std::string>(std::cout, "\n"));
	stringvec pos;
	read_directory("C:/Users/arrastador/source/repos/ComputerVision/Trainer/training/pos", pos);
	std::copy(pos.begin(), pos.end(),
		std::ostream_iterator<std::string>(std::cout, "\n"));

	ifstream myfile2("C:/Users/arrastador/source/repos/ComputerVision/landons junk folder/neg.txt");
	ofstream myPosFile;
	myPosFile.open("C:/Users/arrastador/source/repos/ComputerVision/Trainer/training/pos.txt");
	for (int i = 0; i < pos.size(); i++) {

		string name = pos[i];
		char ptrName[200];
		strncpy_s(ptrName, name.c_str(), 200);
		string write = readPos(ptrName);
		myPosFile << write << "\n";
	}
	myPosFile.close();
	ofstream myNegFile;
	myNegFile.open("C:/Users/arrastador/source/repos/ComputerVision/Trainer/training/neg.txt");
	for (int i = 0; i < neg.size(); i++) {
		myNegFile << neg[i] << "\n";
	}
	myNegFile.close();

	return 0;
}


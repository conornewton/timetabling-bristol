#include "CSV/CSV.hpp"

#include <vector>

std::vector<std::string> split(const std::string& str, const char& delim) {
	std::vector<std::string> splits;
	std::stringstream s(str);
	std::string chunk;

	while (std::getline(s, chunk, delim)) {
		splits.push_back(chunk);

		if (s.peek() == '"') {
			//read the first speech mark
			s.get();

			std::getline(s, chunk, '"');
			splits.push_back(chunk);

			//read the next comma
			s.get();
		}
	}

	return splits;
}

CSV::CSV(std::string FILEPATH) {
	fin.open(FILEPATH, std::ios::in);
	if (!fin.is_open())
	{
		std::cout << "Error Opening File " << FILEPATH << std::endl;
	}
	else {
		//skip the byte order mark at the start of csv if it exists
		char test[3] = { 0 };
		fin.read(test, 3);
		if ((unsigned char)test[0] != 0xEF ||
			(unsigned char)test[1] != 0xBB ||
			(unsigned char)test[2] != 0xBF)
		{
			fin.seekg(0);
		}

		std::string line;

		while (std::getline(fin, line)) {
			lines.push_back(line);
		}
	}
}

CSV::~CSV() {
	fin.close();
}

bool CSV::next_line() {
	return index < lines.size();
}

std::vector<std::string> CSV::get_values() {
	return split(lines[index++], ',');
}



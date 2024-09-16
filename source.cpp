#include <vector>
#include <string>
#include <fstream>
#include <format>
#include <iostream>
#include <sstream>
#include <algorithm>

struct STUDENT_DATA {
	std::string firstName;
	std::string lastName;
};

STUDENT_DATA processLine(std::string line) {
	std::string fname, lname;

	std::istringstream line_stringstream(line);
	line_stringstream >> lname >> fname;

	lname.erase(std::remove(lname.begin(), lname.end(), ','), lname.end());

	STUDENT_DATA newStudent = {.firstName = fname, .lastName = lname};
	return newStudent;
}

int main() {
	std::vector<STUDENT_DATA> studentData;
	std::string studentDataFilename = "StudentData.txt";

	std::ifstream ipf(studentDataFilename);
	if (!ipf.is_open()) {
		std::cout << std::format("Could not open {}", studentDataFilename);
	} else {
		while (!ipf.eof()) {
			std::string line;
			std::getline(ipf, line);
			if (!line.empty()) {
				studentData.push_back(processLine(line));
			}
		}
	}

	#if _DEBUG
		for (int i = 0; i < studentData.size(); i++) {
			std::cout << std::format("[{}]: {}, {}\n", i, studentData[i].lastName, studentData[i].firstName);
		}
	#endif

	return 0;
}
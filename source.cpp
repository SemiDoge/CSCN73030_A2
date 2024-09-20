#include <vector>
#include <string>
#include <fstream>
#include <format>
#include <iostream>
#include <sstream>
#include <algorithm>

#define PRE_RELEASE

struct STUDENT_DATA {
	std::string firstName;
	std::string lastName;
	std::string email;
};

STUDENT_DATA processLine(std::string line) {
	std::string fname, lname;

	std::istringstream line_stringstream(line);
	#ifdef PRE_RELEASE
		std::string email;
		std::getline(line_stringstream, lname, ',');
		std::getline(line_stringstream, fname, ',');
		std::getline(line_stringstream, email, ',');
		fname.erase(std::remove(fname.begin(), fname.end(), ' '), fname.end());

		STUDENT_DATA newStudent = {.firstName = fname, .lastName = lname, .email = email};
	#else
		std::getline(line_stringstream, lname, ',');
		std::getline(line_stringstream, fname, ',');
		fname.erase(std::remove(fname.begin(), fname.end(), ' '), fname.end());

		STUDENT_DATA newStudent = {.firstName = fname, .lastName = lname};
	#endif

	return newStudent;
}

int main() {
	std::vector<STUDENT_DATA> studentData;
	#ifdef PRE_RELEASE
		std::string studentDataFilename = "StudentData_Emails.txt";
	#else
		std::string studentDataFilename = "StudentData.txt";
	#endif

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

	#ifdef PRE_RELEASE
		std::cout << std::format("Running in... PreRelease\n");
	#endif

	#if _DEBUG
		int i = 0;
		for (auto& student : studentData) {
			#ifdef PRE_RELEASE
				std::cout << std::format("[{}]: {}, {}, {}\n", i, student.lastName, student.firstName, student.email);
			#else 
				std::cout << std::format("[{}]: {}, {}\n", i, student.lastName, student.firstName);
			#endif
			i++;
		}
	#endif

	return 0;
}
#include "pch.h"
#include "Solution10.h"

namespace AoC2022_D10 {
	using namespace std;

	// --------------------------- Types ----------------------------------

	typedef struct pc_t {
		pc_t(const vector<string>& lines) :program(lines), CRT(6, string(40, '.')) { }
		vector<string> program;
		size_t PC = 0;
		int64_t clock = 0, rX = 1, signal = 0;
		vector<string> CRT;

		void incrementClock() {
			if (rX - 1 <= (clock % 40) && (clock % 40) <= rX + 1) {
				CRT[clock / 40][clock % 40] = '#';
			}
			clock++;
			if ((clock + 20) % 40 == 0)
				signal += clock * rX;
		}
		void run() {
			while (PC < program.size()) {
				if (program[PC] == "noop")
					incrementClock();
				else { // inst == "addx ???"
					auto idx = program[PC].find(' ');
					incrementClock();
					incrementClock();
					rX += std::stoi(program[PC].substr(idx));
				}
				PC++;
			}
		}
	};

	// ------------------------- Constants --------------------------------

	// -------------------------- Functions -------------------------------

	void printCRT(vector<string> crt, int h = 6, int w = 40) {
		std::ostringstream oss;
		for (int i = 0; i < h; i++) {
			oss << "|";
			for (int j = 0; j < w; j++) {
				oss << crt[i][j];
			}
			oss << "|\r\n";
		}
		std::cout << oss.str();
	}

	// --------------------------- Part 1 ---------------------------------
	int64_t solvePart1(const vector<string>& lines) {
		pc_t program(lines);
		program.run();
		return program.signal;
	}

	// --------------------------- Part 2 ---------------------------------
	int64_t solvePart2(const vector<string>& lines) {
		pc_t program(lines);
		program.run();
		printCRT(program.CRT);
		return 0;
	}
}

int AoC2022_D10::solve() {
#if 1 // smaller test
	auto lines = AoC::readFile("./src/D10_Cathode_Ray_Tube/small.txt");
	if (lines.empty()) return 1;
#else
	auto lines = AoC::readFile("./src/D10_Cathode_Ray_Tube/input.txt");
	if (lines.empty()) return 1;
#endif
	// pretty print
	std::ostringstream oss;
	for (int i = 0; i < lines.size(); i++) {
		oss << i;
		if (i <= 9) oss << "  ";
		else if (10 <= i && i <= 99) oss << " ";
		oss << " " << lines[i] << "\r\n";
	}
	oss << "\r\n";
	cout << oss.str();

	auto part1 = solvePart1(lines);
	auto part2 = solvePart2(lines);

	std::cout << "-----------------------------------------------------\r\n";
	std::cout << "Part 1 = " << part1 << "\r\n"; // 11820
	std::cout << "Part 2 = " << part2 << "\r\n"; // EPJBRKAH
	std::cout << "-----------------------------------------------------\r\n";
	return 0;
}

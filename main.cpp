#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <iomanip>
inline std::string toUpper(std::string str) {std::transform(str.begin(), str.end(), str.begin(), std::ptr_fun<int, int>(std::toupper)); return str;}
inline std::string removeWS(std::string str) {str.erase(remove(str.begin(),str.end(),' '),str.end()); return str;}
bool time_isGood(std::string time) {
	bool error = false;
	bool out = false;
	std::string str;
	if (time.size() == 8) {
		if ( (time[2] == ':') && (time[5] == ':') ) {
			str.push_back(time[0]);
			str.push_back(time[1]);
			try {std::stoi(str);}
			catch (std::out_of_range& oor) {error = true;}
			catch (std::invalid_argument& ia) {error = true;}
			if (error == false) {
				str.clear();
				str.push_back(time[3]);
				str.push_back(time[4]);
				try {std::stoi(str);}
				catch (std::out_of_range& oor) {error = true;}
				catch (std::invalid_argument& ia) {error = true;}
				if (error == false) {
					str.clear();
					str.push_back(time[3]);
					str.push_back(time[4]);
					try {std::stoi(str);}
					catch (std::out_of_range& oor) {error = true;}
					catch (std::invalid_argument& ia) {error = true;}
					if (error == false) {out = true;}
				}
			}
		}
	}
	return out;
}
bool dist_isGood(std::string dist) {
	bool out = false;
	bool error = false;
	try {std::stof(dist);}
	catch (std::out_of_range& oor) {error = true;}
	catch (std::invalid_argument& ia) {error = true;}
	if (error == false) {out = true;}
	return out;
}
bool unit_isGood(std::string unit, std::string &str) {
	bool out = false;
	unit = toUpper( removeWS(unit) );
	if ( (unit == "MILES") || (unit == "MILE") || (unit == "MI") || (unit == "M") ) {out = true; str = "mile";}
	else if ( (unit == "KILOMETERS") || (unit == "KILOMETER") || (unit == "KM") || (unit == "K") ) {out = true; str = "kilometer";}
	return out;
}
int main(int argc, char *argv[]) {
	
	// variables
	std::string str;
	
	// check command line arguments
	// argc must be 4 (range 0-3)
	if (argc != 4) {
		printf("Must have 3 arguments following program name.\n");
		printf("Example: '%s 00:23:19 10 miles'\n", argv[0]);
	}
	
	// proper number of args:
	else {
		
		// command line args as strings
		std::string exec(argv[0]);
		std::string time(argv[1]);
		std::string dist(argv[2]);
		std::string unit(argv[3]);
		
		/// VERIFY AND CALCULATE TIME STRING
		if (time_isGood(time) == false) {
			printf("Invalid time format!\n");
			goto END_EARLY;
		} else {
			float hours = 0;
			float minutes = 0;
			float seconds = 0;
			str.push_back(time[0]);
			str.push_back(time[1]);
			hours = std::stof(str); //
			str.clear();
			str.push_back(time[3]);
			str.push_back(time[4]);
			minutes = std::stof(str); //
			str.clear();
			str.push_back(time[6]);
			str.push_back(time[7]);
			seconds = std::stof(str); //
			str.clear();
			
			/// VERIFY AND CALCULATE DIST STRING
			if (dist_isGood(dist) == false) {
				printf("Invalid distance!\n");
				goto END_EARLY;
			} else {
				float distance = std::stof(dist); //
				
				/// VERIFY AND CALCULATE UNIT STRING
				if (unit_isGood(unit, str) == false) {
					printf("Invalid unit!\n");
					goto END_EARLY;
				} else {
					
					/// ---------------------------------
					/// DO THE MAIN CODE HERE BABEY!!
					/// COMMAND LINE ARGS WORK!!!!
					/// ---------------------------------
					
					// total time in minutes
					float totalTime = (60.0 * hours) + (minutes) + (seconds / 60.0);
					float pacePerUnit = (totalTime / distance);
					
					// print everyhting
					std::cout << std::endl;
					std::cout << "[TOTAL TIME] " << time << " or " << totalTime << " minutes." << std::endl;
					std::cout << std::fixed << std::showpoint << std::setprecision(2);
					std::cout << "[AVG PACE  ] " << static_cast<int>(floor(pacePerUnit)) << ":" << (pacePerUnit - static_cast<int>(floor(pacePerUnit))) * 60 << " per " << str;
					std::cout << std::endl;
					
					// avg pace in opposite unit
					// first, change unit
					if (str == "mile") {
						str = "kilometer";
						distance = distance / 0.6213712;
					}
					else {
						str = "mile";
						distance = distance * 0.6213712;
					}
					pacePerUnit = totalTime / distance;
					std::cout << "           ] " << static_cast<int>(floor(pacePerUnit)) << ":" << ( pacePerUnit - static_cast<int>(floor(pacePerUnit)) ) * 60 << " per " << str;
					std::cout << std::endl;
					
					
				}
			}
		}
	}
	
	// end
END_EARLY:
	return 0;
}
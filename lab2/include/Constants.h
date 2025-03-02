#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace Constants {
	const int M = 8;
	const long long sizes[M] = {1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000};	

	const int amount_of_attempts = 20;
	
	const double min_element = -1.0;
	const double max_element = 1.0;

	const std::string folder("plots/files/");

	const long double c = 0.5 * 1e-5;
}

#endif

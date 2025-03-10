#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include <string>

namespace Constants {
	const int maxPersons = 100;
	const std::vector<std::string> lastNames = { "Zolotukhin", "Burychev", "Kiseleva", "Koshkarev", "Akashev"  };
	const std::vector<std::string> firstNames = { "Andrey", "Leonid", "Alexandra", "Ivan", "Zakhar" };
	const std::vector<std::string> middleNames = { "Alexandrovich", "Vladimirovich", "Maximovna", "Mikhailovich", "Valeryevich" };
	const int min_year = 1950;
	const int max_year = 2025;
	const int min_month = 1;
	const int max_month = 12;
	const int min_day = 1;
	const int max_day = 28;
	
	const int M = 8;
	const long long sizes[M] = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000 };

	const int amount_of_attempts = 20;

	const double min_element = -1.0;
	const double max_element = 1.0;

	const std::string folder("plots/files/");

	const long double c = 0.5 * 1e-5;
}

#endif

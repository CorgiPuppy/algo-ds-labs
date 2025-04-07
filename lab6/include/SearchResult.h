#ifndef SEARCH_RESULT_H
#define SEARCH_RESULT_H

struct SearchResult {
	long long totalTime;
	double averageTime;

	SearchResult() : totalTime(0), averageTime(0.0) {}
	SearchResult(long long total, double avg) : totalTime(total), averageTime(avg) {}
};

#endif

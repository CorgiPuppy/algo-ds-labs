#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>

#include "../include/Constants.h"
#include "../include/DoublyLinkedList.h"
#include "../include/BinarySearchTree.h"
#include "../include/AVLTree.h"
#include "../include/SearchResult.h"

void writeResultsToFile(const std::string&, int, long long, long long, long long, const std::string&);


int main() {
	for (int episode = 0; episode < Constants::amount_of_series - 6; episode++) {
		int n = pow(2, 10 + episode);
		std::cout << "n=== Episode " << episode + 1 << " (n = " << n << ") ===" << std::endl;

		DoublyLinkedList<int> dataList;
		
		for (int loop = 0; loop < Constants::amount_of_loops; loop++) {
			if (loop < Constants::amount_of_loops / 2)
				dataList.fillRandom(n);
			else
				dataList.fillSorted(n);

			BinarySearchTree<int> bst;
			long long bstInsertTime = dataList.measureInsertTime(bst);
			SearchResult bstSearch = dataList.measureSearchTime(bst);
			SearchResult bstDelete = dataList.measureDeleteTime(bst);
			writeResultsToFile("bst_results.dat", n, bstInsertTime, bstSearch.totalTime, bstDelete.totalTime, (loop < Constants::amount_of_loops / 2) ? "random" : "sorted");

			AVLTree<int> avl;
			long long avlInsertTime = dataList.measureInsertTime(avl);
			SearchResult avlSearch = dataList.measureSearchTime(avl);
			SearchResult avlDelete = dataList.measureDeleteTime(avl);

			writeResultsToFile("avl_results.dat", n, avlInsertTime, avlSearch.totalTime, avlDelete.totalTime, (loop < Constants::amount_of_loops / 2) ? "random" : "sorted");

			SearchResult listSearch = dataList.measureListSearchTime<int>();

			writeResultsToFile("list_search_results.dat", n, 0, listSearch.totalTime, 0, (loop < Constants::amount_of_loops / 2) ? "random" : "sorted");
		}
	}

	return 0;
}

void writeResultsToFile(const std::string& filename, int n, long long insertTime, long long searchTime, long long deleteTime, const std::string& type) {
	std::ofstream file(Constants::dataFilePath + filename, std::ios::app);
	if (file.is_open()) {
		file << n << " " << insertTime << " " << searchTime << " " << deleteTime << " " << type << "\n";
		file.close();
	} else
		std::cerr << "Unable to open file: " << filename << std::endl;
}



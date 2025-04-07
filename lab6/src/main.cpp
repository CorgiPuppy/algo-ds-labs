#include <iostream>
#include <cmath>

#include "../include/Constants.h"
#include "../include/DoublyLinkedList.h"
#include "../include/BinarySearchTree.h"
#include "../include/AVLTree.h"
#include "../include/SearchResult.h"

int main() {
	for (int episode = 0; episode < Constants::amount_of_series; episode++) {
		int n = pow(2, 10 + episode);
		std::cout << "n=== Episode " << episode + 1 << " (n = " << n << ") ===" << std::endl;

		DoublyLinkedList<int> dataList;
		
		for (int loop = 0; loop < Constants::amount_of_loops / 2; loop++) {
			std::cout << "Loop " << loop + 1 << " (random data):" << std::endl;

			dataList.fillRandom(n);

			BinarySearchTree<int> bst;
			long long bstInsertTime = dataList.measureInsertTime(bst);
			SearchResult bstSearch = dataList.measureSearchTime(bst);

			std::cout << "BST: Insert=" << bstInsertTime << "mks, " << "Search=" << bstSearch.totalTime << "mks total (" << bstSearch.averageTime << "mks per search)" << std::endl;


			AVLTree<int> avl;
			long long avlInsertTime = dataList.measureInsertTime(avl);
			SearchResult avlSearch = dataList.measureSearchTime(avl);

			std::cout << "AVL: Insert=" << avlInsertTime << "mks, " << "Search=" << avlSearch.totalTime << "mks total (" << avlSearch.averageTime << "mks per search)" << std::endl;
		}

		for (int loop = Constants::amount_of_loops / 2; loop < Constants::amount_of_loops; loop++) {
			std::cout << std::endl << "Loop " << loop + 1 << " (sorted data): " << std::endl;

			dataList.fillRandom(n);

			BinarySearchTree<int> bst;
			long long bstInsertTime = dataList.measureInsertTime(bst);
			SearchResult bstSearch = dataList.measureSearchTime(bst);

			std::cout << "BST: Insert=" << bstInsertTime << "mks, " << "Search=" << bstSearch.totalTime << "mks total (" << bstSearch.averageTime << "mks per search)" << std::endl;


			AVLTree<int> avl;
			long long avlInsertTime = dataList.measureInsertTime(avl);
			SearchResult avlSearch = dataList.measureSearchTime(avl);

			std::cout << "AVL: Insert=" << avlInsertTime << "mks, " << "Search=" << avlSearch.totalTime << "mks total (" << avlSearch.averageTime << "mks per search)" << std::endl;
		}
	}

	return 0;
}

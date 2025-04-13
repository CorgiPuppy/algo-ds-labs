#include <iostream>
#include <cmath>
#include <fstream>

#include "../include/Constants.h"
#include "../include/DoublyLinkedList.h"
#include "../include/BinarySearchTree.h"
#include "../include/AVLTree.h"
#include "../include/SearchResult.h"

int main() {
	std::ofstream insertRandomFile;
	insertRandomFile.open(Constants::dataFilePath + "insert_random.dat");
	std::ofstream searchRandomFile;
	searchRandomFile.open(Constants::dataFilePath + "search_random.dat");
	std::ofstream deleteRandomFile;
	deleteRandomFile.open(Constants::dataFilePath + "delete_random.dat");
	std::ofstream insertSortedFile;
	insertSortedFile.open(Constants::dataFilePath + "insert_sorted.dat");
	std::ofstream searchSortedFile;
	searchSortedFile.open(Constants::dataFilePath + "search_sorted.dat");
	std::ofstream deleteSortedFile;
	deleteSortedFile.open(Constants::dataFilePath + "delete_sorted.dat");

	for (int episode = 0; episode < Constants::amount_of_series - 4; episode++) {
		int n = pow(2, 10 + episode);
		std::cout << "n=== Episode " << episode + 1 << " (n = " << n << ") ===" << std::endl;

		DoublyLinkedList<int> dataList;	

		double averageBstInsertTime = 0.0;
		double averageAvlInsertTime = 0.0;
		double averageBstSearchTime = 0.0;
		double averageAvlSearchTime = 0.0;
		double averageListSearchTime = 0.0;
		double averageBstDeleteTime = 0.0;
		double averageAvlDeleteTime = 0.0;

		for (int loop = 0; loop < Constants::amount_of_loops / 2; loop++) {
			std::cout << "Loop " << loop + 1 << " (random data):" << std::endl;
			dataList.fillRandom(n);

			BinarySearchTree<int> bst;
			long long bstInsertTime = dataList.measureInsertTime(bst);
			SearchResult bstSearch = dataList.measureSearchTime(bst);
			SearchResult bstDelete = dataList.measureDeleteTime(bst);
		
			averageBstInsertTime += bstInsertTime;
			averageBstSearchTime += bstSearch.averageTime;
			averageBstDeleteTime += bstDelete.averageTime;

			std::cout << "BST: Insert=" << bstInsertTime << "mks, " << "Search=" << bstSearch.totalTime << "mks total (" << bstSearch.averageTime << "mks per search), " << "Delete=" << bstDelete.totalTime << "mks (" << bstDelete.averageTime << "mks/delete)" << std::endl;

			AVLTree<int> avl;
			long long avlInsertTime = dataList.measureInsertTime(avl);
			SearchResult avlSearch = dataList.measureSearchTime(avl);
			SearchResult avlDelete = dataList.measureDeleteTime(avl);

			averageAvlInsertTime += avlInsertTime;
			averageAvlSearchTime += avlSearch.averageTime;
			averageAvlDeleteTime += avlDelete.averageTime;

			std::cout << "AVL: Insert=" << avlInsertTime << "mks, " << "Search=" << avlSearch.totalTime << "mks total (" << avlSearch.averageTime << "mks per search), " << "Delete=" << avlDelete.totalTime << "mks (" << avlDelete.averageTime << "mks/delete)" << std::endl;

			SearchResult listSearch = dataList.measureListSearchTime<int>();
			std::cout << "List Search: " << listSearch.totalTime << "mks total (" << listSearch.averageTime << "mks per search)" << std::endl;

			averageListSearchTime += listSearch.averageTime;
		}
		
		insertRandomFile << n << " " << averageBstInsertTime << " " << averageAvlInsertTime << "\n";
		searchRandomFile << n << " " << averageBstSearchTime << " " << averageAvlSearchTime << " " << averageListSearchTime << "\n";
		deleteRandomFile << n << " " << averageBstDeleteTime << " " << averageAvlDeleteTime << "\n";

		averageBstInsertTime = 0.0;
		averageAvlInsertTime = 0.0;
		averageBstSearchTime = 0.0;
		averageAvlSearchTime = 0.0;
		averageListSearchTime = 0.0;
		averageBstDeleteTime = 0.0;
		averageAvlDeleteTime = 0.0;

		for (int loop = Constants::amount_of_loops / 2; loop < Constants::amount_of_loops; loop++) {
			std::cout << std::endl << "Loop " << loop + 1 << " (sorted data): " << std::endl;

			dataList.fillSorted(n);

			BinarySearchTree<int> bst;
			long long bstInsertTime = dataList.measureInsertTime(bst);
			SearchResult bstSearch = dataList.measureSearchTime(bst);
			SearchResult bstDelete = dataList.measureDeleteTime(bst);
		
			averageBstInsertTime += bstInsertTime;
			averageBstSearchTime += bstSearch.averageTime;
			averageBstDeleteTime += bstDelete.averageTime;

			std::cout << "BST: Insert=" << bstInsertTime << "mks, " << "Search=" << bstSearch.totalTime << "mks total (" << bstSearch.averageTime << "mks per search), " << "Delete=" << bstDelete.totalTime << "mks (" << bstDelete.averageTime << "mks/delete)" << std::endl;

			AVLTree<int> avl;
			long long avlInsertTime = dataList.measureInsertTime(avl);
			SearchResult avlSearch = dataList.measureSearchTime(avl);
			SearchResult avlDelete = dataList.measureDeleteTime(avl);

			averageAvlInsertTime += avlInsertTime;
			averageAvlSearchTime += avlSearch.averageTime;
			averageAvlDeleteTime += avlDelete.averageTime;

			std::cout << "AVL: Insert=" << avlInsertTime << "mks, " << "Search=" << avlSearch.totalTime << "mks total (" << avlSearch.averageTime << "mks per search), " << "Delete=" << avlDelete.totalTime << "mks (" << avlDelete.averageTime << "mks/delete)" << std::endl;

			SearchResult listSearch = dataList.measureListSearchTime<int>();
			std::cout << "List Search: " << listSearch.totalTime << "mks total (" << listSearch.averageTime << "mks per search)" << std::endl;
			
			averageListSearchTime += listSearch.averageTime;
		}

		insertSortedFile << n << " " << averageBstInsertTime << " " << averageAvlInsertTime << "\n";
		searchSortedFile << n << " " << averageBstSearchTime << " " << averageAvlSearchTime << " " << averageListSearchTime << "\n";
		deleteSortedFile << n << " " << averageBstDeleteTime << " " << averageAvlDeleteTime << "\n";
	}

	insertRandomFile.close();
	searchRandomFile.close();
	deleteRandomFile.close();
	insertSortedFile.close();
	searchSortedFile.close();
	deleteSortedFile.close();
	
	return 0;
}

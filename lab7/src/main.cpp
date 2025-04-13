#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>

#include "../include/Constants.h"
#include "../include/DoublyLinkedList.h"
#include "../include/BinarySearchTree.h"
#include "../include/AVLTree.h"
#include "../include/CartesianTree.h"
#include "../include/SearchResult.h"

void writeDepthsToFile(const std::string& filename, const std::vector<int>& depths) {
	std::ofstream file(filename);
	for (int depth : depths) {
		file << depth << "\n";
	}
	file.close();
}

int main() {
	std::ofstream insertRandomFile(Constants::dataFilePath + "insert_random.dat");
	std::ofstream searchRandomFile(Constants::dataFilePath + "search_random.dat");
	std::ofstream deleteRandomFile(Constants::dataFilePath + "delete_random.dat");
	std::ofstream insertSortedFile(Constants::dataFilePath + "insert_sorted.dat");
	std::ofstream searchSortedFile(Constants::dataFilePath + "search_sorted.dat");
	std::ofstream deleteSortedFile(Constants::dataFilePath + "delete_sorted.dat");

	std::ofstream maxDepthFile(Constants::dataFilePath + "max_depth.dat");
	std::ofstream avlDepthsFile(Constants::dataFilePath + "avl_depths.dat");
	std::ofstream cartesianTreeDepthsFile(Constants::dataFilePath + "cartesianTree_depths.dat");

	for (int episode = 0; episode <= Constants::amount_of_series; episode++) {
		int n = pow(2, 10 + episode);
        std::cout << "=== Episode " << episode + 1 << " (n = " << n << ") ===" << std::endl;

        DoublyLinkedList<int> dataList;
        std::vector<int> avlDepths, cartesianTreeDepths;
        double avlMaxDepth = 0, cartesianTreeMaxDepth = 0;

        double avgCartesianTreeInsertTime = 0, avgAvlInsertTime = 0;
        double avgCartesianTreeSearchTime = 0, avgAvlSearchTime = 0;
        double avgCartesianTreeDeleteTime = 0, avgAvlDeleteTime = 0;

        for (int loop = 0; loop < Constants::amount_of_loops / 2; loop++) {
            std::cout << "Loop " << loop + 1 << " (random data):" << std::endl;
            dataList.fillRandom(n);

            auto start = std::chrono::high_resolution_clock::now();
            CartesianTree<int> cartesianTree;
            long long cartesianTreeInsertTime = dataList.measureInsertTime(cartesianTree);
            auto end = std::chrono::high_resolution_clock::now();
            cartesianTreeInsertTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            
            SearchResult cartesianTreeSearch = dataList.measureSearchTime(cartesianTree);
            SearchResult cartesianTreeDelete = dataList.measureDeleteTime(cartesianTree);

            start = std::chrono::high_resolution_clock::now();
            AVLTree<int> avl;
            long long avlInsertTime = dataList.measureInsertTime(avl);
            end = std::chrono::high_resolution_clock::now();
            avlInsertTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            
            SearchResult avlSearch = dataList.measureSearchTime(avl);
            SearchResult avlDelete = dataList.measureDeleteTime(avl);

            avgCartesianTreeInsertTime += cartesianTreeInsertTime;
            avgCartesianTreeSearchTime += cartesianTreeSearch.averageTime;
            avgCartesianTreeDeleteTime += cartesianTreeDelete.averageTime;
            
            avgAvlInsertTime += avlInsertTime;
            avgAvlSearchTime += avlSearch.averageTime;
            avgAvlDeleteTime += avlDelete.averageTime;

            if (loop == Constants::amount_of_loops / 2 - 1) {
                avlMaxDepth = avl.getMaxDepth();
                cartesianTreeMaxDepth = cartesianTree.getMaxDepth();
                
                auto depths = avl.getAllDepths();
                avlDepths.insert(avlDepths.end(), depths.begin(), depths.end());
                
                depths = cartesianTree.getAllDepths();
                cartesianTreeDepths.insert(cartesianTreeDepths.end(), depths.begin(), depths.end());
            }
        }

        insertRandomFile << n << " " << avgCartesianTreeInsertTime / (Constants::amount_of_loops / 2) << " " 
                         << avgAvlInsertTime / (Constants::amount_of_loops / 2) << "\n";
        searchRandomFile << n << " " << avgCartesianTreeSearchTime / (Constants::amount_of_loops / 2) << " " 
                         << avgAvlSearchTime / (Constants::amount_of_loops / 2) << "\n";
        deleteRandomFile << n << " " << avgCartesianTreeDeleteTime / (Constants::amount_of_loops / 2) << " " 
                         << avgAvlDeleteTime / (Constants::amount_of_loops / 2) << "\n";
        
        maxDepthFile << n << " " << cartesianTreeMaxDepth << " " << avlMaxDepth << "\n";

        avgCartesianTreeInsertTime = avgAvlInsertTime = 0;
        avgCartesianTreeSearchTime = avgAvlSearchTime = 0;
        avgCartesianTreeDeleteTime = avgAvlDeleteTime = 0;

        for (int loop = Constants::amount_of_loops / 2; loop < Constants::amount_of_loops; loop++) {
            std::cout << "Loop " << loop + 1 << " (sorted data):" << std::endl;
            dataList.fillSorted(n);

            auto start = std::chrono::high_resolution_clock::now();
            CartesianTree<int> cartesianTree;
            long long cartesianTreeInsertTime = dataList.measureInsertTime(cartesianTree);
            auto end = std::chrono::high_resolution_clock::now();
            cartesianTreeInsertTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            
            SearchResult cartesianTreeSearch = dataList.measureSearchTime(cartesianTree);
            SearchResult cartesianTreeDelete = dataList.measureDeleteTime(cartesianTree);

            start = std::chrono::high_resolution_clock::now();
            AVLTree<int> avl;
            long long avlInsertTime = dataList.measureInsertTime(avl);
            end = std::chrono::high_resolution_clock::now();
            avlInsertTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            
            SearchResult avlSearch = dataList.measureSearchTime(avl);
            SearchResult avlDelete = dataList.measureDeleteTime(avl);

            avgCartesianTreeInsertTime += cartesianTreeInsertTime;
            avgCartesianTreeSearchTime += cartesianTreeSearch.averageTime;
            avgCartesianTreeDeleteTime += cartesianTreeDelete.averageTime;
            
            avgAvlInsertTime += avlInsertTime;
            avgAvlSearchTime += avlSearch.averageTime;
            avgAvlDeleteTime += avlDelete.averageTime;

            if (loop == Constants::amount_of_loops - 1) {
                avlMaxDepth = avl.getMaxDepth();
                cartesianTreeMaxDepth = cartesianTree.getMaxDepth();
                
                auto depths = avl.getAllDepths();
                avlDepths.insert(avlDepths.end(), depths.begin(), depths.end());
                
                depths = cartesianTree.getAllDepths();
                cartesianTreeDepths.insert(cartesianTreeDepths.end(), depths.begin(), depths.end());
            }
        }

        insertSortedFile << n << " " << avgCartesianTreeInsertTime / (Constants::amount_of_loops / 2) << " " 
                         << avgAvlInsertTime / (Constants::amount_of_loops / 2) << "\n";
        searchSortedFile << n << " " << avgCartesianTreeSearchTime / (Constants::amount_of_loops / 2) << " " 
                         << avgAvlSearchTime / (Constants::amount_of_loops / 2) << "\n";
        deleteSortedFile << n << " " << avgCartesianTreeDeleteTime / (Constants::amount_of_loops / 2) << " " 
                         << avgAvlDeleteTime / (Constants::amount_of_loops / 2) << "\n";
        
        maxDepthFile << n << " " << cartesianTreeMaxDepth << " " << avlMaxDepth << "\n";

        if (episode == Constants::amount_of_series - 1) {
            writeDepthsToFile(Constants::dataFilePath + "avl_depths.dat", avlDepths);
            writeDepthsToFile(Constants::dataFilePath + "cartesianTree_depths.dat", cartesianTreeDepths);
        }
	}

	insertRandomFile.close();
	searchRandomFile.close();
	deleteRandomFile.close();
	insertSortedFile.close();
	searchSortedFile.close();
	deleteSortedFile.close();
	maxDepthFile.close();
	avlDepthsFile.close();
	cartesianTreeDepthsFile.close();

	return 0;
}

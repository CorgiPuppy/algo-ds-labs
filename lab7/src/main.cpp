#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

#include "../include/Constants.h"
#include "../include/DoublyLinkedList.h"
#include "../include/BinarySearchTree.h"
#include "../include/AVLTree.h"
#include "../include/CartesianTree.h"
#include "../include/RBTree.h"
#include "../include/SearchResult.h"

void writeDepthHistogram(const std::string& filename, const std::vector<int>& depths) {
    if (depths.empty()) return;
    
    std::map<int, int> histogram;
    for (int depth : depths) {
        histogram[depth]++;
    }
    
    std::ofstream file(filename);
    for (const auto& [depth, count] : histogram) {
        file << depth << " " << count << "\n";
    }
    file.close();
}

void writeDepthsToFile(const std::string& filename, const std::vector<int>& depths) {
    if (depths.empty()) return;
    
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
    
    std::ofstream maxHeightRandomFile(Constants::dataFilePath + "max_height_random.dat");
    std::ofstream maxHeightSortedFile(Constants::dataFilePath + "max_height_sorted.dat");
    maxHeightRandomFile << "# N AVL Cartesian RB\n";
    maxHeightSortedFile << "# N AVL Cartesian RB\n";

    std::vector<int> avlMaxHeightsRandom, cartesianMaxHeightsRandom, rbMaxHeightsRandom;
    std::vector<int> avlDepthsRandom, cartesianDepthsRandom, rbDepthsRandom;
    std::vector<int> avlMaxHeightsSorted, cartesianMaxHeightsSorted, rbMaxHeightsSorted;
    std::vector<int> avlDepthsSorted, cartesianDepthsSorted, rbDepthsSorted;

    for (int episode = 0; episode < Constants::amount_of_series; episode++) {
        int n = pow(2, 10 + episode);
        std::cout << "=== Episode " << episode + 1 << " (n = " << n << ") ===" << std::endl;

        DoublyLinkedList<int> dataList;
        
        double avgCartesianTreeInsertTimeRandom = 0, avgAvlInsertTimeRandom = 0, avgRbInsertTimeRandom = 0;
        double avgCartesianTreeSearchTimeRandom = 0, avgAvlSearchTimeRandom = 0, avgRbSearchTimeRandom = 0;
        double avgCartesianTreeDeleteTimeRandom = 0, avgAvlDeleteTimeRandom = 0, avgRbDeleteTimeRandom = 0;
        int avlMaxDepthRandom = 0, cartesianMaxDepthRandom = 0, rbMaxDepthRandom = 0;

        double avgCartesianTreeInsertTimeSorted = 0, avgAvlInsertTimeSorted = 0, avgRbInsertTimeSorted = 0;
        double avgCartesianTreeSearchTimeSorted = 0, avgAvlSearchTimeSorted = 0, avgRbSearchTimeSorted = 0;
        double avgCartesianTreeDeleteTimeSorted = 0, avgAvlDeleteTimeSorted = 0, avgRbDeleteTimeSorted = 0;
        int avlMaxDepthSorted = 0, cartesianMaxDepthSorted = 0, rbMaxDepthSorted = 0;

        for (int loop = 0; loop < Constants::amount_of_loops / 2; loop++) {
            std::cout << "Random Loop " << loop + 1 << std::endl;
            dataList.fillRandom(n);

            CartesianTree<int> cartesianTree;
            long long cartesianTreeInsertTime = dataList.measureInsertTime(cartesianTree);
            SearchResult cartesianTreeSearch = dataList.measureSearchTime(cartesianTree);
            SearchResult cartesianTreeDelete = dataList.measureDeleteTime(cartesianTree);
            
            AVLTree<int> avl;
            long long avlInsertTime = dataList.measureInsertTime(avl);
            SearchResult avlSearch = dataList.measureSearchTime(avl);
            SearchResult avlDelete = dataList.measureDeleteTime(avl);
            
            RBTree<int> rb;
            long long rbInsertTime = dataList.measureInsertTime(rb);
            SearchResult rbSearch = dataList.measureSearchTime(rb);
            SearchResult rbDelete = dataList.measureDeleteTime(rb);

            avgCartesianTreeInsertTimeRandom += cartesianTreeInsertTime;
            avgCartesianTreeSearchTimeRandom += cartesianTreeSearch.averageTime;
            avgCartesianTreeDeleteTimeRandom += cartesianTreeDelete.averageTime;
            
            avgAvlInsertTimeRandom += avlInsertTime;
            avgAvlSearchTimeRandom += avlSearch.averageTime;
            avgAvlDeleteTimeRandom += avlDelete.averageTime;
            
            avgRbInsertTimeRandom += rbInsertTime;
            avgRbSearchTimeRandom += rbSearch.averageTime;
            avgRbDeleteTimeRandom += rbDelete.averageTime;

            avlMaxDepthRandom = std::max(avlMaxDepthRandom, avl.getMaxDepth());
            cartesianMaxDepthRandom = std::max(cartesianMaxDepthRandom, cartesianTree.getMaxDepth());
            rbMaxDepthRandom = std::max(rbMaxDepthRandom, rb.getMaxDepth());

            if (episode == Constants::amount_of_series - 1) {
                avlMaxHeightsRandom.push_back(avl.getMaxDepth());
                cartesianMaxHeightsRandom.push_back(cartesianTree.getMaxDepth());
                rbMaxHeightsRandom.push_back(rb.getMaxDepth());
                
                auto avlDepths = avl.getAllDepths();
                avlDepthsRandom.insert(avlDepthsRandom.end(), avlDepths.begin(), avlDepths.end());
                
                auto cartesianDepths = cartesianTree.getAllDepths();
                cartesianDepthsRandom.insert(cartesianDepthsRandom.end(), cartesianDepths.begin(), cartesianDepths.end());
                
                auto rbDepths = rb.getAllDepths();
                rbDepthsRandom.insert(rbDepthsRandom.end(), rbDepths.begin(), rbDepths.end());
            }
        }

        for (int loop = Constants::amount_of_loops / 2; loop < Constants::amount_of_loops; loop++) {
            std::cout << "Sorted Loop " << loop + 1 << std::endl;
            dataList.fillSorted(n);

            CartesianTree<int> cartesianTree;
            long long cartesianTreeInsertTime = dataList.measureInsertTime(cartesianTree);
            SearchResult cartesianTreeSearch = dataList.measureSearchTime(cartesianTree);
            SearchResult cartesianTreeDelete = dataList.measureDeleteTime(cartesianTree);

            AVLTree<int> avl;
            long long avlInsertTime = dataList.measureInsertTime(avl);
            SearchResult avlSearch = dataList.measureSearchTime(avl);
            SearchResult avlDelete = dataList.measureDeleteTime(avl);
            
            RBTree<int> rb;
            long long rbInsertTime = dataList.measureInsertTime(rb);
            SearchResult rbSearch = dataList.measureSearchTime(rb);
            SearchResult rbDelete = dataList.measureDeleteTime(rb);

            avgCartesianTreeInsertTimeSorted += cartesianTreeInsertTime;
            avgCartesianTreeSearchTimeSorted += cartesianTreeSearch.averageTime;
            avgCartesianTreeDeleteTimeSorted += cartesianTreeDelete.averageTime;
            
            avgAvlInsertTimeSorted += avlInsertTime;
            avgAvlSearchTimeSorted += avlSearch.averageTime;
            avgAvlDeleteTimeSorted += avlDelete.averageTime;
            
            avgRbInsertTimeSorted += rbInsertTime;
            avgRbSearchTimeSorted += rbSearch.averageTime;
            avgRbDeleteTimeSorted += rbDelete.averageTime;

            avlMaxDepthSorted = std::max(avlMaxDepthSorted, avl.getMaxDepth());
            cartesianMaxDepthSorted = std::max(cartesianMaxDepthSorted, cartesianTree.getMaxDepth());
            rbMaxDepthSorted = std::max(rbMaxDepthSorted, rb.getMaxDepth());

            if (episode == Constants::amount_of_series - 1) {
                avlMaxHeightsSorted.push_back(avl.getMaxDepth());
                cartesianMaxHeightsSorted.push_back(cartesianTree.getMaxDepth());
                rbMaxHeightsSorted.push_back(rb.getMaxDepth());
                
                auto avlDepths = avl.getAllDepths();
                avlDepthsSorted.insert(avlDepthsSorted.end(), avlDepths.begin(), avlDepths.end());
                
                auto cartesianDepths = cartesianTree.getAllDepths();
                cartesianDepthsSorted.insert(cartesianDepthsSorted.end(), cartesianDepths.begin(), cartesianDepths.end());
                
                auto rbDepths = rb.getAllDepths();
                rbDepthsSorted.insert(rbDepthsSorted.end(), rbDepths.begin(), rbDepths.end());
            }
        }

        
        avgCartesianTreeInsertTimeRandom /= (Constants::amount_of_loops / 2);
        avgCartesianTreeSearchTimeRandom /= (Constants::amount_of_loops / 2);
        avgCartesianTreeDeleteTimeRandom /= (Constants::amount_of_loops / 2);
        avgAvlInsertTimeRandom /= (Constants::amount_of_loops / 2);
        avgAvlSearchTimeRandom /= (Constants::amount_of_loops / 2);
        avgAvlDeleteTimeRandom /= (Constants::amount_of_loops / 2);
        avgRbInsertTimeRandom /= (Constants::amount_of_loops / 2);
        avgRbSearchTimeRandom /= (Constants::amount_of_loops / 2);
        avgRbDeleteTimeRandom /= (Constants::amount_of_loops / 2);

        insertRandomFile << n << " " << avgCartesianTreeInsertTimeRandom << " " 
                         << avgAvlInsertTimeRandom << " " << avgRbInsertTimeRandom << "\n";
        searchRandomFile << n << " " << avgCartesianTreeSearchTimeRandom << " " 
                         << avgAvlSearchTimeRandom << " " << avgRbSearchTimeRandom << "\n";
        deleteRandomFile << n << " " << avgCartesianTreeDeleteTimeRandom << " " 
                         << avgAvlDeleteTimeRandom << " " << avgRbDeleteTimeRandom << "\n";
        
        maxHeightRandomFile << n << " " << avlMaxDepthRandom << " " 
                           << cartesianMaxDepthRandom << " " << rbMaxDepthRandom << "\n";

        avgCartesianTreeInsertTimeSorted /= (Constants::amount_of_loops / 2);
        avgCartesianTreeSearchTimeSorted /= (Constants::amount_of_loops / 2);
        avgCartesianTreeDeleteTimeSorted /= (Constants::amount_of_loops / 2);
        avgAvlInsertTimeSorted /= (Constants::amount_of_loops / 2);
        avgAvlSearchTimeSorted /= (Constants::amount_of_loops / 2);
        avgAvlDeleteTimeSorted /= (Constants::amount_of_loops / 2);
        avgRbInsertTimeSorted /= (Constants::amount_of_loops / 2);
        avgRbSearchTimeSorted /= (Constants::amount_of_loops / 2);
        avgRbDeleteTimeSorted /= (Constants::amount_of_loops / 2);

        insertSortedFile << n << " " << avgCartesianTreeInsertTimeSorted << " " 
                         << avgAvlInsertTimeSorted << " " << avgRbInsertTimeSorted << "\n";
        searchSortedFile << n << " " << avgCartesianTreeSearchTimeSorted << " " 
                         << avgAvlSearchTimeSorted << " " << avgRbSearchTimeSorted << "\n";
        deleteSortedFile << n << " " << avgCartesianTreeDeleteTimeSorted << " " 
                         << avgAvlDeleteTimeSorted << " " << avgRbDeleteTimeSorted << "\n";
        
        maxHeightSortedFile << n << " " << avlMaxDepthSorted << " " 
                           << cartesianMaxDepthSorted << " " << rbMaxDepthSorted << "\n";
    }

    insertRandomFile.close();
    searchRandomFile.close();
    deleteRandomFile.close();
    insertSortedFile.close();
    searchSortedFile.close();
    deleteSortedFile.close();
    maxHeightRandomFile.close();
    maxHeightSortedFile.close();

	writeDepthHistogram(Constants::dataFilePath + "max_height_avl_random_hist.dat", avlMaxHeightsRandom);
	writeDepthHistogram(Constants::dataFilePath + "max_height_cartesian_random_hist.dat", cartesianMaxHeightsRandom);
	writeDepthHistogram(Constants::dataFilePath + "max_height_rb_random_hist.dat", rbMaxHeightsRandom);
    writeDepthHistogram(Constants::dataFilePath + "max_height_avl_random.dat", avlMaxHeightsRandom);

    writeDepthHistogram(Constants::dataFilePath + "max_height_cartesian_random.dat", cartesianMaxHeightsRandom);
    writeDepthHistogram(Constants::dataFilePath + "max_height_rb_random.dat", rbMaxHeightsRandom);
    
    writeDepthHistogram(Constants::dataFilePath + "max_height_avl_sorted.dat", avlMaxHeightsSorted);
    writeDepthHistogram(Constants::dataFilePath + "max_height_cartesian_sorted.dat", cartesianMaxHeightsSorted);
    writeDepthHistogram(Constants::dataFilePath + "max_height_rb_sorted.dat", rbMaxHeightsSorted);

	writeDepthHistogram(Constants::dataFilePath + "depths_avl_random_hist.dat", avlDepthsRandom);
	writeDepthHistogram(Constants::dataFilePath + "depths_cartesian_random_hist.dat", cartesianDepthsRandom);
	writeDepthHistogram(Constants::dataFilePath + "depths_rb_random_hist.dat", rbDepthsRandom);

	writeDepthHistogram(Constants::dataFilePath + "depths_avl_sorted_hist.dat", avlDepthsSorted);
	writeDepthHistogram(Constants::dataFilePath + "depths_cartesian_sorted_hist.dat", cartesianDepthsSorted);
	writeDepthHistogram(Constants::dataFilePath + "depths_rb_sorted_hist.dat", rbDepthsSorted);

    return 0;
}

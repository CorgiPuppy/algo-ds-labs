package com.heaps;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.lang.Math;
import java.lang.System;

import com.heaps.utils.BinaryHeap;
import com.heaps.utils.BinomialHeap;
import com.heaps.utils.BinomialHeapNode;

class Main {	
	void n() throws FileNotFoundException {
		final String folder = "plots/dat-files/";

		File searchAverageDat = new File(folder + "search_average.dat");
		PrintWriter searchAverage = new PrintWriter(searchAverageDat);
		File searchMaxDat = new File(folder + "search_max.dat");
		PrintWriter searchMax = new PrintWriter(searchMaxDat);

		File insertAverageDat = new File(folder + "insert_average.dat");
		PrintWriter insertAverage = new PrintWriter(insertAverageDat);
		File insertMaxDat = new File(folder + "insert_max.dat");
		PrintWriter insertMax = new PrintWriter(insertMaxDat);

		File deleteAverageDat = new File(folder + "delete_average.dat");
		PrintWriter deleteAverage = new PrintWriter(deleteAverageDat);
		File deleteMaxDat = new File(folder + "delete_max.dat");
		PrintWriter deleteMax = new PrintWriter(deleteMaxDat);

		for (int i = 3; i <= 7; i++) {
			int initialCapacity = 1;
			BinaryHeap heap = new BinaryHeap(initialCapacity);

			int N = (int) Math.pow(10, i);

			searchAverage.print(N + " ");
			searchMax.print(N + " ");

			for(int j = 0; j < N; j++)
				heap.insert(Math.random());

			int Noperations = 1000;

			double temp;
			
			for (int j = 0; j < Noperations; j++)
				temp = heap.getMin();
			double elapsedTime = 0.0;
			double maxTime = 0.0;
			double currentTime = 0.0;
			double start = System.nanoTime();
			for (int j = 0; j < Noperations; j++) {
				double operationStart = System.nanoTime();
				temp = heap.getMin();
				double operationEnd = System.nanoTime();
				currentTime = (operationEnd - operationStart);
				maxTime = (currentTime > maxTime) ? currentTime : maxTime;
			}
			double end = System.nanoTime();
			elapsedTime += (end - start);
			double averageElapsedTime = elapsedTime / Noperations / 1E9;
			maxTime /= 1E9;

			searchAverage.print(averageElapsedTime + " ");
			searchMax.print(maxTime + " ");

			insertAverage.print(N + " ");
			insertMax.print(N + " ");

			elapsedTime = 0.0;
			maxTime = 0.0;
			currentTime = 0.0;
			start = System.nanoTime();
			for (int j = 0; j < Noperations; j++) {
				double operationStart = System.nanoTime();
				heap.insert(Math.random());
				double operationEnd = System.nanoTime();
				currentTime = (operationEnd - operationStart);
				maxTime = (currentTime > maxTime) ? currentTime : maxTime;
			}
			end = System.nanoTime();
			elapsedTime += (end - start);
			averageElapsedTime = elapsedTime / Noperations / 1E9;
			maxTime /= 1E9;
	
			insertAverage.print(averageElapsedTime + " ");
			insertMax.print(maxTime + " ");

			deleteAverage.print(N + " ");
			deleteMax.print(N + " ");

			elapsedTime = 0.0;
			maxTime = 0.0;
			currentTime = 0.0;
			start = System.nanoTime();
			for (int j = 0; j < Noperations; j++) {
				double operationStart = System.nanoTime();
				System.out.println(heap.extractMin());
				double operationEnd = System.nanoTime();
				currentTime = (operationEnd - operationStart);
				maxTime = (currentTime > maxTime) ? currentTime : maxTime;
			}
			end = System.nanoTime();
			elapsedTime += (end - start);
			averageElapsedTime = elapsedTime / Noperations / 1E9;
			maxTime /= 1E9;
	
			deleteAverage.print(averageElapsedTime + " ");
			deleteMax.print(maxTime + " ");

// 		start = System.nanoTime();
// 		for (int j = 0; j < Noperations; j++)
// 			System.out.println(heap.extractMin());
// 		end = System.nanoTime();
// 		elapsedTime = (end - start) / 1E9;
// 		System.out.println("Counting " + end + " " + start + "ms");
// 		System.out.println("Answer: " + elapsedTime);
// 
// 		start = System.nanoTime();
// 		for (int j = 0; j < Noperations; j++)
// 			heap.insert(Math.random());
// 		end = System.nanoTime();
// 		elapsedTime = (end - start) / 1E9;
// 		System.out.println("Counting " + end + " " + start + "ms");
// 		System.out.println("Answer: " + elapsedTime);
// 
// 
			BinomialHeap binomialHeap = new BinomialHeap();		
			BinomialHeapNode binomialHeapNode = null;
			
			for(int j = 0; j < N; j++)
				binomialHeapNode = binomialHeap.insert(binomialHeapNode, Math.random());

			elapsedTime = 0.0;
			maxTime = 0.0;
			currentTime = 0.0;
			start = System.nanoTime();
			for (int j = 0; j < Noperations; j++) {
				double operationStart = System.nanoTime();
				binomialHeapNode = binomialHeap.getMin(binomialHeapNode);
				double operationEnd = System.nanoTime();
				currentTime = (operationEnd - operationStart);
				maxTime = (currentTime > maxTime) ? currentTime : maxTime;
			}
			end = System.nanoTime();
			elapsedTime += (end - start);
			averageElapsedTime = elapsedTime / Noperations / 1E9;
			maxTime /= 1E9;

			searchAverage.println(averageElapsedTime);
			searchMax.println(maxTime);

			elapsedTime = 0.0;
			maxTime = 0.0;
			currentTime = 0.0;
			start = System.nanoTime();
			for (int j = 0; j < Noperations; j++) {
				double operationStart = System.nanoTime();
	 			binomialHeapNode = binomialHeap.insert(binomialHeapNode, Math.random());
				double operationEnd = System.nanoTime();
				currentTime = (operationEnd - operationStart);
				maxTime = (currentTime > maxTime) ? currentTime : maxTime;
			}
			end = System.nanoTime();
			elapsedTime += (end - start);
			averageElapsedTime = elapsedTime / Noperations / 1E9;
			maxTime /= 1E9;

			insertAverage.println(averageElapsedTime);
			insertMax.println(maxTime);

			elapsedTime = 0.0;
			maxTime = 0.0;
			currentTime = 0.0;
			start = System.nanoTime();
			for (int j = 0; j < Noperations; j++) {
				double operationStart = System.nanoTime();
	 			binomialHeapNode = binomialHeap.extractMin(binomialHeapNode);
				double operationEnd = System.nanoTime();
				currentTime = (operationEnd - operationStart);
				maxTime = (currentTime > maxTime) ? currentTime : maxTime;
			}
			end = System.nanoTime();
			elapsedTime += (end - start);
			averageElapsedTime = elapsedTime / Noperations / 1E9;
			maxTime /= 1E9;

			deleteAverage.println(averageElapsedTime);
			deleteMax.println(maxTime);
// 	
// 		start = System.nanoTime();
// 		for (int j = 0; j < Noperations; j++)
// 			binomialHeapNode = binomialHeap.extractMin(binomialHeapNode);
// 		end = System.nanoTime();
// 		elapsedTime = (end - start) / 1E9;
// 		System.out.println("Counting " + end + " " + start + "ms");
// 		System.out.println("Answer: " + elapsedTime);
// 	
// 		start = System.nanoTime();
// 		for (int j = 0; j < Noperations; j++)
// 			binomialHeapNode = binomialHeap.insert(binomialHeapNode, Math.random());
// 		end = System.nanoTime();
// 		elapsedTime = (end - start) / 1E9;
// 		System.out.println("Counting " + end + " " + start + "ms");
// 		System.out.println("Answer: " + elapsedTime);

		}

		searchAverage.close();
		searchMax.close();

		insertAverage.close();
		insertMax.close();

		deleteAverage.close();
		deleteMax.close();
	}


	public static void main(String[] args) throws FileNotFoundException {		
		new Main().n();
	}
}

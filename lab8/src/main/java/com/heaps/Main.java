package com.heaps;

import java.io.*;
import java.util.*;
import com.heaps.utils.*;

import com.heaps.utils.BinaryHeap;
import com.heaps.utils.BinomialHeap;
import com.heaps.utils.BinomialHeapNode;

public class Main {
    private static final int WARMUP_ITERATIONS = 10000;
    private static final int MEASURE_ITERATIONS = 100000;
    private static final int[] GROUP_SIZES = {10, 25, 50, 100};
    
    public static void main(String[] args) throws IOException {
        new Main().runTests();
    }
    
    private void runTests() throws IOException {
        createOutputDirs();
        
        PrintWriter searchAvg = new PrintWriter("plots/dat-files/search_average.dat");
        PrintWriter searchMax = new PrintWriter("plots/dat-files/search_max.dat");
        PrintWriter insertAvg = new PrintWriter("plots/dat-files/insert_average.dat");
        PrintWriter insertMax = new PrintWriter("plots/dat-files/insert_max.dat");
        PrintWriter deleteAvg = new PrintWriter("plots/dat-files/delete_average.dat");
        PrintWriter deleteMax = new PrintWriter("plots/dat-files/delete_max.dat");

        for (int i = 3; i <= 7; i++) {
            int N = (int)Math.pow(10, i);
            System.out.println("Testing N = " + N);
            
            // Бинарная куча
            BinaryHeap binaryHeap = new BinaryHeap(N);
            testBinaryHeap(binaryHeap, N, searchAvg, searchMax, insertAvg, insertMax, deleteAvg, deleteMax);
            
            // Биномиальная куча
            BinomialHeap binomialHeap = new BinomialHeap();
            BinomialHeapNode binomialRoot = null;
            testBinomialHeap(binomialHeap, binomialRoot, N, searchAvg, searchMax, insertAvg, insertMax, deleteAvg, deleteMax);
        }
        
        closeWriters(searchAvg, searchMax, insertAvg, insertMax, deleteAvg, deleteMax);
        generateGnuplotScripts();
    }
    
    private void testBinaryHeap(BinaryHeap heap, int N, 
                              PrintWriter searchAvg, PrintWriter searchMax,
                              PrintWriter insertAvg, PrintWriter insertMax,
                              PrintWriter deleteAvg, PrintWriter deleteMax) {
        // Заполнение кучи
        Random rand = new Random();
        for (int i = 0; i < N; i++) {
            heap.insert(rand.nextDouble());
        }
        
        // Прогрев
        warmupBinaryHeap(heap);
        
        // Тестирование операций
        testOperation(heap, "search", N, searchAvg, searchMax);
        testOperation(heap, "insert", N, insertAvg, insertMax);
        testOperation(heap, "delete", N, deleteAvg, deleteMax);
    }
    
    private void testBinomialHeap(BinomialHeap heap, BinomialHeapNode root, int N,
                                PrintWriter searchAvg, PrintWriter searchMax,
                                PrintWriter insertAvg, PrintWriter insertMax,
                                PrintWriter deleteAvg, PrintWriter deleteMax) {
        // Заполнение кучи
        Random rand = new Random();
        for (int i = 0; i < N; i++) {
            root = heap.insert(root, rand.nextDouble());
        }
        
        // Прогрев
        root = warmupBinomialHeap(heap, root);
        
        // Тестирование операций
        testOperation(heap, root, "search", N, searchAvg, searchMax);
        testOperation(heap, root, "insert", N, insertAvg, insertMax);
        testOperation(heap, root, "delete", N, deleteAvg, deleteMax);
    }
    
    private void warmupBinaryHeap(BinaryHeap heap) {
        Random rand = new Random();
        for (int i = 0; i < WARMUP_ITERATIONS; i++) {
            heap.getMin();
            heap.insert(rand.nextDouble());
            heap.extractMin();
        }
    }
    
    private BinomialHeapNode warmupBinomialHeap(BinomialHeap heap, BinomialHeapNode root) {
        Random rand = new Random();
        for (int i = 0; i < WARMUP_ITERATIONS; i++) {
            heap.getMin(root);
            root = heap.insert(root, rand.nextDouble());
            root = heap.extractMin(root);
        }
        return root;
    }
    
	private void testOperation(BinaryHeap heap, String opType, int N,
							 PrintWriter avgWriter, PrintWriter maxWriter) {
		Random rand = new Random();
		long totalTime = 0;
		double maxTime = 0;
		
		for (int i = 0; i < MEASURE_ITERATIONS; i++) {
			long start = System.nanoTime();
			
			switch(opType) {
				case "search":
					heap.getMin();
					break;
				case "insert":
					heap.insert(rand.nextDouble());
					break;
				case "delete":
					heap.extractMin();
					break;
			}
			
			long duration = System.nanoTime() - start;
			totalTime += duration;
			
			// Измерение максимального времени в группах
			if (i % GROUP_SIZES[0] == 0) {
				double avgGroupTime = duration / (double)GROUP_SIZES[0] / 1e9;
				if (avgGroupTime > maxTime) {
					maxTime = avgGroupTime;
				}
			}
		}
		
		double avgTime = totalTime / (double)MEASURE_ITERATIONS / 1e9;
		
		// Унифицированный вывод для всех операций
		if (opType.equals("search") || opType.equals("insert") || opType.equals("delete")) {
			if (avgWriter.toString().contains(String.valueOf(N))) {
				// Если строка для этого N уже начата, дописываем значения
				avgWriter.print(avgTime + " ");
				maxWriter.print(maxTime + " ");
			} else {
				// Иначе начинаем новую строку
				avgWriter.print(N + " " + avgTime + " ");
				maxWriter.print(N + " " + maxTime + " ");
			}
		}
	}

	private void testOperation(BinomialHeap heap, BinomialHeapNode root, String opType, int N,
							 PrintWriter avgWriter, PrintWriter maxWriter) {
		Random rand = new Random();
		long totalTime = 0;
		double maxTime = 0;
		
		for (int i = 0; i < MEASURE_ITERATIONS; i++) {
			long start = System.nanoTime();
			
			switch(opType) {
				case "search":
					heap.getMin(root);
					break;
				case "insert":
					root = heap.insert(root, rand.nextDouble());
					break;
				case "delete":
					root = heap.extractMin(root);
					break;
			}
			
			long duration = System.nanoTime() - start;
			totalTime += duration;
			
			// Измерение максимального времени в группах
			if (i % GROUP_SIZES[0] == 0) {
				double avgGroupTime = duration / (double)GROUP_SIZES[0] / 1e9;
				if (avgGroupTime > maxTime) {
					maxTime = avgGroupTime;
				}
			}
		}
		
		double avgTime = totalTime / (double)MEASURE_ITERATIONS / 1e9;
		
		// Унифицированный вывод для всех операций
		if (opType.equals("search") || opType.equals("insert") || opType.equals("delete")) {
			if (avgWriter.toString().endsWith(" ")) {
				// Если строка начата, дописываем в нее
				avgWriter.println(avgTime);
				maxWriter.println(maxTime);
			} else {
				// Иначе начинаем новую строку (это не должно происходить)
				avgWriter.print(N + " " + avgTime + " ");
				maxWriter.print(N + " " + maxTime + " ");
			}
		}
	}   
    private void createOutputDirs() {
        new File("plots/dat-files").mkdirs();
        new File("plots/pictures").mkdirs();
    }
    
    private void closeWriters(PrintWriter... writers) {
        for (PrintWriter writer : writers) {
            writer.close();
        }
    }
    
    private void generateGnuplotScripts() throws IOException {
        generatePlotScript("search", "поиска минимума");
        generatePlotScript("insert", "вставки");
        generatePlotScript("delete", "удаления минимума");
    }
    
    private void generatePlotScript(String operation, String title) throws IOException {
        PrintWriter writer = new PrintWriter("plots/gnuplot-files/" + operation + "_average.p");
        writer.println("set terminal pngcairo size 900,900");
        writer.println();
        writer.println("set title \"Расчётные кривые времени " + title + " в Бинарную кучу\"");
        writer.println("set xlabel \"Размер кучи (N)\"");
        writer.println("set ylabel \"Время (t, с)\"");
        writer.println("set grid");
        writer.println("set logscale x 10");
        writer.println("set logscale y 10");
        writer.println();
        writer.println("set output \"plots/pictures/" + operation + "_average.png\"");
        writer.println("plot \"plots/dat-files/" + operation + "_average.dat\" using 1:2 title \"BinaryAvg\" with linespoints, \\");
        writer.println("     \"plots/dat-files/" + operation + "_average.dat\" using 1:3 title \"BinomialAvg\" with linespoints, \\");
        writer.println("     \"plots/dat-files/" + operation + "_max.dat\" using 1:2 title \"BinaryMax\" with linespoints, \\");
        writer.println("     \"plots/dat-files/" + operation + "_max.dat\" using 1:3 title \"BinomialMax\" with linespoints");
        writer.close();
    }
}
//package com.heaps;
//
//import java.io.File;
//import java.io.FileNotFoundException;
//import java.io.PrintWriter;
//import java.lang.Math;
//import java.lang.System;
//
//import com.heaps.utils.BinaryHeap;
//import com.heaps.utils.BinomialHeap;
//import com.heaps.utils.BinomialHeapNode;
//
//class Main {	
//	void n() throws FileNotFoundException {
//		final String folder = "plots/dat-files/";
//
//		File searchAverageDat = new File(folder + "search_average.dat");
//		PrintWriter searchAverage = new PrintWriter(searchAverageDat);
//		File searchMaxDat = new File(folder + "search_max.dat");
//		PrintWriter searchMax = new PrintWriter(searchMaxDat);
//
//		File insertAverageDat = new File(folder + "insert_average.dat");
//		PrintWriter insertAverage = new PrintWriter(insertAverageDat);
//		File insertMaxDat = new File(folder + "insert_max.dat");
//		PrintWriter insertMax = new PrintWriter(insertMaxDat);
//
//		File deleteAverageDat = new File(folder + "delete_average.dat");
//		PrintWriter deleteAverage = new PrintWriter(deleteAverageDat);
//		File deleteMaxDat = new File(folder + "delete_max.dat");
//		PrintWriter deleteMax = new PrintWriter(deleteMaxDat);
//
//		for (int i = 3; i <= 7; i++) {
//			int initialCapacity = 1;
//			BinaryHeap heap = new BinaryHeap(initialCapacity);
//
//			int N = (int) Math.pow(10, i);
//
//			searchAverage.print(N + " ");
//			searchMax.print(N + " ");
//
//			for(int j = 0; j < N; j++)
//				heap.insert(Math.random());
//
//			int Noperations = 100000;
//
//			double temp;
//			
//			for (int j = 0; j < Noperations; j++)
//				temp = heap.getMin();
//			double elapsedTime = 0.0;
//			double maxTime = 0.0;
//			double currentTime = 0.0;
//			double start = System.nanoTime();
//			for (int j = 0; j < Noperations; j++) {
//				double operationStart = System.nanoTime();
//				temp = heap.getMin();
//				double operationEnd = System.nanoTime();
//				currentTime = (operationEnd - operationStart);
//				maxTime = (currentTime > maxTime) ? currentTime : maxTime;
//			}
//			double end = System.nanoTime();
//			elapsedTime += (end - start);
//			double averageElapsedTime = elapsedTime / Noperations / 1E9;
//			maxTime /= 1E9;
//
//			searchAverage.print(averageElapsedTime + " ");
//			searchMax.print(maxTime + " ");
//
//			insertAverage.print(N + " ");
//			insertMax.print(N + " ");
//
//			elapsedTime = 0.0;
//			maxTime = 0.0;
//			currentTime = 0.0;
//			start = System.nanoTime();
//			for (int j = 0; j < Noperations; j++) {
//				double operationStart = System.nanoTime();
//				heap.insert(Math.random());
//				double operationEnd = System.nanoTime();
//				currentTime = (operationEnd - operationStart);
//				maxTime = (currentTime > maxTime) ? currentTime : maxTime;
//			}
//			end = System.nanoTime();
//			elapsedTime += (end - start);
//			averageElapsedTime = elapsedTime / Noperations / 1E9;
//			maxTime /= 1E9;
//	
//			insertAverage.print(averageElapsedTime + " ");
//			insertMax.print(maxTime + " ");
//
//			deleteAverage.print(N + " ");
//			deleteMax.print(N + " ");
//
//			elapsedTime = 0.0;
//			maxTime = 0.0;
//			currentTime = 0.0;
//			start = System.nanoTime();
//			for (int j = 0; j < Noperations; j++) {
//				double operationStart = System.nanoTime();
//				System.out.println(heap.extractMin());
//				double operationEnd = System.nanoTime();
//				currentTime = (operationEnd - operationStart);
//				maxTime = (currentTime > maxTime) ? currentTime : maxTime;
//			}
//			end = System.nanoTime();
//			elapsedTime += (end - start);
//			averageElapsedTime = elapsedTime / Noperations / 1E9;
//			maxTime /= 1E9;
//	
//			deleteAverage.print(averageElapsedTime + " ");
//			deleteMax.print(maxTime + " ");
//
//// 		start = System.nanoTime();
//// 		for (int j = 0; j < Noperations; j++)
//// 			System.out.println(heap.extractMin());
//// 		end = System.nanoTime();
//// 		elapsedTime = (end - start) / 1E9;
//// 		System.out.println("Counting " + end + " " + start + "ms");
//// 		System.out.println("Answer: " + elapsedTime);
//// 
//// 		start = System.nanoTime();
//// 		for (int j = 0; j < Noperations; j++)
//// 			heap.insert(Math.random());
//// 		end = System.nanoTime();
//// 		elapsedTime = (end - start) / 1E9;
//// 		System.out.println("Counting " + end + " " + start + "ms");
//// 		System.out.println("Answer: " + elapsedTime);
//// 
//// 
//			BinomialHeap binomialHeap = new BinomialHeap();		
//			BinomialHeapNode binomialHeapNode = null;
//			
//			for(int j = 0; j < N; j++)
//				binomialHeapNode = binomialHeap.insert(binomialHeapNode, Math.random());
//
//			elapsedTime = 0.0;
//			maxTime = 0.0;
//			currentTime = 0.0;
//			start = System.nanoTime();
//			for (int j = 0; j < Noperations; j++) {
//				double operationStart = System.nanoTime();
//				binomialHeapNode = binomialHeap.getMin(binomialHeapNode);
//				double operationEnd = System.nanoTime();
//				currentTime = (operationEnd - operationStart);
//				maxTime = (currentTime > maxTime) ? currentTime : maxTime;
//			}
//			end = System.nanoTime();
//			elapsedTime += (end - start);
//			averageElapsedTime = elapsedTime / Noperations / 1E9;
//			maxTime /= 1E9;
//
//			searchAverage.println(averageElapsedTime);
//			searchMax.println(maxTime);
//
//			elapsedTime = 0.0;
//			maxTime = 0.0;
//			currentTime = 0.0;
//			start = System.nanoTime();
//			for (int j = 0; j < Noperations; j++) {
//				double operationStart = System.nanoTime();
//				binomialHeapNode = binomialHeap.insert(binomialHeapNode, Math.random());
//				double operationEnd = System.nanoTime();
//				currentTime = (operationEnd - operationStart);
//				maxTime = (currentTime > maxTime) ? currentTime : maxTime;
//			}
//			end = System.nanoTime();
//			elapsedTime += (end - start);
//			averageElapsedTime = elapsedTime / Noperations / 1E9;
//			maxTime /= 1E9;
//
//			insertAverage.println(averageElapsedTime);
//			insertMax.println(maxTime);
//
//			elapsedTime = 0.0;
//			maxTime = 0.0;
//			currentTime = 0.0;
//			start = System.nanoTime();
//			for (int j = 0; j < Noperations; j++) {
//				double operationStart = System.nanoTime();
//				binomialHeapNode = binomialHeap.extractMin(binomialHeapNode);
//				double operationEnd = System.nanoTime();
//				currentTime = (operationEnd - operationStart);
//				maxTime = (currentTime > maxTime) ? currentTime : maxTime;
//			}
//			end = System.nanoTime();
//			elapsedTime += (end - start);
//			averageElapsedTime = elapsedTime / Noperations / 1E9;
//			maxTime /= 1E9;
//
//			deleteAverage.println(averageElapsedTime);
//			deleteMax.println(maxTime);
//// 	
//// 		start = System.nanoTime();
//// 		for (int j = 0; j < Noperations; j++)
//// 			binomialHeapNode = binomialHeap.extractMin(binomialHeapNode);
//// 		end = System.nanoTime();
//// 		elapsedTime = (end - start) / 1E9;
//// 		System.out.println("Counting " + end + " " + start + "ms");
//// 		System.out.println("Answer: " + elapsedTime);
//// 	
//// 		start = System.nanoTime();
//// 		for (int j = 0; j < Noperations; j++)
//// 			binomialHeapNode = binomialHeap.insert(binomialHeapNode, Math.random());
//// 		end = System.nanoTime();
//// 		elapsedTime = (end - start) / 1E9;
//// 		System.out.println("Counting " + end + " " + start + "ms");
//// 		System.out.println("Answer: " + elapsedTime);
//
//		}
//
//		searchAverage.close();
//		searchMax.close();
//
//		insertAverage.close();
//		insertMax.close();
//
//		deleteAverage.close();
//		deleteMax.close();
//	}
//
//
//	public static void main(String[] args) throws FileNotFoundException {		
//		new Main().n();
//	}
//}

package com.heaps.utils;

import java.util.Arrays;

public class BinaryHeap {
	public double heap[];
	public int size;
	public int capacity;

	public BinaryHeap(int capacity) {
		this.capacity = capacity;
		this.heap = new double[capacity];
		this.size = 0;
	}

	private void resize() {
		capacity *= 2;
		heap = Arrays.copyOf(heap, capacity);
	}

	public double getMin() {
		return heap[0];
	}

	private int parent(int i) {
		return (i - 1) / 2;
	}

	public void insert(double element) {
		if (size >= capacity)
			resize();

		heap[size] = element;
		int currentIndex = size;
		size++;

		while (currentIndex > 0 && heap[currentIndex] < heap[parent(currentIndex)]) {
			double temp = heap[currentIndex];
			heap[currentIndex] = heap[parent(currentIndex)];
			heap[parent(currentIndex)] = temp;

			currentIndex = parent(currentIndex);
		}
	}

	private void heapifyDown(int i) {
		int smallestIndex = i;

		int left = 2 * i + 1;
		int right = 2 * i + 2;

		if (left < size && heap[left] < heap[smallestIndex])
			smallestIndex = left;

		if (right < size && heap[right] < heap[smallestIndex])
			smallestIndex = right;

		if (smallestIndex != i) {
			double temp = heap[i];
			heap[i] = heap[smallestIndex];
			heap[smallestIndex] = temp;

			heapifyDown(smallestIndex);
		}
	}

	public double extractMin() {
		if (size == 0)
			throw new RuntimeException("Heap is empty!");

		double min = heap[0];

		heap[0] = heap[size - 1];
		size--;
		
		heapifyDown(0);

		return min;
	}

	public void printHeap() {
		for (int i = 0; i < size; i++)
			System.out.print(heap[i] + " ");
	}
}

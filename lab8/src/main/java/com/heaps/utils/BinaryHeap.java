package com.heaps.utils;

import java.util.Arrays;

public class BinaryHeap {
    private double[] heap;
    private int size;
    private int capacity;

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
        if (size == 0) throw new IllegalStateException("Heap is empty");
        return heap[0];
    }

    private int parent(int i) { return (i - 1) / 2; }
    private int left(int i) { return 2 * i + 1; }
    private int right(int i) { return 2 * i + 2; }

    public void insert(double element) {
        if (size >= capacity) resize();

        heap[size] = element;
        int current = size;
        size++;

        while (current > 0 && heap[current] < heap[parent(current)]) {
            swap(current, parent(current));
            current = parent(current);
        }
    }

    public double extractMin() {
        if (size == 0) throw new IllegalStateException("Heap is empty");

        double min = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        return min;
    }

    private void heapifyDown(int i) {
        int smallest = i;
        int l = left(i);
        int r = right(i);

        if (l < size && heap[l] < heap[smallest]) smallest = l;
        if (r < size && heap[r] < heap[smallest]) smallest = r;

        if (smallest != i) {
            swap(i, smallest);
            heapifyDown(smallest);
        }
    }

    private void swap(int i, int j) {
        double temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }
}

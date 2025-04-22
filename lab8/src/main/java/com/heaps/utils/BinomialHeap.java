package com.heaps.utils;

public class BinomialHeap {
	public BinomialHeapNode newNode(double value) {
		BinomialHeapNode node = new BinomialHeapNode();

		node.data = value;
		node.degree = 0;
		node.child = null;
		node.parent = null;
		node.sibling = null;

		return node;
	}

	public BinomialHeapNode mergeBinomialTrees(BinomialHeapNode b1, BinomialHeapNode b2) {
		if (b1.data > b2.data) {
			BinomialHeapNode temp = b1;
			b1 = b2;
			b2 = temp;
		}
		
		b2.parent = b1;
		b2.sibling = b1.child;
		b1.child = b2;
		b1.degree++;

		return b1;
	}

	public BinomialHeapNode unionBinomialHeap(BinomialHeapNode h1, BinomialHeapNode h2) {
		if (h1 == null) return h2;
		if (h2 == null) return h1;

		BinomialHeapNode dummy = new BinomialHeapNode();
		BinomialHeapNode tail = dummy;
		BinomialHeapNode currentFirst = h1;
		BinomialHeapNode currentSecond = h2;

		while (currentFirst != null && currentSecond != null) {
			if (currentFirst.degree <= currentSecond.degree) {
				tail.sibling = currentFirst;
				currentFirst = currentFirst.sibling;
			} else {
				tail.sibling = currentSecond;
				currentSecond = currentSecond.sibling;
			}

			tail = tail.sibling;
		}

		tail.sibling = (currentFirst != null) ? currentFirst : currentSecond;

		return dummy.sibling;
	}

	public BinomialHeapNode adjustHeap(BinomialHeapNode head) {
		if (head == null) return null;

		BinomialHeapNode previous = null;
		BinomialHeapNode current = head;
		BinomialHeapNode next = head.sibling;

		while (next != null) {
			if (current.degree != next.degree || (next.sibling != null && next.sibling.degree == current.degree)) {
				previous = current;
				current = next;
			} else {
				if (current.data <= next.data) {	
					current.sibling = next.sibling;
					current = mergeBinomialTrees(current, next);
				} else {
					if (previous == null) head = next;
					else previous.sibling = next;
					current = mergeBinomialTrees(next, current);
				}
			}

			next = current.sibling;
		}
		
		return head;
	}

	public BinomialHeapNode insert(BinomialHeapNode heap, double value) {
		BinomialHeapNode temp = newNode(value);
		return adjustHeap(unionBinomialHeap(heap, temp));
	}

	public BinomialHeapNode getMin(BinomialHeapNode heap) {
		if (heap == null) return null;

		BinomialHeapNode min = heap;
		BinomialHeapNode current = heap.sibling;

		while (current != null) {
			if (current.data < min.data) min = current;
			current = current.sibling;
		}

		return min;
	}

	public BinomialHeapNode extractMin(BinomialHeapNode heap) {
		if (heap == null) return null;

		BinomialHeapNode min = getMin(heap);
		BinomialHeapNode previous = null;
		BinomialHeapNode current = heap;

		while (current != min) {
			previous = current;
			current = current.sibling;
		}

		if (previous != null) previous.sibling = min.sibling;
		else heap = min.sibling;

		BinomialHeapNode child = min.child;
		BinomialHeapNode newHeap = null;
		while (child != null) {
			BinomialHeapNode next = child.sibling;
			child.sibling = newHeap;
			child.parent = null;
			newHeap = child;
			child = next;
		}

		return adjustHeap(unionBinomialHeap(heap, newHeap));
	}
}

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

        BinomialHeapNode dummy = newNode(0);
        BinomialHeapNode tail = dummy;
        
        while (h1 != null && h2 != null) {
            if (h1.degree <= h2.degree) {
                tail.sibling = h1;
                h1 = h1.sibling;
            } else {
                tail.sibling = h2;
                h2 = h2.sibling;
            }
            tail = tail.sibling;
        }
        
        tail.sibling = (h1 != null) ? h1 : h2;
        return dummy.sibling;
    }

    public BinomialHeapNode adjustHeap(BinomialHeapNode head) {
        if (head == null || head.sibling == null) return head;
        
        BinomialHeapNode prev = null;
        BinomialHeapNode curr = head;
        BinomialHeapNode next = head.sibling;
        
        while (next != null) {
            if (curr.degree != next.degree || 
                (next.sibling != null && next.sibling.degree == curr.degree)) {
                prev = curr;
                curr = next;
            } else {
                if (curr.data <= next.data) {
                    curr.sibling = next.sibling;
                    curr = mergeBinomialTrees(curr, next);
                } else {
                    if (prev == null) {
                        head = next;
                    } else {
                        prev.sibling = next;
                    }
                    curr = mergeBinomialTrees(next, curr);
                }
            }
            next = curr.sibling;
        }
        return head;
    }

    public BinomialHeapNode insert(BinomialHeapNode heap, double value) {
        BinomialHeapNode temp = newNode(value);
        heap = unionBinomialHeap(heap, temp);
        return adjustHeap(heap);
    }

    public BinomialHeapNode getMin(BinomialHeapNode heap) {
        if (heap == null) return null;
        
        BinomialHeapNode minNode = heap;
        BinomialHeapNode curr = heap.sibling;
        
        while (curr != null) {
            if (curr.data < minNode.data) {
                minNode = curr;
            }
            curr = curr.sibling;
        }
        return minNode;
    }

	public BinomialHeapNode extractMin(BinomialHeapNode heap) {
        if (heap == null) return null;

        BinomialHeapNode min = getMin(heap);
        BinomialHeapNode prev = null;
        BinomialHeapNode current = heap;

        while (current != min) {
            prev = current;
            current = current.sibling;
        }

        if (prev != null) prev.sibling = min.sibling;
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

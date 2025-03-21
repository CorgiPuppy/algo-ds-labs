#ifndef QUEUE_H
#define QUEUE_H

class Queue {
	private:
		int* data;
		int front;
		int rear;
		int capacity;

	public:
		Queue(int size) {
			capacity = size;
			data = new int[capacity];
			front = rear = -1;
		}

		~Queue() {
			delete [] data;
		}

		void enqueue(int value) {
			if (rear == capacity - 1) {
				int* newData = new int[capacity * 2];
				for (int i = 0; i <= rear; i++)
					newData[i] = data[i];
				delete [] data;
				data = newData;
				capacity *= 2;
			}

			if (front == -1)
				front = 0;

			rear++;
			data[rear] = value;
		}

		int dequeue() {
			if (front == -1 || front > rear)
				return -1;

			int value = data[front];
			front++;
			if (front > rear)
				front = rear = -1;

			return value;
		}

		bool isEmpty() const { return front == -1; }
};

#endif

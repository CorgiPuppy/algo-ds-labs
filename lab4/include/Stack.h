#ifndef STACK_H
#define STACK_H

class Stack {
	private:
		int* data;
		int top;
		int capacity;
	
	public:
		Stack(int size) {
			capacity = size;
			data = new int[capacity];
			top = -1;
		}

		~Stack() {
			delete [] data;
		}

		void push(int value) {
			if (top == capacity - 1) {
				int* newData = new int[capacity * 2];
				for (int i = 0; i <= top; i++)
					newData[i] = data[i];
				delete [] data;
				data = newData;
				capacity *= 2;
			}
				
			top++;
			data[top] = value;
		}

		int pop() {
			if (top == -1) return -1;

			int value = data[top];
			top--;
			return value;
		}

		bool isEmpty() const { return top == -1; }
};

#endif

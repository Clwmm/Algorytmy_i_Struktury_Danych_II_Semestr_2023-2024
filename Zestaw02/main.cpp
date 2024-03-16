// Mateusz Kałwa

#include <iostream>
#include <vector>
#include <string>

template <class T>
class PriorityQueue {
private:
    std::vector<T> data;

    void heapifyUp(size_t index)
    {
        size_t parentIndex = (index - 1) / 2;
        while (index > 0 && data[parentIndex] < data[index])
        {
            std::swap(data[parentIndex], data[index]);
            index = parentIndex;
            parentIndex = (index - 1) / 2;
        }
    }

    void heapifyDown(const size_t& index)
    {
        size_t leftChildIndex = 2 * index + 1;
        size_t rightChildIndex = 2 * index + 2;
        size_t largestIndex = index;

        if (leftChildIndex < data.size() && data[leftChildIndex] > data[largestIndex])
            largestIndex = leftChildIndex;
        if (rightChildIndex < data.size() && data[rightChildIndex] > data[largestIndex])
            largestIndex = rightChildIndex;
        if (largestIndex != index)
        {
            std::swap(data[index], data[largestIndex]);
            heapifyDown(largestIndex);
        }
    }

public:
    PriorityQueue() {}

    template <class U>
    void enqueue(U&& value)
    {
        data.push_back(std::forward<U>(value));
        heapifyUp(data.size() - 1);
    }

    int dequeueMax()
    {
        if (isEmpty())
            throw std::out_of_range("Queue is empty");

        T max = data[0];
        data[0] = data.back();
        data.pop_back();
        heapifyDown(0);
        return max;
    }

    void display(std::string text = "")
    {
        std::cout << text;
        for (auto x : data)
            std::cout << x << "\t";
        std::cout << std::endl;
    }

    bool isEmpty() { return data.empty(); }
};

void testPQ(const std::vector<int>& data, PriorityQueue<int>& pq)
{
    for (auto x : data)
    {
        pq.enqueue(x);
        pq.display("Enqueue " + std::to_string(x) + ":\n");
    }
}

int main() {
    PriorityQueue<int> pq;
    std::vector<int> data = { 3, 5, 7, 2, 1, 8, 9, 7, 5, 9 };

    testPQ(data, pq);

    std::cout << "Dequeueing everything:" << std::endl;
    while (!pq.isEmpty()) {
        std::cout << pq.dequeueMax() << " ";
    }
    std::cout << std::endl;

    return 0;
}

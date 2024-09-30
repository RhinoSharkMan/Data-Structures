template <typename Comparable>
#include "BinaryHeap.h"
#include <iostream>

template <typename Comparable>
BinaryHeap<Comparable>::BinaryHeap(const vector<Comparable> & items)
    : array(items.size() + 10), currentSize{items.size()}
    {
        for (int i = 0; i < items.size(); ++i)
        {
            array[i + 1] = items[i];
        }
        buildHeap();
    }

/**
 * Insert item x, allowing duplicates.
 */
template <typename Comparable>
void BinaryHeap<Comparable>::insert(const Comparable & x)
{
    if (currentSize == array.size() - 1)
        array.resize(array.size() * 2);

        // Percolate up
    int hole = ++currentSize;
    Comparable copy = x;

    array[0] = std::move(copy);
    for (; x < array[hole / 2]; hole /= 2)
    {
        array[hole] = std::move(array[hole / 2]);
    }
    array[hole] = std::move(array[0]);
}

/**
 * Remoce the minimum item.
 * Throws UnderflowException if empty.
 */
template <typename Comparable>
void BinaryHeap<Comparable>::deleteMin()
{
    if (isEmpty())
        throw UnderflowException{};
    array[1] = std::move(array[currentSize--]);
    percolateDown(1);
}

/**
 * Remove the minimum item and place it in minItem.
 * Throws UnderflowException if empty.
 */
template <typename Comparable>
void BinaryHeap<Comparable>::deleteMin(Comparable &minItem)
{
    if (isEmpty())
        throw UnderflowException{};
    minItem = std::move(array[1]);
    array[1] = std::move(array[currentSize--]);
    percolateDown(1);
}

/**
 * Internal method to percolate down in the heap.
 * hole is the index at which the percolate begins.
 */
template <typename Comparable>
void BinaryHeap<Comparable>::percolateDown(int hole)
{
    int child;
    Comparable tmp = std::move(array[hole]);

    for (; hole * 2 <= currentSize; hole = child)
    {
        child = hole * 2;
        if (child != currentSize && array[child + 1] < array[child])
            ++child;
        if (array[child] < tmp)
            array[hole] = std::move(array[child]);
        else
            break;
    }
    array[hole] = std::move(tmp);
}

/**
 * Establish heap order property from an arbitrary
 * arrangement of items. Runs in linear time.
 */
template <typename Comparable>
void BinaryHeap<Comparable>::buildHeap()
{
    for (int i = currentSize / 2; i > 0; --i)
        percolateDown(i);
}
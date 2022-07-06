import java.util.ArrayList;
import java.util.Arrays;

public class MinHeap<T extends Comparable<T>> {
    private final ArrayList<T> heap;

    /**
     * Constructor
     */
    public MinHeap() {
        heap = new ArrayList<>();
    }

    /**
     * Insert element into the heap
     *
     * @param element the element to insert
     */
    public void insert(T element) {
        heap.add(element);
        int i = heap.size() - 1;

        while (i > 0 && heap.get(i).compareTo(heap.get(parent(i))) < 0) {
            swap(i, parent(i));
            i = parent(i);
        }
    }

    public int size() {
        return heap.size();
    }


    /**
     * It returns the index of the node's parent
     * (Parent of root is -1)
     *
     * @param i index of the child
     * @return index of the parent of node i
     */
    private static int parent(int i) {
        return (i - 1) / 2;
    }

    /**
     * It returns the index of the node's left child
     *
     * @param i index of the parent node
     * @return index of the left child of node i
     */
    private static int leftChild(int i) {
        return 2 * i + 1;
    }


    /**
     * It returns the index of the node's right child
     *
     * @param i index of parent
     * @return the index of the right child of node i
     */
    private static int rightChild(int i) {
        return 2 * i + 2;
    }


    /**
     * Return the minimum element end extract it from the heap
     *
     * @return the element with the minimum element, or null if the heap is null.
     */
    public T extractMin() {
        if (heap.size() <= 0)
            return null;
        else {
            T minVal = heap.get(0);
            heap.set(0, heap.get(heap.size() - 1));
            heap.remove(heap.size() - 1);
            minHeapify(0);
            return minVal;
        }
    }


    /**
     * Is the heap empty?
     *
     * @return true if the heap is empty, false if it's not empty.
     */
    public boolean isEmpty() {
        return heap.size() == 0;
    }


    /**
     * It returns the minimum, but it doesn't remove it from the heap.
     *
     * @return the minimum element, or null if the heap.
     */
    public T minimum() {
        if (heap.size() <= 0)
            return null;
        else
            return heap.get(0);
    }

    /**
     * Restore the min-heap property.
     *
     * @param i the position where to start restoring
     */
    private void minHeapify(int i) {
        int left = leftChild(i);
        int right = rightChild(i);
        int min;
        if (left <= heap.size() - 1 && heap.get(left).compareTo(heap.get(i)) < 0)
            min = left;
        else
            min = i;

        if (right <= heap.size() - 1 && heap.get(right).compareTo(heap.get(min)) < 0)
            min = right;

        if (min != i) {
            swap(i, min);
            minHeapify(min);
        }
    }

    /**
     * Swap two locations i and j in the heap.
     *
     * @param i first position
     * @param j second position
     */
    private void swap(int i, int j) {
        T t = heap.get(i);
        heap.set(i, heap.get(j));
        heap.set(j, t);
    }

    public void printArray() {
        System.out.println(Arrays.toString(heap.toArray()));
    }

    public void printHeap() {
        for (int i = 0; i < (heap.size() / 2); i++) {
            System.out.print(
                    " PARENT : " + heap.get(i)
                            + " LEFT CHILD : " + heap.get(leftChild(i))
                            + " RIGHT CHILD :" + heap.get(rightChild(i)));
            System.out.println();
        }
    }


    public static void main(String[] arg) {

        System.out.println("min heap: ");

        MinHeap<Integer> minHeap = new MinHeap<>();

        minHeap.insert(5);
        minHeap.insert(3);
        minHeap.insert(17);
        minHeap.insert(10);
        minHeap.insert(84);
        minHeap.insert(19);
        minHeap.insert(6);
        minHeap.insert(22);
        minHeap.insert(9);

        minHeap.printArray();
        minHeap.printHeap();

        System.out.println();
        System.out.println("min -> " + minHeap.minimum());
    }
}
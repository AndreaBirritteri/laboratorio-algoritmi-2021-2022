import java.util.ArrayList;
import java.util.Objects;

public class MinHeap<T extends Comparable<T>> {


    private ArrayList<T> heap;

    public MinHeap() {
        heap = new ArrayList<>();
    }


    private int leftChild(int i) {
        return 2 * i + 1;
    }


    private int rightChild(int i) {
        return 2 * (i + 1);
    }


    private int parent(int i) {
        return (i - 1) / 2;
    }


    public boolean isEmpty() {
        return heap.isEmpty();
    }

    public int size() {
        return heap.size();
    }


    public String toString() {
        return "the heap: " + heap;
    }

    public void insert(T v) {
        heap.add(v);
        int i = heap.size() - 1;
        while (i > 0 && v.compareTo(heap.get(parent(i))) < 0) {
            heap.set(i, heap.get(parent(i)));
            heap.set(parent(i), v);
            i = parent(i);
        }
    }

    private void heapify(int i) {
        int size = heap.size();
        if (size > 0) {
            int l = leftChild(i);
            int r = rightChild(i);
            int min;
            if (l < size && heap.get(i).compareTo(heap.get(l)) > 0)
                min = l;
            else
                min = i;
            if (r < size && heap.get(min).compareTo(heap.get(r)) > 0)
                min = r;

            if (min != i) {
                T t = heap.get(i);
                heap.set(i, heap.get(min));
                heap.set(min, t);
                heapify(min);
            }
        }
    }

    public void buildHeap(ArrayList<T> in) {
        heap = in;
        for (int i = (heap.size() - 2) / 2; i >= 0; i--)
            heapify(i);
    }

    public ArrayList<T> sort() {
        ArrayList<T> res = new ArrayList<>();
        while (!isEmpty()) {
            res.add(extract());
        }
        return res;
    }

    public T extract() {
        if (heap.isEmpty())
            return null;
        else {
            T res = heap.get(0);
            T newRoot = heap.get(heap.size() - 1);
            heap.set(0, newRoot);
            heap.remove(heap.size() - 1);
            heapify(0);
            return res;
        }

    }


    public void decreaseKey(int i, T key) {
        if (heap.get(i).compareTo(key) < 0) {
            throw new IllegalArgumentException("Key is larger than the original key");
        }

        heap.set(i, key);
        int parent = parent(i);
        while (i > 0 && heap.get(parent).compareTo(heap.get(i)) > 0) {
            swap(i, parent);
            i = parent;
            parent = parent(parent);
        }
    }

    private void swap(int i, int j) {
        T t = heap.get(i);
        heap.set(i, heap.get(j));
        heap.set(j, t);
    }

    public boolean contains(T v) {
        return heap.contains(v);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof MinHeap<?> minHeap)) return false;
        return Objects.equals(heap, minHeap.heap);
    }

    @Override
    public int hashCode() {
        return Objects.hash(heap);
    }


}

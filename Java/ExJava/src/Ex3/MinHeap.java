package Ex3;


import java.util.ArrayList;
import java.util.Objects;


/**
 * It contains Min Heap, using generic type t
 *
 * @param <T>: type of the MinHeap elements
 * @author birritteri, rondinella
 */

public class MinHeap<T extends Comparable<T>> {

  private final ArrayList<T> heap;


  /**
   * It is the constructor of the Heap
   * It creates an empty ArrayList.
   */
  public MinHeap() {
    heap = new ArrayList<>();
  }


  /**
   * It returns the left child of the passed index.
   *
   * @return return the value of the left child
   */
  private int leftChild(int i) {
    return 2 * i + 1;
  }

  /**
   * It returns the right child of the passed index.
   *
   * @return return the value of the right child
   */
  private int rightChild(int i) {
    return 2 * (i + 1);
  }


  /**
   * It returns the parent of the passed index.
   *
   * @return return the value of the parent
   */
  private int parent(int i) {
    return (i - 1) / 2;
  }

  /**
   * It returns a boolean if the Heap is Empty or Not.
   *
   * @return true iff Heap is empty, else false.
   */
  public boolean isEmpty() {
    return heap.isEmpty();
  }

  /**
   * It returns the Heap size.
   *
   * @return the integer number of Element in the Heap.
   */
  public int size() {
    return heap.size();
  }

  public String toString() {
    return "the heap: " + heap;
  }


  /**
   * It adds a new element into the Heap. It accepts as input a generic value.
   *
   * @param v: generic value
   */
  public void insert(T v) throws MinHeapException {
    if (v == null)
      throw new MinHeapException("element cannot be null");
    heap.add(v);
    int i = heap.size() - 1;
    while (i > 0 && v.compareTo(heap.get(parent(i))) < 0) {
      heap.set(i, heap.get(parent(i)));
      heap.set(parent(i), v);
      i = parent(i);
    }
  }

  /**
   * It does the heapify with index passed
   *
   * @param i: index
   */
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


  /**
   * It extracts the min element
   *
   * @return the min generic value.
   */
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


  /**
   * It does the Decrease Key method
   *
   * @param i:   index of the element
   * @param key: value decreased
   */
  public T decreaseKey(int i, T key) throws MinHeapException {
    if (heap.get(i).compareTo(key) < 0) {
      throw new MinHeapException("Key is larger than the original key");
    }

    heap.set(i, key);
    int parent = parent(i);
    while (i > 0 && heap.get(parent).compareTo(heap.get(i)) > 0) {
      swap(i, parent);
      i = parent;
      parent = parent(parent);
    }

    System.out.println(heap.get(0));
    System.out.println(heap.get(1));
    System.out.println(heap.get(2));


    return heap.get(i);
  }

  private void swap(int i, int j) {
    T t = heap.get(i);
    heap.set(i, heap.get(j));
    heap.set(j, t);
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

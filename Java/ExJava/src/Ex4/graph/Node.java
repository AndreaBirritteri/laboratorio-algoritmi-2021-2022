package Ex4.graph;


/**
 * It represents a node in Dijkstra.
 * It is defined the name of the interested node
 * and the cost to arrive to that node.
 * The name is a generic type (N) and the cost is a
 * generic number (int, double...)
 *
 * @param <N>
 * @param <T>
 * @author birritteri, rondinella
 */
public class Node<N, T extends Number> implements Comparable<Node<N, T>> {
  public N node;
  public T cost;

  public Node(N node, T cost) {
    this.node = node;
    this.cost = cost;
  }

  @Override
  public int compareTo(Node o) {
    return Double.compare(this.cost.doubleValue(), o.cost.doubleValue());
  }
}
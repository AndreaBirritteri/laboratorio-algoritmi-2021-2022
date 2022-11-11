package Ex4.graph;

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
package Ex4.graph;

public class Node implements Comparable<Node> {
    public String node;
    public Double cost;
    public Node(String node, Double cost) {
        this.node = node;
        this.cost = cost;
    }

    @Override
    public int compareTo(Node o) {
        return this.cost.compareTo(o.cost);
    }
}
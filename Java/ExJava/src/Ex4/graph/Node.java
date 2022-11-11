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
        if (this.cost < o.cost)
            return -1;
        if (this.cost > o.cost)
            return 1;
        return 0;
    }


}
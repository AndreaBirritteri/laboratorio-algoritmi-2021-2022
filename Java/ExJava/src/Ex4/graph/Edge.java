package Ex4.graph;

import java.util.Objects;

public class Edge<N, T extends Number> {
    private final N srcNode, dstNode;
    private final T label;

        public Edge(N srcNode, N dstNode, T label) {
        this.srcNode = srcNode;
        this.dstNode = dstNode;
        this.label = label;
    }

    public N getSrcNode() {
        return srcNode;
    }

    public N getDstNode() {
        return dstNode;
    }

    public T getLabel() {
        return label;
    }

    public boolean isNull() {
        return srcNode == null || dstNode == null || label == null;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Edge)) return false;
        Edge<?, ?> edge = (Edge<?, ?>) o;
        return getSrcNode().equals(edge.getSrcNode()) && getDstNode().equals(edge.getDstNode()) && getLabel().equals(edge.getLabel());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getSrcNode(), getDstNode(), getLabel());
    }

    @Override
    public String toString() {
        return "Edge{" +
                "srcNode=" + srcNode +
                ", dstNode=" + dstNode +
                ", label=" + label +
                '}';
    }
}

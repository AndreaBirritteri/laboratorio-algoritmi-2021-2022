package Ex4.graph;

import java.util.Objects;

/**
 * It represents an edge of a Graph. It links two nodes
 * to each other, and it is defined by a label. Values
 * of the nodes are generic (N) and the label is a
 * generic number (int, double...)
 *
 * @param <N>
 * @param <T>
 * @author birritteri, rondinella
 */
public class Edge<N, T extends Number> {
  private final N srcNode, dstNode;
  private final T label;

  /**
   * It is the constructor of an Edge. It has
   * three parameters, source node, destination node
   * and the label of the Edge.
   * and the label of the Edge.
   *
   * @param srcNode source Node
   * @param dstNode destination Node
   * @param label   generic label
   */
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
    if (this == o) {
      return true;
    }
    if (!(o instanceof Edge<?, ?> edge)) {
      return false;
    }
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

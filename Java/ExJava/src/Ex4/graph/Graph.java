package Ex4.graph;

import java.util.*;


public class Graph<N, T extends Number> {
    private final Map<N, List<Edge<N, T>>> graph;
    private final List<Edge<N, T>> edgeList;
    private final boolean direct;

    public Graph(boolean isDirect) {
        this.graph = new HashMap<>();
        this.edgeList = new ArrayList<>();
        this.direct = isDirect;
    }

    public void addNode(N node) throws GraphException {
        if (node == null)
            throw new GraphException("node value cannot be null");

        graph.put(node, new ArrayList<>());
    }

    public void addEdge(N src, N dst, T label) throws GraphException {
        if (src == null || dst == null)
            throw new GraphException("source or destination cannot be null");

        if (!graph.containsKey(src))
            addNode(src);

        if (!graph.containsKey(dst))
            addNode(dst);

        Edge<N, T> edge = new Edge<>(src, dst, label);
        graph.get(src).add(edge);
        this.edgeList.add(edge);

        if (!isDirect()) {
            edge = new Edge<>(dst, src, label);
            graph.get(dst).add(edge);
            this.edgeList.add(edge);
        }
    }

    public void addEdge(Edge<N, T> edge) throws GraphException {
        if (edge == null)
            throw new GraphException("source or destination cannot be null");

        N src = edge.getSrcNode(), dst = edge.getDstNode();
        if (!graph.containsKey(src))
            addNode(src);

        if (!graph.containsKey(dst))
            addNode(dst);

        graph.get(src).add(edge);
        this.edgeList.add(edge);

        if (!isDirect()) {
            graph.get(dst).add(new Edge<>(dst, src, edge.getLabel()));
            this.edgeList.add(edge);
        }
    }

    public boolean isDirect() {
        return direct;
    }

    public boolean hasNode(N value) throws GraphException {
        if (value == null)
            throw new GraphException("value parameter is null");

        return graph.containsKey(value);
    }

    public boolean hasEdge(N src, N dst) throws GraphException {
        if (src == null || dst == null)
            throw new GraphException("source or destination cannot be null");

        if (!graph.containsKey(src))
            return false;

        List<Edge<N, T>> adjList = graph.get(src);
        boolean found = false;

        for (int i = 0; !found && i < adjList.size(); i++)
            found = adjList.get(i).getDstNode().equals(dst);

        return found;
    }

    public void rmvNode(N value) throws GraphException {
        if (value == null)
            throw new GraphException("value cannot be null");

        graph.remove(value);
    }

    public void rmvEdge(N src, N dst) throws GraphException {
        if (src == null || dst == null)
            throw new GraphException("source or destination cannot be null");

        boolean removed = false;
        List<Edge<N, T>> adjList = graph.get(src);

        if (!adjList.isEmpty())
            for (int i = 0; !removed && i < adjList.size(); i++) {
                if (adjList.get(i).getDstNode().equals(dst)) {
                    removed = true;

                    this.edgeList.remove(adjList.get(i));
                    adjList.remove(i);
                }
            }

        if (removed && !isDirect()) {
            removed = false;
            adjList = graph.get(dst);
            if (!adjList.isEmpty())
                for (int i = 0; !removed && i < adjList.size(); i++) {
                    if (adjList.get(i).getDstNode().equals(src)) {
                        removed = true;
                        this.edgeList.remove(adjList.get(i));
                        adjList.remove(i);
                    }
                }
        }
    }

    public int getNodesCount() {
        return graph.size();
    }

    public int getEdgesCount() {
        int count = edgeList.size();

        if (!isDirect())
            count /= 2;

        return count;
    }

    public Set<N> getNodes() {
        return graph.keySet();
    }

    public List<Edge<N, T>> getEdgeList() {
        return this.edgeList;
    }

    public List<Edge<N, T>> getAdjList(N node) throws GraphException {
        if (node == null)
            throw new GraphException("node cannot be null");

        return graph.get(node);
    }

    public T getLabel(N src, N dst) throws GraphException {
        if (src == null && dst == null)
            throw new GraphException("src and dst cannot be null.");

        if (!hasEdge(src, dst))
            return null;

        List<Edge<N, T>> adjList = graph.get(src);
        T label = null;

        for (Edge<N, T> edge :
                adjList) {
            if (edge.getDstNode().equals(dst))
                label = edge.getLabel();
        }

        return label;
    }

    public void print() {
        int c = 0;
        List<Edge<N, T>> edges = getEdgeList();
        while (c < 20) {
            Edge<N, T> e = edges.get(c);
            System.out.println(e.getSrcNode() + " -- "
                    + e.getDstNode() + " = "
                    + e.getLabel() + ";");
            c++;
        }
    }

}




package Ex4.graph;

import Ex3.MinHeap;
import Ex3.MinHeapException;

import java.util.*;

/**
 * It represents a Graph composed by nodes with generic values. Graph can be
 * direct or indirect.
 *
 * @param <T>
 * @author birritteri, rondinella
 */
public class Graph<N, T extends Number> {
    private final Map<N, List<Edge<N, T>>> graph;
    private final List<Edge<N, T>> edgeList;
    private final boolean direct;

    /**
     * It is the constructor of a Graph. It creates an empty Graph direct or
     * indirect, depending on the parameter isDirect: if it is true the Graph is
     * direct, if false the Graph is indirect. It accepts a boolean parameter.
     *
     * @param isDirect: boolean value that represents if the Graph is direct or
     *                  indirect
     */
    public Graph(boolean isDirect) {
        this.graph = new HashMap<>();
        this.edgeList = new ArrayList<>();
        this.direct = isDirect;
    }

    /**
     * It adds a new Node into the Graph. It accepts as input a generic value.
     * Parameter cannot be null.
     *
     * @param node: generic value : to create Node<T>
     * @throws GraphException if the parameter is null.
     */
    public void addNode(N node) throws GraphException {
        if (node == null)
            throw new GraphException("node value cannot be null");

        graph.put(node, new ArrayList<>());
    }


    /**
     * It adds a new edge between source and destination.
     *
     * @param src,dst: generic values that represent source and
     *                 destination of the edge
     * @param label:   int value that represents the weight of the edge
     * @throws GraphException if the parameter is null.
     */
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


    /**
     * It returns the direct attribute of Graph.
     *
     * @return true iff Graph is direct, else false.
     */
    public boolean isDirect() {
        return direct;
    }


    /**
     * It searches a Node from is value. It accepts as input the value to search.
     * Parameter cannot be null.
     *
     * @param value: generic value to search in the Graph.
     * @throws GraphException iff parameters are null.
     * @return true iff there is a Node with this value in the Graph, else false.
     */
    public boolean hasNode(N value) throws GraphException {
        if (value == null)
            throw new GraphException("value parameter is null");

        return graph.containsKey(value);
    }


    /**
     * It searches an edge between source and destination. It accepts two generic
     * values. Parameters cannot be null.
     *
     * @param src,dst: generic values that represent source and
     *                 destination of the edge
     * @throws GraphException iff parameters are null.
     * @return true iff there is an edge between source and destination in the
     * Graph, else false.
     */
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


    /**
     * It removes, if the Graph contains it, a Node. It accepts as parameter the
     * value of the Node to remove. Parameter cannot be null.
     *
     * @param value: generic value of the Node to remove.
     * @throws GraphException: iff the parameter is null.
     */
    public void rmvNode(N value) throws GraphException {
        if (value == null)
            throw new GraphException("value cannot be null");

        graph.remove(value);
    }


    /**
     * It removes an edge between two Nodes. It accepts as parameter the value of
     * the Node to remove. Parameter cannot be null.
     *
     * @param src,dst: generic values that represent source and
     *                 destination of the edge to remove.
     * @throws GraphException: iff the parameter is null.
     */
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



    /**
     * It returns the count of Nodes of the Graph.
     *
     * @return the integer number of Nodes in the Graph.
     */
    public int getNodesCount() {
        return graph.size();
    }


    /**
     * It returns the count of Edges in the Graph.
     *
     * @return the integer count of Edges
     */
    public int getEdgesCount() {
        int count = edgeList.size();

        if (!isDirect())
            count /= 2;

        return count;
    }

    /**
     * It returns all the Nodes in the Graph.
     *
     * @return a Set of nodes
     */
    public Set<N> getNodes() {
        return graph.keySet();
    }


    /**
     * It returns the Edges in the Graph.
     *
     * @return the list of Edges
     */
    public List<Edge<N, T>> getEdgeList() {
        return this.edgeList;
    }


    /**
     * It returns the adjacent list of the Node. It accepts as input the Node.
     * Parameter cannot be null.
     *
     * @param node: the wanted Node.
     * @throws GraphException: iff the parameter is null.
     * @return ArrayList<Node <T>>, the adjacent list.
     */
    public List<Edge<N, T>> getAdjList(N node) throws GraphException {
        if (node == null)
            throw new GraphException("node cannot be null");

        return graph.get(node);
    }

    /**
     * It returns the label of the Edge which has src and dst values as Node.
     * If there isn't an Edge in the Graph, it returns null.
     *
     * @param src value of the source Node
     * @param dst value of the destination Node
     * @return the generic label of the Edge
     * @throws GraphException exception if
     */
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


    /**
     * It prints some information of the Graph. For each key (Node) it prints all
     * Nodes that have an edge with key.
     */
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

    MinHeap<Node<N, Number>> heap;
    Set<N> visited;
    HashMap<N, Number> distance;
    Set<N> nodes;
    Map<N, N> paths;
    N source;


    /**
     * It is an implementation of the Dijkstra algorithm on generic Graph.
     * @param source node where to start Dijkstra
     * @throws GraphException if edge is null
     */
    public void generateDijkstra(N source) throws GraphException, MinHeapException {
        this.source = source;
        heap = new MinHeap<>();
        visited = new HashSet<>();
        distance = new HashMap<>();
        paths = new HashMap<>();
        nodes = this.getNodes();

        for (N node : nodes) {
            distance.putIfAbsent(node, Double.POSITIVE_INFINITY);
        }

        heap.insert(new Node<>(source, 0.0));
        distance.replace(source, 0.0);

        while (visited.size() != nodes.size()) {
            if (heap.isEmpty()) {
                return;
            }

            N u = heap.extract().node;
            if (visited.contains(u)) {
                continue;
            }
            visited.add(u);
            graph_adjacentNodes(u);
        }
    }

    public void graph_adjacentNodes(N u) throws GraphException, MinHeapException {
        double edgeDistance;
        double newDistance;

        List<Edge<N, T>> adjList = this.getAdjList(u);

        for (Edge<N, T> stringDoubleEdge : adjList) {
            Node<N, T> v = new Node<>(stringDoubleEdge.getDstNode(), stringDoubleEdge.getLabel());

            if (!visited.contains(v.node)) {
                edgeDistance = v.cost.doubleValue();
                newDistance = distance.get(u).doubleValue() + edgeDistance;

                if (newDistance < distance.get(v.node).doubleValue()) {
                    distance.replace(v.node, newDistance);
                    paths.put(v.node, u);
                }

                heap.insert(new Node<>(v.node, distance.get(v.node)));
            }
        }
    }

    /**
     * It returns the distance in km between src and dst.
     *
     * @param path path from src to dst
     * @return the double value of the distance
     * @throws GraphException exception if
     */
    public Double calcPathLengthKm(LinkedList<N> path) throws GraphException {
        double sum = 0.0;
        for (int i = 0; (path != null) && (i < path.size() - 1) ; i++){
            N src = path.get(i);
            N dst = path.get(i + 1);

            sum += this.getLabel(src, dst).doubleValue();
        }
        return Math.floor(sum / 10) / 100;
    }


    /**
     * It returns the path between Dijkstra's src and dst.
     *
     * @param target dst
     * @return LinkedList of the path
     * @throws GraphException exception if
     */
    public LinkedList<N> getPathTo(N target) throws GraphException {
        LinkedList<N> path = new LinkedList<>();
        N step = target;
        if(source.equals(target)){
            path.add(target);
            return path;
        }
        if (paths.get(step) == null) {
            throw new GraphException("Impossible to find a path between \"" + source + "\" and \"" + target + "\"");
        }
        path.add(step);
        while (paths.get(step) != null) {
            step = paths.get(step);
            path.add(step);
        }
        Collections.reverse(path);
        return path;
    }

}




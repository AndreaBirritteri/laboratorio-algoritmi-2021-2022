package Ex4.graph;
/*
import Ex3.MinHeap;
import java.util.*;

public class Dijkstra {
    Graph<String, Double> graph;
    MinHeap<Node> heap;
    Set<String> visited;
    HashMap<String, Double> distance;
    Set<String> nodes;
    Map<String, String> paths;

    public Dijkstra(Graph<String, Double> graph, String source) throws GraphException {
        this.graph = graph;
        heap = new MinHeap<>();
        visited = new HashSet<>();
        distance = new HashMap<>();
        paths = new HashMap<>();
        nodes = graph.getNodes();

        for (String node : nodes) {
            distance.putIfAbsent(node, Double.MAX_VALUE);
        }

        heap.insert(new Node(source, 0.0));
        distance.replace(source, 0.0);

        while (visited.size() != nodes.size()) {
            if (heap.isEmpty()) {
                return;
            }

            String u = heap.extract().node;
            if (visited.contains(u)) {
                continue;
            }
            visited.add(u);
            graph_adjacentNodes(u);
        }
    }

    public void graph_adjacentNodes(String u) throws GraphException {
        double edgeDistance;
        double newDistance;

        List<Edge<String, Double>> adjList = graph.getAdjList(u);

        for (Edge<String, Double> stringDoubleEdge : adjList) {

            Node v = new Node(stringDoubleEdge.getDstNode(), stringDoubleEdge.getLabel());

            if (!visited.contains(v.node)) {
                edgeDistance = v.cost;
                newDistance = distance.get(u) + edgeDistance;

                if (newDistance < distance.get(v.node)) {
                    distance.replace(v.node, newDistance);
                    paths.put(v.node, u);
                }

                heap.insert(new Node(v.node, distance.get(v.node)));
            }

        }

    }

    public LinkedList<String> getPath(String target) {
        LinkedList<String> path = new LinkedList<>();
        String step = target;
        if (paths.get(step) == null) {
            return null;
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
*/
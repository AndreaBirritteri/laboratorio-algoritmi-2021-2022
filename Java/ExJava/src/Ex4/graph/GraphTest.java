package Ex4.graph;


import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

/**
 * @author birritteri, rondinella
 */
class GraphTest {
  private Graph<Integer, Float> directGraph, indirectGraph;

  @org.junit.jupiter.api.BeforeEach
  void setUp() {
    directGraph = new Graph<>(true);
    indirectGraph = new Graph<>(false);
  }

  @org.junit.jupiter.api.Test
  void addNode() throws GraphException {
    assertEquals(0, directGraph.getNodesCount());
    directGraph.addNode(1);
    assertEquals(1, directGraph.getNodesCount());

    assertEquals(0, indirectGraph.getNodesCount());
    indirectGraph.addNode(5);
    assertEquals(1, indirectGraph.getNodesCount());
  }

  @org.junit.jupiter.api.Test
  void addEdge() throws GraphException {
    assertEquals(0, directGraph.getEdgesCount());
    directGraph.addEdge(1, 2, 1.0F);
    assertEquals(1, directGraph.getEdgesCount());

    assertEquals(0, indirectGraph.getEdgesCount());
    indirectGraph.addEdge(3, 4, 3.0F);
    assertEquals(1, indirectGraph.getEdgesCount());
  }

  @org.junit.jupiter.api.Test
  void hasNode() throws GraphException {
    directGraph.addNode(129239912);
    assertTrue(directGraph.hasNode(129239912));

    indirectGraph.addNode(-1234812923);
    assertTrue(indirectGraph.hasNode(-1234812923));
  }

  @org.junit.jupiter.api.Test
  void hasEdge() throws GraphException {
    directGraph.addEdge(2341234, 324321134, -1234102.31234F);
    assertTrue(directGraph.hasEdge(2341234, 324321134));

    indirectGraph.addEdge(45684998, 43563456, -1234102.31234F);
    assertTrue(indirectGraph.hasEdge(45684998, 43563456));
    assertTrue(indirectGraph.hasEdge(43563456, 45684998));

  }

  @org.junit.jupiter.api.Test
  void rmvNode() throws GraphException {
    directGraph.addNode(123);
    assertEquals(1, directGraph.getNodesCount());
    directGraph.rmvNode(123);
    assertEquals(0, directGraph.getNodesCount());

    indirectGraph.addNode(321);
    assertEquals(1, indirectGraph.getNodesCount());
    indirectGraph.rmvNode(321);
    assertEquals(0, indirectGraph.getNodesCount());
  }

  @org.junit.jupiter.api.Test
  void rmvEdge() throws GraphException {
    directGraph.addEdge(2341234, 324321134, -1234102.31234F);
    assertEquals(1, directGraph.getEdgesCount());
    directGraph.rmvEdge(2341234, 324321134);
    assertEquals(0, directGraph.getEdgesCount());

    indirectGraph.addEdge(234, 342, -1234102.31234F);
    assertEquals(1, indirectGraph.getEdgesCount());
    indirectGraph.rmvEdge(234, 342);
    assertEquals(0, indirectGraph.getEdgesCount());
  }

  @org.junit.jupiter.api.Test
  void getNodesCount() throws GraphException {
    directGraph.addNode(21);
    assertEquals(1, directGraph.getNodesCount());

    indirectGraph.addNode(32);
    assertEquals(1, indirectGraph.getNodesCount());
  }

  @org.junit.jupiter.api.Test
  void getEdgesCount() throws GraphException {
    directGraph.addEdge(212, 321, 2929.2131f);
    assertEquals(1, directGraph.getEdgesCount());

    indirectGraph.addEdge(675, 456, 8976.345f);
    assertEquals(1, indirectGraph.getEdgesCount());
  }
}
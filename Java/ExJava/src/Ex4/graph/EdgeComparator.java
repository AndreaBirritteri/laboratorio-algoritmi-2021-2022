package Ex4.graph;

import java.util.Comparator;

public class EdgeComparator<N, T extends Number> implements Comparator<Edge<N, T>> {
	@Override
	public int compare(Edge<N, T> o1, Edge<N, T> o2) {
		return Double.compare(o1.getLabel().doubleValue(), o2.getLabel().doubleValue());
	}
}

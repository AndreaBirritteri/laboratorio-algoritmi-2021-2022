package Ex4.graphusage;

import Ex4.graph.Graph;
import Ex4.graph.GraphException;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;


public class GraphUsage {
    private static final Charset ENCODING = StandardCharsets.UTF_8;

    private static void loadFile(String filePath, Graph<String, Double> graph) throws IOException, GraphException {
        Path inputFilePath = Paths.get(filePath);

        try (BufferedReader fileInputReader = Files.newBufferedReader(inputFilePath, ENCODING)) {
            System.out.println("\nReading from " + filePath);
            String line;
            while ((line = fileInputReader.readLine()) != null) {
                String[] lineElements = line.split(",");
                graph.addEdge(lineElements[0], lineElements[1], Double.parseDouble(lineElements[2]));
            }
        }
        System.out.println("Data loaded.");
    }

    public static void main(String[] args) throws Exception {
        long timer = System.nanoTime();
        File file;

        if (args.length < 1)
            throw new Exception("Usage: Graph <file_name>");

        if (args[0].equalsIgnoreCase("default"))
            file = new File("../file/italian_dist_graph.csv");
        else
            file = new File(args[0]);

        Graph<String, Double> graph = new Graph<>(false);
        loadFile(file.getAbsolutePath(), graph);

        System.out.println("---------------Djikstra---------------");
        graph.dijkstra("torino");

        System.out.println(graph.getPath("catania"));

        Double sum = 0.0;
        for (int i = 0; i < graph.getPath("catania").size() - 1; i++) {
            String src = graph.getPath("catania").get(i);
            String dst = graph.getPath("catania").get(i + 1);


            sum += graph.getLabel(src, dst);
        }
        System.out.println(sum / 1000 + " km");


        timer = System.nanoTime() - timer;
        System.out.println("Execution in " + (timer / 1000000000) + "s");
    }
}

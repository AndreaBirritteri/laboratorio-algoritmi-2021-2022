import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {
        MinHeap<Integer> minheap = new MinHeap<>();
        minheap.insert(8);
        minheap.insert(6);
        minheap.insert(10);
        System.out.println(minheap);

        minheap.insert(4);
        minheap.insert(7);
        minheap.insert(5);
        System.out.println(minheap);

        minheap.insert(15);
        minheap.insert(4);
        minheap.insert(7);
        System.out.println(minheap);

        while (!minheap.isEmpty()) {
            System.out.println("heap Extract: " + minheap.extract());
            System.out.println(minheap);
        }

        if (args.length > 0) {
            System.out.println("\nBuild Min Heap");
            ArrayList<Integer> in = new ArrayList<>();
            Scanner scan = new Scanner(new File(args[0]));
            while (scan.hasNextInt()) {
                in.add(Integer.parseInt(scan.next()));
            }
            System.out.println("      in: " + in);
            minheap.buildHeap(in);
            System.out.println(minheap);
            System.out.println("  sorted: " + minheap.sort());
        }
    }
}
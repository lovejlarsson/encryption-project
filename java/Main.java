import java.io.*;
import java.nio.file.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws IOException {
        if (args.length < 3) {
            System.out.println("java Main <inputfil> <outputfil> <nyckel>");
            return;
        }
        
        String inputFile = args[0];
        String outputFile = args[1];
        String key = args[2];

        Path outputDir = Paths.get("outputJava");
        Path outputPath = outputDir.resolve(outputFile);

        List<String> lines = Files.readAllLines(Paths.get(inputFile));
        List<String> encryptedLines = new ArrayList<>();
        List<String> decryptedLines = new ArrayList<>();
        List<String> timeLines = new ArrayList<>();

        for (int i = 0; i < lines.size(); i++) {
            String line = lines.get(i);

            long startTime = System.nanoTime();
            
            String encrypted = XORkryptering.encrypt(line, key);
            encryptedLines.add(encrypted);
            
            String decrypted = XORkryptering.encrypt(encrypted, key);
            decryptedLines.add(decrypted);
            
            long endTime = System.nanoTime();

            long totalTimeMicro = (endTime - startTime) / 1000;
            timeLines.add(i + "," + totalTimeMicro);

        }

        Files.write(outputDir.resolve("encrypted.csv"), encryptedLines);
        Files.write(outputDir.resolve("decrypted.csv"), decryptedLines);
        Files.write(outputPath, timeLines);

        System.out.println("Klar, resultat sparat i: " + outputPath);

    }
}
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

        List<String> lines = Files.readAllLines(Paths.get(inputFile));
        List<String> encryptedLines = new ArrayList<>();
        List<String> decryptedLines = new ArrayList<>();
        List<String> timeLines = new ArrayList<>();

        for (int i = 0; i < lines.size(); i++) {
            String line = lines.get(i);

            long encryptStart = System.nanoTime();
            String encrypted = XORkryptering.encrypt(line, key);
            long encryptEnd = System.nanoTime();

            encryptedLines.add(encrypted);

            long decryptStart = System.nanoTime();
            String decrypted = XORkryptering.encrypt(encrypted, key);
            long decryptEnd = System.nanoTime();

            decryptedLines.add(decrypted);

            long encryptTime = encryptEnd - encryptStart;
            long decryptTime = decryptEnd - decryptStart;

            timeLines.add((i + 1) + " " + encryptTime + " " + decryptTime);

        }

        Files.write(Paths.get("encrypted.txt"), encryptedLines);
        Files.write(Paths.get("decrypted.txt"), decryptedLines);
        Files.write(Paths.get(outputFile), timeLines);

    }
}
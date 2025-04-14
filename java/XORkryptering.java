public class XORkryptering {

    public static String encrypt(String input, String key) {
        StringBuilder output = new StringBuilder();
        int keyLength = key.length();

        for (int i = 0; i < input.length(); i++) {
            char inputChar = input.charAt(i);
            char keyChar = key.charAt(i % keyLength);
            char xorChar = (char) (inputChar ^ keyChar);
            output.append(xorChar);
        }

        return output.toString();
    }
}
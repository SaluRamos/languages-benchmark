import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Random;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Main {

    public static void main(String[] args) {
        long startFib = System.currentTimeMillis();
        int resultFib = fib(40);
        long finishFib = System.currentTimeMillis();
        System.out.println("result fib = " + resultFib);

        long startGeometry = System.currentTimeMillis();
        double geometrySum = 0;
        for (int i = 0; i < 10000000; i++) {
            double[] vector3_1 = {randomUniform(1, 10), randomUniform(1, 10), randomUniform(1, 10)};
            double[] vector3_2 = {randomUniform(1, 10), randomUniform(1, 10), randomUniform(1, 10)};
            double radius = randomUniform(1, 10);
            geometrySum += testGeometry(vector3_1, vector3_2, radius);
        }
        long finishGeometry = System.currentTimeMillis();

        long startData = System.currentTimeMillis();
        String resultData = loadData();
        long finishData = System.currentTimeMillis();
        System.out.println("data hash = " + md5(resultData));

        System.out.println("Java 20.0.1 (2023-04-18):");
        System.out.println("teste fibonacci: " + (finishFib - startFib) + " ms");
        System.out.println("teste calculos geométricos: " + (finishGeometry - startGeometry) + " ms");
        System.out.println("teste leitura de arquivo 90MB: " + (finishData - startData) + " ms\n");
    }

    public static int fib(int n) {
        if (n == 0 || n == 1) {
            return n;
        } else {
            return fib(n - 1) + fib(n - 2);
        }
    }

    public static double testGeometry(double[] vector3_1, double[] vector3_2, double radius) {
        double distance = Math.sqrt(Math.pow(vector3_2[0] - vector3_1[0], 2) + Math.pow(vector3_2[1] - vector3_1[1], 2) + Math.pow(vector3_2[2] - vector3_1[2], 2));
        double distanceBetweenCenters = Math.sqrt(Math.pow(vector3_2[0] - vector3_1[0], 2) + Math.pow(vector3_2[1] - vector3_1[1], 2) + Math.pow(vector3_2[2] - vector3_1[2], 2));
        double sphereVolume = (4.0 / 3.0) * 3.1415 * Math.pow(radius, 3);
        return distance + distanceBetweenCenters + sphereVolume;
    }

    public static String md5(String str) {
        try {
            MessageDigest md = MessageDigest.getInstance("MD5");
            byte[] messageDigest = md.digest(str.getBytes());
            StringBuilder hexString = new StringBuilder();
            for (byte b : messageDigest) {
                String hex = Integer.toHexString(0xFF & b);
                if (hex.length() == 1) {
                    hexString.append('0');
                }
                hexString.append(hex);
            }
            return hexString.toString();
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static String loadData() {
        StringBuilder data = new StringBuilder();
        try {
            BufferedReader reader = new BufferedReader(new FileReader("../data.txt"));
            String line;
            while ((line = reader.readLine()) != null) {
                data.append(line);
            }
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return data.toString();
    }

    public static double randomUniform(double min, double max) {
        return min + Math.random() * (max - min);
    }

    public static int randomInt(int min, int max) {
        Random random = new Random();
        return random.nextInt(max - min + 1) + min;
    }
}
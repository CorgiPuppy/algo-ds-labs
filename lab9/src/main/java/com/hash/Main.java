package com.hash;

import java.util.Random;
import java.io.FileWriter;
import java.io.IOException;

import com.hash.utils.SHA1;

class Main {
    private static final Random random = new Random();
    
    public static void main(String[] args) {
        task1();
        task2();
        task3();
    }
    
    private static void task1() {
        try (FileWriter writer = new FileWriter("plots/dat-files/sha1_similarity.dat")) {
            int[] diffs = {1, 2, 4, 8, 16};
            for (int diff : diffs) {
                int maxCommon = 0;
                for (int i = 0; i < 1000; i++) {
                    String s1 = generateRandomString(128);
                    String s2 = modifyString(s1, diff);
                    String h1 = SHA1.hash(s1);
                    String h2 = SHA1.hash(s2);
                    int common = longestCommonSubstring(h1, h2);
                    if (common > maxCommon) {
                        maxCommon = common;
                    }
                }
                writer.write(diff + " " + maxCommon + "\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    private static void task2() {
        System.out.println("N\tCollisions");
        for (int i = 2; i <= 3; i++) {
            int N = (int) Math.pow(10, i);
            int collisions = 0;
            String[] hashes = new String[N];
            
            for (int j = 0; j < N; j++) {
                String s = generateRandomString(256);
                hashes[j] = SHA1.hash(s);
            }
            
            for (int j = 0; j < N; j++) {
                for (int k = j + 1; k < N; k++) {
                    if (hashes[j].equals(hashes[k])) {
                        collisions++;
                    }
                }
            }
            
            System.out.println(N + "\t" + collisions);
        }
    }
    
    private static void task3() {
        try (FileWriter writer = new FileWriter("plots/dat-files/sha1_speed.dat")) {
            writer.write("# Length Time(ms)\n");
            
            int[] lengths = {64, 128, 256, 512, 1024, 2048, 4096, 8192};
            for (int len : lengths) {
                long totalTime = 0;
                for (int i = 0; i < 1000; i++) {
                    String s = generateRandomString(len);
                    long start = System.nanoTime();
                    SHA1.hash(s);
                    long end = System.nanoTime();
                    totalTime += (end - start) / 1_000_000;
                }
                double avgTime = totalTime / 1000.0;
                writer.write(len + " " + avgTime + "\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    private static String generateRandomString(int length) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < length; i++) {
            sb.append((char) (random.nextInt(94) + 32));
        }
        return sb.toString();
    }
    
    private static String modifyString(String s, int changes) {
        char[] chars = s.toCharArray();
        for (int i = 0; i < changes; i++) {
            int pos = random.nextInt(s.length());
			// chars[pos] = (char) (random.nextInt(94) + 32);
			char tempChar = chars[pos];
			char newChar;
			do {
				newChar = (char) (random.nextInt(94) + 32);
			} while (newChar == tempChar);
			chars[pos] = newChar;
        }
        return new String(chars);
    }
    
    private static int longestCommonSubstring(String s1, String s2) {
        int max = 0;
        int[][] dp = new int[s1.length() + 1][s2.length() + 1];
        
        for (int i = 1; i <= s1.length(); i++) {
            for (int j = 1; j <= s2.length(); j++) {
                if (s1.charAt(i-1) == s2.charAt(j-1)) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                    if (dp[i][j] > max) {
                        max = dp[i][j];
                    }
                }
            }
        }
        
        return max;
    }
}

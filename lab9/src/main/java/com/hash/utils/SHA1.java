package com.hash.utils;

public class SHA1 {
    private static int h1 = 0x67452301;
    private static int h2 = 0xEFCDAB89;
    private static int h3 = 0x98BADCFE;
    private static int h4 = 0x10325476;
    private static int h5 = 0xC3D2E1F0;
    private static final int k1 = 0x5A827999;
    private static final int k2 = 0x6ED9EBA1;
    private static final int k3 = 0x8F1BBCDC;
    private static final int k4 = 0xCA62C1D6;

	public static String hash(String input) {
		String binary = convertToBinary(input);
		int originalLength = binary.length();
		
		binary = binary + "1";
		
		int neededLength = (originalLength + 1) % 512;
		int zerosToAdd;
		if (neededLength <= 448) {
			zerosToAdd = 448 - neededLength;
		} else {
			zerosToAdd = 512 - neededLength + 448;
		}
		
		StringBuilder message = new StringBuilder(binary);
		for (int i = 0; i < zerosToAdd; i++) {
			message.append("0");
		}
		
		String lengthBits = String.format("%64s", 
			Integer.toBinaryString(originalLength)).replace(' ', '0');
		message.append(lengthBits);
		
		if (message.length() % 512 != 0) {
			throw new IllegalStateException("Неправильное дополнение: " + message.length());
		}
		
		int[] mArray = new int[message.length() / 32];
		for (int i = 0; i < mArray.length; i++) {
			String word = message.substring(i * 32, (i + 1) * 32);
			mArray[i] = (int) Long.parseLong(word, 2);
		}
		
		return hash(mArray);
	}

	private static String convertToBinary(String word) {
		byte[] bytes = word.getBytes();
		StringBuilder binary = new StringBuilder();
		for (byte b : bytes) {
			for (int i = 7; i >= 0; i--) {
				binary.append((b >> i) & 1);
			}
		}
		return binary.toString();
	}

    private static String calculateMessageLength(int bitLength) {
        StringBuilder sb = new StringBuilder(Integer.toBinaryString(bitLength));
        while (sb.length() < 64) {
            sb.insert(0, 0);
        }
        return sb.toString();
    }

	private static String hash(int[] z) {
		int integer_count = z.length / 16;
		int[] intArray = new int[80];
		
		for (int i = 0; i < integer_count; i++) {
			System.arraycopy(z, i*16, intArray, 0, 16);
			
			for (int j = 16; j < 80; j++) {
				intArray[j] = leftrotate(intArray[j-3] ^ intArray[j-8] ^ intArray[j-14] ^ intArray[j-16], 1);
			}
			
			int A = h1;
			int B = h2;
			int C = h3;
			int D = h4;
			int E = h5;
			int t;
			
			for (int x = 0; x < 80; x++) {
				if (x < 20) {
					t = leftrotate(A,5) + ((B&C)|((~B)&D)) + E + intArray[x] + k1;
				} else if (x < 40) {
					t = leftrotate(A,5) + (B^C^D) + E + intArray[x] + k2;
				} else if (x < 60) {
					t = leftrotate(A,5) + ((B&C)|(B&D)|(C&D)) + E + intArray[x] + k3;
				} else {
					t = leftrotate(A,5) + (B^C^D) + E + intArray[x] + k4;
				}
				
				E = D;
				D = C;
				C = leftrotate(B,30);
				B = A;
				A = t;
			}
			
			h1 += A;
			h2 += B;
			h3 += C;
			h4 += D;
			h5 += E;
		}
		
		String h1Hex = String.format("%08x", h1);
		String h2Hex = String.format("%08x", h2);
		String h3Hex = String.format("%08x", h3);
		String h4Hex = String.format("%08x", h4);
		String h5Hex = String.format("%08x", h5);
		
		// Reset for next use
		h1 = 0x67452301;
		h2 = 0xEFCDAB89;
		h3 = 0x98BADCFE;
		h4 = 0x10325476;
		h5 = 0xC3D2E1F0;
		
		return h1Hex + h2Hex + h3Hex + h4Hex + h5Hex;
	}

    private static int leftrotate(int x, int shift) {
        return (x << shift) | (x >>> (32 - shift));
    }
}

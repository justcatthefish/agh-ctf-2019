package j.ctf;

import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;
import java.util.Base64;
import java.io.*;
import java.util.Scanner;
 
import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;

// class from https://howtodoinjava.com/security/java-aes-encryption-example/
class AES {
 
    private static SecretKeySpec secretKey;
    private static byte[] key;
 
    public static void setKey(String myKey)
    {
        MessageDigest sha = null;
        try {
            key = myKey.getBytes("UTF-8");
            sha = MessageDigest.getInstance("SHA-1");
            key = sha.digest(key);
            key = Arrays.copyOf(key, 16);
            secretKey = new SecretKeySpec(key, "AES");
        }
        catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
    }
 
    public static String encrypt(String strToEncrypt, String secret)
    {
        try
        {
            setKey(secret);
            Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");
            cipher.init(Cipher.ENCRYPT_MODE, secretKey);
            return Base64.getEncoder().encodeToString(cipher.doFinal(strToEncrypt.getBytes("UTF-8")));
        }
        catch (Exception e)
        {
            System.out.println("Error while encrypting: " + e.toString());
        }
        return null;
    }
 
    public static String decrypt(String strToDecrypt, String secret)
    {
        try
        {
            setKey(secret);
            Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5PADDING");
            cipher.init(Cipher.DECRYPT_MODE, secretKey);
            return new String(cipher.doFinal(Base64.getDecoder().decode(strToDecrypt)));
        }
        catch (Exception e)
        {
            System.out.println("Error while decrypting: " + e.toString());
        }
        return null;
    }
}

public class AesOhAes {
    public static void main(String[] args)
    {   
        String secretKey, flag;
        try {
            File file = new File("./secretPassword.txt"); 
            BufferedReader br = new BufferedReader(new FileReader(file)); 
            secretKey = br.readLine();
            
            file = new File("./flag.txt"); 
            br = new BufferedReader(new FileReader(file)); 
            flag =  br.readLine();
        } catch(IOException e) {
            System.out.println("Error reading key or flag file, contact admins");
            return;
        }

        Scanner inputScanner = new Scanner(System.in);
        while(true) {
            try {
                String input = inputScanner.nextLine();
                String decodedInput = new String(Base64.getDecoder().decode(input));
                String encryptedString = AES.encrypt(decodedInput+flag, secretKey);
                System.out.println(encryptedString);
            } catch (Exception e) {
                System.out.println("Wrong base64");
            }
        }
    }
}
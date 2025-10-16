//encrypt decrypt
internal class crypt
{
    public static string GetKey(string aa)
    {
        string filtered = Regex.Replace(aa.Trim(), "[\u4e00-\u9fa5]", "");
        string a = filtered.Trim();
        // 初始的128位密钥
        string initialKey = "lg13sgziwsaaig!z";
        byte[] keyBytes = Encoding.UTF8.GetBytes(initialKey);

        // 遍历输入字符串a
        for (int i = 0; i < a.Length && i < keyBytes.Length; i++)
        {
            if (char.IsLetterOrDigit(a[i])) // 如果是字母或数字
            {
                // 替换key中的对应位置的字符
                keyBytes[i] = (byte)a[i];
            }
        }

        // 将字节数组转换为字符串
        return Encoding.UTF8.GetString(keyBytes);
    }
    public static string EncryptString(string plainText, string secretKey)
    {
        // 确保密钥长度为16字节
        if (secretKey.Length != 16)
        {
            throw new ArgumentException("Secret key must be 16 bytes long");
        }

        byte[] key = Encoding.UTF8.GetBytes(secretKey);
        byte[] iv = Encoding.UTF8.GetBytes("1234567890123456"); // 初始化向量，必须是16字节

        using (Aes aesAlg = Aes.Create())
        {
            aesAlg.Key = key;
            aesAlg.IV = iv;
            aesAlg.Mode = CipherMode.CBC;
            aesAlg.Padding = PaddingMode.PKCS7;

            ICryptoTransform encryptor = aesAlg.CreateEncryptor(aesAlg.Key, aesAlg.IV);

            using (MemoryStream msEncrypt = new MemoryStream())
            {
                using (CryptoStream csEncrypt = new CryptoStream(msEncrypt, encryptor, CryptoStreamMode.Write))
                {
                    using (StreamWriter swEncrypt = new StreamWriter(csEncrypt))
                    {
                        swEncrypt.Write(plainText);
                    }
                }
                return Convert.ToBase64String(msEncrypt.ToArray());
            }
        }
    }

    public static string DecryptString(string cipherText, string secretKey)
    {
        // 确保密钥长度为16字节
        if (secretKey.Length != 16)
        {
            throw new ArgumentException("Secret key must be 16 bytes long");
        }

        byte[] key = Encoding.UTF8.GetBytes(secretKey);
        byte[] iv = Encoding.UTF8.GetBytes("1234567890123456"); // 初始化向量，必须是16字节

        try
        {
            byte[] cipherBytes = Convert.FromBase64String(cipherText);

            using (Aes aesAlg = Aes.Create())
            {
                aesAlg.Key = key;
                aesAlg.IV = iv;
                aesAlg.Mode = CipherMode.CBC;
                aesAlg.Padding = PaddingMode.PKCS7;

                ICryptoTransform decryptor = aesAlg.CreateDecryptor(aesAlg.Key, aesAlg.IV);

                using (MemoryStream msDecrypt = new MemoryStream(cipherBytes))
                {
                    using (CryptoStream csDecrypt = new CryptoStream(msDecrypt, decryptor, CryptoStreamMode.Read))
                    {
                        using (StreamReader srDecrypt = new StreamReader(csDecrypt))
                        {
                            return srDecrypt.ReadToEnd();
                        }
                    }
                }
            }
        }
        catch (Exception e)
        {
            Console.Error.WriteLine("Error in decryption: " + e.Message);
            return null;
        }
    }
 }
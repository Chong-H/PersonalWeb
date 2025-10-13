<template>
  <div class="project-info">
    <h2>ProjectName：PMS密码管理系统</h2>
    <h3>Role项目角色</h3>
    <p>项目经理，软件开发者</p>
    <h3>技术栈</h3>
    <div class="tech-list">
      <span class="tech-tag">SpringBoot</span>
      <span class="tech-tag">SpringDataJPA</span>
      <span class="tech-tag">.NET</span>
      <span class="tech-tag">Winform</span>
      <span class="tech-tag">RestfulAPI</span>
      <span class="tech-tag">VUE3</span>
      <span class="tech-tag">AES加密算法</span>
      <span class="tech-tag">ECDH密钥协商算法</span>
      <span class="tech-tag">Java</span>
      <span class="tech-tag">Ts</span>
      <span class="tech-tag">C#</span>
      <span class="tech-tag">nginx</span>
      <span class="tech-tag">OTP(TOTP)验证码生成算法</span>
      <span class="tech-tag">2fa验证</span>
    </div>
    <h3>项目内容</h3>
    <p>
      负责密码管理系统的开发和实现，采用CS和BS双架构。<br />
      CS架构程序部分主要使用C#语言和.NET
      Winform框架，实现对密码的增删改查功能。加密算法采用AES（128bit）算法，对数据库敏感词条（如账号和密码）进行加密存储和解密展示。<br />
      BS架构程序部分采用前后端分离的模式，展示各个账号信息。前后端交流时，通过ECDH算法协商生成信息交流的密钥，并使用AES加密进行数据传输。后端与数据库交互也通过AES加密进行。<br />
      本项目也实现了2fa验证码（基于OTP算法），可以代替Google Authenticator,SafeAuth,Microsoft
      Authenticator进行身份验证。<br />
      项目部署在RK3399单板机（Ubuntu）和Intel
      laptop（Win11）上，并使用花生壳进行内网穿透，开放端口到域名，实现外网访问。
    </p>
    <h3>CS客户端页面示例-2fa验证码生成</h3>
    <img class="image" src="@/assets/PMSPageCS.png" alt="密码管理系统界面截图" />
    <h3>BS客户端页面示例-信道密钥生成与协商</h3>
    <img class="image" src="@/assets/PMSPageBS.png" alt="密码管理系统界面截图" />
    <h3>BS客户端页面示例-加密数据交流演示</h3>
    <img class="image" src="@/assets/PMSPageBSCommunicate.png" alt="密码管理系统加密信道截图" />
    <h3>CS客户端页面示例-AES加密解密代码C#实现（部分）</h3>
    <CollapsibleCodeBlock :code="code1" :previewLines="8" />

    <h3>CS客户端页面示例-TOTP算法基于C#实现（部分）</h3>
    <CollapsibleCodeBlock :code="code2" :previewLines="8" />

    <h3>BS客户端页面示例-AES算法基于Java实现（部分）</h3>
    <CollapsibleCodeBlock :code="code3" :previewLines="8" />

    <h3>BS客户端页面示例-TOTP算法基于Java实现（部分）</h3>
    <CollapsibleCodeBlock :code="code4" :previewLines="8" />
  </div>
</template>

<script setup lang="ts">
// @ts-ignore   忽略这一行的类型检查。
import CollapsibleCodeBlock from './CollapsibleCodeBlock.vue'
const code4 = `
if(Objects.equals(decryptedAccount.classify, "2fa")){

                    // 你已有的 Base32 密钥字符串，例如 "JBSWY3DPEHPK3PXP"
                    String base32Secret = decryptedAccount.getPin(); // 从 Account 对象中获取 PIN 字段
                    // 把 Base32 转换为二进制密钥
                    byte[] secretBytes = new org.apache.commons.codec.binary.Base32().decode(base32Secret);
                    SecretKey secretKey = new javax.crypto.spec.SecretKeySpec(secretBytes, "HmacSHA1");

                    // 每 30 秒变一次
                    TimeBasedOneTimePasswordGenerator totp = new TimeBasedOneTimePasswordGenerator(Duration.ofSeconds(30));

                    // 当前时刻验证码
                    Instant now = Instant.now();
                    try{
                        int code = totp.generateOneTimePassword(secretKey, now);
                        decryptedAccount.setPin(String.format("%06d", code)); // 设置为6位数，前面补0
                    }catch (Exception e){
                        e.printStackTrace();
                    }
                }
                    `

const code3 = `
 package com.example.demo.services.classes;
import org.springframework.stereotype.Component;

import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.util.Base64;
@Component
public class AesUtils {

    private static final String ALGORITHM = "AES/CBC/PKCS5Padding";
    private static final String KEY_ALGORITHM = "AES";
    private static final byte[] IV = "1234567890123456".getBytes(); // 初始化向量，必须是16字节

    /**
     * AES加密
     * @param data 待加密数据
     * @param secretKey 密钥
     * @return 加密后的数据
     */
    public String encrypt(String data, String secretKey) {
        try {
            SecretKeySpec keySpec = new SecretKeySpec(secretKey.getBytes("UTF-8"), KEY_ALGORITHM);
            IvParameterSpec ivSpec = new IvParameterSpec(IV);
            Cipher cipher = Cipher.getInstance(ALGORITHM);
            cipher.init(Cipher.ENCRYPT_MODE, keySpec, ivSpec);
            byte[] encryptedBytes = cipher.doFinal(data.getBytes("UTF-8"));
            return Base64.getEncoder().encodeToString(encryptedBytes);
        } catch (Exception e) {
            e.printStackTrace();
            System.out.println("error encode");
            return null;
        }
    }

    /**
     * AES解密
     * @param encryptedData 待解密数据
     * @param secretKey 密钥
     * @return 解密后的数据
     */
    public String decrypt(String encryptedData, String secretKey) {
        try {
            SecretKeySpec keySpec = new SecretKeySpec(secretKey.getBytes("UTF-8"), KEY_ALGORITHM);
            IvParameterSpec ivSpec = new IvParameterSpec(IV);
            Cipher cipher = Cipher.getInstance(ALGORITHM);
            cipher.init(Cipher.DECRYPT_MODE, keySpec, ivSpec);
            byte[] decryptedBytes = cipher.doFinal(Base64.getDecoder().decode(encryptedData));
            return new String(decryptedBytes, "UTF-8");
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
}
 `
const code2 = `
//TOTP
using System;
using System.Security.Cryptography;
using System.Text;
public class TOTPUtil
{
    private const string Base32Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

    // Base32 解码
    public static byte[] Base32Decode(string base32)
    {
        base32 = base32.TrimEnd('=').ToUpperInvariant();
        byte[] result = new byte[base32.Length * 5 / 8];
        int buffer = 0, bitsLeft = 0, count = 0;

        foreach (char c in base32)
        {
            int val = Base32Chars.IndexOf(c);
            if (val < 0) continue;

            buffer <<= 5;
            buffer |= val & 31;
            bitsLeft += 5;

            if (bitsLeft >= 8)
            {
                result[count++] = (byte)((buffer >> (bitsLeft - 8)) & 0xFF);
                bitsLeft -= 8;
            }
        }
        Array.Resize(ref result, count);
        return result;
    }

    // 生成 TOTP
    public static string GenerateTOTP(string base32Secret, int digits = 6, int timestep = 30)
    {
        byte[] key = Base32Decode(base32Secret);

        long counter = DateTimeOffset.UtcNow.ToUnixTimeSeconds() / timestep;
        byte[] counterBytes = BitConverter.GetBytes(counter);
        if (BitConverter.IsLittleEndian)
        {
            Array.Reverse(counterBytes);
        }

        using (HMACSHA1 hmac = new HMACSHA1(key))
        {
            byte[] hash = hmac.ComputeHash(counterBytes);

            int offset = hash[hash.Length - 1] & 0x0F;
            int binary = ((hash[offset] & 0x7F) << 24)
                       | ((hash[offset + 1] & 0xFF) << 16)
                       | ((hash[offset + 2] & 0xFF) << 8)
                       | (hash[offset + 3] & 0xFF);

            int otp = binary % (int)Math.Pow(10, digits);
            return otp.ToString(new string('0', digits)); // 补零
        }
    }
}
 `
const code1 = `
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
`
</script>

<style scoped>
.image {
  display: block;
  max-width: 100%;
  height: auto;
  margin: 2rem auto;
  border-radius: 8px;
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.08);
}
.project-info {
  background: #fff;
  padding: 2rem;
  border-radius: 12px;
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.05);
  max-width: 1200px;
  margin: 2rem auto;
}
.project-info h2 {
  font-size: 2.6rem;
  font-weight: bold;
  margin-bottom: 1.5rem;
  background: linear-gradient(90deg, #409eff 40%, #67c23a 100%);
  color: transparent;
  -webkit-background-clip: text;
  background-clip: text;
  text-shadow: 0 2px 8px rgba(64, 158, 255, 0.12);
  letter-spacing: 2px;
}

.project-info h3 {
  font-size: 1.5rem;
  font-weight: bold;
  margin-top: 2rem;
  margin-bottom: 1rem;
  color: #409eff;
  text-shadow: 0 1px 4px rgba(64, 158, 255, 0.08);
  border-left: 5px solid #67c23a;
  padding-left: 0.6em;
  background: linear-gradient(90deg, #e0f7fa 0%, #fff 100%);
  border-radius: 6px;
}

.project-info p {
  font-size: 1.08rem;
  line-height: 1.8;
  margin-bottom: 0.8rem;
}
.tech-list {
  margin: 1rem 0 2rem 0;
  display: flex;
  flex-wrap: wrap;
  gap: 0.8rem;
}

.tech-tag {
  display: inline-block;
  font-size: 1.1rem;
  font-weight: bold;
  color: #fff;
  background: linear-gradient(90deg, #409eff 60%, #67c23a 100%);
  padding: 0.4em 1em;
  border-radius: 20px;
  box-shadow: 0 2px 8px rgba(64, 158, 255, 0.08);
  letter-spacing: 1px;
  transition: transform 0.2s;
}
.tech-tag:hover {
  transform: scale(1.08);
  background: linear-gradient(90deg, #67c23a 60%, #409eff 100%);
}
.code-block {
  background: #23272e;
  color: #dcdcdc;
  font-size: 0.95rem;
  padding: 1.2rem;
  border-radius: 8px;
  overflow-x: auto;
  margin: 1.5rem 0;
  line-height: 1.6;
  font-family: 'Fira Mono', 'Consolas', 'Menlo', 'Monaco', monospace;
}
</style>

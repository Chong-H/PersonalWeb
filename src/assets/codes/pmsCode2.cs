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
using System;
using System.Collections.Specialized;

namespace CSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            BitVector32 bv = new BitVector32(7896);
            int[] nums = new int[16] { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768};
            int val = 0;
            var m = BitVector32.CreateMask();

            for (int i = 0; i < nums.Length; ++i)
            {
                val += bv[m] ? nums[i] : 0;

                m = BitVector32.CreateMask(m);
            }

            return;
        }
    }
}
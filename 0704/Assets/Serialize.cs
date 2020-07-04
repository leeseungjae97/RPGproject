using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;
using UnityEngine;

using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.InteropServices;
using Assets.Factors;

namespace Assets.Scripts
{
    static class Serializer
    {
        static byte[] buffer;

        static Serializer()
        {
            buffer = new byte[0];
        }

        static void SetBufferSize(int size)
        {
            if (buffer.Length == size)
                return;
            else buffer = new byte[size];
        }

        public static byte[] Serialize<T>(T _object)
        {
            int size = Marshal.SizeOf(_object.GetType());
            SetBufferSize(size);
            using (MemoryStream ms = new MemoryStream())
            {
                BinaryFormatter bf = new BinaryFormatter();
                bf.Serialize(ms, _object);
                byte[] msBuffer = ms.ToArray();
                Buffer.BlockCopy(msBuffer, msBuffer.Length - size - 1, buffer, 0, size);
            }
            return buffer;
        }

        public static void Deserialize<T>(byte[] bytes, ref T _object)
        {
            int size = Marshal.SizeOf(_object.GetType());
            using (MemoryStream ms = new MemoryStream())
            {
                BinaryFormatter bf = new BinaryFormatter();
                bf.Serialize(ms, _object);
                byte[] msBuffer = ms.ToArray();
                Buffer.BlockCopy(bytes, 0, msBuffer, msBuffer.Length - size - 1, size);

                ms.SetLength(0);
                ms.Write(msBuffer, 0, msBuffer.Length);
                ms.Position = 0;
                _object = (T)bf.Deserialize(ms);
            }
        }



        //internal static void Deserialize<T>(byte[] recvBuf1, ref Item item)
        //{
        //    throw new NotImplementedException();
        //}
    }
}
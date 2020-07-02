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
namespace Assets.Scripts
{
    class ClientSok
    {
        Socket sock;
        public byte[] recMessage(int i)
        {
            byte[] recvBuf = new byte[i];
            int recvLen = sock.Receive(recvBuf);
            return recvBuf;
        }
        public void connect()
        {
            sock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            var ep = new IPEndPoint(IPAddress.Parse("192.168.30.23"), 4000);
            sock.Connect(ep);
 
        }
        public void send()
        {

        }
        public Socket getSock()
        {
            return sock;
        }
    }
}
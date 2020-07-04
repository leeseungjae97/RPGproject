using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace Assets
{
    [System.Serializable]
    struct SendPoint : Idata
    {
        public int type, x, y, z;
        public SendPoint(int type, int x, int y, int z)
        {
            this.type = type;
            this.x = x;
            this.y = y;
            this.z = z;
        }

    }

    [System.Serializable]
    struct RecvPoint : Idata
    {
        public int x, y, z;
        public int getX()
        {
            return x;
        }
        public int getY()
        {
            return y;
        }
        public int getZ()
        {
            return z;
        }

    }
}

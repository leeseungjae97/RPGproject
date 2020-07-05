using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assets.Factors
{
    [System.Serializable]
    struct Shop : Idata
    {
        public int Shop_code;
        public int Item_code;
        public int Npc_code;
        public int Index;
    }
}

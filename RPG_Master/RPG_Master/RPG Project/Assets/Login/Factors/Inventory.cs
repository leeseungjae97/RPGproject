using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assets.Factors
{
    [System.Serializable]
    struct Inventory : Idata
    {
        public int Inventory_code;
        public int Item_code;
        public int User_code;
        public int index;
    }
}

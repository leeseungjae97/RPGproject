using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assets.Factors
{
    [System.Serializable]
    struct Monster :Idata
    {
        public int Monster_code;
        public int Drop_item_code;
        public int Drop_exp;
        public int Damamge;
        public int Defense;
        public int Hp;
    }

 
}

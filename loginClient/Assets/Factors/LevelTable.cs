using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assets.Factors
{
    [System.Serializable]
    struct LevelTable : Idata
    {
        public int Level;
        public int RequireTotExp;
        public int Damamge;
        public int Defense;
        public int Hp;
    }
}

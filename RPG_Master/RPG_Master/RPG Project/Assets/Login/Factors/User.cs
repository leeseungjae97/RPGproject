using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assets.Factors
{
    [System.Serializable]
    struct User : Idata
    {
        public int User_code;
        public int id;
        public int password;
        public int totExp;
        public int Money;
        public int Login;
        public int Health;
        public int Level;
    }
}

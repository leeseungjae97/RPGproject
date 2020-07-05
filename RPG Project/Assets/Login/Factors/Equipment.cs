using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assets.Factors
{
    [System.Serializable]
    struct Equipment : Idata
    {
        public int Equipment_code;
        public int User_code;
        public int Head_item_code;
        public int Weapon_item_code;
        public int Shield_item_code;
        public int Shoes_item_code;
        public int Armor_item_code;
        public int Accessories_item_code;
        public int Gauntlets_item_code;
        public int BottomArmor_item_code;
    }
}

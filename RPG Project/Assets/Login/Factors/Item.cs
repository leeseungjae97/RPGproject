using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace Assets.Factors
{
    [System.Serializable]
    struct Item : Idata
    {
        public int Item_code;
        public int Item_name;
        public int damage;
        public int defence;
        public int price_to_shop;
        public int price_to_user;

        public Item(int Item_code, int Item_name, int damage, int defence, int price_to_shop, int price_to_user)
        {
            this.Item_code = Item_code;
            this.Item_name = Item_name;
            this.damage = damage;
            this.defence = defence;
            this.price_to_shop = price_to_shop;
            this.price_to_user = price_to_user;

        }


    }
}

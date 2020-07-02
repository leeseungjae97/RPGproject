using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Assets.Factors
{
    [System.Serializable]
    struct SendMemberInfo :Idata
    {
        public int type;
        public int id;
        public int password;


        public SendMemberInfo(int type, int id, int password)
        {
            this.type = type;
            this.id = id;
            this.password = password;
        }
    }
    [System.Serializable]
    struct RecvMemberInfo : Idata
    {
        public int id;
        public int password;

        public RecvMemberInfo(int id, int password)
        {
            this.id = id;
            this.password = password;

        }

    }
    //[System.Serializable]
    //struct SendMemberInfo
    //{
    //    public int type;
    //    public char[] id;
    //    public char[] password;


    //    public SendMemberInfo(int type, char[] id, char[] password)
    //    {
    //        this.type = type;
    //        this.id = id;
    //        this.password = password;
    //    }
    //}
    //[System.Serializable]
    //struct RecvMemberInfo : Idata
    //{
    //    public string id;
    //    public string password;

    //    public RecvMemberInfo(string id, string password)
    //    {
    //        this.id = id;
    //        this.password = password;

    //    }

    //}



}

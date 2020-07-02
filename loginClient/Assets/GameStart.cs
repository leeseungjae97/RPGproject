//using Cinemachine;
using System.Collections.Generic;
using System.Threading;
using UnityEngine;
using System;
using Assets.Scripts;
using Assets;
using System.Runtime.InteropServices;

public class gameStart : MonoBehaviour

{
    private Thread thread = null;
    private object lockObject = new object();       // 임계영역 처리를 위한 오브젝트 생성
    private static Queue<Task> TaskQueue = new Queue<Task>();
    ClientSok client;
    [SerializeField] public GameObject character;
    [SerializeField] public GameObject followCamera;
    private class Task
    {
        public int type;    // 작업 방식
        public Idata data;
    }
    // Start is called before the first frame update
    void Start()
    {

        GameObject myCharacter = Instantiate(character, transform.position, transform.rotation);
        //followCamera.GetComponent<CinemachineVirtualCamera>().Follow = myCharacter.transform;

        client = new ClientSok();
        client.connect();
        if (thread == null)
        {
            thread = new Thread(RunThread);
            thread.Start();
        }




    }
    // Update is called once per frame
    void Update()
    {
        while (TaskQueue.Count > 0)
        {
            Task task;

            task = TaskQueue.Dequeue();
            int num = task.type;
            switch (num)
            {
                case 0:
                    int x = ((RecvPoint)(task.data)).getX();
                    int y = ((RecvPoint)(task.data)).getY();
                    int z = ((RecvPoint)(task.data)).getZ();
                    print("value" + x + y + z);
                    print("0");

                    SendPoint sendPoint3 = new SendPoint(4, 3, 4, 5);
                    byte[] sendBuf = Serializer.Serialize<SendPoint>(sendPoint3);
                    int sendLen = client.getSock().Send(sendBuf);
                    print(sendLen);

                    break;



            }
        }

    }


    // 쓰레드 함수 구현
    void RunThread()
    {
        while (true)
        {
            // 처리
            byte[] recvBuf = client.recMessage(4);
            int num = BitConverter.ToInt32(recvBuf, 0);
            Task task = new Task();
            task.type = num;
            switch (num)
            {
                case 0:
                    RecvPoint recvPoint = new RecvPoint();
                    byte[] recvBuf1 = client.recMessage(Marshal.SizeOf(typeof(RecvPoint)));
                    task.type = BitConverter.ToInt32(recvBuf, 0);
                    Serializer.Deserialize<RecvPoint>(recvBuf1, ref recvPoint);
                    task.data = recvPoint;
                    break;

            }
            TaskQueue.Enqueue(task);
        }
    }





}


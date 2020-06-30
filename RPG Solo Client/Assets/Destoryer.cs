using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Destoryer : MonoBehaviour
{
   [SerializeField] GameObject targetToDestory = null;

   public void DestoryToTarget()
   {
       Destroy(targetToDestory);
   }
}

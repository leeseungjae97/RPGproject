using System.Collections;
using System.Collections.Generic;
using GameDevTV.Inventories;
using UnityEngine;

namespace RPG.Control
{
    [RequireComponent(typeof(Pickup))]
    public class ClickablePickup : MonoBehaviour, IRaycastable
    {
        Pickup pickup;

        private void Awake()
        {
            pickup = GetComponent<Pickup>();
        }

        public CursorType GetCursorType()
        {
            if (pickup.CanBePickedUp())
            {
                return CursorType.Pickup;
            }
            else
            {
                return CursorType.FullPickup;
            }
        }

        public bool HandleRaycast(PlayerController callingController)
        {
            if (Input.GetMouseButtonDown(0))
            {
                pickup.PickupItem();
            }
            return true;
        }
        // private void OnTriggerEnter(Collider other)
        // {
        //     GameObject dicisionPlayer = GameObject.Find("GameStart").GetComponent<gameStart>().myDicisionPlayer;
        //     if (other.gameObject == dicisionPlayer.GetComponent<dicision>().myAnimator)////////////내가 먹는 것만 처리하고 다른 놈들이 먹는 것은 여기서 하는 것이 아니라 그려주기 만 하기
        //     {
        //         dicisionPlayer.GetComponent<Fighter>().EquipItem(weapon.weaponNumber);/////////////////////이런식으로 다 인벤토리에 담기//현재는 걍 장착함
        //         StartCoroutine(HideForSeconds(respawnTime));
        //     }
        // }
    }
}

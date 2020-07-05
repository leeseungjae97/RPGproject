using System;
using System.Collections;
using System.Collections.Generic;
using RPG.Attributes;
using RPG.Control;
using UnityEngine;

namespace RPG.Combat
{
    public class WeaponPickup : MonoBehaviour, IRaycastable
    {
        [SerializeField] ItemConfig weapon = null;
        [SerializeField] float healthToRestore = 0;
        [SerializeField] float respawnTime = 5;
    
        private void OnTriggerEnter(Collider other) 
        {
            if (other.gameObject.tag == "Player")
            {
                Pickup(other.gameObject);
            }
        }

        private void Pickup(GameObject subject)
        {
            if (weapon != null)
            {
                subject.GetComponent<Fighter>().EquipWeapon(weapon);
            }
            if (healthToRestore > 0)
            {
                subject.GetComponent<Health>().Heal(healthToRestore);
            }
            StartCoroutine(HideForSeconds(respawnTime));
        }

        private IEnumerator HideForSeconds(float seconds)
        {
            ShowPickup(false);
            yield return new WaitForSeconds(seconds);
            ShowPickup(true);
        }

        private void ShowPickup(bool shouldShow)
        {
            GetComponent<Collider>().enabled = shouldShow;
            foreach (Transform child in transform)
            {
                child.gameObject.SetActive(shouldShow);
            }
        }

        public bool HandleRaycast(PlayerController callingController)
        {
            if (Input.GetMouseButtonDown(0))
            {
                Pickup(callingController.gameObject);
            }
            return true;
        }
        //Handle RayCast를 OnTriggerEnter로 바꾸기.
        // private void OnTriggerEnter(Collider other)
        // {
        //     GameObject dicisionPlayer = GameObject.Find("GameStart").GetComponent<gameStart>().myDicisionPlayer;
        //     if (other.gameObject == dicisionPlayer.GetComponent<dicision>().myAnimator)////////////내가 먹는 것만 처리하고 다른 놈들이 먹는 것은 여기서 하는 것이 아니라 그려주기 만 하기
        //     {
        //         dicisionPlayer.GetComponent<Fighter>().EquipItem(weapon.weaponNumber);/////////////////////이런식으로 다 인벤토리에 담기//현재는 걍 장착함
        //         StartCoroutine(HideForSeconds(respawnTime));
        //     }
        // }

        public CursorType GetCursorType()
        {
            return CursorType.Pickup;
        }
    }
}
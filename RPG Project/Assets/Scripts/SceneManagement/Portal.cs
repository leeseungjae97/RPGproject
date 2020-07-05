using System;
using System.Collections;
using RPG.Control;
using GameDevTV.Saving;
using UnityEngine;
using UnityEngine.AI;
using UnityEngine.SceneManagement;

namespace RPG.SceneManagement
{
    public class Portal : MonoBehaviour
    {
        enum DestinationIdentifier
        {
            A, B, C, D
        }

        [SerializeField] Transform spawnPoint;
        [SerializeField] DestinationIdentifier destination;
        [SerializeField] float fadeOutTime = 1f;
        [SerializeField] float fadeInTime = 2f;
        [SerializeField] float fadeWaitTime = 0.5f;

        private void OnTriggerEnter(Collider other) {
            if (other.tag == "Player")
            {
                StartCoroutine(Transition());
            }
        }

        private IEnumerator Transition()
        {

            Fader fader = FindObjectOfType<Fader>();
            //SavingWrapper savingWrapper = FindObjectOfType<SavingWrapper>();
            PlayerController playerController = GameObject.FindWithTag("Player").GetComponent<PlayerController>();
            playerController.enabled = false;
            
            yield return fader.FadeOut(fadeOutTime);
            
            Portal otherPortal = GetOtherPortal();

            UpdatePlayer(otherPortal);

            yield return new WaitForSeconds(fadeWaitTime);
            playerController.enabled = true;
            fader.FadeIn(fadeInTime);
        }

        private void UpdatePlayer(Portal otherPortal)
        {
            GameObject player = GameObject.FindWithTag("Player");
            player.GetComponent<NavMeshAgent>().enabled = false;
            player.transform.position = otherPortal.spawnPoint.position;
            player.transform.rotation = otherPortal.spawnPoint.rotation;
            player.GetComponent<NavMeshAgent>().enabled = true;
        }

        private Portal GetOtherPortal()
        {
            foreach (Portal portal in FindObjectsOfType<Portal>())
            {
                if (portal == this) continue;
                if (this.destination == DestinationIdentifier.A) {
                    if(portal.destination == DestinationIdentifier.B) return portal;
                }
                else if (this.destination == DestinationIdentifier.B) {
                    if(portal.destination == DestinationIdentifier.A) return portal;
                }
                else if (this.destination == DestinationIdentifier.C) {
                    if(portal.destination == DestinationIdentifier.D) return portal;
                }
                else if (this.destination == DestinationIdentifier.D) {
                    if(portal.destination == DestinationIdentifier.C) return portal;
                }
                //if (portal.destination != destination) continue;
            }

            return null;
        }
    }
}
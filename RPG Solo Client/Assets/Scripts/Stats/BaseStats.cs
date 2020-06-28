using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace RPG.Stats
{
    public class BaseStats : MonoBehaviour
    {   
        [Range(1, 99)]
        [SerializeField] int startinglevel = 1;
        [SerializeField] CharaterClass characterClass;
        [SerializeField] Progression progression = null;

        public float GetHealth()
        {
            return progression.GetHealth(characterClass, startinglevel);
        }
    }
} 
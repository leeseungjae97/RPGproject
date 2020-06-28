using System;
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
        [SerializeField] GameObject levelUpParticleEffect = null;
        [SerializeField] bool shouldUseModifiers = false;
        int currentLevel = 0;

        public event Action onLevelUp;
        private void Start() {
            currentLevel= CalculateLevel();
            Experience experience = GetComponent<Experience>();
            if(experience != null)
            {
                experience.onExperienceGained += UpdateLevel;    
            }
        }
        private void UpdateLevel() {
            int newLevel = CalculateLevel();
            if(newLevel > currentLevel)
            {
                currentLevel = newLevel;
                LevelUpEffect();
                onLevelUp();
            }
        }

        private void LevelUpEffect()
        {
            Instantiate(levelUpParticleEffect, transform);
        }

        public float GetStat(Stat stat)
        {
            return (GetBaseStat(stat) + GetAdditiveModifier(stat)) * (1 + GetPercentageModifier(stat)/ 100);
        }

        private float GetPercentageModifier(Stat stat) //damage Percentage + 
        {
            if(!shouldUseModifiers) return 0;
            
            float total = 0;
            foreach (IModifierProvier provider in GetComponents<IModifierProvier>())
            {
                foreach(float percentageModifier in provider.GetPercentageModifiers(stat))
                {
                    total += percentageModifier;
                }
            }
            return total;
        }

        private float GetBaseStat(Stat stat)
        {
            return progression.GetStat(stat, characterClass, GetLevel());
        }

        private float GetAdditiveModifier(Stat stat) //damage Weapon + stat
        {
            if(!shouldUseModifiers) return 0;

            float total = 0;
            foreach (IModifierProvier provider in GetComponents<IModifierProvier>())
            {
                foreach(float modifier in provider.GetAdditiveModifier(stat))
                {
                    total += modifier;
                }
            }
            return total;
        }

        public int GetLevel()
        {
            if(currentLevel < 1)
            {
                currentLevel = CalculateLevel(); 
            }
            return currentLevel;
        }

        private int CalculateLevel()
        {
            Experience experience = GetComponent<Experience>();
            if(experience == null) return startinglevel;

            float currentXP = experience.GetPoint();
            int penultimateLevel = progression.GetLevels(Stat.ExperienceToLevelUp, characterClass);
            for (int level = 1; level <= penultimateLevel; level++)
            {
                float XPToLevelUp = progression.GetStat(Stat.ExperienceToLevelUp, characterClass, level);
                if(XPToLevelUp > currentXP)
                {
                    return level;
                }
            }
            return penultimateLevel + 1;
        }

        internal float GetStat(object damage)
        {
            throw new NotImplementedException();
        }
    }
} 
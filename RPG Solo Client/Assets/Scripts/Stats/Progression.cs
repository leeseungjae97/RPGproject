using UnityEngine;
using System.Collections.Generic;
using System;

namespace RPG.Stats {
    [CreateAssetMenu (fileName = "Progression", menuName = "Stats/New Progression", order = 0)]
    public class Progression : ScriptableObject {
        [SerializeField] ProgressionCharacterClass[] characterClasses = null;

        Dictionary<CharaterClass, Dictionary<Stat, float[]>> lookupTable = null;

        public float GetStat(Stat stat, CharaterClass charaterClass,  int level)
        {
            BuildLookup();

            float[] levels = lookupTable[charaterClass][stat];

            if(levels.Length < level)
            {
                return 0;
            }
            return levels[level-1];
            // foreach (ProgressionCharacterClass progressionClass in characterClasses)
            // {
            //     if(progressionClass.characterClass != charaterClass) continue;

            //     foreach (ProgressionStat progressionStat in progressionClass.stats)
            //     {
            //         if(progressionStat.stat != stat) continue;

            //         if(progressionStat.levels.Length < level) continue;

            //         return progressionStat.levels[level -1];
            //     }
            // }
            // return 0;
        }

        public int GetLevels(Stat stat, CharaterClass charaterClass) {

            BuildLookup();

            float[] levels = lookupTable[charaterClass][stat];
            return levels.Length;
        }

        private void BuildLookup()
        {
            if(lookupTable != null) return;

            lookupTable = new Dictionary<CharaterClass, Dictionary<Stat, float[]>>();

            foreach (ProgressionCharacterClass progressionClass in characterClasses)
            {
                var statLookupTable = new Dictionary<Stat, float[]>();

                    foreach (ProgressionStat progressionStat in progressionClass.stats)
                    {
                        statLookupTable[progressionStat.stat] =  progressionStat.levels;
                    }

                lookupTable[progressionClass.characterClass] = statLookupTable;
            }

        }

        [System.Serializable]
        class ProgressionCharacterClass {
            public CharaterClass characterClass;
            public ProgressionStat[] stats;
            //public float[] health;
        }

        [System.Serializable]
        class ProgressionStat
        {
            public Stat stat;
            public float[] levels;
        }

    }
}
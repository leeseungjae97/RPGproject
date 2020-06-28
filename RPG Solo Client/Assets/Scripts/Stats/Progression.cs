using UnityEngine;

namespace RPG.Stats {
    [CreateAssetMenu (fileName = "Progression", menuName = "Stats/New Progression", order = 0)]
    public class Progression : ScriptableObject {
        [SerializeField] ProgressionCharacterClass[] characterClasses = null;

        public float GetHealth(CharaterClass charaterClass, int level)
        {
            foreach (ProgressionCharacterClass progressionClass in characterClasses)
            {
                if(progressionClass.charaterClass == charaterClass)
                {
                    return progressionClass.health[level-1];
                }
            }
            return 0;
        }

        [System.Serializable]
        class ProgressionCharacterClass {
            public CharaterClass charaterClass;
            public float[] health;
        }
    }
}
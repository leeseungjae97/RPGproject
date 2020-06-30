using System.Collections.Generic;

namespace RPG.Stats
{
    public interface IModifierProvier
    {
        IEnumerable<float> GetAdditiveModifier(Stat stat);
        IEnumerable<float> GetPercentageModifiers(Stat stat);
    }
}
using System.Collections;
using System.Collections.Generic;
using GameDevTV.Inventories;
using RPG.Stats;
using UnityEngine;

namespace RPG.Inventories
{
    public class StatsEquipment : Equipment, IModifierProvier
    {
        IEnumerable<float> IModifierProvier.GetAdditiveModifier(Stat stat)
        {
            foreach (var slot in GetAllPopulatedSlots())
            {
                var item = GetItemInSlot(slot) as IModifierProvier;
                if (item == null) continue;

                foreach (float modifier in item.GetAdditiveModifier(stat))
                {
                    yield return modifier;
                }
            }
        }

        IEnumerable<float> IModifierProvier.GetPercentageModifiers(Stat stat)
        {
            foreach (var slot in GetAllPopulatedSlots())
            {
                var item = GetItemInSlot(slot) as IModifierProvier;
                if (item == null) continue;

                foreach (float modifier in item.GetPercentageModifiers(stat))
                {
                    yield return modifier;
                }
            }
        }

    }
}

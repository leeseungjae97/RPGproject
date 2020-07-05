using RPG.Control;
using UnityEngine;
namespace RPG.NPC
{
    public class CanTalkNpc : MonoBehaviour, IRaycastable {
        public CursorType GetCursorType()
        {
            return CursorType.Trade;
        }

        public bool HandleRaycast(PlayerController callingController)
        {
            //상점 NPC의 component return

            //Quest NPC의 component return
            return true;
        }
    }
}
using MelonLoader;

namespace MelonSeed.Plugin
{
    public class Plugin : MelonPlugin
    {
        public override void OnApplicationEarlyStart()
        {
            MelonSeed.Init();
        }

        public override void OnPreModsLoaded()
        {
            MelonSeed.LateInit();
        }
    }
}
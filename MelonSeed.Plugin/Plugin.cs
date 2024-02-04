using MelonLoader;

namespace MelonSeed.Plugin
{
    public class Plugin : MelonPlugin
    {
        public override void OnPreInitialization()
        {
            MelonSeed.Init();
        }
    }
}
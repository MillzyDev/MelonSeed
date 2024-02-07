using System;
using MelonLoader;

namespace MelonSeed
{
    // ReSharper disable once UnusedType.Global
    public class Plugin : MelonPlugin
    {
        private Action? _melonSeedInit;
        private Action? _melonSeedStart;

        public override void OnPreInitialization()
        {
            var melonSeed = NativeLibrary.Load("MelonSeed/MelonSeed.dll");
            _melonSeedInit = melonSeed.GetExport<Action>("melon_seed_init");
            _melonSeedStart = melonSeed.GetExport<Action>("melon_seed_start");
            
            _melonSeedInit.Invoke();
        }

        public override void OnLateInitializeMelon()
        {
            _melonSeedStart!.Invoke();
        }
    }
}
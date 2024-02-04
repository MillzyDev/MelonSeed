using System;
using System.Runtime.InteropServices;

namespace MelonSeed.Plugin;

public static class MelonSeed
{
    [DllImport("MelonSeed/MelonSeed.dll", CharSet = CharSet.Auto, SetLastError = true)]
    public static extern void Init();
}
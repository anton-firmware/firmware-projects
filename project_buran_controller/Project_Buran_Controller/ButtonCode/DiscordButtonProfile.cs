using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Threading;

namespace Buran_Controller
{
    class DiscordButtonProfile : ButtonProfile
    {
        [DllImport("user32.dll", SetLastError = true)]
        static extern void keybd_event(byte bVk, byte bScan, int dwFlags, int dwExtraInfo);

        const int VIRTUAL_F5 = 0x74;
        const int VIRTUAL_KEY_DOWN = 0x0000;
        const int VIRTUAL_KEY_UP = 0x0002;

        ///<summary>Variable representing the mute setting for the discord button profile</summary>
        private bool MuteSetting { get; set; } = false;

        /// <summary>
        /// Constructor for discord button profile, calls the base constructor for ButtonProfile.
        /// </summary>
        /// <param name="ID">The ID for the button for firmware identification</param>
        /// <param name="Color">The color of the button.</param>
        /// <param name="Function">Enum representing the function of the button.</param>
        public DiscordButtonProfile(int ID, Color Color, BUTTON_FUNCTION Function, 
            string ButtonDescription) : base(ID, Color, Function, ButtonDescription) 
        {
              
        }

        /// <summary>
        /// Overriden function for the button function
        /// </summary>
        public override void ExecuteFunction()
        {
            Process p = Process.GetProcessesByName("discord").FirstOrDefault();

            if (p != null)
            {
                IntPtr h = p.MainWindowHandle;
                Thread.Sleep(10);
                keybd_event(VIRTUAL_F5, 0, VIRTUAL_KEY_DOWN, 0);
                Thread.Sleep(10);
                keybd_event(VIRTUAL_F5, 0, VIRTUAL_KEY_UP, 0);

                Debug.WriteLine("Buran: Discord mute toggle.");
            }
        }
    }
}

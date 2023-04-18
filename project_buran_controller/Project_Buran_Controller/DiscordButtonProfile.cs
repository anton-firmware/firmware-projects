using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace Buran_Controller
{
    class DiscordButtonProfile : ButtonProfile
    {

        [DllImport("User32.dll")]
        static extern int SetForegroundWindow(IntPtr point);

        ///<summary>Variable representing the mute setting for the discord button profile</summary>
        private bool MuteSetting { get; set; } = false;

        /// <summary>
        /// Constructor for discord button profile, calls the base constructor for ButtonProfile.
        /// </summary>
        /// <param name="ID">The ID for the button for firmware identification</param>
        /// <param name="Color">The color of the button.</param>
        /// <param name="Function">Enum representing the function of the button.</param>
        public DiscordButtonProfile(int ID, Color Color, BUTTON_FUNCTION Function) : base(ID, Color, Function) 
        {
              
        }
        /// <summary>
        /// Overriden function for the button function
        /// </summary>
        public override void ExecuteFunction()
        {
            //DiscordLocal.MuteSetting(!this.MuteSetting);

            Process p = Process.GetProcessesByName("discord").FirstOrDefault();
            if (p != null)
            {
                IntPtr h = p.MainWindowHandle;
                SetForegroundWindow(h);
                SendKeys.SendWait("^%");
            }
        }
    }
}

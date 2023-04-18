using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Buran_Controller
{
    public class BuranExecutive
    {
        /// <summary>Global button profile list the GUI uses to show buttons</summary>
        public static List<ButtonProfile> ButtonProfiles { get; set; } = new List<ButtonProfile>();

        /// <summary>Update GUI flag</summary>
        public static bool UpdateGUI = false;
    }
}

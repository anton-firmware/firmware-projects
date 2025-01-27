using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using Newtonsoft.Json;

namespace Buran_Controller
{
    public abstract class ButtonProfile
    {
        /// <summary>The ID of the button</summary>
        public int ID { get; set; }
        /// <summary>The color of the button</summary>
        public Color ButtonColor { get; set; }
        /// <summary>The function of the button</summary>
        public BUTTON_FUNCTION Function { get; set; }

        /// <summary>
        /// Constructor for generic button profile.
        /// </summary>
        /// <param name="ID">The ID for the button for firmware identification</param>
        /// <param name="ButtonColor">The color of the button.</param>
        /// <param name="Function">The function of the button.</param>
        public ButtonProfile(int ID, Color ButtonColor, BUTTON_FUNCTION Function)
        {
            this.ID = ID;
            this.ButtonColor = ButtonColor;
            this.Function = Function;
        }
        /// <summary> Generic method re</summary>
        public abstract void ExecuteFunction();
    }
}

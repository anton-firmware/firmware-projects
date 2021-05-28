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

        public ButtonProfile(int ID, Color ButtonColor, BUTTON_FUNCTION Function)
        {
            this.ID = ID;
            this.ButtonColor = ButtonColor;
            this.Function = Function;
        }
        /// <summary> Generic function for the button action </summary>
        public abstract void ExecuteFunction();
    }
}

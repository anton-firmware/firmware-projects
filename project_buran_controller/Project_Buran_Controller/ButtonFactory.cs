using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Buran_Controller
{
    public enum BUTTON_FUNCTION
    {
        DISCORD_MUTE,
        SLOBS_SCENE
    };

    public class ButtonFactory
    {
        /// <summary>SceneName used when constructing a SLOBS Scene Change button</summary>
        public static string SceneName { get; set; }
        /// <summary>Button ID used to identify the button for firmware and other uses</summary>
        public static int ID { get; set; }
        /// <summary>The color of the button to be created</summary>
        public static Color ButtonColor { get; set; }
        /// <summary>The function of the button</summary>
        public static BUTTON_FUNCTION Function { get; set; }

        /// <summary>
        /// Creates a ButtonProfile based on the set parameters of Color, ID, and Function specific parameters
        /// </summary>
        /// <returns>The created ButtonProfile</returns>
        public static ButtonProfile CreateButtonProfile()
        {
            ButtonProfile Button;

            switch (Function)
            {
                case BUTTON_FUNCTION.DISCORD_MUTE:
                    Button = new DiscordButtonProfile(ID, ButtonColor, Function);
                    break;
                case BUTTON_FUNCTION.SLOBS_SCENE:
                    Button = new StreamSceneButtonProfile(ID, ButtonColor, SceneName, Function);
                    break;
                default:
                    Button = null;
                    break;
            }

            return Button;
        }
    }
}

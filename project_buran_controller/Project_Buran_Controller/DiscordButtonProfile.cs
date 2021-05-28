using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Buran_Controller
{
    class DiscordButtonProfile : ButtonProfile
    {
        private bool MuteSetting { get; set; } = false;

        public DiscordButtonProfile(int ID, System.Drawing.Color Color, BUTTON_FUNCTION Function) : base(ID, Color, Function)
        {
        }

        public override void ExecuteFunction()
        {
            DiscordLocal.MuteSetting(!this.MuteSetting);
        }
    }
}

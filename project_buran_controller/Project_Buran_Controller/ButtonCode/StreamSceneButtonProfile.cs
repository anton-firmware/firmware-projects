using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Buran_Controller
{
    public class StreamSceneButtonProfile : ButtonProfile
    {
        public String SceneName { get; set; }

        public StreamSceneButtonProfile(int ID, System.Drawing.Color Color, String SceneName, BUTTON_FUNCTION Function) : base(ID, Color, Function)
        {
            this.SceneName = SceneName;
        }

        public override void ExecuteFunction()
        {
            SLOBSLocal.SwitchToScene(this.SceneName);
        }
    }
}

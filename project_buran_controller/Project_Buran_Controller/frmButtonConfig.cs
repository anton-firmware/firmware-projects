using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Buran_Controller
{
    public partial class frmButtonConfig : Form
    {
        public frmButtonConfig()
        {
            InitializeComponent();
            cboFunction.Items.AddRange(Enum.GetNames(typeof(BUTTON_FUNCTION)));
            //cboSceneSelect.Items.AddRange(SLOBSLocal.SceneValuePairs.Keys.ToArray());
        }

        private void frmButtonConfig_Load(object sender, EventArgs e)
        {
            guiUpdateTimer.Enabled = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ButtonFactory.ButtonColor = buttonColorDialog.Color;
            ButtonFactory.ID = 0;

            if (pnlScene.Visible)
            {
                ButtonFactory.SceneName = cboSceneSelect.SelectedItem.ToString();
            }

            ButtonFactory.Function = (BUTTON_FUNCTION)Enum.Parse(typeof(BUTTON_FUNCTION), cboFunction.SelectedItem.ToString());
            BuranExecutive.ButtonProfiles.Add(ButtonFactory.CreateButtonProfile());
            BuranExecutive.UpdateGUI = true;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            buttonColorDialog.ShowDialog();
            tboColorIndicator.BackColor = buttonColorDialog.Color;
        }

        private void lblFunction_Click(object sender, EventArgs e)
        {

        }

        private void guiUpdateTimer_Tick(object sender, EventArgs e)
        {
            if(cboFunction.SelectedItem != null)
            {
                if (cboFunction.SelectedItem.ToString() == BUTTON_FUNCTION.SLOBS_SCENE.ToString())
                {
                    pnlScene.Visible = true;
                }
                else
                {
                    pnlScene.Visible = false;
                }
            }
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            this.Hide();
        }
    }
}

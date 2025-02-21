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
        }

        private void frmButtonConfig_Load(object sender, EventArgs e)
        {
            guiUpdateTimer.Enabled = true;
            cboSceneSelect.Items.Clear();
            cboSceneSelect.Items.AddRange(SLOBSLocal.SceneValuePairs.Keys.ToArray());

            if (BuranExecutive.USBControl.buran_active) 
            {
                buttonIDUpDown.Enabled = true;
                btnAddButton.Enabled = true;
                buttonIDUpDown.Maximum = BuranExecutive.USBControl.number_of_buttons;
                buttonIDUpDown.Minimum = 1;
            }
            else
            {
                btnAddButton.Enabled = false;
                buttonIDUpDown.Enabled = false;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ButtonFactory.ButtonColor = buttonColorDialog.Color;
            ButtonFactory.ID = (int)buttonIDUpDown.Value;
            ButtonFactory.ButtonDescription = cboSceneSelect.Text;
            bool add = true;

            if (pnlScene.Visible)
            {
                ButtonFactory.SceneName = cboSceneSelect.SelectedItem.ToString();
            }

            ButtonFactory.Function = (BUTTON_FUNCTION)Enum.Parse(typeof(BUTTON_FUNCTION), cboFunction.SelectedItem.ToString());

            ButtonProfile existing_button = BuranExecutive.ButtonProfiles.Find(x => x.ID == ButtonFactory.ID);

            if (existing_button != null) 
            {
                DialogResult result = MessageBox.Show($"The button with ID {ButtonFactory.ID} has already been assigned to! Would you like to replace the assignment?", "Button Exists",
                    MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation);

                if (result == DialogResult.Yes) 
                {
                    BuranExecutive.ButtonProfiles.Remove(existing_button);
                }
                else
                {
                    add = false;
                }
            }

            if (add) 
            {
                BuranExecutive.ButtonProfiles.Add(ButtonFactory.CreateButtonProfile());
            }

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

        private void pnlScene_Paint(object sender, PaintEventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void cboFunction_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}

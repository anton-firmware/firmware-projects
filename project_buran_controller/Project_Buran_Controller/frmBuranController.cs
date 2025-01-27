using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Buran_Controller;
using Project_Buran_Controller;

namespace Buran_Controller
{
    public partial class frmBuranController : Form
    {
        frmButtonConfig buttonConfig;
        frmSettings SettingsDialog;

        public frmBuranController()
        {
            InitializeComponent();

            buttonConfig = new frmButtonConfig();
            SettingsDialog = new frmSettings(); 
        }

        private void frmBuranController_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            switch (ConfigManager.SaveButtonProfiles()) 
            {
                case BuranResult.Result.SUCCESS:
                    MessageBox.Show("Profiles saved successfully!", "Success!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    break;
                case BuranResult.Result.INVALID_PATH:
                    MessageBox.Show("Config path not set correctly!\n" +
                        "Please modify in the settings dialog!", "Unable to save!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    break;
                default:
                    MessageBox.Show("Unexpected error - Code 0x0!", "Unexpected error!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    break;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            buttonConfig.ShowDialog();
        }

        private void olvTimer_Tick(object sender, EventArgs e)
        {
            /*if(BuranExecutive.ButtonProfiles != null && BuranExecutive.UpdateGUI) 
            {
                this.olvController.SetObjects(BuranExecutive.ButtonProfiles);

                BuranExecutive.UpdateGUI = false;
            }*/
        }

        private void olvController_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void SettingsButton_Click(object sender, EventArgs e)
        {
            SettingsDialog.Show();
        }
    }
}

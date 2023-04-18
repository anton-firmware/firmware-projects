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

namespace Buran_Controller
{
    public partial class frmBuranController : Form
    {
        frmButtonConfig buttonConfig;
        USBControl USBControl;

        public frmBuranController()
        {
            InitializeComponent();

            buttonConfig = new frmButtonConfig();
            USBControl = new USBControl();
        }

        private void frmBuranController_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            USBControl.toggle_led();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            buttonConfig.ShowDialog();
        }

        private void olvTimer_Tick(object sender, EventArgs e)
        {
            if(BuranExecutive.ButtonProfiles != null && BuranExecutive.UpdateGUI) 
            {
                this.olvController.SetObjects(BuranExecutive.ButtonProfiles);

                BuranExecutive.UpdateGUI = false;
            }
        }

        private void olvController_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}

using Buran_Controller;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Project_Buran_Controller
{
    public partial class frmSettings : Form
    {

        private FolderBrowserDialog ConfigPathDialog;

        public frmSettings()
        {
            InitializeComponent();
            ConfigPathDialog = new FolderBrowserDialog(); 
        }

        private void frmSettings_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Hide();
        }

        private void ButtonProfilePathButton_Click(object sender, EventArgs e)
        {
            ConfigPathDialog.ShowDialog();
            ButtonPathTextBox.Text = ConfigPathDialog.SelectedPath;
        }

        private void ApplyButton_Click(object sender, EventArgs e)
        {
            BuranExecutive.BuranConfig.ButtonConfigFilePath = ConfigPathDialog.SelectedPath;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if(BuranExecutive.USBControl != null) 
            {
                string[] ports = BuranExecutive.USBControl.GetPorts();

                if (ports.Count() > 0)
                {
                    foreach (string port in ports)
                    {
                        COMPortComboBox.Items.Add(port);
                    }
                }
                else 
                {
                    BuranResult.RaiseMessageBox(BuranResult.Result.NO_PORTS);
                }
            }
        }

        private void ConfigGroup_Enter(object sender, EventArgs e)
        {

        }

        private void BuranButtonProfileButton_Click(object sender, EventArgs e)
        {
            ConfigPathDialog.ShowDialog();
            BuranPathTextBox.Text = ConfigPathDialog.SelectedPath;
        }
    }
}

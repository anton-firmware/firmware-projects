using Buran_Controller;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Windows.Forms;

namespace Project_Buran_Controller
{
    public partial class frmSettings : Form
    {
        private FolderBrowserDialog ConfigPathDialog;
        private List<String> COMPorts = new List<String>();
        
        public frmSettings()
        {
            InitializeComponent();
            PopulatePaths();
            ConfigPathDialog = new FolderBrowserDialog();
        }

        private void PopulateCOMPorts()
        {
            string[] ports = BuranExecutive.USBControl.GetPorts();

            if (ports.Count() > 0)
            {
                COMPorts.Clear();

                foreach (string port in ports)
                {
                    COMPorts.Add(port);
                }
            }
            else
            {
                BuranResult.RaiseMessageBox(BuranResult.Result.NO_PORTS);
            }
        }

        private void PopulatePaths()
        {
            string buranConfigPath = BuranExecutive.BuranConfig.BuranConfigFilePath;
            string buttonConfigPath = BuranExecutive.BuranConfig.ButtonConfigFilePath;

            if (!string.IsNullOrEmpty(buttonConfigPath))
            {
                ButtonPathTextBox.Text = buttonConfigPath;
            }

            if (!string.IsNullOrEmpty(buranConfigPath))
            {
                BuranPathTextBox.Text = buranConfigPath;
            }
        }

        private void frmSettings_Load(object sender, EventArgs e)
        {
            PopulateCOMPorts();
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
            BuranExecutive.BuranConfig.ButtonConfigFilePath = ButtonPathTextBox.Text;
            BuranExecutive.BuranConfig.BuranConfigFilePath = BuranPathTextBox.Text;

            this.Hide();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            COMPortComboBox.Items.Clear();

            if (BuranExecutive.USBControl != null) 
            {
                COMPortComboBox.Items.AddRange(COMPorts.ToArray());
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

        private void SerialConnectButton_Click(object sender, EventArgs e)
        {
            string com = COMPortComboBox.SelectedItem.ToString();

            if (BuranExecutive.USBControl.IsBuran(com)) 
            {
                int buttons = BuranExecutive.USBControl.GetButtons();
                this.label2.Text = buttons.ToString();
                this.BuranStatusDynmaicLabel.Text = "Active";
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            foreach (string com_port in COMPorts) 
            {
                if (BuranExecutive.USBControl.IsBuran(com_port))
                {
                    int buttons = BuranExecutive.USBControl.GetButtons();
                    this.label2.Text = buttons.ToString();
                    this.BuranStatusDynmaicLabel.Text = "Active";
                    MessageBox.Show($"Buran detected on {com_port} with {buttons} buttons!");
                    break;
                }
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            string path;

            if (!string.IsNullOrEmpty(BuranExecutive.BuranConfig.BuranConfigFilePath))
            {
                path = BuranExecutive.BuranConfig.BuranConfigFilePath;
            }
            else
            {
                path = System.Environment.GetFolderPath(Environment.SpecialFolder.CommonApplicationData);
                path = Path.Combine(path, "BuranData");
            }

            switch (ConfigManager.ImportBuranConfig(path))
            {
                case BuranResult.Result.SUCCESS:
                    MessageBox.Show("Profiles loaded successfully!", "Success!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    PopulatePaths();
                    break;
                case BuranResult.Result.INVALID_PATH:
                    MessageBox.Show("Buran path not set correctly!\n" +
                        "Please modify in the settings dialog!", "Unable to save!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    break;
                default:
                    MessageBox.Show("Unexpected error - Code 0x1", "Unexpected error!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    break;
            }
        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            string path;

            if (!string.IsNullOrEmpty(BuranExecutive.BuranConfig.BuranConfigFilePath))
            {
                path = BuranExecutive.BuranConfig.BuranConfigFilePath;
            }
            else 
            {
                path = System.Environment.GetFolderPath(Environment.SpecialFolder.CommonApplicationData);
                path = Path.Combine(path, "BuranData");

                if (!Directory.Exists(path)) 
                {
                    Directory.CreateDirectory(path);
                }
            }

            BuranExecutive.BuranConfig.BuranConfigFilePath = BuranPathTextBox.Text;
            BuranExecutive.BuranConfig.ButtonConfigFilePath = ButtonPathTextBox.Text;

            switch (ConfigManager.SaveConfigButtons(BuranExecutive.BuranConfig, path))
            {
                case BuranResult.Result.SUCCESS:
                    MessageBox.Show("Profiles saved successfully!", "Success!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    break;
                case BuranResult.Result.INVALID_PATH:
                    MessageBox.Show("Config path not set correctly!\n" +
                        "Please modify in the settings dialog!", "Unable to save!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    break;
                default:
                    MessageBox.Show("Unexpected error - Code 0x0", "Unexpected error!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    break;
            }
        }
    }
}

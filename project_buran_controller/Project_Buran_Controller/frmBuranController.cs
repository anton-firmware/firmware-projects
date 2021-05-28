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
        DiscordLocal discordLocal;
        frmButtonConfig buttonConfig;

        public frmBuranController()
        {
            InitializeComponent();

            buttonConfig = new frmButtonConfig();
        }

        private void frmBuranController_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            discordLocal = new DiscordLocal();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            //discordLocal.MuteSetting(true);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //discordLocal.MuteSetting(false);
            buttonConfig.ShowDialog();
        }
    }
}

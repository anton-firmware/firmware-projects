using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms.VisualStyles;

/**
 * This code is responsiple for communicating with the board over the COM port
 * By default the following options are assumed:
 * Baud rate: 9600
 * Parity: None
 * Data bits: 8
 * Stop bits: 1
 */

namespace Buran_Controller
{
    public class USBControl
    {
        private SerialPort SerialPort = null;

        public USBControl()
        {
            SerialPort = new SerialPort();
            SerialPort.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);

            SerialPort.BaudRate = 9600;
            SerialPort.StopBits = StopBits.One;
            SerialPort.DataBits = 8;
            SerialPort.Parity = Parity.None;
            SerialPort.Handshake = Handshake.XOnXOff;
            SerialPort.DtrEnable = true;
        }

        private static void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            ButtonProfile profile = BuranExecutive.ButtonProfiles.Find(x => x.ID == sp.ReadChar());

            profile.ExecuteFunction();
        }

        public string[] GetPorts() 
        {
            return SerialPort.GetPortNames();
        }

        public bool IsBuran(string name) 
        {
            SerialPort.Write(new byte[] { 128, 128 }, 0, 2);
            return true;
        }

        public void toggle_led()
        {
            SerialPort.Write(new byte[] { 128, 128 }, 0, 2);
        }
    }
}

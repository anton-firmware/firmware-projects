using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

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
        private const string COM_PORT = "COM4"; // COM Port whilst testing, will change later to make it so you can input from the gui
        private SerialPort SerialPort = null;

        public USBControl()
        {
            SerialPort = new SerialPort(COM_PORT);
            SerialPort.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);

            SerialPort.BaudRate = 9600;
            SerialPort.StopBits = StopBits.One;
            SerialPort.DataBits = 8;
            SerialPort.Parity = Parity.None;
            SerialPort.Handshake = Handshake.XOnXOff;

            SerialPort.Open();
            SerialPort.DtrEnable = true;

            SerialPort.DiscardOutBuffer();

            //SerialPort.Write(new byte[] { 97, 97 }, 0, 2);
        }

        private static void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            ButtonProfile profile = BuranExecutive.ButtonProfiles.Find(x => x.ID == sp.ReadChar());

            profile.ExecuteFunction();
        }

        public void toggle_led()
        {
            SerialPort.Write(new byte[] { 128, 128 }, 0, 2);
        }
    }
}

using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Security.Cryptography;
using System.Security.Principal;
using System.Text;
using System.Text.RegularExpressions;
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
        public bool buran_active { get; private set; } = false;
        public int number_of_buttons { get; private set; }  = -1;

        public USBControl()
        {
            SerialPort = new SerialPort();

            SerialPort.BaudRate = 9600;
            SerialPort.StopBits = StopBits.One;
            SerialPort.DataBits = 8;
            SerialPort.Parity = Parity.None;
            SerialPort.Handshake = Handshake.XOnXOff;
            SerialPort.DtrEnable = true;
            SerialPort.WriteTimeout = 50;
            SerialPort.ReadTimeout = 50;
        }

        private static void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            int button_id = Int32.Parse(Regex.Match(sp.ReadLine(), @"\d+").Value);
            ButtonProfile profile = BuranExecutive.ButtonProfiles.Find(x => x.ID == button_id);

            if (profile != null) 
            {
                profile.ExecuteFunction();
            }
        }

        public string[] GetPorts() 
        {
            return SerialPort.GetPortNames();
        }

        public int GetButtons() 
        {
            if (buran_active) 
            {
                SerialPort.Write(new byte[] { (byte)'B' }, 0, 1);
                string identify = SerialPort.ReadLine().TrimEnd('\r');
                this.number_of_buttons = Int32.Parse(Regex.Match(identify, @"\d+").Value);
                SerialPort.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);
            }

            return this.number_of_buttons;
        }

        public bool PollStatus()
        {
            bool result = false;

            SerialPort.Write(new byte[] { (byte)'I' }, 0, 1);
            string identify = SerialPort.ReadLine().TrimEnd('\r');

            if (identify != null)
            {
                if (identify == "BuranPCB")
                {
                    result = true;
                }
                else
                {
                    this.SerialPort.Close();
                    this.SerialPort.PortName = null;
                }
            }

            return result;
        }

        public bool IsBuran(string name) 
        {
            bool response = false;
            SerialPort.PortName = name;

            try 
            {
                if (!SerialPort.IsOpen)
                {
                    SerialPort.Open();
                }

                SerialPort.Write(new byte[] { (byte)'I' }, 0, 1);

                string identify = SerialPort.ReadLine().TrimEnd('\r');

                if (!string.IsNullOrEmpty(identify))
                {
                    if (identify == "BuranPCB")
                    {
                        buran_active = true;
                        response = true;
                    }
                    else
                    {
                        SerialPort.Close();
                        SerialPort.PortName = null;
                    }
                }
            }
            catch(Exception e) 
            { 
                SerialPort.Close();
            }

            return response;
        }
    }
}

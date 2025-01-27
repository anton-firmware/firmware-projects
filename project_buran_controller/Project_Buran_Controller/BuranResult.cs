using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Project_Buran_Controller
{
    public class BuranResult
    {
        public enum Result
        {
            SUCCESS,
            NO_BUTTONS,
            NO_PORTS,
            INVALID_PATH,
            FILE_ERROR,
            GENERAL_ERROR,
        }

        /// <summary>
        /// Helper function to generate an error message based on a given result.
        /// </summary>
        /// <param name="Result">Result to generate a message box.</param>
        public static void RaiseMessageBox(Result Result) 
        {
            switch(Result) 
            {
                case Result.NO_PORTS:
                    MessageBox.Show("No COM Ports detected, please check your connection!", "No COM Ports", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    break;
            }
        }   
    }
}

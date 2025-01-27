using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Project_Buran_Controller
{
    public class BuranConfig
    {
        /// <summary>Path to where button profiles should be saved</summary>
        public string ButtonConfigFilePath { get; set; } = null;

        /// <summary>Path to where the buran config profile should be saved</summary>
        public string BuranConfigFilePath { get; set; } = null;

        public BuranConfig() 
        {
            
        }
    }
}

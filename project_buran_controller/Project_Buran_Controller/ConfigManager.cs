using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Buran_Controller;
using Newtonsoft.Json;
using System.IO;

namespace Project_Buran_Controller
{
    public class ConfigManager
    {
        private static StringBuilder JSONConfig = new StringBuilder();
        private const string ButtonProfileFileName = "\\button_profiles.json";
        private const string BuranConfigFileName = "\\buran_profile_config.json";

        /// <summary>
        /// Save the button profiles in JSON format.
        /// </summary>
        /// <returns>The result of the save operation as a BuranResult.</returns>
        public static BuranResult.Result SaveButtonProfiles(List<ButtonProfile> buttonProfiles, string buttonConfigFilePath)
        {
            /** Assume Success. */
            BuranResult.Result result = BuranResult.Result.SUCCESS;

            if (buttonConfigFilePath == null)
            {
                result = BuranResult.Result.INVALID_PATH;
            }
            else if(buttonProfiles == null) 
            {
                result = BuranResult.Result.GENERAL_ERROR;
            }
            else if (buttonProfiles.Count == 0)
            {
                result = BuranResult.Result.NO_BUTTONS;
            }
            else
            {
                foreach (ButtonProfile profile in buttonProfiles)
                {
                    string ButtonJson = JsonConvert.SerializeObject(profile);
                    JSONConfig.Append(ButtonJson);
                }

                string FullPath = buttonConfigFilePath + ButtonProfileFileName;

                using (StreamWriter writer = new StreamWriter(FullPath))
                {
                    writer.WriteLine(JSONConfig.ToString());
                }
            }

            return result;
        }

        /// <summary>
        /// Save the Buran controller config in JSON Format.
        /// </summary>
        /// <returns>The result of the save operation as a BuranResult.</returns>
        public static BuranResult.Result SaveConfigButtons(BuranConfig buranConfig, string buttonConfigFilePath) 
        {
            /** Assume Success. */
            BuranResult.Result result = BuranResult.Result.SUCCESS;

            if (buttonConfigFilePath == null)
            {
                result = BuranResult.Result.INVALID_PATH;
            }
            else if (buranConfig == null)
            {
                result = BuranResult.Result.GENERAL_ERROR;
            }
            else
            {
                string BuranJson = JsonConvert.SerializeObject(buranConfig);
                JSONConfig.Append(BuranJson);

                string FullPath = buttonConfigFilePath + BuranConfigFileName;

                using (StreamWriter writer = new StreamWriter(FullPath))
                {
                    writer.WriteLine(JSONConfig.ToString());
                }
            }

            return result;
        }

        public static BuranResult.Result ImportConfig(string ButtonProfilePath) 
        {
            /** Assume Success. */
            BuranResult.Result result = BuranResult.Result.SUCCESS;

            return result;
        }

        public static BuranResult.Result ImportConfig(string BuranConfigPath)
        {
            /** Assume Success. */
            BuranResult.Result result = BuranResult.Result.SUCCESS;

            return result;
        }
    }
}

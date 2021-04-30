using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SLOBSharp;
using SLOBSharp.Client.Requests;
using SLOBSharp.Client.Requests.Scenes;
using SLOBSharp.Client.Responses;
using SLOBSharp.Client;
using SLOBSharp.Domain.Services;
using SLOBSharp.Domain;

namespace Buran_Controller
{
    public class SLOBSLocal
    {
        private SlobsPipeClient pipeClient;
        private string apiKey;

        public SLOBSLocal()
        {
            this.pipeClient = new SlobsPipeClient("slobs");
            this.apiKey = "";
        }

        public void authRequest()
        {
            issueRequest(SlobsRequestBuilder.NewRequest().SetMethod("auth").SetResource("TcpServerService").AddArgs(new string [] { apiKey }).BuildRequest());
        }

        /// <summary>
        /// Returns a dictionary with scene names and IDs from within SLOBS
        /// </summary>
        public Dictionary<String, String> getSceneNamesIDs()
        {
            List<SlobsResult> responses = issueRequest(SlobsRequestBuilder.NewRequest().SetMethod("getScenes").SetResource("ScenesService").BuildRequest()).Result.ToList();
            Dictionary<String, String> scenes = new Dictionary<String, String>();

            foreach(SlobsResult sr in responses)
            {
                scenes.Add(sr.Id, sr.Name);
            }

            return scenes;
        }

        public void switchToScene(string scene)
        {
            issueRequest(SlobsRequestBuilder.NewRequest().SetMethod("makeSceneActive").SetResource("ScenesService").AddArgs(new string[] { scene }).BuildRequest());
        }

        private SlobsRpcResponse issueRequest(ISlobsRequest request)
        {
            return this.pipeClient.ExecuteRequest(request);
        }
    }
}

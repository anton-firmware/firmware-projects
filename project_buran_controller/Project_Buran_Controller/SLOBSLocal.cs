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
        private static readonly SlobsPipeClient pipeClient = new SlobsPipeClient("slobs");
        private static readonly string apiKey = Environment.GetEnvironmentVariable("SLOBSAPI");
        public static Dictionary<String, String> SceneValuePairs { get; private set; }

        static SLOBSLocal()
        {
            SceneValuePairs = new Dictionary<string, string>();

            AuthRequest();
            GetSceneNamesIDs();
        }

        /// <summary>
        /// Issues an authentication request to the client so we can control it.
        /// </summary>
        private static void AuthRequest()
        {
            IssueRequest(SlobsRequestBuilder.NewRequest().SetMethod("auth").SetResource("TcpServerService").AddArgs(new string [] { apiKey }).BuildRequest());
        }

        /// <summary>
        /// Issues a request to the SLOBS service and forms a dictionary of scene names and IDs to be used later.
        /// </summary>
        private static void GetSceneNamesIDs()
        {
            List<SlobsResult> responses = IssueRequest(SlobsRequestBuilder.NewRequest().SetMethod("getScenes").SetResource("ScenesService").BuildRequest()).Result.ToList();
            Dictionary<String, String> scenes = new Dictionary<String, String>();

            foreach(SlobsResult sr in responses)
            {
                scenes.Add(sr.Name, sr.Id);
            }

            SceneValuePairs = scenes;
        }
        
        /// <summary>
        /// Issues a request to the SLOBS service to switch to a particular scene.
        /// </summary>
        /// <param name="scene">The scene ID to switch to.</param>
        public static void SwitchToScene(string scene)
        {
            IssueRequest(SlobsRequestBuilder.NewRequest().SetMethod("makeSceneActive").SetResource("ScenesService").AddArgs(new string[] { SceneValuePairs[scene] }).BuildRequest());
        }
        
        /// <summary>
        /// Issues a request to the SLOBS service and returns the response
        /// </summary>
        /// <param name="request"></param>
        /// <returns>The response of the request</returns>
        private static SlobsRpcResponse IssueRequest(ISlobsRequest request)
        {
            return pipeClient.ExecuteRequest(request);
        }
    }
}

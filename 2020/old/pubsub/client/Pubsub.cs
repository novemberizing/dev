using System;
using System.Net;
using System.IO;
using Newtonsoft.Json;
using System.Threading;
using System.Net.Http;
using System.Collections.Generic;

namespace client
{
    class Pubsub
    {

        String host = null;
        Thread thread = null;
        String auth = null;
        Boolean cancel = false;
        StreamReader reader = null;

        public Pubsub(String host, String auth)
        {
            this.host = host;
            this.auth = auth;
            this.on();

        }

        private void on()
        {
            thread = new Thread(new ThreadStart(run));
            thread.Start();
        }

        public void off()
        {
            cancel = true;
            if(reader != null)
            {
                reader.Close();
            }
        }

        private String httpGet(String url)
        {
            HttpWebRequest request = (HttpWebRequest) WebRequest.Create(url);
            request.Method = "GET";

            var webResponse = request.GetResponse();
            var webStream = webResponse.GetResponseStream();
            var responseReader = new StreamReader(webStream);
            var response = responseReader.ReadToEnd();
            Console.WriteLine("Response: " + response);
            responseReader.Close();
            return response;
        }
        public async void run()
        {
            while (cancel == false)
            {
                try
                {
                    using (var client = new HttpClient())
                    {
                        using (var stream = await client.GetStreamAsync(this.host + "/events/?auth=" + this.auth))
                        {
                            using (reader = new StreamReader(stream))
                            {
                                while (cancel == false)
                                {
                                    String line = reader.ReadLine();
                                    if (line.StartsWith("data: "))
                                    {
                                        String message = line.Substring(6);
                                        Console.WriteLine(message);
                                        var json = JsonConvert.DeserializeObject<Dictionary<String, Dictionary<String, String>>>(message);
                                        var map = json["message"];
                                        if (map != null)
                                        {
                                            foreach (KeyValuePair<String, String> pair in map)
                                            {
                                                // CALL DEL
                                                Console.WriteLine(pair.Key + " => " + pair.Value);
                                                httpGet(this.host + "/del/?auth=" + this.auth + "&key=" + pair.Key);
                                            }
                                        }
                                        else
                                        {
                                            foreach (String item in json.Keys)
                                            {
                                                Console.WriteLine(item);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.ToString());
                    Thread.Sleep(3000);
                }
            }
            reader.Close();
        }
    }

}

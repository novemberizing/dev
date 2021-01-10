using System;
using System.Threading;

namespace client
{
    class Program
    {
        static void Main(string[] args)
        {
            Pubsub pubsub = new Pubsub("http://localhost:8080", "93");
            Console.WriteLine("Hello World!");

            while(true)
            {
                Thread.Sleep(1000);
            }

            Console.WriteLine("Hello World!");
        }
    }
}

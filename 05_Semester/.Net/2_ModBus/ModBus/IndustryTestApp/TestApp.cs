/*
 Class for testing Assemblies 
 * IndustrieEngine
 * ModBus
 Vidmar/Brescher
*/
using IndustryEngine;
using ModBus;
using System.Reflection.PortableExecutable;
using Machine = IndustryEngine.Machine;

internal class Program
{
    private static int Main(string[] args)
    {
        Program application = new Program();
        application.TestApp();
        return 0 ;
    }

    internal void TestApp()
    {
        Console.WriteLine("- - - Vidmar / Brescher - - -");

        // Setup our Factory
        Machine machine0 = new Machine(0);
        Machine machine1 = new Machine(1);
        Machine machine2 = new Machine(2);
        Machine machine3 = new Machine(3);
        Machine machine4 = new Machine(4);

        Factory myFactory = new Factory();
        myFactory.AddMachine(machine0);
        myFactory.AddMachine(machine1);
        myFactory.AddMachine(machine2);
        myFactory.AddMachine(machine3);
        myFactory.AddMachine(machine4);

        Mapper myMapper = new Mapper(myFactory);

        Console.WriteLine("Start Modbus server");
        ModbusTCPServer myServer = new ModbusTCPServer();

        if (!myServer.StartServer(myMapper)) { Environment.Exit(1); }
        
        Console.WriteLine("Starting up our factory");
        if (!myFactory.IsRunning) { myFactory.Start(); }

        Thread publishThread = new Thread(myServer.publishData);
        publishThread.Start();

        Console.WriteLine("Start Client");
        Thread.Sleep(1000);

        // Client Test Start all Machines 
        ModbusTCPClient myClient = new ModbusTCPClient();
        myClient.StartClientConnection();
        try
        {
            myClient.TogglCoil(0);  // Machine 0
            myClient.TogglCoil(10); // Machine 1
            myClient.TogglCoil(20); // Machine 2
            myClient.TogglCoil(30); // Machine 3
            myClient.TogglCoil(40); // Machine 4
        }
        catch { Console.WriteLine("Error Client |Coils|"); }

        // Production cycle
        Thread.Sleep(10000);

        Console.WriteLine("Shutting down our factory");
        if (myFactory.IsRunning) { myFactory.Stop(); }

        Console.WriteLine("Output report for production");
        myFactory.Report();

        //Get Serverdata
        myServer.PrintData();

        Console.WriteLine("Disconnect Client & Server");
        myClient.DisconnectClient();
        myServer.StopServer();
    }
}
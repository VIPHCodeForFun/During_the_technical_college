/*
 Class for testing ModbusClient implementation with EasyModbus assembly
 Vidmar/Brescher
*/
using EasyModbus.Exceptions;
using ModBus;
using System;
using System.Reflection.PortableExecutable;
using System.Runtime.ConstrainedExecution;

/// <summary>
/// Test Programm
/// </summary>
internal class Program
{
    // Number of coils/registers to alter and display
    internal const int _clientArraySize = 22;

    // time between refreshs in ms
    internal const int _refreshIntervall = 1500;

    private static int Main(string[] args)
    {
        Program application = new Program();
        application.ClientTest(args);
        return 0;
    }

    /// <summary>
    /// Helper Function to handle the connection to the Modbus TCP Server
    /// </summary>
    /// <param name="client"><c>ModbusTCPClient</c> object</param>
    internal void ConnectToServer(ModbusTCPClient client)
    {
        while (true)
        {
            if (client.ServerReachable())
            {
                client.StartClientConnection();
                return;
            }
            else
            {
                Console.WriteLine("Server not reachable...");
            }
            Thread.Sleep(1000);

        }
    }

    /// <summary>
    /// Helper Function to handle Reconnects in case of a lost connection
    /// </summary>
    /// <param name="client"><c>ModbusTCPClient</c> object</param>
    internal void ReconnectToServer(ModbusTCPClient client)
    {
        Console.WriteLine("Lost connection, trying to reconnect...");
        client.DisconnectClient();
        Thread.Sleep(1000);
        ConnectToServer(client);
        Console.Clear();
    }

    /// <summary>
    /// Populates coils and Register with random values
    /// </summary>
    /// <param name="client">ModbusTCPClient instance</param>
    /// <param name="coilsArraySize">Range of coils to alter</param>
    internal void RandomizeValues(ModbusTCPClient client)
    {
        Random random = new Random();

        for (int i = 0; i < _clientArraySize; i++)
        {
            // randomize values
            if (random.Next(100) < 50)
            {
                client.TogglSingleCoil(i);
                client.SetSingleRegister(i, (short)random.Next(0, ushort.MaxValue));
            }
        }
    }
    /// <summary>
    /// This Function is used to demonstrate the Modbus TCP Client functions.
    /// It connects to a server and populates the coils and Holding-Registers with random values. Then it reads them back and displays them on the console.
    /// </summary>
    /// <param name="args">Arguments passed through from main()</param>
    internal void ClientTest(string[] args)
    {
        Console.Clear();
        Console.WriteLine("- - - Vidmar / Brescher - - -");

        // Setup
        ModbusTCPClient client = new ModbusTCPClient();
        ConnectToServer(client);
        Random random = new Random();

        int firstCoil = 0;
        bool[] CoilArray;
        int[] HoldingRegister;

        while (true)
        {
            try
            {

                for (int i = 0; i < _clientArraySize; i++)
                {
                    // initialize coils
                    client.SetSingleCoil(i, (random.Next(100) <= 50 ? true : false));
                }

                Console.WriteLine("Setting random values...");
                RandomizeValues(client);

                // read values
                CoilArray = client.GetCoilsArray(firstCoil, _clientArraySize);
                HoldingRegister = client.GetHoldingRegisterArray(firstCoil, _clientArraySize);

                // display values
                Console.SetCursorPosition(Console.WindowLeft, Console.WindowTop + 4);
                Console.WriteLine("┌─────────────┬─────────────┬─────────────────┬───────────────┐");

                for (int i = 0; i < _clientArraySize; i++)
                {
                    // Console.WriteLine("Coil=" + CoilArray[i] + " H-Register=" + HoldingRegister[i]);
                    Console.WriteLine("│  Coil {0,-2}    │ {1,-5}       │ H-Register {2,-2}   │ {3,-8}      │", i+1, CoilArray[i], i+1, HoldingRegister[i]);
                }

                Console.WriteLine("└─────────────┴─────────────┴─────────────────┴───────────────┘");
                
                Thread.Sleep(_refreshIntervall);

            }
            catch (ConnectionException ex)
            {
                Console.WriteLine(ex.ToString());
                ReconnectToServer(client);
            }
            catch (IndexOutOfRangeException ex)
            {
                Console.WriteLine(ex.ToString());
                ReconnectToServer(client);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
                Console.WriteLine(ex.StackTrace);
                continue;
            }
        }
    }

}// End of Class

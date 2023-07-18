/*
 Class to create a virtual machine 
 Vidmar/Brescher
*/

using System;
using System.Collections.Generic;
using System.Data.Common;
using System.Linq;
using System.Reflection;
using System.Reflection.PortableExecutable;
using System.Text;
using ModBus;


namespace IndustryEngine
{
    /// <summary>
    /// derived and extended class of machine
    /// </summary>
    public class Machine : IMachineInterface
    {
        // * interface members
        public int MachineId { get; }
        public MachineStatus Status { get; set; }
        public int NumberOfProducedItems { get; set; }

        public ModbusTCPServer ServerAccess;
        // * extended members

        /// <summary>
        /// Parameters for the machine speed <c>SpeedOfProcessing</c>
        /// </summary>
        public double SpeedOfProcessing { get; set; }

        /// <summary>
        /// Items produced per Run <c>ItemsPerRun</c>
        /// </summary>
        public int ItemsPerRun { get; set; }

        /// <summary>
        /// Current temperature of the machine <c>TemperatureOfMachine</c> 
        /// </summary>
        public double TemperatureOfMachine { get; set; }

        // * unix timestamp (ms), ItemsProduced

        /// <summary>
        /// List of <c>LogRecord</c> for an production Log
        /// </summary>
        internal List<LogRecord> _productionLog { get; set; }


        /// <summary>
        /// Constructor to create a machine with an custom identivier 
        /// </summary>
        /// <param name="machineId"></param>
        public Machine(int machineId, ModbusTCPServer server)
        {
            MachineId = machineId;
            NumberOfProducedItems = 0;
            Status = MachineStatus.Stopped;
            SpeedOfProcessing = 10;
            ItemsPerRun = 1;
            TemperatureOfMachine = 20.00;
            _productionLog = new List<LogRecord>();
            ServerAccess = server;
        }

        /// <summary>
        /// This method creats a new produced item and logs an <c>LogRecord</c>
        /// </summary>
        /// <param name="numberOfItems"></param>
        internal void ProducedItem(int numberOfItems)
        {
            NumberOfProducedItems++;
            DateTimeOffset now = DateTimeOffset.UtcNow;
            long unixTimeMilliseconds = now.ToUnixTimeMilliseconds();
            var record = new LogRecord(unixTimeMilliseconds, numberOfItems);
            _productionLog.Add(record);
        }

        /// <summary>
        /// Interface method
        /// </summary>
        /// <returns></returns>
        public bool StartProcessing()
        {
            Status = MachineStatus.Running;
            return true;
        }

        /// <summary>
        /// Interface method
        /// </summary>
        /// <returns></returns>
        public bool StopProcessing()
        {
            Status = MachineStatus.Stopped;
            return true;
        }

        /// <summary>
        /// Sets the number of Items that a <c>Machine</c> produces per cycle.
        /// </summary>
        /// <returns></returns>
        public bool setItemsPerRun(int itemsPerRun)
        {
            ItemsPerRun = itemsPerRun;
            return true;
        }

        /// <summary>
        /// Interface method for an endless thread. Checks the Machine Status on delay. 
        /// Chance of Errors and services with <c>_diceSet</c>
        /// A running machine is producing items
        /// </summary>
        /// <returns></returns>
        public void ThreadRun()
        {
            // Processing Loop
            while (true)
            {
                // -------- ERROR --------
                if (Status == MachineStatus.Error)
                {
                    // Reset Machine Data
                    NumberOfProducedItems = 0;
                    SpeedOfProcessing = 10;
                    ItemsPerRun = 1;
                    TemperatureOfMachine = 20.00;
                }
                // -------- STOPPED --------
                if (Status == MachineStatus.Stopped)
                {
                    // Set Temperature
                    if (TemperatureOfMachine > 10) { TemperatureOfMachine--; }
                }
                // -------- RUNNING --------
                if (Status == MachineStatus.Running)
                {
                    // Produce Item & Make a log
                    ProducedItem(ItemsPerRun);

                    // Set new Temperature
                    RandomizeValues();
                }

                // -------- PRINT DATA --------
                PrintMachineData();

                // -------- WAIT --------
                int time = (int)(10000.0 * (SpeedOfProcessing / 100));
                Thread.Sleep(time);

                // -------- UPDATE --------
                SetDataToModbusServer();

                int machineIndexSpace = MachineId * 10;
                // Set Start Stopp Repair for machine 
                if (ServerAccess.getSingleCoil(machineIndexSpace + 1) == true)
                {
                    Status = MachineStatus.Running;
                }
                else if (ServerAccess.getSingleCoil(machineIndexSpace + 2) == true)
                {
                    Status = MachineStatus.Stopped;
                }
                else if (ServerAccess.getSingleCoil(machineIndexSpace + 3))
                {
                    Status = MachineStatus.Error;
                }
            }
        }

        /// <summary>
        /// prints the actual MachineData on the terminal
        /// </summary>
        public void PrintMachineData()
        {
            Console.Clear();
            System.Console.WriteLine("---------------------------------------");
            System.Console.WriteLine("MachineId: " + MachineId);
            System.Console.WriteLine("Status: " + Status);
            System.Console.WriteLine("NumberOfProducedItems: " + NumberOfProducedItems + " stk");
            System.Console.WriteLine("SpeedOfProcessing: " + SpeedOfProcessing + " % of 10 sek");
            System.Console.WriteLine("ItemsPerRun: " + ItemsPerRun);
            System.Console.WriteLine("TemperatureOfMachine: " + TemperatureOfMachine + " °C");
            System.Console.WriteLine("---------------------------------------");
        }

        /// <summary>
        /// Update Data on ModbusServer
        /// </summary>
        public void SetDataToModbusServer()
        {
            int machineIndexSpace = MachineId * 10;
            ServerAccess.setSingleRegister(machineIndexSpace + 1, (short)Status);
            ServerAccess.setSingleRegister(machineIndexSpace + 2, (short)NumberOfProducedItems);
            ServerAccess.setSingleRegister(machineIndexSpace + 3, (short)SpeedOfProcessing);
            ServerAccess.setSingleRegister(machineIndexSpace + 4, (short)ItemsPerRun);
            ServerAccess.setSingleRegister(machineIndexSpace + 5, (short)TemperatureOfMachine);
        }

        /// <summary>
        /// Randomize some values for Grafana
        /// </summary>
        internal void RandomizeValues()
        {
            Random random = new Random();

            if (random.Next(100) > 66 || TemperatureOfMachine <= 20)
            {
                TemperatureOfMachine += 2;
            }
            else if (TemperatureOfMachine > 20)
            {
                TemperatureOfMachine -= 1;
            }

            if (random.Next(100) > 50 || SpeedOfProcessing <= 80)
            {
                SpeedOfProcessing += 5;
            }
            else if (SpeedOfProcessing >= 15)
            {
                SpeedOfProcessing -= 5;
            }
        }

        /// <summary>
        /// Read Data from ModbusServer
        /// </summary>
        public void ReadStateFromModbusServer()
        {
            int machineIndexSpace = MachineId * 10;

            int serverSpeedOfProcessing = ServerAccess.getSingleRegister(machineIndexSpace + 3);
            int serverItemsPerRun = ServerAccess.getSingleRegister(machineIndexSpace + 4);

            SpeedOfProcessing = ((short)SpeedOfProcessing != serverSpeedOfProcessing) ? serverSpeedOfProcessing : SpeedOfProcessing;
            ItemsPerRun = ((short)ItemsPerRun != serverItemsPerRun) ? serverItemsPerRun : ItemsPerRun;
        }

    }

}
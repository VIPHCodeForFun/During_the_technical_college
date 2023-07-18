/*
 Class to create a virtual machine 
 Vidmar/Brescher
*/
using DiceEngine;
using System;
using System.Collections.Generic;
using System.Data.Common;
using System.Linq;
using System.Reflection;
using System.Text;

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
        /// <c>DiceSet</c> for creating a <c>PockerHand</c>
        /// </summary>
        internal DiceSet _diceSet { get; set; }

        /// <summary>
        /// <c>PockerHand</c> to ermite different probabilities 
        /// </summary>
        internal PockerHand _hand = new PockerHand();

        /// <summary>
        /// Constructor to create a machine with an custom identivier 
        /// </summary>
        /// <param name="machineId"></param>
        public Machine(int machineId)
        {
            MachineId = machineId;
            NumberOfProducedItems = 0;
            Status = MachineStatus.Stopped;
            SpeedOfProcessing = 0;
            ItemsPerRun = 1;
            TemperatureOfMachine = 20.00;
            _productionLog = new List<LogRecord>();
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
                while (Status == MachineStatus.Running || Status == MachineStatus.Error)
                {
                    if (Status == MachineStatus.Error) { Console.WriteLine("Machine {0} is out of order!", MachineId); }
                    if (Status == MachineStatus.Stopped) { Console.WriteLine("Machine {0} is stopped.", MachineId); }
                    if (Status == MachineStatus.Running) { ProducedItem(ItemsPerRun); }

                    // The processing delay is used to simulate the speed from 1-100%
                    int delay = 1000;
                    if (SpeedOfProcessing == 0)
                    {
                        Status = MachineStatus.Stopped;
                    }
                    else
                    {
                        delay = (int)(1000 / SpeedOfProcessing);
                    }

                    // check MachineState on delay for fast shutdown
                    while (Status == MachineStatus.Running && delay > 0)
                    {
                        Thread.Sleep(250);
                        delay -= 250;
                    }

                    // Random chance of failure
                    _diceSet.RollAllDice();
                    if (_hand.CheckRoll(_diceSet) == "Three of a kind")
                    {
                        Status = MachineStatus.Error;
                    }

                    // From Error back to Running with 23% chance
                    if (Status == MachineStatus.Error && _hand.CheckRoll(_diceSet) == "Two pairs")
                    {
                        Status = MachineStatus.Running;
                    }

                }
            }
        }

    }
}

/*
 Class to create a virtual fabrick
 Vidmar/Brescher
*/
using DiceEngine;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IndustryEngine
{
    /// <summary>
    /// Class to create a virtual Factory who runs different machines
    /// </summary>
    public class Factory
    {
        /// <summary>
        /// List of different <c>Machine</c> 
        /// </summary>
        public List<Machine> _FactoryMachines;

        /// <summary>
        /// Factory <c>IsRunning</c> (True / False)
        /// </summary>
        public bool IsRunning { get; set; }

        /// <summary>
        /// Constructor for an new Factory, default <c>IsRunning</c> = false
        /// </summary>
        public Factory()
        {
            _FactoryMachines = new List<Machine>();
            IsRunning = false;
        }

        /// <summary>
        /// Adds a new machine to the factory
        /// </summary>
        /// <param name="machineToAdd"></param>
        /// <returns></returns>
        public bool AddMachine(Machine machineToAdd)
        {
            int listLengthBefore = _FactoryMachines.Count;
            _FactoryMachines.Add(machineToAdd);
            if (_FactoryMachines.Count > listLengthBefore)
            {
                return true;
            }
            return false;
        }

        /// <summary>
        /// Method to start a factory
        /// creates random Speed, a dice and a new thread for all machines.
        /// </summary>
        /// <returns></returns>
        public bool Start()
        {
            Thread mainThread = Thread.CurrentThread;
            Console.WriteLine("Starting up Machine Treads ...");
         
            Random random = new Random();

            // Compose a dice set
            DiceSide dAce = new DiceSide("Ace");
            DiceSide dKing = new DiceSide("King");
            DiceSide dQueen = new DiceSide("Queen");
            DiceSide dJack = new DiceSide("Jack");
            DiceSide d10 = new DiceSide("10");
            DiceSide d9 = new DiceSide("9");
            Dice diceOne = new Dice();
            diceOne.AddSide(dAce);
            diceOne.AddSide(dKing);
            diceOne.AddSide(dQueen);
            diceOne.AddSide(dJack);
            diceOne.AddSide(d10);
            diceOne.AddSide(d9);

            try
            {
                int check = 0;
                foreach (Machine machine in _FactoryMachines)
                {
                    // Ceate random machinespeed
                    machine.SpeedOfProcessing = random.NextDouble();
                    machine.setItemsPerRun(random.Next(1, 5));

                    // Create Dice
                    DiceSet machineDiceSet = new DiceSet(diceOne, 5);
                    machine._diceSet = machineDiceSet;

                    // Create Thread
                    Thread machineThread = new Thread(machine.ThreadRun);
                    machineThread.Start();
                    Console.WriteLine("Machinethread {0} is up" , ++check);
                }
                IsRunning = true;
            }
            catch (Exception ex) { return false; }
            return true;
        }

        /// <summary>
        /// Method to stop the factory -> all machines
        /// </summary>
        /// <returns></returns>
        public bool Stop()
        {
            Console.WriteLine("Stopping machines...");
            foreach (Machine machine in _FactoryMachines)
            {
                machine.StopProcessing();
            }

            // let machineThreads exit
            Thread.Sleep(250);

            IsRunning = false;
            return true;
        }

        /// <summary>
        /// Method for an Console Output all machines with
        ///     <c>MachineId</c> and <c>NumberOfProducedItems</c>
        /// </summary>
        public void Report()
        {
            foreach (Machine machine in _FactoryMachines)
            {
                Console.WriteLine("Machine {0} Produced {1} items", machine.MachineId, machine.NumberOfProducedItems);
            }
        }
    }
}

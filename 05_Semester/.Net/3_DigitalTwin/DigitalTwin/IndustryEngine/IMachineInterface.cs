/*
 Interface for new machines 
 Vidmar/Brescher
*/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IndustryEngine
{
    public enum MachineStatus { Running, Stopped, Error };

    /// <summary>
    /// Interface <c>IMachineInterface</c> for creating a new machine
    /// </summary>
    internal interface IMachineInterface
    {
        /// <summary>
        /// Indentify the machine with <c>MachineId</c>
        /// </summary>
        int MachineId { get; }

        /// <summary>
        /// Current <c>Status</c> of the machine
        /// </summary>
        MachineStatus Status { get; set; }

        /// <summary>
        /// Total number of produced Items
        /// </summary>
        int NumberOfProducedItems { get; }

        /// <summary>
        /// Set the <c>MachineStatus</c> to <c>Running</c>
        /// </summary>
        /// <returns>True</returns>
        public bool StartProcessing()
        {
            Status = MachineStatus.Running;
            return true;
        }

        /// <summary>
        /// Set the <c>MachineStatus</c> to <c>Stopped</c>
        /// </summary>
        /// <returns>True</returns>
        public bool StopProcessing()
        {
            Status = MachineStatus.Stopped;
            return true;
        }

        /// <summary>
        /// Endless loop for a new machinethread
        /// </summary>
        internal void ThreadRun()
        {
            // Processing Loop
            while (true)
            {
                // do something
            }
        }
    }
}

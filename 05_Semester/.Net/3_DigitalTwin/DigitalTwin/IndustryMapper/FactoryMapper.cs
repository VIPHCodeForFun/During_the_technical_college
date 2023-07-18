using IndustryEngine;
using EasyModbus;
using ModBus;

namespace IndustryMapper
{   
    /// <summary>
    /// Class to Mapp an Factory with an Modbus TCP-Server
    /// </summary>
    public class FactoryMapper
    {
        private ModbusTCPServer ourServer;
        private Factory ourFactory;

        /// <summary>
        /// Constructor for the Mapper
        /// </summary>
        /// <param name="ourServer"></param>
        /// <param name="ourFactory"></param>
        public FactoryMapper(ModbusTCPServer ourServer, Factory ourFactory)
        {
            this.ourServer = ourServer;
            this.ourFactory = ourFactory;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="coilNumber"></param>
        /// <param name="numberOfCoils"></param>
        /// <returns></returns>
        public bool handleCoils(int coilNumber, int numberOfCoils)
        {
            // 1  -> Machine 1 
            // 11 -> Machine 2
            // 21 -> Machine 3
            int machineId = (int)(coilNumber / 10) + 1;
            Console.WriteLine("Coil {0} bestätigt machineID {1}", coilNumber, machineId);
            return true;
        }

        /// <summary>
        /// Starts the machines in the factory
        /// </summary>
        /// <param name="machineId"></param>
        public void startMachine(int machineId)
        {
            ourFactory._FactoryMachines[machineId].StartProcessing();
        }

        /// <summary>
        /// Stops all machines in the factory
        /// </summary>
        /// <param name="machineId"></param>
        public void stopMachine(int machineId)
        {
            ourFactory._FactoryMachines[machineId].StopProcessing();
        }

        /// <summary>
        /// Fetches a machine from the service mode and starts it again
        /// </summary>
        /// <param name="machineId"></param>
        public void repairMachine(int machineId)
        {
            ourFactory._FactoryMachines[machineId].Status = MachineStatus.Running;
        }
    }
}
using IndustryEngine;
using EasyModbus;
using ModBus;

namespace IndustryMapper
{
    public class Mapper
    {
        private ModbusTCPServer ourServer;
        private Factory ourFactory;

        public Mapper(ModbusTCPServer ourServer, Factory ourFactory)
        {
            this.ourServer = ourServer;
            this.ourFactory = ourFactory;
        }
        public bool handleCoils(int coilNumber, int numberOfCoils)
        {
            // 1 -> 1
            // 11 -> 2
            // 21 -> 3
            int machineId = (int)(coilNumber / 10) + 1;
            Console.WriteLine("Coil {0} bestätigt machineID {1}", coilNumber, machineId);
                return true;

        }

        public void startMachine(int machineId)
        {
            ourFactory._FactoryMachines[machineId].StartProcessing();
        }

        public void stopMachine(int machineId)
        {
            ourFactory._FactoryMachines[machineId].StopProcessing();
        }
        public void repairMachine(int machineId)
        {
            ourFactory._FactoryMachines[machineId]._Status = MachineStatus.Running;
        }
    }
}
using System;

namespace MyApp // Note: actual namespace depends on the project name.
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            /*
             * AAS Model
             * 
            _easyModbusTCPServer.holdingRegisters[machineId * 10 + 1] = (short)machine.Status;
            https://example.com/ids/prop/343fe2b7-392d-432a-9842-a99f7f964336

            _easyModbusTCPServer.holdingRegisters[machineId * 10 + 2] = (short)machine.NumberOfProducedItems;
            https://example.com/ids/prop/59667297-3de6-4e00-b610-ecd8dec14fef

            _easyModbusTCPServer.holdingRegisters[machineId * 10 + 3] = (short)machine.SpeedOfProcessing;
            https://example.com/ids/prop/f5089e14-e2a5-46d2-a5f2-aebd6aec9fef

            (_easyModbusTCPServer.holdingRegisters[machineId * 10 + 4] = (short)machine.ItemsPerRun;)

            _easyModbusTCPServer.holdingRegisters[machineId * 10 + 5] = (short)machine.TemperatureOfMachine;
            https://example.com/ids/prop/e9122abe-d684-463f-a429-88e35f87a7b2
            */
        }
    }
}
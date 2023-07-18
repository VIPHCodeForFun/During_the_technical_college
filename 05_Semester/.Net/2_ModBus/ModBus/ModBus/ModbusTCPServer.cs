/*
 Class for creating an TCP ModBus Server
 Vidmar/Brescher
*/
using EasyModbus; //EasyModbusTCP 5.6.0 MIT
using System.IO.Ports;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using static EasyModbus.ModbusServer;
using IndustryEngine;
using System.Runtime.InteropServices;

namespace ModBus
{
    /// <summary>
    /// Class to setup an new <c>ModbusTCPServer</c>
    /// </summary>
    public class ModbusTCPServer
    {
        /// <summary>
        /// <c>_easyModbusTCPServer</c> New Server instance
        /// <c>_startingAddressDiscreteInputs</c>
        /// <c>_startingAddressCoils</c>
        /// <c>_startingAddressCoils</c>
        /// <c>_startingAddressHoldingRegisters</c>
        /// <c>_startingAddressInputRegisters</c>
        /// <c>_industryMapper</c> Mapper for the <c>IndustryEngine</c>
        /// </summary>
        private EasyModbus.ModbusServer _easyModbusTCPServer;
        private UInt16 _startingAddressDiscreteInputs = 1;
        private UInt16 _startingAddressCoils = 1;
        private UInt16 _startingAddressHoldingRegisters = 1;
        private UInt16 _startingAddressInputRegisters = 1;
        private Mapper _industryMapper;

        /// <summary>
        /// Method to start the server with an Mapper
        /// </summary>
        /// <param name="ourMapper"></param>
        public bool StartServer(Mapper ourMapper)
        {
            _industryMapper = ourMapper;
            _easyModbusTCPServer = new ModbusServer();
            _easyModbusTCPServer.Port = 502;
            try
            {
                _easyModbusTCPServer.Listen();
            }
            catch (Exception ex) { 
                Console.WriteLine(ex.Message);
                return false; 
            }

            _easyModbusTCPServer.CoilsChanged += new ModbusServer.CoilsChangedHandler(CoilsChanged);
            _easyModbusTCPServer.HoldingRegistersChanged += new ModbusServer.HoldingRegistersChangedHandler(HoldingRegistersChanged);
            _easyModbusTCPServer.NumberOfConnectedClientsChanged += new ModbusServer.NumberOfConnectedClientsChangedHandler(NumberOfConnectionsChanged);
            _easyModbusTCPServer.LogDataChanged += new ModbusServer.LogDataChangedHandler(LogDataChanged);
            return true;
        }

        /// <summary>
        /// Thread Method to update the factory -> machines with the Server Informations
        /// </summary>
        public void publishData()
        {
            while (true)
            {
                foreach (var machine in _industryMapper.OurFactory._FactoryMachines)
                {
                    int machineId = machine.MachineId;
                    if (machine.Status == MachineStatus.Running)
                    {
                        _easyModbusTCPServer.holdingRegisters[machineId * 10 + 1] = 1;

                    }
                    else if (machine.Status == MachineStatus.Stopped)
                    {
                        _easyModbusTCPServer.holdingRegisters[machineId * 10 + 1] = 0;
                    }
                    _easyModbusTCPServer.holdingRegisters[machineId * 10 + 1] = (short)machine.Status;
                    _easyModbusTCPServer.holdingRegisters[machineId * 10 + 2] = (short)machine.NumberOfProducedItems;
                    _easyModbusTCPServer.holdingRegisters[machineId * 10 + 3] = (short)machine.SpeedOfProcessing;
                    _easyModbusTCPServer.holdingRegisters[machineId * 10 + 4] = (short)machine.ItemsPerRun;
                    _easyModbusTCPServer.holdingRegisters[machineId * 10 + 5] = (short)machine.TemperatureOfMachine;
                }
                Thread.Sleep(500);
            }
        }

        /// <summary>
        /// Method to stop the Server
        /// </summary>
        public void StopServer()
        {
            _easyModbusTCPServer.StopListening();
        }

        /// <summary>
        /// Method gets called when an Coil gets Changed
        /// Used to set new status for an machine 
        /// </summary>
        /// <param name="coil"></param>
        /// <param name="numberOfCoil"></param>
        internal void CoilsChanged(int coil, int numberOfCoil)
        {
            // Coil     Procedure
            //  1       Start
            //  2       Stop
            //  3       repair
            Console.WriteLine("CoilsChanged: coil {0}, numberOfCoil {1}", coil, numberOfCoil);
            _industryMapper.handleCoils(coil, numberOfCoil);
        }

        /// <summary>
        /// Method gets called on HoldingRegistersChanged event
        /// NOT USED
        /// </summary>
        /// <param name="startingAddress"></param>
        /// <param name="numberOfRegisters"></param>
        internal void HoldingRegistersChanged(int startingAddress, int numberOfRegisters)
        {
            // do something
            Console.WriteLine("HoldingRegistersChanged: startingAddress {0}, numberOfRegisters {1}", startingAddress, numberOfRegisters);
        }

        /// <summary>
        /// Method gets called on NumberOfConnectedClientsChanged event
        /// NOT USED
        /// </summary>
        internal void NumberOfConnectionsChanged()
        {
            Console.WriteLine("New Connection number {0} on {1}:{2}",
                _easyModbusTCPServer.NumberOfConnections, _easyModbusTCPServer.LocalIPAddress, _easyModbusTCPServer.Port);
        }

        /// <summary>
        /// NOT USED
        /// </summary>
        internal void LogDataChanged()
        {
            // do something
        }

        /// <summary>
        /// Prints Serverdata to the Console
        /// </summary>
        public void PrintData()
        {
            foreach (var machine in _industryMapper.OurFactory._FactoryMachines)
            {
                int machineId = machine.MachineId;
                Console.WriteLine("ModBusServerData--------------");
                Console.WriteLine("ID                   |{0} ", machineId);
                Console.WriteLine("Status               |{0} ", _easyModbusTCPServer.holdingRegisters[machineId * 10 + 1]);
                Console.WriteLine("NumberOfProducedItems|{0} ", _easyModbusTCPServer.holdingRegisters[machineId * 10 + 2]);
                Console.WriteLine("SpeedOfProcessing    |{0} ", _easyModbusTCPServer.holdingRegisters[machineId * 10 + 3]);
                Console.WriteLine("ItemsPerRun          |{0} ", _easyModbusTCPServer.holdingRegisters[machineId * 10 + 4]);
                Console.WriteLine("TemperatureOfMachin  |{0} ", _easyModbusTCPServer.holdingRegisters[machineId * 10 + 5]);
            }
        }
    }
}

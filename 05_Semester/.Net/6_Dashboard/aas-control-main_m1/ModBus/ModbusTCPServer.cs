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

        /// <summary>
        /// Method to start the server with an Mapper
        /// </summary>
        /// <param name="ourMapper"></param>
        public bool StartServer()
        {
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

            // _easyModbusTCPServer.CoilsChanged += new ModbusServer.CoilsChangedHandler(CoilsChanged);
            _easyModbusTCPServer.HoldingRegistersChanged += new ModbusServer.HoldingRegistersChangedHandler(HoldingRegistersChanged);
            _easyModbusTCPServer.NumberOfConnectedClientsChanged += new ModbusServer.NumberOfConnectedClientsChangedHandler(NumberOfConnectionsChanged);
            _easyModbusTCPServer.LogDataChanged += new ModbusServer.LogDataChangedHandler(LogDataChanged);

            return true;
        }

        
        /// <summary>
        /// Method to stop the Server
        /// </summary>
        public void StopServer()
        {
            _easyModbusTCPServer.StopListening();
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


        public bool SetSingleCoil(int address, bool coilValue)
        {
            if ((address < 0) || (address >= ushort.MaxValue)) { throw new Exception("Invalid input parameter"); }

            try
            {
                _easyModbusTCPServer.coils[address] = coilValue;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
                Console.WriteLine(ex.StackTrace);
                throw;
            }
            return true;
        }
        public bool getSingleCoil(int address)
        {
            return _easyModbusTCPServer.coils[address];
        }

        /// <summary>
        /// Set Register
        /// </summary>
        /// <param name="address"></param>
        /// <param name="val"></param>
        /// <returns></returns>
        public bool setSingleRegister(int address, short val)
        {
            try 
            { 
                _easyModbusTCPServer.holdingRegisters[address] = val;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
                Console.WriteLine(ex.StackTrace);
                throw;
            }
            return true;
        }

        /// <summary>
        /// Get register
        /// </summary>
        /// <param name="address"></param>
        /// <returns></returns>
        public int getSingleRegister(int address)
        {
            return (int)_easyModbusTCPServer.holdingRegisters[address];
        }

    }
}

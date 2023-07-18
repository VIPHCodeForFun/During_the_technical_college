/*
 Class for creating an TCP ModBus Client
 Vidmar/Brescher
*/
using EasyModbus; //EasyModbusTCP 5.6.0 MIT
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Net;
using System.Net.Sockets;
using System.Reflection.Metadata.Ecma335;

namespace ModBus
{
    /// <summary>
    /// Class to create an Modbus TCP Client
    /// </summary>
    public class ModbusTCPClient
    {
        private ModbusClient _client;
        public string _serverIP { get; set; }
        public int _serverPort { get; set; }


        /// <summary>
        /// Constructor for <c>ModbusTCPClient</c> object.
        /// </summary>
        public ModbusTCPClient()
        {
            _serverIP = "127.0.0.1";
            _serverPort = 502;
            _client = new ModbusClient(_serverIP, _serverPort);
        }

        /// <summary>
        /// Constructor for <c>ModbusTCPClient</c> object.
        /// </summary>
        /// <param name="serverIP">IPv4 address of the Server to connect to</param>
        /// <param name="serverPort">Port of the Server to connect to</param>
        public ModbusTCPClient(string serverIP, int serverPort)
        {
            _serverIP = serverIP;
            _serverPort = serverPort;
            _client = new ModbusClient(_serverIP, _serverPort);
        }

        /// <summary>
        /// Starts Client Connection on <c>_serverIP</c> and <c>_serverPort</c>.
        /// </summary>
        /// <returns><c>True</c> is successfull</returns>
        public bool StartClientConnection()
        {
            if (ServerReachable())
            {
                Console.WriteLine("Connecting to server on {0}:{1}", _serverIP, _serverPort);
            }
            else
            {
                Console.WriteLine("Server on {0}:{1} is not responding!", _serverIP, _serverPort);
                return false;
            }

            try
            {
                _client.Connect();
                return true;
            }
            catch (EasyModbus.Exceptions.ConnectionException ex)
            {
                Console.WriteLine(ex.ToString());
                Console.WriteLine(ex.StackTrace);
                // throw ex;
                return false;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
                Console.WriteLine(ex.StackTrace);
                throw;
            }
        }

        /// <summary>
        /// Disconnects Client
        /// </summary>
        public void DisconnectClient()
        {
            _client.Disconnect();
            Console.Write("Client Disconnected");
        }

        // Coils read/write ---------------------------------------
        #region Coils

        /// <summary>
        /// Method to toggle coils on the server.
        /// </summary>
        /// <param name="address">Address from 0-65533</param>
        /// <returns><c>True</c> is successfull</returns>
        /// <exception cref="Exception">Invalid input parameter</exception>
        public bool TogglSingleCoil(int address)
        {
            if ((address < 0) || (address >= ushort.MaxValue)) { throw new Exception("Invalid input parameter"); }

            try
            {
                bool[] temp = _client.ReadCoils(address, 1);
                if (temp[0] == true)
                {
                    temp[0] = false;
                }
                else
                {
                    temp[0] = true;
                }
                _client.WriteSingleCoil(address, temp[0]);
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
        /// Setter for a single Coil on the Server.
        /// </summary>
        /// <param name="address">Address from 0-65533</param>
        /// <param name="coilValue">value as bool</param>
        /// <returns><c>True</c> is successfull</returns>
        /// <exception cref="Exception">Invalid input parameter</exception>
        public bool SetSingleCoil(int address, bool coilValue)
        {
            if ((address < 0) || (address >= ushort.MaxValue)) { throw new Exception("Invalid input parameter"); }

            try
            {
                _client.WriteSingleCoil(address, coilValue);
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
        /// Getter for Coils array on the server.
        /// </summary>
        /// <param name="startigAddress">Starting address from 0-65533</param>
        /// <param name="len">Length of array</param>
        /// <returns>bool[] of Coils</returns>
        /// <exception cref="Exception">Invalid input parameter</exception>
        public bool[] GetCoilsArray(int startigAddress, int len)
        {
            if( (startigAddress < 0) || (startigAddress >= ushort.MaxValue)) { throw new Exception("Invalid input parameter"); }
            if( (len < 1) || (len >= ushort.MaxValue)) { throw new Exception("Invalid input parameter"); }

            try
            {
                return _client.ReadCoils(startigAddress, len);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
                Console.WriteLine(ex.StackTrace);
                throw;
            }
        }
        #endregion

        // HoldingRegisters read/write ----------------------------
        #region HoldingRegisters

        /// <summary>
        /// Getter for Holding Register array on the server.
        /// </summary>
        /// <param name="startigAddress">Starting address from 0-65533</param>
        /// <param name="len">Length of array</param>
        /// <returns>int[] of Holding Registers</returns>
        /// <exception cref="Exception">Invalid input parameter</exception>
        public int[] GetHoldingRegisterArray(int startigAddress, int len)
        {
            if ((startigAddress < 0) || (startigAddress >= ushort.MaxValue)) { throw new Exception("Invalid input parameter"); }
            if ((len < 1) || (len >= ushort.MaxValue)) { throw new Exception("Invalid input parameter"); }

            try
            {
                return _client.ReadHoldingRegisters(startigAddress, len);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
                Console.WriteLine(ex.StackTrace);
                throw;
            }
        }

        /// <summary>
        /// Setter for a single Register on the Server.
        /// </summary>
        /// <param name="address">Address from 0-65533</param>
        /// <param name="registerValue">Value as <c>int</c> in the value range of <c>short</c></param>
        /// <returns><c>True</c> is successfull</returns>
        /// <exception cref="Exception">Invalid input parameter</exception>
        public bool SetSingleRegister(int address, int registerValue)
        {
            if ((address < 0) || (address >= ushort.MaxValue)) { throw new Exception("Invalid input parameter"); }
            if ((registerValue < short.MinValue) || (registerValue > short.MaxValue)) { throw new Exception("Invalid input parameter"); }

            try
            {
                _client.WriteSingleRegister(address, registerValue);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
                Console.WriteLine(ex.StackTrace);
                throw;
            }
            return true;
        }
        #endregion

        // DiscreteInputs -----------------------------------------
        #region DiscreteInputs

        /// <summary>
        /// Getter for a single "Discrete Input" on the Server.
        /// </summary>
        /// <param name="address">Address from 0-65533</param>
        /// <returns>Value of Discrete Input</returns>
        /// <exception cref="Exception">Invalid input parameter</exception>
        public bool GetSingleDiscreteInput(int address)
        {
            if ((address < 0) || (address >= ushort.MaxValue)) { throw new Exception("Invalid input parameter"); }

            try
            {
                var result = _client.ReadDiscreteInputs(address, 1);
                return result[0];
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
                Console.WriteLine(ex.StackTrace);
                throw;
            }
        }

        /// <summary>
        /// Getter for an array of "Discrete Input" on the Server.
        /// </summary>
        /// <param name="address">Address from 0-65533</param>
        /// <param name="quantity">Length of array</param>
        /// <returns>bool array of values</returns>
        /// <exception cref="Exception">Invalid input parameter</exception>
        public bool[] GetDiscreteInputArray(int address, int quantity)
        {
            if ((address < 0) || (address >= ushort.MaxValue)) { throw new Exception("Invalid input parameter"); }
            if ((quantity < 0) || (quantity) >= ushort.MaxValue) { throw new Exception("Invalid input parameter"); }

            try
            {
                var result = _client.ReadDiscreteInputs(address, quantity);
                return result;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
                Console.WriteLine(ex.StackTrace);
                throw;
            }
        }

        #endregion

        // InputRegisters -----------------------------------------
        #region InputRegister

        /// <summary>
        /// Getter for a single "Input Register" on the Server.
        /// </summary>
        /// <param name="address">Address from 0-65533</param>
        /// <returns>Value of Input Register</returns>
        /// <exception cref="Exception">Invalid input parameter</exception>
        public int GetSingleInputRegister(int address)
        {
            if ((address < 0) || (address >= ushort.MaxValue)) { throw new Exception("Invalid input parameter"); }

            try
            {
                var result = _client.ReadInputRegisters(address, 1);
                return result[0];
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
                Console.WriteLine(ex.StackTrace);
                throw;
            }
        }

        /// <summary>
        /// Getter for an array of "Input Registers" on the Server.
        /// </summary>
        /// <param name="address">Address from 0-65533</param>
        /// <param name="quantity">Length of array</param>
        /// <returns>Int array of values</returns>
        /// <exception cref="Exception">Invalid input parameter</exception>
        public int[] GetInputRegisterArray(int address, int quantity)
        {
            if ((address < 0) || (address >= ushort.MaxValue)) { throw new Exception("Invalid input parameter"); }
            if ((quantity < 0) || (quantity) >= ushort.MaxValue) { throw new Exception("Invalid input parameter"); }

            try
            {
                var result = _client.ReadInputRegisters(address, quantity);
                return result;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
                Console.WriteLine(ex.StackTrace);
                throw;
            }
        }

        #endregion

        /// <summary>
        /// The <c>ModbusTCPClient.Connected</c> member variable is not working correctly. This Helper function tries to do a 
        /// TCP connect on the given <c>_serverIP</c> and <c>_serverPort</c> to find out if there is a service running.
        /// </summary>
        /// <returns><c>True</c> is Server is reachable</returns>
        public bool ServerReachable()
        {
            /*
             * The easymodbus module does not provide a way to check if the server is available, see:
             * https://github.com/rossmann-engineering/EasyModbusTCP.NET/issues/16
             * 
             * and the implementation of Available() -> just does a TCP ping
             * that does not apply to the usual localhost use-case.
             * That is why we have to resort to this function which tries to connect to the port
             */
            using (TcpClient tcpClient = new TcpClient())
            {
                try
                {
                    tcpClient.Connect(_serverIP, _serverPort);
                    // Console.WriteLine("Port open");
                    return true;
                }
                catch (Exception)
                {
                    return false;
                }
            }
        }
    }
}

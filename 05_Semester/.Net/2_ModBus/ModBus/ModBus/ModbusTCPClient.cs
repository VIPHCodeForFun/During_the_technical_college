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

namespace ModBus
{
    /// <summary>
    /// Class to create an Modbus TCP Client on IP:127.0.0.1 Port:502
    /// </summary>
    public class ModbusTCPClient
    {
        private ModbusClient _client;

        /// <summary>
        /// Starts Client Connection on IP:127.0.0.1 Port:502
        /// </summary>
        public void StartClientConnection()
        {
            try
            {
                // Ip-Address and Port of Modbus-TCP-Server
                _client = new ModbusClient("127.0.0.1", 502);
                _client.Connect();
            }
            catch
            {
                Console.WriteLine("No Server accessible!");
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

        /// <summary>
        /// Method to Toggl coils on the server with the client
        /// </summary>
        /// <param name="address"></param>
        public void TogglCoil(int address)
        {
            bool[] temp = _client.ReadCoils(address, 1);
            if (temp[0] == true) { temp[0] = false; }
            else { temp[0] = true; }
            _client.WriteSingleCoil(address, temp[0]);
        }

        /// <summary>
        /// Method to ptint coils to the console
        /// </summary>
        /// <param name="startigAddress"></param>
        /// <param name="len"></param>
        public void GetCoils(int startigAddress, int len)
        {
            bool[] readCoils = _client.ReadCoils(startigAddress, len);
            for (int i = 0; i < readCoils.Length; i++)
            {
                Console.WriteLine("[" + i + "] " + readCoils[i]);
            }
        }
    }
}

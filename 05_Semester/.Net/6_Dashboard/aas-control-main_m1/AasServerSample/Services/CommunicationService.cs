using NLog;
using ILogger = NLog.ILogger;
using ModBus;
using BaSyx.Utils.Settings.Types;

namespace DiceDigitalTwin.Services;

/// <summary>
/// this class Connects the AssetAdministrationShell to a ModbusServer
/// </summary>
public class CommunicationService
{
    private static readonly ILogger Logger = LogManager.GetCurrentClassLogger();

    /// <summary>
    /// The client used to communicate with the AAS Server component
    /// </summary>
    private ModbusTCPClient _aasModbusClient;
    private string ServerSettings = "Docker";
    private int _addressspace = 10;
    /// <summary>
    /// This method connects to the Modbus server of docker 4001 or if docker is not reachable to our factory 502
    /// </summary>
    public CommunicationService()
    {
        string server;
        int port;
        
        // using Port 502 for debugging/developement
        server = "127.0.0.1";
        port = 502;

        // connect to ModBus Server
        try
        {
            _aasModbusClient = new ModbusTCPClient(server, port);
        }
        catch (Exception ex)
        {
            Logger.Error(ex);
        }
    }

    /// <summary>
    /// Starts the connection to the Modbus server
    /// </summary>
    public void Connect()
    {
        try
        {
            // Initialize connection to our field bus protocol
            _aasModbusClient.StartClientConnection();
            Logger.Info("Connected to server {}:{}", _aasModbusClient._serverIP, _aasModbusClient._serverPort);
        }
        catch (Exception ex)
        {
            Logger.Error(ex, "Cannot connect to MODBUS server", ex);
        }
    }

    /// <summary>
    /// Writes or fetches the technical data from the modsserver (status)
    /// </summary>
    public int Status
    {
        get
        {
            var elem = _aasModbusClient.GetHoldingRegisterArray(_addressspace, 9);
            return elem[0];
        }
        set
        {
            _aasModbusClient.SetSingleRegister(_addressspace, value);
            Logger.Info($"Setting Status to '{value}'");
        }
    }

    /// <summary>
    /// Fetches the technical data from the modsserver (NumberOfProducedItems)
    /// </summary>
    public int NumberOfProducedItems
    {
        get
        {
            var elem = _aasModbusClient.GetHoldingRegisterArray(_addressspace, 9);
            return elem[1];
        }
    }

    /// <summary>
    /// Writes or fetches the technical data from the modsserver (SpeedOfProcessing)
    /// </summary>
    public int SpeedOfProcessing
    {
        get
        {
            var elem = _aasModbusClient.GetHoldingRegisterArray(_addressspace, 9);
            return elem[2];
        }
        set
        {
            _aasModbusClient.SetSingleRegister(2, value);
            Logger.Info($"Setting SpeedOfProcessing to '{value}'");
        }
    }

    /// <summary>
    /// Writes or fetches the technical data from the modsserver (ItemsPerRun)
    /// </summary>
    public int ItemsPerRun
    {
        get
        {
            var elem = _aasModbusClient.GetHoldingRegisterArray(_addressspace, 9);
            return elem[3];
        }
        set
        {
            _aasModbusClient.SetSingleRegister(4, value);
            Logger.Info($"Setting ItemsPerRun to '{value}'");
        }
    }

    /// <summary>
    /// Fetches the technical data from the modsserver (TemperatureOfMachine)
    /// </summary>
    public int TemperatureOfMachine
    {
        get
        {
            var elem = _aasModbusClient.GetHoldingRegisterArray(_addressspace, 9);
            return elem[4];
        }
    }

    /// <summary>
    /// "Start" Operation of machine Sets the correct coils at the modbus server
    /// </summary>
    public void CallExternalMethodStart()
    {
        try
        {
            // Coil 11 is defined as running
            _aasModbusClient.SetSingleCoil(_addressspace, true);
            _aasModbusClient.SetSingleCoil(_addressspace + 1, false);
            _aasModbusClient.SetSingleCoil(_addressspace + 2, false);
            Logger.Info("Operation 'Start' succeeded");
        }
        catch (Exception ex)
        {
            Logger.Error(ex.Message);
        }
    }

    /// <summary>
    /// "Stop" Operation of machine Sets the correct coils at the modbus server
    /// </summary>
    public void CallExternalMethodStop()
    {
        try
        {
            // Coil 12 is defined as stopped
            _aasModbusClient.SetSingleCoil(_addressspace, false);
            _aasModbusClient.SetSingleCoil(_addressspace + 1, true);
            _aasModbusClient.SetSingleCoil(_addressspace + 2, false);
            Logger.Info("Operation 'Stop' succeeded");
        }
        catch (Exception ex)
        {
            Logger.Error(ex.Message);
        }
    }

    /// <summary>
    /// "Repair" Operation of machine Sets the correct coils at the modbus server
    /// </summary>
    public void CallExternalMethodRepair()
    {
        // Coil 13 is defined as in maintenance
        try
        {
            _aasModbusClient.SetSingleCoil(_addressspace, false);
            _aasModbusClient.SetSingleCoil(_addressspace + 1, false);
            _aasModbusClient.SetSingleCoil(_addressspace + 2, true);
            Logger.Info("Operation 'Repair' succeeded");

        }
        catch (Exception ex)
        {
            Logger.Error(ex.Message);
        }
    }
}
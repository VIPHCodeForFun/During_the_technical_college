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
    /// the client used to communicate with the AAS Server component
    /// </summary>
    private ModbusTCPClient _aasModbusClient;
    private string ServerSettings = "Docker";

    /// <summary>
    /// This method connects to the Modbus server of docker 4001 or if docker is not reachable to our factory 502
    /// </summary>
    public CommunicationService()
    {
        string server;
        int port;

        if (ServerSettings.Equals("Docker"))
        {
            // using port 4001 from given docker-compose.yml
            server = "localhost";
            port = 4001;
        }
        else
        {
            // using Port 502 for debugging/developement
            server = "localhost";
            port = 502;
        }

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
        catch (Exception e)
        {
            Logger.Error(e, "Cannot connect to MODBUS server", e);
        }
    }

    /// <summary>
    /// Writes or fetches the technical data from the modsserver (status)
    /// </summary>
    public int Status
    {
        get
        {
            return _aasModbusClient.GetHoldingRegisterArray(0, 9)[0];
        }
        set
        {
            _aasModbusClient.SetSingleRegister(0, value);
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
            return _aasModbusClient.GetHoldingRegisterArray(0, 9)[1];
        }
    }

    /// <summary>
    /// Writes or fetches the technical data from the modsserver (SpeedOfProcessing)
    /// </summary>
    public int SpeedOfProcessing
    {
        get
        {
            return _aasModbusClient.GetHoldingRegisterArray(0, 9)[2];
        }
        set
        {
            _aasModbusClient.SetSingleRegister(2, value);
            Logger.Info($"Setting SpeedOfProcessing to '{value}'");
        }
    }

    /// <summary>
    /// Fetches the technical data from the modsserver (TemperatureOfMachine)
    /// </summary>
    public int TemperatureOfMachine
    {
        get
        {
            return _aasModbusClient.GetHoldingRegisterArray(0, 9)[3];
        }
    }

    /// <summary>
    /// Writes or fetches the technical data from the modsserver (ItemsPerRun)
    /// </summary>
    public int ItemsPerRun
    {
        get
        {
            return _aasModbusClient.GetHoldingRegisterArray(0, 9)[4];
        }
        set
        {
            _aasModbusClient.SetSingleRegister(4, value);
            Logger.Info($"Setting ItemsPerRun to '{value}'");
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
            _aasModbusClient.SetSingleCoil(10, true);
            _aasModbusClient.SetSingleCoil(11, false);
            _aasModbusClient.SetSingleCoil(12, false);
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
            _aasModbusClient.SetSingleCoil(10, false);
            _aasModbusClient.SetSingleCoil(11, true);
            _aasModbusClient.SetSingleCoil(12, false);
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
            _aasModbusClient.SetSingleCoil(10, false);
            _aasModbusClient.SetSingleCoil(11, false);
            _aasModbusClient.SetSingleCoil(12, true);
            Logger.Info("Operation 'Repair' succeeded");

        }
        catch (Exception ex)
        {
            Logger.Error(ex.Message);
        }
    }
}
/*
 Class for connecting a Fabrick and a TCP MOdbus server 
 Vidmar/Brescher
*/
using DiceEngine;
using System;
using System.Collections.Generic;
using System.Data.Common;
using System.Linq;
using System.Reflection;
using System.Text;

namespace IndustryEngine;

/// <summary>
/// Class to Mapp a Factory to an ModBus TCP Server
/// </summary>
public class Mapper
{
    /// <summary>
    /// Reference to <c>Factory</c>, used to map with the data of a <c>ModbusTCPServer</c>
    /// </summary>
    public Factory OurFactory;

    /// <summary>
    /// Constructor for a new Mapper
    /// </summary>
    /// <param name="ourFactory"></param>
    public Mapper(Factory ourFactory)
    {
        OurFactory = ourFactory;
    }

    /// <summary>
    /// Method to write a Coil imput to an Machine. Every machine has an addressspace from 1-9 in blocks of 10
    /// 
    /// machine 0:  1- 9
    /// machine 1: 11-19
    /// machine 2: 21-29
    /// etc.
    /// </summary>
    /// <param name="coilNumber"></param>
    /// <param name="numberOfCoils"></param>
    /// <returns></returns>
    public bool handleCoils(int coilNumber, int numberOfCoils)
    {
        
        int machineId = (int)coilNumber / 10;
        Console.WriteLine("Coil {0} bestätigt machineID {1}", coilNumber, machineId);

        int coil = coilNumber - (machineId * 10);

        switch (coil)
        {
            case 1:
                Console.WriteLine("Starte Maschine {0}", machineId);
                startMachine(machineId);
                break;
            case 2:
                stopMachine(machineId);
                break;
            case 3:
                if (OurFactory._FactoryMachines[machineId].Status == MachineStatus.Error) { 
                    repairMachine(machineId); 
                }
                break;
            default:
                break;
        }
        return true;
    }

    /// <summary>
    /// Method to start an instance of <c>Machine</c>
    /// </summary>
    /// <param name="machineId"></param>
    public void startMachine(int machineId)
    {
        OurFactory._FactoryMachines[machineId].StartProcessing();
    }

    /// <summary>
    /// Method to stop an instance of <c>Machine</c>
    /// </summary>
    /// <param name="machineId"></param>
    public void stopMachine(int machineId)
    {
        OurFactory._FactoryMachines[machineId].StopProcessing();
    }

    /// <summary>
    /// Method to set an instance of <c>Machine</c> back to <c>Running</c>
    /// </summary>
    /// <param name="machineId"></param>
    public void repairMachine(int machineId)
    {
        OurFactory._FactoryMachines[machineId].Status = MachineStatus.Running;
    }

    /// <summary>
    /// Method to get the current <c>Status</c>
    /// </summary>
    /// <param name="machineId"></param>
    /// <returns></returns>
    public MachineStatus getStatus(int machineId)
    {
        return OurFactory._FactoryMachines[machineId].Status;
    }
}
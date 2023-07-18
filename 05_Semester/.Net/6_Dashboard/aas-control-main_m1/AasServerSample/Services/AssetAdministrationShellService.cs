using BaSyx.API.Components;
using BaSyx.Models.Core.AssetAdministrationShell.Generics;
using BaSyx.Models.Core.AssetAdministrationShell.Implementations;
using BaSyx.Models.Core.Common;
using BaSyx.Models.Export;
using BaSyx.Utils.ResultHandling;
using NLog;
using ILogger = NLog.ILogger;


namespace DiceDigitalTwin.Services
{
    /// <summary>
    /// Load AAS from file and connect methods
    /// </summary>
    public sealed class AssetAdministrationShellService : AssetAdministrationShellServiceProvider
    {
        private readonly CommunicationService _communicationService;
        private static readonly ILogger Logger = LogManager.GetCurrentClassLogger();

        /// <summary>
        /// provides the communication
        /// </summary>
        /// <param name="communicationService"></param>
        public AssetAdministrationShellService(CommunicationService communicationService)
        {
            _communicationService = communicationService;

            #region Operations
            var operationsServiceProvider = new SubmodelServiceProvider();
            operationsServiceProvider.BindTo(AssetAdministrationShell.Submodels["Operations"]);

            // register Methods of sub model "Operations"
            operationsServiceProvider.RegisterMethodCalledHandler("Start", StartOperationHandler);
            operationsServiceProvider.RegisterMethodCalledHandler("Stop", StopOperationHandler);
            operationsServiceProvider.RegisterMethodCalledHandler("Repair", RepairOperationHandler);
            
            // now register the sub model "Operations" to the AAS
            RegisterSubmodelServiceProvider("Operations", operationsServiceProvider);

            #endregion
            #region GeneralInformation

            // bind to operations of sub model "GeneralInformation"
            var generalInformationServiceProvider = new SubmodelServiceProvider();
            generalInformationServiceProvider.BindTo(AssetAdministrationShell.Submodels["GeneralInformation"]);
            generalInformationServiceProvider.UseInMemorySubmodelElementHandler();
            
            // now register the sub model "GeneralInformation" to the AAS
            RegisterSubmodelServiceProvider("GeneralInformation", generalInformationServiceProvider);

            #endregion
            #region TechnicalData

            // now register the sub model "TechnicalData" to the AAS
            var technicalDataServiceProvider = new SubmodelServiceProvider();
            technicalDataServiceProvider.BindTo(AssetAdministrationShell.Submodels["TechnicalData"]);

            // register properties of sub model "TechnicalData"
            technicalDataServiceProvider.RegisterSubmodelElementHandler("Status", new SubmodelElementHandler(StatusPropertyGetHandler, StatusPropertySetHandler));
            technicalDataServiceProvider.RegisterSubmodelElementHandler("NumberOfProducedItems", new SubmodelElementHandler(NumberOfProducedItemsPropertyGetHandler, null));
            technicalDataServiceProvider.RegisterSubmodelElementHandler("SpeedOfProcessing", new SubmodelElementHandler(SpeedOfProcessingPropertyGetHandler, SpeedOfProcessingPropertySetHandler));
            technicalDataServiceProvider.RegisterSubmodelElementHandler("TemperatureOfMachine", new SubmodelElementHandler(TemperatureOfMachinePropertyGetHandler, null));
            technicalDataServiceProvider.RegisterSubmodelElementHandler("ItemsPerRun", new SubmodelElementHandler(ItemsPerRunPropertyGetHandler, ItemsPerRunPropertySetHandler));

            // now register the sub model "TechnicalData" to the AAS
            RegisterSubmodelServiceProvider("TechnicalData", technicalDataServiceProvider);
            #endregion

            #region Documentation
            var documentationDataServiceProvider = new SubmodelServiceProvider();
            documentationDataServiceProvider.BindTo(AssetAdministrationShell.Submodels["Documentation"]);
            RegisterSubmodelServiceProvider("Documentation", documentationDataServiceProvider);

            #endregion

        }

        #region GettersAndSetters
        private IValue StatusPropertyGetHandler(ISubmodelElement submodelElement)
        {
            return new ElementValue<int?>(_communicationService.Status);
        }

        private void StatusPropertySetHandler(ISubmodelElement submodelElement, IValue value)
        {
            if (Int32.TryParse(value.ToString(), out int val))
            {
                _communicationService.Status = val;
            } else
            {
                Logger.Error("Could not parse {value} to Integer");
            }
        }

        private IValue NumberOfProducedItemsPropertyGetHandler(ISubmodelElement submodelElement)
        {
            return new ElementValue<int?>(_communicationService.NumberOfProducedItems);
        }

        private IValue SpeedOfProcessingPropertyGetHandler(ISubmodelElement submodelElement)
        {
            return new ElementValue<int?>(_communicationService.SpeedOfProcessing);
        }

        private void SpeedOfProcessingPropertySetHandler(ISubmodelElement submodelElement, IValue value)
        {
            if (Int32.TryParse(value.ToString(), out int val))
            {
                _communicationService.SpeedOfProcessing = val;
            }
            else
            {
                Logger.Error("Could not parse {value} to Integer");
            }
        }

        private IValue TemperatureOfMachinePropertyGetHandler(ISubmodelElement submodelElement)
        {
            return new ElementValue<decimal?>(_communicationService.TemperatureOfMachine);
        }

        private IValue ItemsPerRunPropertyGetHandler(ISubmodelElement submodelElement)
        {
            return new ElementValue<int?>(_communicationService.ItemsPerRun);
        }

        private void ItemsPerRunPropertySetHandler(ISubmodelElement submodelElement, IValue value)
        {
            if (Int32.TryParse(value.ToString(), out int val))
            {
                _communicationService.ItemsPerRun = val;
            }
            else
            {
                Logger.Error("Could not parse {value} to Integer");
            }
        }

        #endregion
        #region Methods
        private Task<OperationResult> StartOperationHandler(IOperation operation, IOperationVariableSet inputarguments, IOperationVariableSet inoutputarguments, IOperationVariableSet outputarguments, CancellationToken cancellationtoken)
        {
            _communicationService.CallExternalMethodStart();
            return Task.FromResult(new OperationResult(true));
        }

        private Task<OperationResult> StopOperationHandler(IOperation operation, IOperationVariableSet inputarguments, IOperationVariableSet inoutputarguments, IOperationVariableSet outputarguments, CancellationToken cancellationtoken)
        {
            _communicationService.CallExternalMethodStop();
            return Task.FromResult(new OperationResult(true));
        }

        private Task<OperationResult> RepairOperationHandler(IOperation operation, IOperationVariableSet inputarguments, IOperationVariableSet inoutputarguments, IOperationVariableSet outputarguments, CancellationToken cancellationtoken)
        {
            _communicationService.CallExternalMethodRepair();
            return Task.FromResult(new OperationResult(true));
        }

        #endregion

        /// <summary>
        /// Load AAS_Model
        /// </summary>
        /// <returns></returns>
        public override IAssetAdministrationShell? BuildAssetAdministrationShell()
        {
            string aasxFilePath = "Content/AAS_Model - machine 1.aasx";
            
            using (AASX aasx = new AASX(aasxFilePath, FileMode.Open, FileAccess.Read, FileShare.ReadWrite))
            {
                AssetAdministrationShellEnvironment_V2_0 environment = aasx.GetEnvironment_V2_0();
                if (environment == null)
                {
                    Logger.Error("Asset Administration Shell Environment cannot be obtained from AASX-Package " + aasxFilePath);
                    return null;
                }

                Logger.Info("AASX-Package successfully loaded");

                if (environment.AssetAdministrationShells.Count != 0)
                {
                    var aas = environment.AssetAdministrationShells.FirstOrDefault();
                    return aas;
                }

                Logger.Error("No Asset Administration Shells found AASX-Package " + aasxFilePath);
                return null;
            }
        }
    }
}
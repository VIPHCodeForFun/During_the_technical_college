# NET-Labor 06: Daten der Control Components visualisieren per Grafana

## Authors

- [Philipp Vidmar](pvidmar.itsb-b2020@fh-salzburg.ac.at)
- [Jürgen Brescher](jbrescher.itsb-b2020@fh-salzburg.ac.at)

## Setup

- Install Docker CE + Docker Compose Plugin or Docker Desktop
- Start Docker Stack with ./Docker/start.ps1 
- Install Grafana + Grafana SimpleJson Addon
- Launch aas-control-main_m1 / AasServer (Digital Twin)
- Launch ControlComponent / GrafanaConnector (Glue Code)
- Grafana is available at http://localhost:3000/
- Import Dashboard with ./Digital Twin-1672845182934.json
- Navigate to Dashboards - General - DigitalTwin

## Screenshot

![Alt text](./Grafana_Dashboard_DigitalTwin.png?raw=true "Screenshot Grafana Dashboard")

## Modbus Server

| Wert                          | Variable               | Register     |
| ----------------------------- | ---------------------- | ------------ |
| Status                        | Status                 | 11           |
| Stück produziert              | NumberOfProducedItems  | 12           |
| Produktionsgeschwindigkeit    | SpeedOfProcessing      | 13           |
| produzierte Gegenstände       | ItemsPerRun            | 14           |
| Betriebstemperatur            | TemperatureOfMachine   | 15           |


## Changes

### Philipp Vidmar 03.01.2023
aas-control-main_m1 ->

Programm:
	Machine1 hinzugefügt
	Machine1 Thread start

MaschinenThread geändert:
>	* Machine 1 -> Server 10-19
>		Coils --------------------------
>			11 == true == Running
>			12 == true == Stop 
>			13 == true == Error 
>		Register -----------------------
>			11 = Status
>			12 = NumberOfProducedItems
>			13 = SpeedOfProcessing
>			14 = ItemsPerRun
>			15 = TemperatureOfMachine
	
	- Temperatur geht in Running auf 40 hoch bei Stopped auf 10 zurück
	- Error Resettet die Maschine auf Standart
	- Speed wird neu berechnet 10sek/SpeedOfProcessing

Modbus Server
	Get und Set für Singelregister implementiert

ComunicationService
	_addressspace = 10 eingefügt
		*Machine 1 -> Server 10-19

## Jürgen Brescher 2023-01-04

- Implementierung Filter Condition für Glue-Code
- Randomizer für variable Werte
- Grafana Dashboard
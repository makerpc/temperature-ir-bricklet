program ExampleWaterBoiling;

{$ifdef MSWINDOWS}{$apptype CONSOLE}{$endif}
{$ifdef FPC}{$mode OBJFPC}{$H+}{$endif}

uses
  Math, SysUtils, IPConnection, BrickletTemperatureIR;

type
  TExample = class
  private
    ipcon: TIPConnection;
    tir: TBrickletTemperatureIR;
  public
    procedure ReachedCB(const temperature: smallint);
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = '365';

var
  e: TExample;

{ Callback for object temperature greater than 100 °C
  (parameter has unit °C/10) }
procedure TExample.ReachedCB(const temperature: smallint);
begin
  WriteLn(Format('The surface has a temperature of %f °C', [temperature/10.0]));
  WriteLn('The water is boiling!');
end;

procedure TExample.Execute;
begin
  { Create IP connection to brickd }
  ipcon := TIPConnection.Create(HOST, PORT);

  { Create device object }
  tir := TBrickletTemperatureIR.Create(UID);

  { Add device to IP connection }
  ipcon.AddDevice(tir);
  { Don't use device before it is added to a connection }

  { Set emissivity to 0.98 (emissivity of water) }
  tir.SetEmissivity(Floor($FFFF*0.98));

  { Get threshold callbacks with a debounce time of 10 seconds (10000ms) }
  tir.SetDebouncePeriod(10000);

  { Register threshold reached callback to procedure ReachedCB }
  tir.OnObjectTemperatureReached := {$ifdef FPC}@{$endif}ReachedCB;

  { Configure threshold for "greater than 100 °C" (unit is °C/10) }
  tir.SetObjectTemperatureCallbackThreshold('>', 100*10, 0);

  WriteLn('Press key to exit');
  ReadLn;
  ipcon.Destroy;
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
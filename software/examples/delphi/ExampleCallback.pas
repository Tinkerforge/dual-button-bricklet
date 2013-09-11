program ExampleCallback;

{$ifdef MSWINDOWS}{$apptype CONSOLE}{$endif}
{$ifdef FPC}{$mode OBJFPC}{$H+}{$endif}

uses
  SysUtils, IPConnection, BrickletDualButton;

type
  TExample = class
  private
    ipcon: TIPConnection;
    db: TBrickletDualButton;
  public
    procedure StateChangedCB(sender: TBrickletDualButton;                                   
                             const buttonL: byte; const buttonR: byte; 
                             const ledL: byte; const ledR: byte);
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = 'XYZ'; { Change to your UID }

var
  e: TExample;

{ Callback function for state changed callback }
procedure TExample.StateChangedCB(sender: TBrickletDualButton; 
                                  const buttonL: byte; const buttonR: byte; 
                                  const ledL: byte; const ledR: byte);
begin
  if (buttonL = BRICKLET_DUAL_BUTTON_BUTTON_STATE_PRESSED) then begin
    WriteLn('Left button pressed');
  end
  else begin
    WriteLn('Left button released');
  end;

  if (buttonR = BRICKLET_DUAL_BUTTON_BUTTON_STATE_PRESSED) then begin
    WriteLn('Right button pressed');
  end
  else begin
    WriteLn('Right button released');
  end;

  WriteLn('');
end;

procedure TExample.Execute;
begin
  { Create IP connection }
  ipcon := TIPConnection.Create;

  { Create device object }
  db := TBrickletDualButton.Create(UID, ipcon);

  { Connect to brickd }
  ipcon.Connect(HOST, PORT);
  { Don't use device before ipcon is connected }

  { Register state changed callback to procedure StateChangedCB }
  db.OnStateChanged := {$ifdef FPC}@{$endif}StateChangedCB;

  WriteLn('Press key to exit');
  ReadLn;
  ipcon.Destroy; { Calls ipcon.Disconnect internally }
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.

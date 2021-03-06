program lab3;

{$APPTYPE CONSOLE}

{$R *.res}

uses
  System.SysUtils;

//????????? ??? ????? ????????? ???????? ??? ????????? ???????
const InitialFunctionStep = 0.0;

const IterationsLimit = 1024;

function GetFunctionResult(root : double) : double;
begin
  GetFunctionResult := root * root * root - 4.0 * root;
end;

function FindFunctionInterval(stepSize : double) : double;
begin
     var a := InitialFunctionStep;
     var instFunctionV := GetFunctionResult(a);

     var step := a;

     var i : integer;
     for i := 0 to (IterationsLimit + 1) do
     begin
           if (GetFunctionResult(step) * instFunctionV < 0) then
           begin
             FindFunctionInterval := step;
             break;
           end;

           step := step + stepSize;
     end;
end;

begin
  Writeln('Equation is x^3 - 4x', #13#10);

  while True do
  begin
    Writeln('Enter result value tolerance:');

    var tolerance := 1e-1;
    Readln(tolerance);


    Writeln('Enter interval:');

    var a := 0.0;
    var b := 0.0;
    Readln(a, b);

    //????????? ?? ? ???????? ????????? ??????? ??????
    if(GetFunctionResult(a) * GetFunctionResult(b) > 0.0) then
    begin
        //???? ???????? ? ????????? ???????? ???? ?????????? ??????? ??????????? ???????
        a := InitialFunctionStep;
        b := FindFunctionInterval(1.0);

        if(GetFunctionResult(a) * GetFunctionResult(b) > 0.0) then
        begin
           Writeln('Coudlnt find any root in this equation');
           continue;
        end;
    end;

    if(Abs(GetFunctionResult(a)) <= tolerance) then
    begin
      Writeln('Root is ', a, #13#10);
      continue;
    end
    else if(Abs(GetFunctionResult(b)) <= tolerance) then
    begin
      Writeln('nRoot is ', b, #13#10);
      continue;
    end;

    var c := 0.0;
    var iterationsCount := 0;

    while True do
    begin
      c := (a + b) / 2.0;

      if(Abs(GetFunctionResult(c)) <= tolerance)
         or (iterationsCount >= IterationsLimit) then
      begin
        Writeln('Root is ', c, ', computed in ', iterationsCount, ' iterations');
        break;
      end;

      if(GetFunctionResult(a) * GetFunctionResult(c) < 0.0) then
        begin
          b := c
        end
      else
        begin
          a := c;
        end;

      iterationsCount := iterationsCount + 1;
    end;

    Writeln(#13#10);
  end;
end.

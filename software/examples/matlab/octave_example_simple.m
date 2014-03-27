function octave_example_simple
    more off;
    
    HOST = "localhost";
    PORT = 4223;
    UID = "kqw"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    tir = java_new("com.tinkerforge.BrickletTemperatureIR", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current object and ambient temperatures (unit is °C/10)
    obj = str2num(tir.getObjectTemperature().toString())/10;
    amb = str2num(tir.getAmbientTemperature().toString())/10;

    fprintf("Object Temperature: %g°C\n", obj);
    fprintf("Ambient Temperature: %g°C\n", amb);

    input("\nPress any key to exit...\n", "s");
    ipcon.disconnect();
end

Send basic commands via Arduino serial port.
Awaiting text commands via serial port #1 - digital pins 0 (RX1), 1 (TX1)
Max command length - 64 chars. Longer commands a sprit to 64 chars commands.
Command ends with "new-line" char.
Supports two commands: "start", "stop", which print back command names (started with capital letter). On any other commands the program responds with a message "Unknown command:command-name".
Diagnostics messages are sent back to serial port #1.


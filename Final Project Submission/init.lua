-- Lua script to set up ESP8266 Wi-fi module to upload to Thingspeak
-- Connect to an Access Point
wifi.setmode(wifi.STATION);
-- In this case I set up my phone as a wifi hotspot
wifi.sta.config("Nexus 5" ,"tatertime"); 

-- Variables
X_acc = 0;
Y_acc = 0;
Z_acc = 0;
alt = 0;
TmpC = 0;
X_Gy = 0;
Y_Gy = 0;
Z_Gy = 0;
Heading = 0;
Z_Comp = 0;

-- Code to initalize the UART on the ESP8266 also disables the interpreter
-- This is necessary to ensure proper reading of the received values
-- Code compares the received values whenever a linefeed character (\n) is received
-- These values are then stored in their respective variables
uart.on("data", "\n", 
    function(data)
        if (string.match(data, "quit")) then
            print("Quitting...")
            uart.on("data") 
        end
        X_acc, Y_acc, Z_acc, alt, TmpC, X_Gy, Y_Gy, Z_Gy, Heading, Z_Comp = data:match("(-*%d+.%d+) (-*%d+.%d+) (-*%d+.%d+) (-*%d+.%d+) (-*%d+.%d+) (-*%d+.%d+) (-*%d+.%d+) (-*%d+.%d+) (-*%d+.%d+) (-*%d+)")
    end, 
0)
 
 -- Function to post the received data to thingspeak
 -- Note the code is copied twice in this block, each set is to send
 -- data to each webpage.  Since thingspeak can only support up to eight
 -- sets of data on each page, it becomes necessary for us to open and close
 -- a connection to each webpage we are going to be posting the data to
function postThingSpeak(level)
    connout = nil
    connout = net.createConnection(net.TCP, 0)
	
	-- If the data posts correctly, output that the data posted correctly
	-- to the UART
	-- Needed mostly for debugging since that is the only time you will
	-- have the ESP8266 connected to a PC
    connout:on("receive", function(connout, payloadout)
        if (string.find(payloadout, "Status: 200 OK") ~= nil) then
            print("Posted Set 1 OK");
        end
    end)
	
	-- Open the connection and post the data
    connout:on("connection", function(connout, payloadout)
 
        print ("Posting Set 1...");
 
        connout:send("GET /update?api_key=571L2JBQYIO43484&field1=" .. X_acc
        .. "GET /update?api_key=571L2JBQYIO43484&field2=" .. Y_acc
        .. "GET /update?api_key=571L2JBQYIO43484&field3=" .. Z_acc
        .. "GET /update?api_key=571L2JBQYIO43484&field4=" .. alt
        .. "GET /update?api_key=571L2JBQYIO43484&field5=" .. TmpC
        .. "GET /update?api_key=571L2JBQYIO43484&field6=" .. X_Gy
        .. "GET /update?api_key=571L2JBQYIO43484&field7=" .. Y_Gy
        .. "GET /update?api_key=571L2JBQYIO43484&field8=" .. Z_Gy
        .. " HTTP/1.1\r\n"
        .. "Host: api.thingspeak.com\r\n"
        .. "Connection: close\r\n"
        .. "Accept: */*\r\n"
        .. "User-Agent: Mozilla/4.0 (compatible; esp8266 Lua; Windows NT 5.1)\r\n"
        .. "\r\n")
    end)
	
	-- Close the connection
    connout:on("disconnection", function(connout, payloadout)
        connout:close();
        collectgarbage();
    end)
	-- Address of where the device is connecting
    connout:connect(80,'api.thingspeak.com')
	
	-- Reinitialize all the values for the second batch of data values
    connout = nil
    connout = net.createConnection(net.TCP, 0)
 
    connout:on("receive", function(connout, payloadout)
        if (string.find(payloadout, "Status: 200 OK") ~= nil) then
            print("Posted Set 2 OK");
        end
    end)
 
	-- Open the connection to the second webpage and post the other two values
    connout:on("connection", function(connout, payloadout)
 
        print ("Posting Set 2...");
 
        connout:send("GET /update?api_key=TSE4R56WPOW0A4TM&field1=" .. Heading
        .. "GET /update?api_key=TSE4R56WPOW0A4TM&field2=" .. Z_Comp
        .. " HTTP/1.1\r\n"
        .. "Host: api.thingspeak.com\r\n"
        .. "Connection: close\r\n"
        .. "Accept: */*\r\n"
        .. "User-Agent: Mozilla/4.0 (compatible; esp8266 Lua; Windows NT 5.1)\r\n"
        .. "\r\n")
    end)
	-- Disconnect from the webpage
    connout:on("disconnection", function(connout, payloadout)
        connout:close();
        collectgarbage();
    end)
 
    connout:connect(80,'api.thingspeak.com')
end

-- Run the above function on a loop that happens every 10 seconds
-- Thingspeak only accepts values at around this frequency so this time
-- period is acceptable
tmr.alarm(1, 10000, 1, function() postThingSpeak(0) end)
